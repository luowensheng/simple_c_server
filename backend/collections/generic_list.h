
#ifndef __COLLECTION_GENERIC_LIST_H__
#define __COLLECTION_GENERIC_LIST_H__

#include "../c_lib/c_lib.h"
#include "stdio.h"
#define DEFAULT_MAX_LIST_LENGTH  25

#define MAKES_LIST(COLLECTION_NAME, ITEM_TYPE, FORMATTER) \
    \
    typedef struct\
    { \
        ITEM_TYPE* items;\
        size_t length; \
    } COLLECTION_NAME; \
    \
    void COLLECTION_NAME##_print(COLLECTION_NAME* s){ \
        printf("\n[ "); \
        for (size_t i = 0; i < s->length-1; i++) \
        { \
            printf(FORMATTER ", ", s->items[i]); \
        } \
        printf(FORMATTER " ]\n", s->items[s->length-1]); \
    } \
    void COLLECTION_NAME##_update_with_length(COLLECTION_NAME* s, ITEM_TYPE* input, size_t new_length){ \
        s->length = new_length; \
        for (size_t i = 0; i < new_length; i++) \
        { \
            s->items[i] = input[i]; \
        } \
    } \
    bool COLLECTION_NAME##_equals_##COLLECTION_NAME(COLLECTION_NAME* s, COLLECTION_NAME* other){ \
        if (s->length != other->length) return false; \
        for (size_t i = 0; i < s->length; i++) \
        { \
            if (s->items[i] != other->items[i]) return false; \
        } \
        return true; \
    } \
    \
    COLLECTION_NAME COLLECTION_NAME##_new_with_items(ITEM_TYPE* input, size_t length){ \
        COLLECTION_NAME s; \
        s.items = new_with_capacity(ITEM_TYPE, DEFAULT_MAX_LIST_LENGTH); \
        COLLECTION_NAME##_update_with_length(&s, input, length); \
        return s;  \
    }  \
    COLLECTION_NAME COLLECTION_NAME##_new(){ \
        COLLECTION_NAME s; \
        s.items = new_with_capacity(ITEM_TYPE, DEFAULT_MAX_LIST_LENGTH); \
        return s;  \
    }  \
    \
    COLLECTION_NAME COLLECTION_NAME##_copy(COLLECTION_NAME* s){ \
        COLLECTION_NAME res = COLLECTION_NAME##_new_with_items(s->items, s->length); \
        return res; \
    } \
    \
    void COLLECTION_NAME##_empty(COLLECTION_NAME* s){  \
        s->length = 0; \
    }  \
    void COLLECTION_NAME##_append(COLLECTION_NAME* s, ITEM_TYPE input){ \
        s->items[s->length] = input; \
        s->length ++; \
    } \
    void COLLECTION_NAME##_prepend(COLLECTION_NAME* s, ITEM_TYPE input){ \
        for (size_t i=1; i<= s->length; i++) s->items[i]=s->items[i-1];\
        s->items[0] = input;\
        s->length++; \
    } 

#endif