
#ifndef __C_EASE_HANDLER_H_
#define __C_EASE_HANDLER_H_

#include "./request.h"
#include "./response.h"
#include "./url.h"

typedef struct 
{
  char* path;
  void(*handle)(Response* rw, Request* r);
} Handler;

size_t URL_hash_function(URL* s){
    return char_int_hash(s->path.chars) + s->method;
}


#endif

