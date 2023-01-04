

#ifndef __MEMORY__
#define __MEMORY__

#include <stdlib.h>
#define expand(item, item_type, size) item = (item_type) realloc (item, size * sizeof(item_type));

void free_pointer(void* p){
    if (p==NULL) return;
    free(p);
    p = NULL;  
}

#define new(type) (type*)malloc(sizeof(type))
#define new_with_capacity(type, capacity) (type*)malloc(sizeof(type)*capacity)


#endif

