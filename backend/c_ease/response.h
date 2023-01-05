
#ifndef __C_EASE_RESPONSE_WRITER_H_
#define __C_EASE_RESPONSE_WRITER_H_

#include "../collections/string.h"

typedef struct {
    string protocol; 
    unsigned int status_code; 
    string status; 
    string content_type; 
    string content; 

} Response;



Response response_new() {
        Response response;
        response.protocol = string_new("HTTP/1.1"); 
        response.status_code = 200; 
        response.status = string_new("OK"); 
        response.content_type = string_new("text/html");  
        response.content= string_new("");
        return response;
    }

    void response_set_protocol(Response* response, char* protocol) {
        string_update(&response->protocol, protocol);
    }
    void response_set_status_code(Response* response, unsigned int status_code) {
        response->status_code = status_code;

    }
    void response_set_status(Response* response, char* status) {
        string_update(&response->status, status);
    }
    void response_set_content_type(Response* response, char* content_type) {
        string_update(&response->content_type, content_type);

    }
    void response_set_content(Response* response, char* content) {
        string_update(&response->content, content);
    }

    void response_set_json_content(Response* response, char* json_string) {
        string_update(&response->content_type, "application/json");
        char temp[1024];
        sprintf(temp, "<pre>%s</pre>", json_string);
        string_update(&response->content, temp);

    }

    string response_get_response(Response* rw) {
        char temp[2048];
        sprintf(temp,
         "%s %d %s\r\nContent-Type: %s\r\n\r\n\r\n%s",
          rw->protocol.chars, rw->status_code, rw->status.chars, rw->content_type.chars,rw->content.chars
        );
        return string_new(temp);
    }



#endif