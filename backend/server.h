#ifndef SERVER_H
#define SERVER_H

#include<io.h>
#include<stdio.h>
#include<winsock2.h>

#include "./collections/collections.h"

#define QUOTE(seq) "\""#seq"\""
#define HTML(seq) ""#seq""


typedef enum {
    GET, POST, PUT 
} HTTP_METHOD;

typedef struct {
    string path;
    HTTP_METHOD method;
} URL;

URL* URL_new(HTTP_METHOD method, char* path){
    URL* url = new(URL);
    url->method = method;
    url->path = string_new(path);
    return url;
}


typedef struct {
    string protocol; 
    unsigned int status_code; 
    string status; 
    string content_type; 
    string content; 

} ResponseWriter;



ResponseWriter response_writer_new() {
        ResponseWriter response_writer;
        response_writer.protocol = string_new("HTTP/1.1"); 
        response_writer.status_code = 200; 
        response_writer.status = string_new("OK"); 
        response_writer.content_type = string_new("text/html");  
        response_writer.content= string_new("");
        return response_writer;
    }

    void response_writer_set_protocol(ResponseWriter* response_writer, char* protocol) {
        string_update(&response_writer->protocol, protocol);
    }
    void response_writer_set_status_code(ResponseWriter* response_writer, unsigned int status_code) {
        response_writer->status_code = status_code;

    }
    void response_writer_set_status(ResponseWriter* response_writer, char* status) {
        string_update(&response_writer->status, status);
    }
    void response_writer_set_content_type(ResponseWriter* response_writer, char* content_type) {
        string_update(&response_writer->content_type, content_type);

    }
    void response_writer_set_content(ResponseWriter* response_writer, char* content) {
        string_update(&response_writer->content, content);
    }

    void response_writer_set_json_content(ResponseWriter* response_writer, char* json_string) {
        string_update(&response_writer->content_type, "application/json");
        char temp[1024];
        sprintf(temp, "<pre>%s</pre>", json_string);
        string_update(&response_writer->content, temp);

    }

    string response_writer_get_response(ResponseWriter* rw) {
        char temp[2048];
        sprintf(temp,
         "%s %d %s\r\nContent-Type: %s\r\n\r\n\r\n%s",
          rw->protocol.chars, rw->status_code, rw->status.chars, rw->content_type.chars,rw->content.chars
        );
        return string_new(temp);
    }


typedef struct {
    hashmap_char_string *headers;
    string method;
    string path;
    string protocol;
} Request;

Request* request_new(string* request){

    Request* req = new(Request);
    list_string* list = string_split(request, '\n');
    list_string* req_line = string_split(list->items[0], ' ');

    if (req_line->length != 3) puts(list->items[0]->chars);

    req->method = string_copy(req_line->items[0]);
    req->path = string_copy(req_line->items[1]);
    req->protocol = string_substring(req_line->items[2], 0, -2);

    req->headers = new_hashmap_char_string();

    string* temp;
    size_t j;
    size_t i;
    string key;
    string value;

    for (i= 1; i < list->length; i++)
    {
        temp = list->items[i];
        for (j=0; j < temp->length; j++)
        {
            if (temp->chars[j] == ':'){
                key = string_substring(temp, 0, j);
                value = string_substring(temp, j+1, -2);

                set_char_string(req->headers, key.chars, string_copy(&value)) ;
                break;
            }
        }
    }
    
    return req;

    
}

typedef struct 
{
  char* path;
  void(*handle)(ResponseWriter* rw, Request* r);
} Handler;

size_t URL_hash_function(URL* s){
    return char_int_hash(s->path.chars) + s->method;
}

MAKE_HASHMAP(URL, Handler, URL_hash_function)



typedef struct 
{
  size_t n_routes;
  hashmap_URL_Handler handlers; 
} Router;


void router_new_handler(Router* router, HTTP_METHOD method, char* path, void(*func)(ResponseWriter* rw, Request* r)){
    Handler* handler = new(Handler);
    handler->handle = func;
    handler->path = path;
    URL* key = URL_new(method, path);
    set_URL_Handler(&router->handlers, key, *handler);
    router->n_routes += 1;
}


typedef struct 
{
  Router* router;
} App;



 
void app_new_endpoint(App* app, HTTP_METHOD m, char* path, void(*func)(ResponseWriter* rw, Request* r)){
     router_new_handler(app->router, m, path, func);
}


void app_get(App* app, char* path, void(*func)(ResponseWriter* rw, Request* r)){
   app_new_endpoint(app, GET, path, func);
}

void app_gets(App* app, char* path, char*(*func)(void)){
   
}

void app_post(App* app, char* path, void(*func)(ResponseWriter* rw, Request* r)){
   app_new_endpoint(app, POST, path, func);
    
}

// void app_delete(App* app, char* path, void*(func)(ResponseWriter* rw, Request* r)){
   
// }

void app_put(App* app, char* path, void(*func)(ResponseWriter* rw, Request* r)){
   app_new_endpoint(app, PUT, path, func);
   
}

void handle_connection(SOCKET socket, Router* router){
    
    ResponseWriter rw = response_writer_new();

    char BUFFER[1024], message[1024];
    recv(socket, BUFFER, 1024, 0);
    string result = string_new(BUFFER);
    Request* r = request_new(&result);
    URL* url = URL_new(GET, r->path.chars);
    Handler* handler = get_URL_Handler(&router->handlers, url);
    if (handler!=NULL){
        handler->handle(&rw, r);
        string response = response_writer_get_response(&rw);
        
        string_print(&response);

        send(socket , response.chars, response.length , 0);
    
    } else {
        
        sprintf(message,
            "HTTP/1.1 404 OK\r\nContent-Length: %zu\r\nContent-Type: text/html\r\n\r\n<html><head><title>Example</title></head><body><p>404 Page Not Found: %s</p></body></html>",
            r->path.length + 81, r->path.chars
        );
     send(socket , message, get_string_length(message) , 0);
    }


}


App* create_app(){
    App* app = new(App);
    Router* router = new(Router);
    router->n_routes = 0;
    app->router = router;
    return app;
}

void app_shutdown(App* app){
    puts("Shutting down app");
    free_pointer(app->router);
    free_pointer(app);
    puts("App Shutdown");
}





int app_listen(App* app, size_t port)
{
	WSADATA wsa;
	SOCKET s , new_socket;
	struct sockaddr_in server , client;
	int c;

	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
        app_shutdown(app);
		return 1;
	}
	
	printf("Initialised.\n");
	
	//Create a socket
	if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d" , WSAGetLastError());
        app_shutdown(app);
		return 1;
	}

	printf("Socket created.\n");
	
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( port );
	
	//Bind
	if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d" , WSAGetLastError());
        app_shutdown(app);
		exit(EXIT_FAILURE);
	}
	
	printf("Server started at http://localhost:%zu\n", port);

	//Listen to incoming connections
	listen(s , 3);
	
	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	
	c = sizeof(struct sockaddr_in);
	
	while( (new_socket = accept(s , (struct sockaddr *)&client, &c)) != INVALID_SOCKET )
	{
		puts("Connection accepted");
        handle_connection(new_socket, app->router);
        closesocket(new_socket);
		puts("Connection Closed");

	}
	
	if (new_socket == INVALID_SOCKET)
	{
		printf("accept failed with error code : %d" , WSAGetLastError());
        app_shutdown(app);
		return 1;
	}

	closesocket(s);
    app_shutdown(app);
	WSACleanup();
	
	return 0;
}

#endif 
