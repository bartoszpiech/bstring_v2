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
    bstr c = bstr_cstr("alamakota");
    bstrbuf buffer = bstrbuf_make(2, myalloc);
    bstrbuf b2 = bstrbuf_copy(buffer, myalloc);
    bstrbuf_append(&buffer, c);
    bstr_print(c);
    bstrbuf_print(buffer);
    bstrbuf_print(b2);


    buffer.data[0] = 'X';
    b2.data[0] = 'Y';
    bstrbuf_print(buffer);
    bstrbuf_print(b2);

    bstrbuf_free(&buffer);
    bstrbuf_free(&b2);
    return 0;
}
