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
    bstr c = bstr_cstr("09/09/09");
    bstrbuf cbuf = bstrbuf_make(16, myalloc);
    bstrbuf_append(&cbuf, c);
    /*
    for_bstr_chop(it, c, bstr_cstr("/")) {
        bstr_print(it);
    }
    */
    size_t r = bstrbuf_replace_all(&cbuf, bstr_cstr("09"), bstr_cstr("HALO"));
    printf("%ld\n", r);
    bstrbuf_print(cbuf);
    bstrbuf_free(&cbuf);

    return 0;
}
