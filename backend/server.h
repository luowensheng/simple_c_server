#ifndef SERVER_H
#define SERVER_H

#include<io.h>
#include<stdio.h>
#include<winsock2.h>
#include <stdlib.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library
#define QUOTE(seq) "\""#seq"\""
#define HTML(seq) QUOTE(seq)
#define new(Item) (Item*)malloc(sizeof(Item))
#define new_with_capacity(Item, n) (Item*)malloc(sizeof(Item)*n)
#define DEFAULT_LIST_SIZE 20
#define expand(item, item_type, size) item = (item_type) realloc (item, size * 10 * sizeof(item_type));
        // ptr = realloc(ptr, n * sizeof(int));

void free_pointer(void* p){
    if (p==NULL) return;
    free(p);
    p = NULL;  
}


#define HashMap(K, V) \
    typedef struct \
    { \
     \
    } HashMap_##K_##V;

#define List(K) \
    typedef struct \
    { \
     size_t length;\
     K* items[];  \
    } List_##K; \
    List_##K* new_##K##_list_with_capacity(size_t capacity){ \
        List_##K* list = new_with_capacity(List_##K, capacity); \
        list->length = 0; \
        return list; \
    }\
    List_##K* new_##K##_list(){ \
        return new_##K##_list_with_capacity(DEFAULT_LIST_SIZE); \
    }\
    void push_##K(List_##K* list, K item){ \
         K* h_item = new(K); \
        if (list->length == DEFAULT_LIST_SIZE){ \
           printf("HERRE\n"); \
           expand(list, List_##K*, list->length+DEFAULT_LIST_SIZE+20);\
        } \
         *h_item = item; \
         list->items[list->length++] = h_item; \
    } \
    K* get_##K(List_##K* list, size_t index){ \
        return list->items[index];   \
    } \
    void each_##K(List_##K* list, void(*f)(K*)){ \
        for (size_t i = 0; i < list->length; i++){ f(list->items[i]); } \
    } \
    void free_##K##_list(List_##K* list){ \
       for (size_t i = 0; i < list->length; i++){ free_pointer(list->items[i]); } \
       list->length = 0; \
       free_pointer(list);\
    } 

List(char);
typedef struct { List_char chars; } String;   
List(String);



void string_split(char* string, const char* delimiter){

    puts("STARTED");
	
    // List_String* out = new_String_list();
    // puts("STARTED OUT");

    // String temp;
    // puts("STARTED TEMP");

	char * token = strtok(string, " ");
    printf( "GOT %s\n", token ); //printing each token

    // loop through the string to extract all other tokens
    while( token != NULL ) {
        char * token = strtok(string, " ");
        printf( " %s\n", token ); //printing each token
       
        // temp.item = token;

        // push_String(out, temp);

        token = strtok(NULL, " ");
    }
    puts("ENDED");

    // return out;
}



typedef struct {} ResponseWriter;
typedef struct {} Request;
typedef struct 
{
  char* path;
  void(*handle)(ResponseWriter* rw, Request* r);
} Handler;



List(Handler);

typedef struct 
{
  size_t n_routes;
  List_Handler handlers; 
} Router;

void router_new_handler(Router* router, char* path, void(*func)(ResponseWriter* rw, Request* r)){
    Handler* handler = new(Handler);
    handler->handle = func;
    handler->path = path;
    push_Handler(&router->handlers, *handler);
    router->n_routes += 1;
}


typedef struct 
{
  Router* router;
} App;



// void app_route(App* app, char* path, void*(func)(ResponseWriter* rw, Request* r)){
   
// }

void app_get(App* app, char* path, void(*func)(ResponseWriter* rw, Request* r)){
   
}

void app_gets(App* app, char* path, char*(*func)(void)){
   
}

// void app_post(App* app, char* path, void*(func)(ResponseWriter* rw, Request* r)){
   
// }

// void app_delete(App* app, char* path, void*(func)(ResponseWriter* rw, Request* r)){
   
// }

// void app_put(App* app, char* path, void*(func)(ResponseWriter* rw, Request* r)){
   
// }

void handle_connection(SOCKET socket, Router* router){
    
    ResponseWriter rw;
    Request r;
    char * url = "";
    for (size_t i = 0; i < router->n_routes; i++)
    {
        Handler* handler = get_Handler(&router->handlers, i);
        if (handler->path == url){
            handler->handle(&rw, &r);
            break;
        }
        // Handler* handler = router->handlers[i];

    }
    char BUFFER[1024];
    
    char* message = "HTTP/1.1 200 OK\r\nContent-Length: 77\r\nContent-Type: text/html\r\n\r\n<html><head><title>Example</title></head><body><p>Worked!!!</p></body></html>";
    recv(socket, BUFFER, 1024, 0);
    puts(BUFFER);
    int res = send(socket , message , strlen(message)*8 , 0);
    res = send(socket , message , strlen(message) , 0);

}

// typedef struct 
// {
//   size_t n_routes;
//   Handler* handlers; 
// } Router;

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
	char *message;

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
	
	printf("Server started at http://localhost:%d\n", port);

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
