

#ifndef __C_EASE_SERVER_H_
#define __C_EASE_SERVER_H_

 
#include<io.h>
#include<stdio.h>
#include<winsock2.h>

#include "../collections/collections.h"

#include "./url.h"
#include "./router.h"

typedef struct 
{
  Router* router;
} App;



 
void app_new_endpoint(App* app, HTTP_METHOD m, char* path, void(*func)(Response* rw, Request* r)){
     router_new_handler(app->router, m, path, func);
}


void app_get(App* app, char* path, void(*func)(Response* rw, Request* r)){
   app_new_endpoint(app, GET, path, func);
}

void app_gets(App* app, char* path, char*(*func)(void)){
   
}

void app_post(App* app, char* path, void(*func)(Response* rw, Request* r)){
   app_new_endpoint(app, POST, path, func);
    
}

// void app_delete(App* app, char* path, void*(func)(Response* rw, Request* r)){
   
// }

void app_put(App* app, char* path, void(*func)(Response* rw, Request* r)){
   app_new_endpoint(app, PUT, path, func);
   
}

void handle_connection(SOCKET socket, Router* router){
    
    Response rw = response_new();

    char BUFFER[1024], message[1024];
    recv(socket, BUFFER, 1024, 0);
    string result = string_new(BUFFER);
    Request* r = request_new(&result);
    URL* url = URL_new(GET, r->path.chars);
    Handler* handler = get_URL_Handler(&router->handlers, url);

    if (handler!=NULL){

        handler->handle(&rw, r);
        string response = response_get_response(&rw);
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
