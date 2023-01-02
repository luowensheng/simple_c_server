#ifndef MACROS_H
#define MACROS_H

#include <stdlib.h>
#include<stdbool.h>

#define QUOTE(seq) "\""#seq"\""
#define HTML(seq) QUOTE(seq)
#define new(Item) (Item*)malloc(sizeof(Item))
#define new_with_capacity(Item, n) (Item*)malloc(sizeof(Item)*n)
#define DEFAULT_LIST_SIZE 50
#define expand(item, item_type, size) item = (item_type) realloc (item, size * 10 * sizeof(item_type));
        // ptr = realloc(ptr, n * sizeof(int));

void free_pointer(void* p){
    if (p==NULL) return;
    free(p);
    p = NULL;  
}


#define HashMap(K, V) \
    typedef struct \
    { \
     \
    } HashMap_##K_##V;

#define List(K) \
    typedef struct \
    { \
     size_t length;\
     K* items[];  \
    } List_##K; \
    List_##K* new_##K##_list_with_capacity(size_t capacity){ \
        List_##K* list = new_with_capacity(List_##K, capacity); \
        list->length = 0; \
        return list; \
    }\
    List_##K* new_##K##_list(){ \
        return new_##K##_list_with_capacity(DEFAULT_LIST_SIZE); \
    }\
    void push_##K(List_##K* list, K item){ \
         K* h_item = new(K); \
        if (list->length == DEFAULT_LIST_SIZE){ \
           printf("HERRE\n"); \
           expand(list, List_##K*, list->length+DEFAULT_LIST_SIZE+20);\
        } \
         *h_item = item; \
         list->items[list->length++] = h_item; \
    } \
    K* get_##K(List_##K* list, size_t index){ \
        return list->items[index];   \
    } \
    K* set_##K(List_##K* list, size_t index, K* target, K*(*copy_fn)(K*)){ \
        return list->items[index] = copy_fn(target);   \
    } \
    void each_##K(List_##K* list, void(*f)(K*)){ \
        for (size_t i = 0; i < list->length; i++){ f(list->items[i]); } \
    } \
    bool equals_##K(List_##K* list, List_##K* other){ \
        if (list->length != other->length){ return false; } \
        for (size_t i = 0; i < list->length; i++){ \
            if (get_##K(list, i) != get_##K(other, i)){ return false; }\
        } \
        return true; \
    } \
    void free_##K##_list(List_##K* list){ \
       for (size_t i = 0; i < list->length; i++){ free_pointer(list->items[i]); } \
       list->length = 0; \
       free_pointer(list);\
    }

#endif 
