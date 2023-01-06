
#ifndef __STRING__
#define __STRING__

#include "../c_lib/c_lib.h"
#include "stdio.h"
#include "./list.h"
#define DEFAULT_MAX_STRING_LENGTH  1000

typedef struct
{
    char* chars;
    size_t length;
} string;

MAKE_LIST(string);


int get_string_length(char* text){
    int length = 0;
    for (size_t i = 0; text[i] != '\0'; i++)
    {
        length++;
    }
    return length;
}

void string_update(string* s, char* text){

    int new_length = get_string_length(text);
    // printf("OLD TEXT (%d): %s,  NEW_TEXT (%d): %s\n", s->length, s->chars, new_length, text);
    s->length = new_length;
    for (size_t i = 0; i < new_length+1; i++)
    {
        s->chars[i] = text[i];
    }
    s->chars[new_length] = '\0';
}

bool string_equals_string(string* s, string* other){
     
     if (s->length != other->length) return false;

     for (size_t i = 0; i < s->length; i++)
     {
        if (s->chars[i] != other->chars[i]) return false;
     }
     return true;
}

void string_print(string* s){

    printf("\n\t{ %s }\n", s->chars);
}


string string_new(char* str){
    string s;
    s.chars = new_with_capacity(char, DEFAULT_MAX_STRING_LENGTH);
    string_update(&s, str);
    return s;
}

string string_copy(string* s){
    string res = string_new(s->chars);
    return res;
}



void string_empty(string* s){
    string_update(s, "");
}

void string_append_char(string* s, char c){
    char* temp = new_with_capacity(char, s->length + 2);
    sprintf(temp, "%s%c", s->chars, c);
    string_update(s, temp);
}

void string_prepend_char(string* s, char c){
    char* temp = new_with_capacity(char, s->length + 2);
    sprintf(temp, "%c%s", c, s->chars);
    string_update(s, temp);

}

void string_append_string(string* s, string* other){
    int n = other->length;
    char* temp = new_with_capacity(char, s->length + n);
    sprintf(temp, "%s%s", s->chars, other->chars);
    string_update(s, temp);
}

void string_prepend_string(string* s, string* other){
    int n = other->length;
    char* temp = new_with_capacity(char, s->length + n);
    sprintf(temp, "%s%s", other->chars, s->chars);
    string_update(s, temp);

}

void string_append(string* s, char* str){
    int n = get_string_length(str);
    char* temp = new_with_capacity(char, s->length + n);
    sprintf(temp, "%s%s", s->chars, str);
    string_update(s, temp);
}

void string_prepend(string* s, char* str){
    int n = get_string_length(str);
    char* temp = new_with_capacity(char, s->length + n);
    sprintf(temp, "%s%s", str, s->chars);
    string_update(s, temp);
}

void string_trim_right(string* s, char c){

    char last_char;

    for (int i = s->length; i <= 0; i--)
    {
        last_char = s->chars[i];

        if (last_char == c)
        {
            s->chars[i] = '\0';
        } 
        else
        {
            break;
        }
    }
}

void string_trim_left(string* s, char c){

    char last_char;

    for (int i = 0; i < s->length; i++)
    {
        last_char = s->chars[i];

        if (last_char == c)
        {
            s->chars[i] = '\0';
        } 
        else
        {
            break;
        }
    }
}

list_string* string_split(string* s, char delimiter){

    list_string* list = new_string_list(); 
    string temp = string_new("");
    char current_char;
    for (size_t i = 0; i < s->length; i++)
    {
        current_char = s->chars[i];
        if (current_char == delimiter){
            push_string(list, string_copy(&temp));
            string_empty(&temp);
            continue;
        } 
        string_append_char(&temp, current_char);
    }

    if (temp.length >= 0)
    {
        push_string(list, string_copy(&temp));
    }

    return list;
}

string string_substring(string* s, size_t start, int stop){
    string sub = string_new("");

    int max; 
    if (stop > 0){
       max = (s->length>=stop)? stop: s->length;
    } else {
       max = s->length + stop;
    }

    for (size_t i = start; i < max; i++)
    {
        string_append_char(&sub, s->chars[i]);
    }
    return sub;
}

list_string* string_split_by_length(string* s, int length){

    list_string* list = new_string_list();
    string temp = string_new("");

    puts(s->chars);

    for (size_t i = 0; i < s->length; i++)
    {
        string_append_char(&temp, s->chars[i]);

       if (temp.length==length){
           push_string(list, string_copy(&temp));
           string_empty(&temp);
        }
    }

    return list;
}

string int_to_base_n(int x, unsigned int base){
    
    string result = string_new("");

    int remainder, quotient, acc = x;
    char temp[100];
    
    while (acc > 0)
    {
        quotient = acc / base;
        remainder = acc - ( quotient * base );
        sprintf(temp, "%d", remainder);
        string_prepend(&result, temp);
        acc = quotient;
    }
    
    while (result.length < 8) string_prepend_char(&result, '0');
    return result;     
}


string string_to_base_n(string* s, unsigned int base){
    
    string result = string_new("");
    string temp;

    for (size_t i = 0; i < s->length; i++)
    {
        temp = int_to_base_n(s->chars[i], base);
        string_append_string(&result, &temp);
    }
    
    return result;     
}

string str_to_base_n(char* s, unsigned int base){
    
    string result = string_new(s);
    return string_to_base_n(&result, base);     
}




//    string splaintext = string_new(plaintext);
//    list_string* split = string_split(&splaintext, ' ');

//    for (size_t i = 0; i < split->length; i++)
//    {
//        printf("%zu. [%s]\n", i, get_string(split, i)->chars);
//    }
   
//    string sub = string_substring(get_string(split, 0), 2, -1);
//    string_print(&sub);
   

#endif