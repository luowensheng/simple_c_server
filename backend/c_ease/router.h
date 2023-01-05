
#ifndef __C_EASE_ROUTER_H_
#define __C_EASE_ROUTER_H_

#include "../collections/collections.h"
#include "./url.h"
#include "./handler.h"

MAKE_HASHMAP(URL, Handler, URL_hash_function)


typedef struct 
{
  size_t n_routes;
  hashmap_URL_Handler handlers; 
} Router;


void router_new_handler(Router* router, HTTP_METHOD method, char* path, void(*func)(Response* rw, Request* r)){
    Handler* handler = new(Handler);
    handler->handle = func;
    handler->path = path;
    URL* key = URL_new(method, path);
    set_URL_Handler(&router->handlers, key, *handler);
    router->n_routes += 1;
}



#endif




