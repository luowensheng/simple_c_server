#ifndef __C_EASE_URL_H_
#define __C_EASE_URL_H_

#include "../collections/collections.h"

#ifdef DELETE
  #undef DELETE
#endif


typedef enum {
    GET, POST, PUT, DELETE
} HTTP_METHOD;

char* http_method_to_chars(HTTP_METHOD method){

     switch (method)
    {
    case GET: return "GET";
    case POST: return "POST";
    case PUT: return "PUT";
    case DELETE: return "DELETE";
    default: return "";
    }
}

HTTP_METHOD http_method_from_chars(char* method){

     switch (method[2])
    {
    case 'E': 
    if (method[0]=='G') return GET; else return DELETE;
    case 'O': return POST;
    case 'U': return PUT;
    default: return GET;
    }
}

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