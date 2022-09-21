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

/* bstr */
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

bool bstr_valid(bstr string) {
    return string.size != 0 && string.data;
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
    bstr res = { 0 };
    if (ind != -1) {
        res.size = ind,
        res.data = string->data,
        string->size -= ind + delim.size;
        string->data = &string->data[ind + delim.size];
    } else {
        res = *string;
        *string = (bstr) { 0 };
    }
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

/* bstrbuf */
bstrbuf bstrbuf_make(size_t initial_capacity, alloc allocator) {
    bstrbuf result = { 0 };
    void *data = allocator.malloc(initial_capacity);
    if (data) {
        result.data = data;
        result.cap = initial_capacity;
        result.alloc = allocator;
        result.valid = true;
    }
    return result;
}

bstrbuf bstrbuf_copy(bstrbuf buffer, alloc allocator) {
    bstrbuf result = { 0 };
    if (buffer.valid) {
        result = bstrbuf_make(buffer.cap, allocator);
        bstrbuf_append(&result, bstrbuf_to_bstr(buffer));
    }
    return result;
}

void bstrbuf_free(bstrbuf *string_buffer) {
    if (!string_buffer->valid) {
        return;
    }
    string_buffer->alloc.free(string_buffer->data);
}

size_t bstrbuf_space_left(const bstrbuf *string_buffer) {
    return string_buffer->cap - string_buffer->size;
}

void bstrbuf_inc_to_fit(bstrbuf *string_buffer, size_t size_to_fit) {
    if (!string_buffer->valid) {
        return;
    }
    string_buffer->cap = size_to_fit + string_buffer->size;
    string_buffer->data = string_buffer->alloc.realloc(
            string_buffer->data,
            string_buffer->cap);
    if (!string_buffer->data) {
        string_buffer->valid = false;
        return;
    }
}

void bstrbuf_prepend(bstrbuf *string_buffer, bstr string) {
    bstrbuf_insert(string_buffer, string, 0);
}

void bstrbuf_append(bstrbuf *string_buffer, bstr string) { /* faster than insert */
    if (bstrbuf_space_left(string_buffer) < string.size) {
        bstrbuf_inc_to_fit(string_buffer, string.size);
    }
    if (!string_buffer->valid) {
        return;
    }
    memcpy(&string_buffer->data[string_buffer->size], string.data, string.size);
    string_buffer->size += string.size;
}

void bstrbuf_insert(bstrbuf *string_buffer, bstr string, size_t index) {
    if (bstrbuf_space_left(string_buffer) < string.size) {
        bstrbuf_inc_to_fit(string_buffer, string.size);
    }
    if (index < 0) {
        index = 0;
    } else if (index > string_buffer->size) {
        index = string_buffer->size;
    }
    if (!string_buffer->valid) {
        return;
    }
    memmove(&string_buffer->data[index + string.size], &string_buffer->data[index], string_buffer->size - index);
    memmove(&string_buffer->data[index], string.data, string.size);
    string_buffer->size += string.size;
}

void bstrbuf_remove(bstrbuf *string_buffer, size_t from, size_t to) {
    if (!string_buffer->valid) {
        return;
    }
    /* safer execution of the function */
    if (from >= to) {
        size_t tmp = from;
        from = to;
        to = tmp;
    }
    if (from < 0) {
        from = 0;
    } else if (to > string_buffer->size) {
        to = string_buffer->size;
    }
    memmove(&string_buffer->data[from], &string_buffer->data[to], string_buffer->size - to);
    string_buffer->size -= to - from;
}

void bstrbuf_print(const bstrbuf b) {
    printf("%s"bstr_fmt"\n", b.valid ? "(valid)" : "(invalid)", bstr_arg(b));
}

bstr bstrbuf_to_bstr(const bstrbuf b) {
    bstr result = { 0 };
    if (b.valid) {
        result.size = b.size;
        result.data = b.data;
    }
    return result;
}
