#ifndef _BSTRING_H_
#define _BSTRING_H_

/* stddef.h */
typedef long unsigned int size_t;
/* stdbool.h */
typedef _Bool bool;
#define true 1;
#define false 0;
#define bstr_fmt "%.*s"
#define bstr_arg(bstr) (int)(bstr).size, (bstr).data

typedef void *(*allocator_cb)(size_t);
typedef void *(*reallocator_cb)(void *, size_t);
typedef void  (*free_cb)(void *);

typedef struct allocator {
    allocator_cb malloc;
    reallocator_cb realloc;
    free_cb free;
} alloc;

/* add ifdef stdlib.h */
//#ifdef 
alloc gnu_alloc = {
    .malloc = malloc,
    .realloc = realloc,
    .free = free
};

typedef struct bstring {
    size_t size;
    char *data;
} bstr;

typedef struct bstring_buffer {
    size_t size;
    char *data;
    size_t cap;
    alloc alloc;
    bool valid;
} bstrbuf;

/* bstr */
bstr    bstr_cstr(const char *data);
void    bstr_print(const bstr);
void    bstr_print_dbg(const bstr);
size_t  bstr_strlen(bstr string);
bool    bstr_valid(bstr string);
bool    bstr_eq(bstr a, bstr b);
bool    bstr_eq_ignorecase(bstr a, bstr b);
bool    bstr_contains(bstr string, bstr substring);
int     bstr_index(bstr string, bstr substring);
bstr    bstr_trim_left(bstr string);
bstr    bstr_trim_right(bstr string);
bstr    bstr_trim(bstr string);
bstr    bstr_sub_left(bstr string, size_t amount);             // substract
bstr    bstr_sub_right(bstr string, size_t amount);            // substract
bstr    bstr_substr(bstr string, size_t begin, size_t end);    // substring
bool    bstr_starts_with(bstr string, bstr prefix);
bool    bstr_ends_with(bstr string, bstr suffix);
bstr    bstr_without_prefix(bstr string, bstr prefix);
bstr    bstr_without_suffix(bstr string, bstr suffix);
double  bstr_to_double(bstr string);
bstr    bstr_chop_impl1(bstr *string, bstr delim);
bstr    bstr_chop_impl2(bstr *string, const char *delim);
/* idk if i should leave this macro but i made it */
#define bstr_chop(string, delim)                                \
     _Generic((delim),                                          \
            char*:       bstr_chop_impl2,                       \
            default:     bstr_chop_impl1)(string, delim)

#define concat_impl(a, b) a##b
#define concat(a, b)      concat_impl(a, b)
#define macro_var(X) concat(macro_gen_var, concat(X, __LINE__))

#define for_bstr_chop(iter, string, delim)                      \
    bstr macro_var(string_) = string;                           \
    bstr iter = bstr_chop(&macro_var(string_), delim);          \
    bstr macro_var(delim_) = delim;                             \
    for (; bstr_valid(iter); iter = bstr_chop(&macro_var(string_), macro_var(delim_)))

/* optional bstr functions */
/*!
 * function that counts fields inside bstr. An example of the field is:
 * ...{...}...
 * it takes the string, open and closing brackets as arguments
 * returns amount of fields 
 */
size_t  bstr_count_fields(bstr string, char open_bracket, char close_bracket);

/* bstrbuf */
bstrbuf bstrbuf_make(size_t initial_capacity, alloc allocator);
bstrbuf bstrbuf_copy(bstrbuf buffer, alloc allocator);
void    bstrbuf_free(bstrbuf *string_buffer);
size_t  bstrbuf_space_left(const bstrbuf *string_buffer);
void    bstrbuf_prepend(bstrbuf *string_buffer, bstr string);
void    bstrbuf_append(bstrbuf *string_buffer, bstr string);
void    bstrbuf_insert(bstrbuf *string_buffer, bstr string, size_t index);
void    bstrbuf_remove(bstrbuf *string_buffer, size_t from, size_t to);
void    bstrbuf_print(const bstrbuf b);
bstr    bstrbuf_to_bstr(const bstrbuf b);  /* beware freeing bstrbuf makes bstr owned */
int     bstrbuf_replace_first(bstrbuf *string_buffer, bstr original, bstr replacement); /* replaces first occurence and returns its previous index, if not found returns -1 */
size_t  bstrbuf_replace_all(bstrbuf *string_buffer, bstr original, bstr replacement); /* replaces all occurences and returns number of replacements */

#endif // _BSTRING_H_
