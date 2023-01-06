#ifndef __C_EASE_SERVER_H_
#define __C_EASE_SERVER_H_

#include <io.h>
#include <stdio.h>
#include <time.h>

#include "../collections/collections.h"

#include "./url.h"
#include "./router.h"
#include "./color.h"
#include "./socket.h"


typedef struct 
{
  Router* router;
} App;

typedef struct {
  HTTP_METHOD method;
  char* path;
  void(*handle)(Response* rw, Request* r);

} ROUTER;

ROUTER*_ALL_ROUTERS;

#define ROUTE(name, method, path, ...) \
void name##_handle_func __VA_ARGS__ \
ROUTER name = {method, path, &name##_handle_func};

#define ROUTE_HTML(name, method, path, ...) \
        ROUTE(name, method, path, (Response* rw, Request* r){ \
        response_set_content(rw, STRINGIFY(__VA_ARGS__));})

 
void app_new_endpoint(App* app, HTTP_METHOD m, char* path, void(*func)(Response* rw, Request* r)){
     router_new_handler(app->router, m, path, func);
     printf(GREEN("Added new route -> method: %s, path: %s\n"), http_method_to_chars(m) , path);
}

// https://stackoverflow.com/questions/12447557/can-we-have-recursive-macros
// https://codecraft.co/2014/11/25/variadic-macros-tricks/

void app_add_router(App* app, ROUTER* router){
   app_new_endpoint(app, router->method, router->path, router->handle);
}

// void app_add_routers(App* app, int n, ...){
//     ROUTER router;
//     // Declaring pointer to the
//     // argument list
//     va_list ptr;
//     va_list cc;

//     // Initializing argument to the
//     // list pointer
//     va_start(ptr, n);
//     for (int i=0; i<n; i++){
//         // Accessing current variable
//         // and pointing to next one
//         puts("ADDING NEW ROUTE");
//         router = va_arg(ptr, ROUTER);
//         printf("[%p]\n", cc);
//         puts("ADDING NEW ROUTE...");
//         app_add_router(app, &router);
//         printf("added %s\n", router.path);
//         cc = ptr+1;

//     }
//     puts("HERE");
 
//     // Ending argument list traversal
//     va_end(ptr);
//     puts("EXITING");
// }


#define RUN_APP(port, ...)\
	App* app = create_app();\
    puts("CREATED APP"); \
    ROUTER routers[] = {__VA_ARGS__}; \
    for (int i=0; i< LENGTH(routers); i++){\
	    app_add_router(app, &routers[i]); \
    } \
    puts("ADDED ROUTES"); \
	return app_listen(app, port); 


#define APP_MAIN(port, ...) \
int main(){ \
	RUN_APP(port, __VA_ARGS__)\
}


void app_post(App* app, char* path, void(*func)(Response* rw, Request* r)){
   app_new_endpoint(app, POST, path, func);
}

void app_delete(App* app, char* path, void(*func)(Response* rw, Request* r)){
   app_new_endpoint(app, PUT, path, func);
   
}

void app_put(App* app, char* path, void(*func)(Response* rw, Request* r)){
   app_new_endpoint(app, DELETE, path, func);
}

char* get_asci_time(){
    time_t raw_time;
    struct tm* time_info;
    time(&raw_time);
    time_info = localtime(&raw_time);
    char* s = asctime(time_info);
    sprintf(s, "%d/%d/%d %d:%d:%d", time_info->tm_mon+1, time_info->tm_mday,time_info->tm_year + 1900, time_info->tm_hour, time_info->tm_min, time_info->tm_sec);
    return s;
}

void handle_connection(socket_t* socket, Router* router){
    
    Response rw = response_new();

    char BUFFER[1024], message[1024];
    socket_recv(socket, BUFFER, 1024, 0);
    string result = string_new(BUFFER);
    Request* r = request_new(&result);
    URL* url = URL_new(GET, r->path.chars);
    Handler* handler = get_URL_Handler(&router->handlers, url);
    
    int status_code;

    if (handler!=NULL){

        handler->handle(&rw, r);
        string response = response_get_response(&rw);
        status_code =  rw.status_code;
        socket_send(socket , response.chars, response.length , 0);
    
    } else {
        status_code = 404;
        sprintf(message,
            "HTTP/1.1 404 ERROR\r\nContent-Length: %zu\r\nContent-Type: text/html\r\n\r\n<html><head><title>Page Not Found</title></head><body><p>404 Page Not Found: %s</p></body></html>",
            r->path.length + 81, r->path.chars
        );
        
     socket_send(socket , message, get_string_length(message) , 0);
    }

    if (status_code > 500){
        printf(BLUE("[%s] ") RED("method: %s, path: %s, status code: %d") "\n", get_asci_time(), http_method_to_chars(url->method) , url->path.chars, status_code);
    }     
    else if (status_code > 400){
        printf(BLUE("[%s] ") YELLOW("method: %s, path: %s, status code: %d") "\n", get_asci_time(), http_method_to_chars(url->method) , url->path.chars, status_code);
    } else {
        printf(BLUE("[%s] ") GREEN("method: %s, path: %s, status code: %d") "\n", get_asci_time(), http_method_to_chars(url->method) , url->path.chars, status_code);
    }


    free_pointer(url);
    free_pointer(r);


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
	socket_t client, tcp_server = socket_create_tcp(port);
    bool keep_server_running = true;
	
    socket_bind(&tcp_server);
	printf("Server started at http://localhost:%zu\n", port);

	//Listen to incoming connections
    socket_listen(&tcp_server, 30);
	
	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	
	while(keep_server_running)
	{
        client = socket_accept(&tcp_server);
        if (socket_is_valid(&client)){
           handle_connection(&client, app->router);
        }
        socket_close(&client);
	}

    app_shutdown(app);
	return 0;
}

#endif
