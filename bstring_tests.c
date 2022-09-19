#include <stdio.h>
#include "bstring.h"

int main() {
    bstr c = bstr_cstr("brzeczyszczykiewicz");
    bstr_print_dbg(bstr_without_prefix(c, bstr_cstr("brze")));
    bstr_print_dbg(bstr_chop(&c, bstr_cstr("czy")));
    bstr_print_dbg(bstr_chop(&c, "k"));
    return 0;
}
