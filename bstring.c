#include "bstring.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

size_t cstrlen(const char *cstr) {
    if (cstr == NULL) {
        fprintf(stderr, "Error (cstrlen), cstring is NULL!\n");
        return 0;
    }
    int n = 0;
    while (cstr[n] != '\0') {
        n++;
    }
    return n;
}

bstr bstr_cstr(const char *cstr) {
    return (bstr) { cstrlen(cstr), (char *)cstr };
}

void bstr_print(const bstr b) {
    printf(bstr_fmt"\n", bstr_arg(b));
}

void bstr_print_dbg(const bstr b) {
    printf("DBG: %ld \""bstr_fmt"\"\n", b.size, bstr_arg(b));
}

size_t bstr_strlen(bstr string) {
    return string.size;
}

bool bstr_eq(bstr a, bstr b) {
    if (a.size != b.size) {
        return false;
    }
    return memcmp(a.data, b.data, a.size) == 0;
}

bool bstr_eq_ignorecase(bstr a, bstr b) {
    if (a.size != b.size) {
        return false;
    }
    for (size_t i = 0; i < a.size; i++) {
        if (tolower(a.data[i]) != tolower(b.data[i])) {
            return false;
        }
    }
    return true;
}

bool bstr_contains(bstr string, bstr substring) {
    for (size_t i = 0; i < string.size; i++) {
        if (memcmp(string.data + i, substring.data, substring.size) == 0) {
            return true;
        }
    }
    return false;
}

int bstr_index(bstr string, bstr substring) {
    for (size_t i = 0; i < string.size; i++) {
        if (memcmp(string.data + i, substring.data, substring.size) == 0) {
            return i;
        }
    }
    return -1;
}

bstr bstr_trim_left(bstr string) {
    size_t i;
    for (i = 0; i < string.size; i++) {
        if (!isspace(string.data[i])) {
            break;
        }
    }
    return (bstr) {
        .size = string.size - i,
        .data = &string.data[i],
    };
}

bstr bstr_trim_right(bstr string) {
    size_t i;
    for (i = string.size - 1; i >= 0; i--) {
        if (!isspace(string.data[i])) {
            break;
        }
    }
    return (bstr) {
        .size = i + 1,
        .data = string.data,
    };

    return string;
}

bstr bstr_trim(bstr string) {
    return bstr_trim_right(bstr_trim_left(string));
}

bstr bstr_sub_left(bstr string, size_t amount) {
    if (amount > string.size) {
        amount = string.size;
    }
    return (bstr) { 
        .size = string.size - amount,
        .data = &string.data[amount],
    };
}

bstr bstr_sub_right(bstr string, size_t amount) {
    if (amount > string.size) {
        amount = string.size;
    }
    return (bstr) { 
        .size = string.size - amount,
        .data = string.data,
    };
}

bstr bstr_substr(bstr string, size_t begin, size_t end) {
    if (begin > string.size || end > string.size || begin > end) {
        return (bstr) { 0, "" };
    }
    return (bstr) {
        .size = end - begin + 1,
        .data = &string.data[begin]
    };
}

bstr bstr_chop_impl1(bstr *string, bstr delim) {
    int ind = bstr_index(*string, delim);
    if (ind == -1) {
        return *string;
    }
    bstr res = {
        .size = ind,
        .data = string->data,
    };
    string->size -= ind + delim.size;
    string->data = &string->data[ind + delim.size];
    return res;
}

bstr bstr_chop_impl2(bstr *string, const char *delim) {
    return bstr_chop_impl1(string, bstr_cstr(delim));
}

bool bstr_starts_with(bstr string, bstr prefix) {
    return bstr_index(string, prefix) == 0;
}

bool bstr_ends_with(bstr string, bstr suffix) {
    if (string.size < suffix.size) {
        return false;
    }
    string.data = &string.data[string.size - suffix.size];
    string.size = suffix.size;
    return bstr_index(string, suffix) == 0;
}

bstr bstr_without_prefix(bstr string, bstr prefix) {
    if (!bstr_starts_with(string, prefix)) {
        return string;
    }
    return (bstr) {
        .size = string.size - prefix.size,
        .data = &string.data[prefix.size]
    };
}

bstr bstr_without_suffix(bstr string, bstr suffix) {
    if (!bstr_ends_with(string, suffix)) {
        return string;
    }
    return (bstr) {
        .size = string.size - suffix.size,
        .data = string.data
    };
}

double bstr_to_double(bstr string) {
    double res = 0;
    size_t i = 0;
    double minus = 1.0;
    while (i < string.size && string.data[i] != '-' && string.data[i] != '.' && !isdigit(string.data[i]) ) {
        i++;
    }
    if (string.data[i] == '-') {
        minus *= -1;
        i++;
    }
    while (i < string.size && string.data[i] >= '0' && string.data[i] <= '9') {
        res *= 10;
        res += string.data[i] - '0';
        i++;
    }
    if (string.data[i] == '.') {
        i++;
        double factor = 1;
        while (i < string.size && string.data[i] >= '0' && string.data[i] <= '9') {
            factor /= 10;
            res += (string.data[i] - '0') * factor;
            i++;
        }
    }
    return res * minus;
}

/*
bstr bstr_reverse(bstr string) {
    bstr res = string;
    bstr_print_dbg(res);
    for (int i = 0; i < string.size; i++) {
        res.data[i] = 'X';
        bstr_print_dbg(res);
    }
    return res;
}
*/
