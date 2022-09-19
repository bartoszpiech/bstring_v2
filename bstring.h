#ifndef _BSTRING_H_
#define _BSTRING_H_

#define bstr_fmt "%.*s"
#define bstr_arg(bstr) (int)(bstr).size, (bstr).data

// stddef.h
typedef long unsigned int size_t;
// stdbool.h
typedef _Bool bool;
#define true 1;
#define false 0;

typedef struct bstring {
    size_t size;
    char *data;
} bstr;

bstr bstr_cstr(const char *data);
void bstr_print(const bstr);
void bstr_print_dbg(const bstr);

size_t bstr_strlen(bstr string);

bool bstr_eq(bstr a, bstr b);
bool bstr_eq_ignorecase(bstr a, bstr b);

bool bstr_contains(bstr a, bstr b);
bool bstr_contains(bstr string, bstr substring);

int bstr_index(bstr string, bstr substring);

bstr bstr_trim_left(bstr string);
bstr bstr_trim_right(bstr string);
bstr bstr_trim(bstr string);

bstr bstr_sub_left(bstr string, size_t amount);             // substract
bstr bstr_sub_right(bstr string, size_t amount);            // substract

bstr bstr_substr(bstr string, size_t begin, size_t end);    // substring

// idk if i should leave this macro but i made it
bstr bstr_chop_impl1(bstr *string, bstr delim);
bstr bstr_chop_impl2(bstr *string, const char *delim);
#define bstr_chop(string, delim)                                    \
     _Generic((delim),                                              \
            char*:       bstr_chop_impl2,                           \
            default:     bstr_chop_impl1)(string, delim)

bool bstr_starts_with(bstr string, bstr prefix);
bool bstr_ends_with(bstr string, bstr suffix);
bstr bstr_without_prefix(bstr string, bstr prefix);
bstr bstr_without_suffix(bstr string, bstr suffix);

double bstr_to_double(bstr string);

// cannot reverse non-owning string-view
// bstr bstr_reverse(bstr string);

#endif // _BSTRING_H_
