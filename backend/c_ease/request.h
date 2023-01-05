
#ifndef __C_EASE_REQUEST_H_
#define __C_EASE_REQUEST_H_

#include "../collections/collections.h"
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

#endif