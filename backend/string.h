#ifndef STRING_H
#define STRING_H
#define STRING_MIN_LENGTH 20
#include <stdio.h>
#include "./macros.h"


typedef struct {
  char* s;
  size_t length;
} string;

int get_char_p_length(char* str){
    int length = 0;
    for (size_t i = 0; str[i] != '\0'; i++)
    {
        length++;
    }
    
    return length;
}

string* string_new(char* s){

    string* ns = new(string);
    ns->s = s;
    sprintf(ns->s, "%s", s);
    ns->length = get_char_p_length(s);

    return ns;
}

string* string_copy(string* s){
    string* out = string_new(s->s);
    return out;
}

string* string_push(string* s, string* other_str){
    char *result = new_with_capacity(char, s->length+other_str->length);
    sprintf(result, "%s%s", s->s, other_str->s);     
    string* out = string_new(result);
    return out;
}
string* string_push_str(string* s, char* other){
   string* other_str = string_new(other);
   return string_concat(s, other_str);
}

string* string_push_char(string* s, char c){
    char t[2];
    t[0] = c;
    return string_push_str(s, t);
}

void string_print(string* s){
    if (s->length<1) return;
    
    printf("%s", s->s);
}

void string_delete(string* s){
    free_pointer(s->s);
    s->length = 0;
    free_pointer(s);
}

List(string);

List_string* string_split(string* s, char delimiter){

    List_string* p = new_string_list();
    int current_idx = 0;
    string* temp = string_new("");
    for (size_t i = 0; i < s->length; i++)
    {
        char c = s->s[i];
        // printf("\n(%d/%d). %c == %c is %d\n", i, s->length, c, delimiter, c==delimiter);
        if (c==delimiter){
            push_string(p, *temp);
            temp = string_new("");
        } 
        else {
           string_push_char(temp, c);
        }       
    }
    each_string(p, &string_print);
    
    return p;
}


#endif