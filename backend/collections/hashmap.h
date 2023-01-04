#ifndef __HASHMAP__
#define __HASHMAP__

#include <stdbool.h> 
#include "../c_lib/c_lib.h"
#include "./string.h"

#define MAX_MAP_ARRAY_LENGTH 19111

#define MAKE_HASHMAP(K, V, hash_function) \
        typedef struct\
        { \
         K* key; \
         V* value; \
        } K##_##V##_pair ; \
        V* new_##V##_value(V value){ \
            V* x = new(V); \
            *x = value; \
            return x; \
        } \
        typedef struct\
        { \
         K##_##V##_pair* items[MAX_MAP_ARRAY_LENGTH]; \
         int length; \
        } hashmap_##K##_##V ; \
        K##_##V##_pair* get_##K##_##V##_pair(hashmap_##K##_##V* map, K* key){ \
          int index = hash_function(key) % MAX_MAP_ARRAY_LENGTH; \
          K##_##V##_pair* match = map->items[index]; \
          return match; \
        } \
        hashmap_##K##_##V* new_hashmap_##K##_##V(){  \
          hashmap_##K##_##V* map = new(hashmap_##K##_##V); \
          map->length = 0;\
          return map; \
        }\
        V* get_##K##_##V(hashmap_##K##_##V* map, K* key){ \
            K##_##V##_pair* match = get_##K##_##V##_pair(map, key); \
            if (match==NULL) return NULL; \
            return match->value;  \
        } \
        bool set_##K##_##V(hashmap_##K##_##V* map, K* key, V value){ \
          int index = hash_function(key) % MAX_MAP_ARRAY_LENGTH; \
          K##_##V##_pair* match = map->items[index]; \
          if (match != NULL) { \
            printf("Collision detetcted at index = %d\n", index); \
            return false;\
          } \
          K##_##V##_pair* pair = new(K##_##V##_pair); \
          pair->value = new_##V##_value(value); \
          pair->key = key; \
          map->items[index] = pair; \
            map->length++; \
          return true; \
        } \
        bool update_##K##_##V(hashmap_##K##_##V* map, K* key, V value){ \
          K##_##V##_pair* match = get_##K##_##V##_pair(map, key); \
          if (match == NULL) return false; \
          match->value = new_##V##_value(value); \
          return true; \
        } \
        bool delete_##K##_##V(hashmap_##K##_##V* map, K* key){ \
          K##_##V##_pair* match = get_##K##_##V##_pair(map, key); \
          if (match == NULL) return false; \
          free_pointer(match); \
            map->length--; \
          return true; \
        } \
        void empty_##K##_##V(hashmap_##K##_##V* map){ \
          for (size_t i = 0; i < MAX_MAP_ARRAY_LENGTH; i++) \
          { \
            free_pointer(map->items[i]); \
            map->length--; \
          }\
        } \
        void each_##K##_##V(hashmap_##K##_##V* map, bool (*func)(K##_##V##_pair* pair)){\
             for (size_t i = 0; i < MAX_MAP_ARRAY_LENGTH; i++) \
             { \
                 if (map->items[i] == NULL) continue; \
                  if (func(map->items[i])) break; \
             } \
        } \
        void free_##K##_##V(hashmap_##K##_##V* map){ \
           empty_##K##_##V(map); \
           free_pointer(map); \
        }       

size_t char_int_hash(char* str){
    size_t sum = 0;
    size_t n = 1;
    for (size_t i = 0; str[i] != '\0'; i++)
    { 
        sum += (size_t)str[i] * n;
        n *= 11;
    }
    return sum;
}

MAKE_HASHMAP(char, int, char_int_hash);
MAKE_HASHMAP(char, char, char_int_hash);
MAKE_HASHMAP(char, string, char_int_hash);

#endif
