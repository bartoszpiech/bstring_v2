#ifndef _BSTRING_H_
#define _BSTRING_H_

/* TODO:
SV:
done SVDEF String_View sv_from_cstr(const char *cstr);
done                SVDEF bool sv_eq(String_View a, String_View b);
done                SVDEF bool sv_eq_ignorecase(String_View a, String_View b);
done differently    SVDEF bool sv_index_of(String_View sv, char c, size_t *index);
done                SVDEF String_View sv_trim_left(String_View sv);
done                SVDEF String_View sv_trim_right(String_View sv);
done                SVDEF String_View sv_trim(String_View sv);
not needed bcs named declarations       SVDEF String_View sv_from_parts(const char *data, size_t count);
done                SVDEF String_View sv_chop_left(String_View *sv, size_t n);
done                SVDEF String_View sv_chop_right(String_View *sv, size_t n);
done differently    SVDEF String_View sv_chop_by_delim(String_View *sv, char delim);
done differently    SVDEF String_View sv_chop_by_sv(String_View *sv, String_View thicc_delim);
done differently    SVDEF bool sv_try_chop_by_delim(String_View *sv, char delim, String_View *chunk);
done                SVDEF bool sv_starts_with(String_View sv, String_View prefix);
done                SVDEF bool sv_ends_with(String_View sv, String_View suffix);

SVDEF String_View sv_chop_left_while(String_View *sv, bool (*predicate)(char x));
SVDEF String_View sv_take_left_while(String_View sv, bool (*predicate)(char x));


doing        SVDEF uint64_t sv_to_u64(String_View sv);

rf str:
idk if needed rf_public rf_bool rf_str_valid(rf_str src);
done        rf_public rf_int rf_str_len(rf_str src);
done        rf_public rf_str rf_cstr(const char* src);
made eq     rf_public int rf_str_cmp(rf_str a, rf_str b);
done        rf_public rf_bool rf_str_contains(rf_str, rf_str);
done        rf_public rf_bool rf_str_match(rf_str, rf_str);
done        rf_public rf_str rf_str_pop_first_split(rf_str* src, rf_str split_by);
not doing   rf_public rf_str rf_str_pop_last_split(rf_str* src, rf_str split_by);
done        rf_public rf_int rf_str_find_first(rf_str haystack, rf_str needle);
not doing   rf_public rf_int rf_str_find_last(rf_str haystack, rf_str needle);

rf_public rf_bool rf_str_match_prefix(rf_str, rf_str);
rf_public rf_bool rf_str_match_suffix(rf_str, rf_str);

rf_public rf_str rf_str_advance_b(rf_str src, rf_int amount);
rf_public rf_str rf_str_eat_spaces(rf_str src);
rf_public rf_rune rf_str_get_rune(rf_str src, rf_int n);
rf_public rf_utf8_char rf_str_get_utf8_char(rf_str src, rf_int n);
rf_public rf_str rf_str_sub_utf8(rf_str, rf_int begin, rf_int end);
rf_public rf_str rf_str_sub_b(rf_str, rf_int begin, rf_int end);
rf_public rf_utf8_char rf_rune_to_utf8_char(rf_rune src);
*/

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

bstr bstr_sub_left(bstr string, size_t amount);
bstr bstr_sub_right(bstr string, size_t amount);

bstr bstr_chop(bstr *string, bstr delim);
bool bstr_starts_with(bstr string, bstr prefix);
bool bstr_ends_with(bstr string, bstr suffix);

double bstr_to_double(bstr string);

#endif // _BSTRING_H_
