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
    bstr c = bstr_cstr("21/09/22");
    for_bstr_chop(it, c, bstr_cstr("/")) {
        bstr_print(it);
    }
    return 0;
}
