#include <stdio.h>
#include <stdlib.h>
#include "bstring.h"

void *mymalloc(size_t size) {
    void *res = malloc(size);
    printf("!!! malloc(%ld)\t%p\n", size, res);
    return res;
}

void *myrealloc(void *ptr, size_t size) {
    void *res = realloc(ptr, size);
    printf("!!! realloc(%ld)\t%p\n", size, res);
    return res;
}

void myfree(void *ptr) {
    printf("!!! free()\t%p\n", ptr);
    free(ptr);
}

alloc myalloc = {
    .malloc = mymalloc,
    .realloc = myrealloc,
    .free = myfree
};

int main() {
    bstr c = bstr_cstr("brzeczyszczykiewicz");
    bstrbuf buffer = bstrbuf_make(2, myalloc);
    bstrbuf_print(buffer);
    bstrbuf_append(&buffer, c);
    bstrbuf_append(&buffer, c);
    bstrbuf_append(&buffer, c);
    bstrbuf_append(&buffer, c);
    bstrbuf_print(buffer);
    
    bstrbuf_free(&buffer);
    return 0;
}
