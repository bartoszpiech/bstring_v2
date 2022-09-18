#include <stdio.h>
#include "bstring.h"

int main() {
    bstr c = bstr_cstr("aao123b.23o345eu");
    bstr d = bstr_sub_left(c, 6);
    bstr_print_dbg(c);
    bstr_print_dbg(d);
    printf("%f\n", bstr_to_double(c));
    printf("%f\n", bstr_to_double(d));
    return 0;
}
