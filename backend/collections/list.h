#ifndef __LIST__
#define __LIST__

#define DEFAULT_LIST_SIZE 50
#include "../c_lib/c_lib.h"
#include "stdbool.h"


#define MAKE_LIST(K) \
    typedef struct \
    { \
     size_t length;\
     K* items[];  \
    } list_##K; \
    list_##K* new_##K##_list_with_capacity(size_t capacity){ \
        list_##K* list = new_with_capacity(list_##K, capacity); \
        list->length = 0; \
        return list; \
    }\
    list_##K* new_##K##_list(){ \
        return new_##K##_list_with_capacity(DEFAULT_LIST_SIZE); \
    }\
    void push_##K(list_##K* list, K item){ \
         K* h_item = new(K); \
        if (list->length == DEFAULT_LIST_SIZE){ \
           printf("HERRE\n"); \
           expand(list, list_##K*, list->length+DEFAULT_LIST_SIZE+20);\
        } \
         *h_item = item; \
         list->items[list->length++] = h_item; \
    } \
    K* get_##K(list_##K* list, size_t index){ \
        return list->items[index];   \
    } \
    K* set_##K(list_##K* list, size_t index, K* target, K*(*copy_fn)(K*)){ \
        return list->items[index] = copy_fn(target);   \
    } \
    void each_##K(list_##K* list, void(*f)(K*)){ \
        for (size_t i = 0; i < list->length; i++){ f(list->items[i]); } \
    } \
    bool equals_##K(list_##K* list, list_##K* other){ \
        if (list->length != other->length){ return false; } \
        for (size_t i = 0; i < list->length; i++){ \
            if (get_##K(list, i) != get_##K(other, i)){ return false; }\
        } \
        return true; \
    } \
    void free_##K##_list(list_##K* list){ \
       for (size_t i = 0; i < list->length; i++){ free_pointer(list->items[i]); } \
       list->length = 0; \
       free_pointer(list);\
    }

#endif