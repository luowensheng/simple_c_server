#ifndef __C_EASE_URL_H_
#define __C_EASE_URL_H_

#include "../collections/collections.h"

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




#endif