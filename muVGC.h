/*
muVGC - Muukid
Public domain single-file C library for compiling Vulkan GLSL shader code into SPIR-V.
No warranty implied; use at your own risk.

Licensed under MIT License or public domain, whichever you prefer.
More explicit license information at the end of the file.
*/

#ifndef MUVGC_H
#define MUVGC_H

#ifdef __cplusplus
extern "C" { // }
#endif

/* basics */

#define MUVGC_VERSION_MAJOR 1
#define MUVGC_VERSION_MINOR 0
#define MUVGC_VERSION_PATCH 0

#ifndef MUDEF
    #ifdef MU_STATIC
        #define MUDEF static
    #else
        #define MUDEF extern
    #endif
#endif

/* C standard library dependencies */

#if !defined(mu_print) || !defined(mu_printf)
    #ifdef MUVGC_NO_PRINT
        #ifndef mu_print
            #define mu_print(msg)
        #endif
        #ifndef mu_printf
            #define mu_printf(msg, ...)
        #endif
    #else
        #include <stdio.h>
        #ifndef mu_print
            #define mu_print printf
        #endif
        #ifndef mu_printf
            #define mu_printf printf
        #endif
    #endif
#endif

#ifndef mu_strncmp
	#include <string.h>
	#define mu_strncmp strncmp
#endif

#if !defined(int8_m)   || \
	!defined(uint8_m)  || \
	!defined(int16_m)  || \
	!defined(uint16_m) || \
	!defined(int32_m)  || \
	!defined(uint32_m) || \
	!defined(int64_m)  || \
	!defined(uint64_m)

	#include <stdint.h>

	#ifndef int8_m
		#define int8_m int8_t
	#endif
	#ifndef uint8_m
		#define uint8_m uint8_t
	#endif

	#ifndef int16_m
		#define int16_m int16_t
	#endif
	#ifndef uint16_m
		#define uint16_m uint16_t
	#endif

	#ifndef int32_m
		#define int32_m int32_t
	#endif
	#ifndef uint32_m
		#define uint32_m uint32_t
	#endif

	#ifndef int64_m
		#define int64_m int64_t
	#endif
	#ifndef uint64_m
		#define uint64_m uint64_t
	#endif

#endif

/* mus v3.1.0 header */

#ifndef MUS_H
	#define MUS_H

	#define MUS_VERSION_MAJOR 3
	#define MUS_VERSION_MINOR 1
	#define MUS_VERSION_PATCH 0

	#ifndef MUDEF
	    #ifdef MU_STATIC
	        #define MUDEF static
	    #else
	        #define MUDEF extern
	    #endif
	#endif

	#if !defined(int64_m)

	    #include <stdint.h>

	    #ifndef int64_m
	        #define int64_m int64_t
	    #endif

	#endif

	#ifndef size_m
	    #include <stddef.h>
	    #define size_m size_t
	#endif

	#ifndef wchar_m
	    #include <wchar.h>
	    #define wchar_m wchar_t
	#endif

	#ifndef MU_NULL
	    #define MU_NULL 0
	#endif

	#ifndef MU_BOOL
	    #define MU_BOOL
	    typedef enum { MU_FALSE, MU_TRUE } muBool;
	#endif

	typedef enum { MU_STRING_TYPE_CHAR, MU_STRING_TYPE_WCHAR } muStringType;
	typedef struct {
	    char* s;
	    wchar_m* ws;
	    muStringType type;
	    size_m size;
	    size_m len;
	} muString;

	/* muString */

	MUDEF size_m mu_string_strlen(muString s);

	MUDEF muString mu_string_create (char* s);
	MUDEF muString mu_wstring_create(wchar_m* ws);

	MUDEF muString mu_string_destroy(muString str);

	MUDEF muString mu_string_size_check(muString str, size_m size);

	MUDEF muString mu_string_delete(muString str, size_m beg, size_m end);

	MUDEF muString mu_string_insert (muString str, char* insert,    size_m i);
	MUDEF muString mu_wstring_insert(muString str, wchar_m* insert, size_m i);

	MUDEF muString mu_string_insert_integer (muString str, int64_m n, size_m i);
	MUDEF muString mu_wstring_insert_integer(muString str, int64_m n, size_m i);

	MUDEF muString mu_string_insert_float (muString str, double n, size_m max_decimals, size_m i);
	MUDEF muString mu_wstring_insert_float(muString str, double n, size_m max_decimals, size_m i);

	MUDEF muString mu_string_replace (muString str, char* find,    char* replace,    size_m beg, size_m end);
	MUDEF muString mu_wstring_replace(muString str, wchar_m* find, wchar_m* replace, size_m beg, size_m end);

	MUDEF muString mu_string_to_lowercase(muString str, size_m beg, size_m end);
	MUDEF muString mu_string_to_uppercase(muString str, size_m beg, size_m end);

	/* string */

	MUDEF muBool mu_here (char* str,    char* check,    size_m i);
	MUDEF muBool mu_where(wchar_m* str, wchar_m* check, size_m i);

	MUDEF muBool mu_has (char* str,    char* find,    size_m beg, size_m end);
	MUDEF muBool mu_whas(wchar_m* str, wchar_m* find, size_m beg, size_m end);

	/* character conversion */

	MUDEF int mu_wstring_to_string(char* dest,    wchar_m* src, size_m dest_len);
	MUDEF int mu_string_to_wstring(wchar_m* dest, char* src,    size_m dest_len);

	/* uppercase/lowercase */

	MUDEF char    mu_char_to_lowercase (char c);
	MUDEF wchar_m mu_wchar_to_lowercase(wchar_m c);

	MUDEF char    mu_char_to_uppercase (char c);
	MUDEF wchar_m mu_wchar_to_uppercase(wchar_m c);

	MUDEF muBool mu_char_is_lowercase (char c);
	MUDEF muBool mu_wchar_is_lowercase(wchar_m c);

	MUDEF muBool mu_char_is_uppercase (char c);
	MUDEF muBool mu_wchar_is_uppercase(wchar_m c);

	/* numbers */

	MUDEF int   mu_integer_to_string (int64_m n, char* dest,    size_m dest_len);
	MUDEF int   mu_integer_to_wstring(int64_m n, wchar_m* dest, size_m dest_len);

	MUDEF int   mu_float_to_string (double n, size_m max_decimals, char* dest,    size_m dest_len);
MUDEF int   mu_float_to_wstring(double n, size_m max_decimals, wchar_m* dest, size_m dest_len);

#endif /* MUS_H */

/* defines */

#ifndef muResult
	#define muResult muBool
	#define MU_FAILURE MU_FALSE
	#define MU_SUCCESS MU_TRUE
#endif

#ifndef MU_NULL_PTR
	#define MU_NULL_PTR 0
#endif

/* enums */

enum muVGCShader {
	MUVGC_VERTEX,
	MUVGC_TESSELLATION_CONTROL,
	MUVGC_TESSELLATION_EVALUATION,
	MUVGC_GEOMETRY,
	MUVGC_FRAGMENT,
	MUVGC_COMPUTE
};
typedef enum muVGCShader muVGCShader;

/* functions */

MUDEF muString mu_compile_vulkan_glsl(muResult* result, const char* code, muVGCShader shader);

#ifdef __cplusplus
}
#endif

#endif /* MUVGC_H */

#ifdef MUVGC_IMPLEMENTATION

#ifdef __cplusplus
extern "C" { // }
#endif

#define MUS_IMPLEMENTATION
/* mus v3.1.0 implementation */

#ifdef MUS_IMPLEMENTATION

	#if !defined(mu_malloc)    || \
	    !defined(mu_free)      || \
	    !defined(mu_realloc)   || \
	    !defined(mu_mbstowcs)  || \
	    !defined(mu_mbsrtowcs) || \
	    !defined(mu_wcstombs)  || \
	    !defined(mu_wcsrtombs)

	    #include <stdlib.h>
	    #ifndef mu_malloc
	        #define mu_malloc malloc
	    #endif
	    #ifndef mu_free
	        #define mu_free free
	    #endif
	    #ifndef mu_realloc
	        #define mu_realloc realloc
	    #endif
	    #ifndef mu_mbstowcs
	        #define mu_mbstowcs mbstowcs
	    #endif
	    #ifndef mu_mbsrtowcs
	        #define mu_mbsrtowcs mbsrtowcs
	    #endif
	    #ifndef mu_wcstombs
	        #define mu_wcstombs wcstombs
	    #endif
	    #ifndef mu_wcsrtombs
	        #define mu_wcsrtombs wcsrtombs
	    #endif
	#endif

	#if !defined(mu_strlen) || !defined(mu_wstrlen)
	    #ifndef mu_strlen
	        #include <string.h>
	        #define mu_strlen strlen
	    #endif
	    #ifndef mu_wstrlen
	        #include <wchar.h>
	        #define mu_wstrlen wcslen
	    #endif
	#endif

	#if !defined(mu_snprintf)

	    #include <stdio.h>

	    #ifndef mu_snprintf
	        #define mu_snprintf snprintf
	    #endif

	#endif

	// not sure if multi-byte state being null is fully safe

	MUDEF int mu_wstring_to_string(char* dest, wchar_m* src, size_m dest_len) {
	    if (dest == MU_NULL) return (size_m)mu_wcsrtombs(MU_NULL, (const wchar_m**)&src, 1, MU_NULL);
	    return (size_m)mu_wcstombs(dest, src, dest_len);
	}
	MUDEF int mu_string_to_wstring(wchar_m* dest, char* src, size_m dest_len) {
	    if (dest == MU_NULL) return (size_m)mu_mbsrtowcs(MU_NULL, (const char**)&src, 1, MU_NULL);
	    return (size_m)mu_mbstowcs(dest, src, dest_len);
	}

	MUDEF size_m mu_string_strlen(muString s) {
	    return s.len;
	}

	MUDEF muString mu_string_create(char* s) {
	    muString str;
	    str.len = mu_strlen(s);
	    str.size = (sizeof(char) * (str.len)) * 2;
	    str.s = mu_malloc(str.size);
	    str.ws = 0;
	    str.type = MU_STRING_TYPE_CHAR;
	    for (size_m i = 0; i < str.len; i++) {
	        str.s[i] = s[i];
	    }
	    str.s[str.len] = '\0';
	    return str;
	}
	MUDEF muString mu_wstring_create(wchar_m* ws) {
	    muString str;
	    str.len = mu_wstrlen(ws);
	    str.size = (sizeof(wchar_m) * (str.len)) * 2;
	    str.ws = mu_malloc(str.size);
	    str.s = 0;
	    str.type = MU_STRING_TYPE_WCHAR;
	    for (size_m i = 0; i < str.len; i++) {
	        str.ws[i] = ws[i];
	    }
	    str.ws[str.len] = '\0';
	    return str;
	}

	MUDEF muString mu_string_destroy(muString str) {
	    if (str.s) mu_free(str.s);
	    str.s = 0;
	    if (str.ws) mu_free(str.ws);
	    str.ws = 0;
	    return str;
	}

	MUDEF muString mu_string_size_check(muString str, size_m size) {
	    muBool resized = MU_FALSE;
	    while (str.size < size) {
	        str.size *= 2;
	        resized = MU_TRUE;
	    }
	    if (resized == MU_TRUE) {
	        if (str.type == MU_STRING_TYPE_CHAR) {
	            str.s = mu_realloc(str.s, str.size);
	        } else {
	            str.ws = mu_realloc(str.ws, str.size);
	        }
	    }
	    return str;
	}

	MUDEF muBool mu_here(char* str, char* check, size_m i) {
	    if (str[i] != check[0]) return MU_FALSE;
	    size_m check_len = mu_strlen(check);
	    size_m str_len = mu_strlen(str);
	    for (size_m j = 0; j < check_len; j++) {
	        if (i+j >= str_len || str[i+j] != check[j]) {
	            return MU_FALSE;
	        }
	    }
	    return MU_TRUE;
	}
	MUDEF muBool mu_where(wchar_m* str, wchar_m* check, size_m i) {
	    if (str[i] != check[0]) return MU_FALSE;
	    size_m check_len = mu_wstrlen(check);
	    size_m str_len = mu_wstrlen(str);
	    for (size_m j = 0; j < check_len; j++) {
	        if (i+j >= str_len || str[i+j] != check[j]) {
	            return MU_FALSE;
	        }
	    }
	    return MU_TRUE;
	}

	MUDEF muBool mu_has(char* str, char* find, size_m beg, size_m end) {
	    size_m find_len = mu_strlen(find);
	    for (size_m i = beg; i + find_len < end; i++) {
	        muBool found = MU_TRUE;
	        for (size_m j = 0; j < find_len; j++) {
	            if (str[i+j] != find[j]) found = MU_FALSE;
	        }
	        if (found == MU_TRUE) return MU_TRUE;
	    }
	    return MU_FALSE;
	}
	MUDEF muBool mu_whas(wchar_m* str, wchar_m* find, size_m beg, size_m end) {
	    size_m find_len = mu_wstrlen(find);
	    for (size_m i = beg; i + find_len < end; i++) {
	        muBool found = MU_TRUE;
	        for (size_m j = 0; j < find_len; j++) {
	            if (str[i+j] != find[j]) found = MU_FALSE;
	        }
	        if (found == MU_TRUE) return MU_TRUE;
	    }
	    return MU_FALSE;
	}

	MUDEF muString mu_string_delete(muString str, size_m beg, size_m end) {
	    for (size_m i = end; i < mu_string_strlen(str) + 1; i++) {
	        if (str.type == MU_STRING_TYPE_CHAR) {
	            str.s[i-(end-beg)] = str.s[i];
	        } else {
	            str.ws[i-(end-beg)] = str.ws[i];
	        }
	    }
	    str.len -= (end - beg);
	    return str;
	}

	MUDEF muString mu_string_insert(muString str, char* insert, size_m i) {
	    if (str.type == MU_STRING_TYPE_WCHAR) {
	        size_m size = mu_string_to_wstring(MU_NULL, insert, 0);
	        wchar_m* insert_w = mu_malloc(size * sizeof(wchar_m));
	        mu_string_to_wstring(insert_w, insert, size);
	        str = mu_wstring_insert(str, insert_w, i);
	        mu_free(insert_w);
	        return str;
	    }
	    size_m insert_len = mu_strlen(insert);
	    str = mu_string_size_check(str, sizeof(char) * (mu_string_strlen(str) + insert_len + 1));
	    for (size_m j = mu_strlen(str.s); i < j+1; j--) {
	        if (str.type == MU_STRING_TYPE_CHAR) {
	            str.s[j+insert_len] = str.s[j];
	        } else {
	            str.ws[j+insert_len] = str.ws[j];
	        }
	    }
	    for (size_m j = 0; j < insert_len; j++) {
	        if (str.type == MU_STRING_TYPE_CHAR) {
	            str.s[i+j] = insert[j];
	        } else {
	            str.ws[i+j] = insert[j];
	        }
	    }
	    str.len += insert_len;
	    return str;
	}
	MUDEF muString mu_wstring_insert(muString str, wchar_m* insert, size_m i) {
	    if (str.type == MU_STRING_TYPE_CHAR) {
	        size_m size = mu_wstring_to_string(MU_NULL, insert, 0);
	        char* insert_c = mu_malloc(size * sizeof(char));
	        mu_wstring_to_string(insert_c, insert, size);
	        str = mu_string_insert(str, insert_c, i);
	        mu_free(insert_c);
	        return str;
	    }
	    size_m insert_len = mu_wstrlen(insert);
	    str = mu_string_size_check(str, sizeof(wchar_m) * (mu_string_strlen(str) + insert_len + 1));
	    for (size_m j = mu_string_strlen(str); i < j+1; j--) {
	        if (str.type == MU_STRING_TYPE_CHAR) {
	            str.s[j+insert_len] = str.s[j];
	        } else {
	            str.ws[j+insert_len] = str.ws[j];
	        }
	    }
	    for (size_m j = 0; j < insert_len; j++) {
	        if (str.type == MU_STRING_TYPE_CHAR) {
	            str.s[i+j] = insert[j];
	        } else {
	            str.ws[i+j] = insert[j];
	        }
	    }
	    str.len += insert_len;
	    return str;
	}

	MUDEF muString mu_string_insert_integer(muString str, int64_m n, size_m i) {
	    size_m len = mu_integer_to_string(n, MU_NULL, 0);
	    len++;
	    char* s = mu_malloc(len * sizeof(char));
	    mu_integer_to_string(n, s, len);
	    s[len-1] = 0;
	    str = mu_string_insert(str, s, i);
	    mu_free(s);
	    return str;
	}
	MUDEF muString mu_wstring_insert_integer(muString str, int64_m n, size_m i) {
	    size_m len = mu_integer_to_wstring(n, MU_NULL, 0);
	    len++;
	    wchar_m* s = mu_malloc(len * sizeof(wchar_m));
	    mu_integer_to_wstring(n, s, len);
	    s[len-1] = 0;
	    str = mu_wstring_insert(str, s, i);
	    mu_free(s);
	    return str;
	}

	MUDEF muString mu_string_insert_float(muString str, double n, size_m max_decimals, size_m i) {
	    size_m len = mu_float_to_string(n, max_decimals, MU_NULL, 0);
	    len++;
	    char* s = mu_malloc(len * sizeof(char));
	    mu_float_to_string(n, max_decimals, s, len);
	    s[len-1] = 0;
	    str = mu_string_insert(str, s, i);
	    mu_free(s);
	    return str;
	}
	MUDEF muString mu_wstring_insert_float(muString str, double n, size_m max_decimals, size_m i) {
	    size_m len = mu_float_to_wstring(n, max_decimals, MU_NULL, 0);
	    len++;
	    wchar_m* s = mu_malloc(len * sizeof(wchar_m));
	    mu_float_to_wstring(n, max_decimals, s, len);
	    s[len-1] = 0;
	    str = mu_wstring_insert(str, s, i);
	    mu_free(s);
	    return str;
	}

	MUDEF muString mu_string_replace(muString str, char* find, char* replace, size_m beg, size_m end) {
	    if (str.type == MU_STRING_TYPE_WCHAR) {
	        size_m find_size = mu_string_to_wstring(MU_NULL, find, 0);
	        size_m replace_size = mu_string_to_wstring(MU_NULL, replace, 0);
	        wchar_m* find_w = mu_malloc(find_size * sizeof(wchar_m));
	        wchar_m* replace_w = mu_malloc(replace_size * sizeof(wchar_m));
	        mu_string_to_wstring(find_w, find, find_size);
	        mu_string_to_wstring(replace_w, replace, replace_size);
	        str = mu_wstring_replace(str, find_w, replace_w, beg, end);
	        mu_free(find_w);
	        mu_free(replace_w);
	        return str;
	    }
	    size_m find_len = mu_strlen(find);
	    size_m replace_len = mu_strlen(replace);
	    size_m len_dif = find_len - replace_len;
	    if (replace_len > find_len) len_dif = replace_len - find_len;
	    for (size_m i = beg; i < end + 1 && i < mu_string_strlen(str); i++) {
	        if (mu_here(str.s, find, i) == MU_TRUE) {
	            str = mu_string_delete(str, i, i + find_len);
	            if (replace_len > 0) {
	                str = mu_string_insert(str, replace, i);
	            }
	            end -= len_dif;
	        }
	    }
	    str.len = mu_strlen(str.s);
	    return str;
	}
	MUDEF muString mu_wstring_replace(muString str, wchar_m* find, wchar_m* replace, size_m beg, size_m end) {
	    if (str.type == MU_STRING_TYPE_CHAR) {
	        size_m find_size = mu_wstring_to_string(MU_NULL, find, 0);
	        size_m replace_size = mu_wstring_to_string(MU_NULL, replace, 0);
	        char* find_c = mu_malloc(find_size * sizeof(char));
	        char* replace_c = mu_malloc(replace_size * sizeof(char));
	        mu_wstring_to_string(find_c, find, find_size);
	        mu_wstring_to_string(replace_c, replace, replace_size);
	        str = mu_string_replace(str, find_c, replace_c, beg, end);
	        mu_free(find_c);
	        mu_free(replace_c);
	        return str;
	    }
	    size_m find_len = mu_wstrlen(find);
	    size_m replace_len = mu_wstrlen(replace);
	    size_m len_dif = find_len - replace_len;
	    if (replace_len > find_len) len_dif = replace_len - find_len;
	    for (size_m i = beg; i < end + 1 && i < mu_string_strlen(str); i++) {
	        if (mu_where(str.ws, find, i) == MU_TRUE) {
	            str = mu_string_delete(str, i, i + find_len);
	            if (replace_len > 0) {
	                str = mu_wstring_insert(str, replace, i);
	            }
	            end -= len_dif;
	        }
	    }
	    str.len = mu_wstrlen(str.ws);
	    return str;
	}

	MUDEF muString mu_string_to_lowercase(muString str, size_m beg, size_m end) {
	    for (size_m i = beg; i < str.len && i < end + 1; i++) {
	        if (str.type == MU_STRING_TYPE_CHAR) {
	            str.s[i] = mu_char_to_lowercase(str.s[i]);
	        } else {
	            str.ws[i] = mu_wchar_to_lowercase(str.ws[i]);
	        }
	    }
	    return str;
	}
	MUDEF muString mu_string_to_uppercase(muString str, size_m beg, size_m end) {
	    for (size_m i = beg; i < str.len && i < end + 1; i++) {
	        if (str.type == MU_STRING_TYPE_CHAR) {
	            str.s[i] = mu_char_to_uppercase(str.s[i]);
	        } else {
	            str.ws[i] = mu_wchar_to_uppercase(str.ws[i]);
	        }
	    }
	    return str;
	}

	// did this manually because C standards suck
	// last updated 16 September 2023, covers 0 -> 65533
	// https://en.wikipedia.org/wiki/List_of_Unicode_characters
	// https://www.ssec.wisc.edu/~tomw/java/unicode.html

	MUDEF char mu_char_to_lowercase(char c) {
	    if (c >= 65 && c <= 90) c += 32;
	    return c;
	}
	MUDEF wchar_m mu_wchar_to_lowercase(wchar_m c) {
	    if (
	    // latin alphabet
	        (c >= 65 && c <= 90) ||
	    // latin-1 supplement
	        (c >= 192 && c <= 222 && c != 215) ||
	    // greek and coptic
	        (c >= 913 && c <= 939) ||
	    // cyrillic
	        (c >= 0x0410 && c <= 0x042F) ||
	    // halfwidth and fullwidth forms
	        (c >= 65313 && c <= 65338)
	    ) {
	        return c + 32;
	    } else if (
	    // latin extended-a
	        (
	            (c >= 256 && c <= 310 && c % 2 == 0) || 
	            (c >= 313 && c <= 327 && c % 2 != 0) ||
	            (c >= 330 && c <= 376 && c % 2 == 0) ||
	            (c >= 377 && c <= 381 && c % 2 != 0)
	        ) ||
	    // latin extended-b
	        (
	            (c >= 461 && c <= 475 && c % 2 != 0) ||
	            (c >= 478 && c <= 494 && c % 2 == 0) ||
	            (c >= 504 && c <= 542 && c % 2 == 0) ||
	            (c >= 546 && c <= 562 && c % 2 == 0) ||
	            (c >= 582 && c <= 590 && c % 2 == 0)
	        ) ||
	    // greek and coptic
	        (
	            (c >= 984 && c <= 1006 && c % 2 == 0)
	        ) ||
	    // cyrillic
	        (
	            (c >= 0x0460 && c <= 0x0480 && c % 2 == 0) ||
	            (c >= 0x048A && c <= 0x04BE && c % 2 == 0) ||
	            (c >= 0x04C1 && c <= 0x04CD && c % 2 != 0) ||
	            (c >= 0x04D0 && c <= 0x04FE && c % 2 == 0) ||
	            // cyrillic supplement
	            (c >= 0x0500 && c <= 0x052E && c % 2 == 0)
	        ) ||
	    // latin extended additional
	        (
	            (c >= 7680 && c <= 7828 && c % 2 == 0) ||
	            (c >= 7840 && c <= 7928 && c % 2 == 0)
	        )
	    ) {
	        return c + 1;
	    } else if (
	    // cyrillic
	        (
	            (c >= 0x0400 && c <= 0x040F)
	        )
	    ) {
	        return c + 80;
	    } else if (
	    // armenian
	        (
	            (c >= 0x0530 && c <= 0x0558)
	        ) ||
	    // georgian
	        (
	            (c >= 0x10A0 && c <= 0x10CF)
	        )
	    ) {
	        return c + 48;
	    } else if (
	    // greek extended
	        (
	            (c >= 7944 && c <= 7951) || (c >= 7960 && c <= 7965) || (c >= 7976 && c <= 7983) || (c >= 7992 && c <= 7999) ||
	            (c >= 8008 && c <= 8013) || (c >= 8025 && c <= 8031) || (c >= 8040 && c <= 8047) || (c >= 8072 && c <= 8079) ||
	            (c >= 8088 && c <= 8095) || (c >= 8104 && c <= 8111) || (c >= 8120 && c <= 8124)
	        )
	    ) {
	        return c - 8;
	    } else if (
	    // enclosed alphanumerics
	        (
	            (c >= 9398 && c <= 9423)
	        )
	    ) {
	        return c + 26;
	    }
	    switch (c) {
	    default: break;
	    // odd latin extended-b / ipa extensions
	    case 386: case 388: case 391: case 395: case 401: case 408: case 416: case 418: case 420: case 423: case 428: case 431: 
	    case 435: case 437: case 440: case 444: case 453: case 456: case 459: case 498: case 500: case 571: case 577: return c+1; break;
	    case 384: return 579; break;
	    case 385: return 595; break;
	    case 390: return 596; break;
	    case 393: return 598; break;
	    case 394: return 599; break;
	    case 398: return 600; break;
	    case 399: return 601; break;
	    case 400: return 603; break;
	    case 403: return 608; break;
	    case 404: return 611; break;
	    case 406: return 617; break;
	    case 407: return 616; break;
	    case 412: return 623; break;
	    case 413: return 626; break;
	    case 425: return 643; break;
	    case 430: return 648; break;
	    case 433: return 650; break;
	    case 434: return 641; break;
	    case 439: return 658; break;
	    case 452: return 454; break;
	    case 455: return 457; break;
	    case 458: return 460; break;
	    case 497: return 499; break;
	    case 544: return 414; break;
	    case 573: return 410; break;
	    case 579: return 384; break;
	    case 580: return 649; break;
	    case 581: return 652; break;

	    // odd greek and coptic
	    case 880: case 882: case 886: case 1015: case 1018: return c+1; break;
	    case 895: return 1011; break;
	    case 904: case 905: case 906: return c+37; break;
	    case 908: case 910: case 911: return c+64; break;
	    case 975: return 983; break;
	    case 1012: return 977; break;
	    case 1017: return 1010; break;
	    case 1021: case 1022: case 1023: return c-130; break;

	    // odd greek extended
	    // this is so unsorted it makes my room look like a masterpiece
	    case 8136: case 8137: case 8138: case 8139: return c-86; break;
	    case 8140: return 8131; break;
	    case 8152: return 8144; break;
	    case 8153: return 8145; break;
	    case 8154: case 8155: return c-100; break;
	    case 8168: return 8160; break;
	    case 8169: return 8161; break;
	    case 8170: return 8058; break;
	    case 8171: return 8059; break;
	    case 8172: return 8165; break;
	    case 8184: case 8185: return c-128; break;
	    case 8187: return 8061; break;
	    }
	    return c;
	}
	MUDEF char mu_char_to_uppercase(char c) {
	    if (c >= 97 && c <= 122) c -= 32;
	    return c;
	}
	MUDEF wchar_m mu_wchar_to_uppercase(wchar_m c) {
	    if (
	    // latin alphabet
	        (c >= 97 && c <= 122) ||
	    // latin-1 supplement
	        (c >= 224 && c <= 255 && c != 247) ||
	    // greek and coptic
	        (c >= 945 && c <= 971) ||
	    // cyrillic
	        (c >= (0x0410 + 32) && c <= (0x042F + 32)) ||
	    // halfwidth and fullwidth forms
	        (c >= (65313 + 32) && c <= (65338 + 32))
	    ) {
	        return c - 32;
	    } else if (
	    // latin extended-a
	        (
	            (c >= 257 && c <= 311 && c % 2 != 0) || 
	            (c >= 312 && c <= 328 && c % 2 == 0) ||
	            (c >= 329 && c <= 375 && c % 2 != 0) ||
	            (c >= 378 && c <= 382 && c % 2 == 0)
	        ) ||
	    // latin extended-b
	        (
	            (c >= 462 && c <= 476 && c % 2 == 0) ||
	            (c >= 479 && c <= 495 && c % 2 != 0) ||
	            (c >= 505 && c <= 543 && c % 2 != 0) ||
	            (c >= 547 && c <= 563 && c % 2 != 0) ||
	            (c >= 583 && c <= 591 && c % 2 != 0)
	        ) ||
	    // greek and coptic
	        (
	            (c >= 985 && c <= 1007 && c % 2 != 0)
	        ) ||
	    // cyrillic
	        (
	            (c >= 0x0461 && c <= 0x0481 && c % 2 != 0) ||
	            (c >= 0x048B && c <= 0x04BF && c % 2 != 0) ||
	            (c >= 0x04C2 && c <= 0x04CE && c % 2 == 0) ||
	            (c >= 0x04D1 && c <= 0x04FF && c % 2 != 0) ||
	            // cyrillic supplement
	            (c >= 0x0501 && c <= 0x052F && c % 2 != 0)
	        ) ||
	    // latin extended additional
	        (
	            (c >= 7681 && c <= 7829 && c % 2 != 0) ||
	            (c >= 7841 && c <= 7929 && c % 2 != 0)
	        )
	    ) {
	        return c - 1;
	    } else if (
	    // cyrillic
	        (
	            (c >= (0x0400+80) && c <= (0x040F+80))
	        )
	    ) {
	        return c - 80;
	    } else if (
	    // armenian
	        (
	            (c >= (0x0530+48) && c <= (0x0558+48))
	        ) ||
	    // georgian
	        (
	            (c >= (0x10A0+48) && c <= (0x10CF+48))
	        )
	    ) {
	        return c - 48;
	    } else if (
	    // greek extended
	        (
	            (c >= (7944-8) && c <= (7951-8)) || (c >= (7960-8) && c <= (7965-8)) || (c >= (7976-8) && c <= (7983-8)) || (c >= (7992-8) && c <= (7999-8)) ||
	            (c >= (8008-8) && c <= (8013-8)) || (c >= (8025-8) && c <= (8031-8)) || (c >= (8040-8) && c <= (8047-8)) || (c >= (8072-8) && c <= (8079-8)) ||
	            (c >= (8088-8) && c <= (8095-8)) || (c >= (8104-8) && c <= (8111-8)) || (c >= (8120-8) && c <= (8124-8))
	        )
	    ) {
	        return c + 8;
	    } else if (
	    // enclosed alphanumerics
	        (
	            (c >= (9398+26) && c <= (9423+26))
	        )
	    ) {
	        return c - 26;
	    }
	    switch (c) {
	    default: break;
	    // odd latin extended-b / ipa extensions
	    case 387: case 389: case 392: case 396: case 402: case 409: case 417: case 419: case 421: case 424: case 429: case 432: 
	    case 436: case 438: case 441: case 445: case 453: case 456: case 459: case 498: case 501: case 572: case 578: return c-1; break;
	    case 579: return 384; break;
	    case 595: return 385; break;
	    case 596: return 390; break;
	    case 598: return 393; break;
	    case 599: return 394; break;
	    case 600: return 398; break;
	    case 601: return 399; break;
	    case 603: return 400; break;
	    case 608: return 403; break;
	    case 611: return 404; break;
	    case 617: return 406; break;
	    case 616: return 407; break;
	    case 623: return 412; break;
	    case 626: return 413; break;
	    case 643: return 425; break;
	    case 648: return 430; break;
	    case 650: return 433; break;
	    case 641: return 434; break;
	    case 658: return 439; break;
	    case 454: return 452; break;
	    case 457: return 455; break;
	    case 460: return 458; break;
	    case 499: return 497; break;
	    case 414: return 544; break;
	    case 410: return 573; break;
	    case 384: return 579; break;
	    case 649: return 580; break;
	    case 652: return 581; break;

	    // odd greek and coptic
	    case 881: case 883: case 887: case 1016: case 1019: return c-1; break;
	    case 1011: return 895; break;
	    case 941: case 942: case 943: return c-37; break;
	    case 972: case 974: case 975: return c-64; break;
	    case 983: return 975; break;
	    case 977: return 1012; break;
	    case 1010: return 1017; break;
	    case 891: case 892: case 893: return c+130; break;

	    // odd greek extended
	    // this is so unsorted it makes my room look like a masterpiece
	    case 8050: case 8051: case 8052: case 8053: return c+86; break;
	    case 8131: return 8140; break;
	    case 8144: return 8152; break;
	    case 8145: return 8153; break;
	    case 8054: case 8055: return c+100; break;
	    case 8160: return 8168; break;
	    case 8161: return 8169; break;
	    case 8058: return 8170; break;
	    case 8059: return 8171; break;
	    case 8165: return 8172; break;
	    case 8056: case 8057: return c+128; break;
	    case 8061: return 8187; break;
	    }
	    return c;
	}

	// these funcs aren't entirely necessary
	MUDEF muBool mu_char_is_lowercase(char c) {
	    return c != mu_char_to_uppercase(c);
	}
	MUDEF muBool mu_wchar_is_lowercase(wchar_m c) {
	    return c != mu_wchar_to_uppercase(c);
	}
	MUDEF muBool mu_char_is_uppercase(char c) {
	    return c != mu_char_to_lowercase(c);
	}
	MUDEF muBool mu_wchar_is_uppercase(wchar_m c) {
	    return c != mu_wchar_to_lowercase(c);
	}

	MUDEF int mu_integer_to_string(int64_m n, char* dest, size_m dest_len) {
	    if (dest == MU_NULL) return mu_snprintf(MU_NULL, 0, "%ld", (long)n);
	    return mu_snprintf(dest, dest_len+1, "%ld", (long)n);
	}

	// would like to not have to convert here, but snwprintf isn't standard
	MUDEF int mu_integer_to_wstring(int64_m n, wchar_m* dest, size_m dest_len) {
	    if (dest == MU_NULL) return mu_snprintf(MU_NULL, 0, "%ld", (long)n);
	    size_m len = mu_integer_to_string(n, MU_NULL, 0);
	    char* s = mu_malloc(len * sizeof(char));
	    mu_integer_to_string(n, s, len);
	    for (size_m i = 0; i < dest_len; i++) {
	        dest[i] = (wchar_m)s[i];
	    }
	    free(s);
	    return 0;
	}

	MUDEF int mu_float_to_string(double n, size_m max_decimals, char* dest, size_m dest_len) {
	    if (max_decimals >= 10) max_decimals = 9;
	    char format[7] = "%0.0lf\0";
	    format[3] = '0' + max_decimals;
	    if (dest == MU_NULL) return mu_snprintf(MU_NULL, 0, format, n);
	    return mu_snprintf(dest, dest_len+1, format, n);
	}

	MUDEF int mu_float_to_wstring(double n, size_m max_decimals, wchar_m* dest, size_m dest_len) {
	    size_m len = mu_float_to_string(n, max_decimals, MU_NULL, 0);
	    if (dest == MU_NULL) return len;
	    char* s = mu_malloc(len * sizeof(char));
	    mu_float_to_string(n, max_decimals, s, len);
	    for (size_m i = 0; i < dest_len; i++) {
	        dest[i] = (wchar_m)s[i];
	    }
	    mu_free(s);
	    return 0;
}

#endif /* MUS_IMPLEMENTATION */

/* TO BE IMPLEMENTED IN MUS */

	muString mu_string_create_raw(char* s, size_m s_len) {
	    muString str;
	    str.len = s_len;
	    str.size = (sizeof(char) * (str.len)) * 2;
	    str.s = mu_malloc(str.size);
	    str.ws = 0;
	    str.type = MU_STRING_TYPE_CHAR;
	    for (size_m i = 0; i < str.len; i++) {
	        str.s[i] = s[i];
	    }
	    return str;
	}

	int64_m mu_get_integer_from_string(char* s, size_m len) {
		int64_m ret = 0;
		size_m i = 0;
		char mul = 1;
		while (i < len) {
			if (s[i] == '-') {
				if (ret != 0) {
					return ret;
				}
				mul *= -1;
			} else if (s[i] < '0' || s[i] > '9') {
				return ret;
			} else {
				ret = (ret*10) + (s[i] - '0');
			}
			i++;
		}
		return ret;
	}

	// might want to use memcpy, eh
	muString mu_string_insert_raw(muString str, char* insert, size_m insert_len, size_m i) {
	    str = mu_string_size_check(str, sizeof(char) * (mu_string_strlen(str) + insert_len + 1));
	    for (size_m j = mu_string_strlen(str); i < j+1; j--) {
	        if (str.type == MU_STRING_TYPE_CHAR) {
	            str.s[j+insert_len] = str.s[j];
	        } else {
	            str.ws[j+insert_len] = str.ws[j];
	        }
	    }
	    for (size_m j = 0; j < insert_len; j++) {
	        if (str.type == MU_STRING_TYPE_CHAR) {
	            str.s[i+j] = insert[j];
	        } else {
	            str.ws[i+j] = insert[j];
	        }
	    }
	    str.len += insert_len;
	    return str;
	}

/* CODE MOVEMENT/IDENTIFICATION FUNCTIONS */

	size_m muVGC_get_line_of_code(const char* s, size_m index) {
		size_m len = mu_strlen(s);
		size_m linecount = 1;
		for (size_m i = 0; i < len; i++) {
			if (s[i] == '\n') {
				linecount++;
			} else if (s[i] == '\\' && s[i+1] == '\n') {
				index += 2;
			}
			if (i == index) {
				return linecount;
			}
		}
		return linecount;
	}

	size_m muVGC_get_character(const char* s, size_m index) {
		size_m len = mu_strlen(s);
		size_m linecount = 0;
		size_m char_count = 0;
		for (size_m i = 0; i < len; i++) {
			char_count++;
			if (s[i] == '\n') {
				linecount++;
				char_count = 0;
			} else if (s[i] == '\\' && s[i+1] == '\n') {
				index += 2;
			}
			if (i == index) {
				return char_count;
			}
		}
		return char_count;
	}

	muBool muVGC_is_character_empty(char c) {
		return c == ' ' || c == '\\' || c == '\t' || c == '\n';
	}

	size_m muVGC_get_next_new_line(const char* s, size_m slen, size_m index) {
		if (index >= slen) {
			return slen;
		}
		while (index < slen && (s[index] != '\n')) {
			index++;
			if (index < slen && index > 0 && s[index] == '\n' && s[index-1] == '\\') {
				index++;
			}
		}
		return index;
	}

	size_m muVGC_get_next_non_empty_char(const char* s, size_m slen, size_m index) {
		if (index >= slen) {
			return slen;
		}
		while (index < slen && (s[index] == ' ' || s[index] == '\n' || s[index] == '\t')) {
			index++;
		}
		return index;
	}

	size_m muVGC_get_next_empty_char(const char* s, size_m slen, size_m index) {
		if (index >= slen) {
			return slen;
		}
		while (index < slen && s[index] != ' ' && s[index] != '\n' && s[index] != '\t') {
			index++;
		}
		return index;
	}

	size_m muVGC_get_next_non_space(const char* s, size_m slen, size_m index) {
		if (index >= slen) {
			return slen;
		}
		while (index < slen && s[index] == ' ') {
			index++;
		}
		return index;
	}

	uint32_m muVGC_get_word(const char* b) {
		const unsigned char* ub = (const unsigned char*)b;
		return ub[0] + (ub[1] << 8) + (ub[2] << 16) + (ub[3] << 24);
	}
	int16_m muVGC_get_halfword(const char* b) {
		const unsigned char* ub = (const unsigned char*)b;
		return ub[0] + (ub[1] << 8);
	}

	// Instruction sections

	size_m muVGC_hop_to_naming_section(muString bytecode) {
		for (size_m i = 20; i <= mu_string_strlen(bytecode);) {
			int instruction = muVGC_get_halfword(&bytecode.s[i]);
			int step = muVGC_get_halfword(&bytecode.s[i+2]);
			if (step == 0) {
				return 20;
			}

			// Go to OpSource call
			if (instruction == 3) {
				i += step * 4;
				instruction = muVGC_get_halfword(&bytecode.s[i]);
				step = muVGC_get_halfword(&bytecode.s[i+2]);

				// Go past all calls to:
				// OpSourceContinued, OpSource, OpSourceExtension, OpName, OpMemberName,
				// OpString, OpLine, OpNoLine, OpModuleProcessed
				while (i < mu_string_strlen(bytecode) && (
					(instruction >= 2 && instruction <= 8) || 
					(instruction == 317) || (instruction == 330))
				) {
					i += step * 4;
					instruction = muVGC_get_halfword(&bytecode.s[i]);
					step = muVGC_get_halfword(&bytecode.s[i+2]);
				}

				return i;
			}

			i += step * 4;
		}

		return 20;
	}

	size_m muVGC_hop_to_decoration_section(muString bytecode) {
		for (size_m i = muVGC_hop_to_naming_section(bytecode); i <= mu_string_strlen(bytecode);) {
			int instruction = muVGC_get_halfword(&bytecode.s[i]);
			int step = muVGC_get_halfword(&bytecode.s[i+2]);

			// Go past all calls to:
			// OpDecorate, OpMemberDecorate, OpDecorationGroup, OpGroupDecorate, OpGroupMemberDecorate,
			// OpDecorateId, OpDecorateString, OpMemberDecorateString
			while (i < mu_string_strlen(bytecode) && (
				(instruction >= 71 && instruction <= 75) || 
				(instruction == 332) || (instruction == 5632) || 
				(instruction == 5633))
			) {
				i += step * 4;
				instruction = muVGC_get_halfword(&bytecode.s[i]);
				step = muVGC_get_halfword(&bytecode.s[i+2]);
			}

			return i;

			//i += step * 4;
		}

		return 20;
	}

	size_m muVGC_hop_to_variable_section(muString bytecode) {
		for (size_m i = muVGC_hop_to_decoration_section(bytecode); i <= mu_string_strlen(bytecode);) {
			int instruction = muVGC_get_halfword(&bytecode.s[i]);
			int step = muVGC_get_halfword(&bytecode.s[i+2]);

			// Go past all calls to:
			// Type-Declaration Instructions
			// Constant-Creation Instructions
			// Memory Instructions
			while (i < mu_string_strlen(bytecode) && (
				(instruction >= 19 && instruction <= 39) || 
				(instruction == 322) || (instruction == 327) ||
				(instruction == 4456) || (instruction == 6086) ||
				(instruction == 6090) ||

				(instruction >= 41 && instruction <= 46) ||
				(instruction >= 48 && instruction <= 52) ||
				(instruction == 6091) || (instruction == 6092) ||

				(instruction >= 59 && instruction <= 70) || 
				(instruction >= 401 && instruction <= 403) ||
				(instruction == 4457) || (instruction == 4458))
			) {
				i += step * 4;
				instruction = muVGC_get_halfword(&bytecode.s[i]);
				step = muVGC_get_halfword(&bytecode.s[i+2]);
			}

			return i;

			//i += step * 4;
		}

		return 20;
	}

	size_m muVGC_hop_to_function_section(muString bytecode) {
		return mu_string_strlen(bytecode);
	}

/* CODE MODIFICATION FUNCS */

	void muVGC_clear_code(char* s, size_m beg, size_m end) {
		for (size_m i = beg; i < end; i++) {
			if (s[i] != '\n') {
				s[i] = ' ';
			}
		}
	}

	#define MUVGC_2_BYTE_LE(n) (n)&0xFF,((n)>>8)&0xFF
	#define MUVGC_2_BYTE_LE_SET(a, n, i) (a)[(i)]=(n)&0xFF;(a)[(i)+1]=((n)>>8)&0xFF;
	#define MUVGC_4_BYTE_LE(n) (n)&0xFF,((n)>>8)&0xFF,((n)>>16)&0xFF,((n)>>24)&0xFF
	#define MUVGC_4_BYTE_LE_SET(a, n, i) (a)[(i)]=(n)&0xFF;(a)[(i)+1]=((n)>>8)&0xFF;(a)[(i)+2]=((n)>>16)&0xFF;(a)[(i)+3]=((n)>>24)&0xFF;

/* PRINT FUNCS */

	void muVGC_print_syntax_error(const char* s, size_m index) {
		mu_print("[muVGC] Syntax error (line %zu, character %zu); ", muVGC_get_line_of_code(s, index), muVGC_get_character(s, index));
	}

/* COMMENT HANDLING */

	muResult muVGC_error_check_comments(muString code) {
		for (size_m i = 0; i < mu_string_strlen(code); i++) {
			size_m orig_i = i;
			if (mu_here(code.s, "/*", i)) {
				i += 2;
				while ((i < mu_string_strlen(code) && (mu_here(code.s, "*/", i) == MU_FALSE))) {
					i++;
				}
				if (i >= mu_string_strlen(code)) {
					muVGC_print_syntax_error(code.s, orig_i);
					mu_print("comment beginning with '/*' never has a corresponding end '*/'\n");
					return MU_FAILURE;
				}
			}
		}

		return MU_SUCCESS;
	}

	void muVGC_empty_comments(muString code) {
		for (size_m i = 0; i < mu_string_strlen(code); i++) {
			if (mu_here(code.s, "/*", i)) {
				while ((i < mu_string_strlen(code) && (mu_here(code.s, "*/", i) == MU_FALSE))) {
					if (code.s[i] != '\n') {
						code.s[i] = ' ';
					}
					i++;
				}
				code.s[i] = ' ';
				code.s[i+1] = ' ';
			}
			if (mu_here(code.s, "//", i)) {
				size_m end = muVGC_get_next_new_line(code.s, mu_string_strlen(code), i);
				if (end >= mu_string_strlen(code)) {
					end--;
				}
				for (size_m j = i; j <= end; j++) {
					if (code.s[j] != '\n') {
						code.s[j] = ' ';
					}
				}
			}
		}
	}

	muString muVGC_handle_line_continuation(muResult* result, muString code) {
		for (int64_m i = 0; i < mu_string_strlen(code); i++) {
			if (mu_here(code.s, "\\\n", i)) {
				code = mu_string_delete(code, i, i+2);
				i--;
			} else if (code.s[i] == '\\') {
				// This is a little bit strict, as many like to put a space or two after,
				// but eh
				muVGC_print_syntax_error(code.s, i);
				mu_print("incorrect usage of line continuation, expected newline to follow after '\\'\n");
				*result = MU_FAILURE;
				return code;
			}
		}

		return code;
	}

	muString muVGC_handle_comments(muResult* result, muString code) {
		if (muVGC_error_check_comments(code) != MU_SUCCESS) {
			*result = MU_FAILURE;
			return code;
		}

		muVGC_empty_comments(code);

		return muVGC_handle_line_continuation(result, code);
	}

/* MACRO HANDLING */

	muResult muVGC_is_version_valid(muString code, const char* og, size_m* number_index, size_m* beg, size_m* end) {
		size_m i = muVGC_get_next_non_empty_char(code.s, mu_string_strlen(code), 0);
		if (i >= mu_string_strlen(code)) {
			muVGC_print_syntax_error(og, 0);
			mu_print("string passed contains no readable code\n");
			return MU_FAILURE;
		}

		*beg = i;
		if (code.s[i] != '#') {
			muVGC_print_syntax_error(og, i);
			mu_print("expected '#' as first token to specify version\n");
			return MU_FAILURE;
		}

		i = muVGC_get_next_non_space(code.s, mu_string_strlen(code), i+1);
		if ((i+8 >= mu_string_strlen(code)) || (mu_strncmp(&code.s[i], "version ", 8) != 0)) {
			muVGC_print_syntax_error(og, i);
			mu_print("expected 'version' after token '#'\n");
			return MU_FAILURE;
		}

		i = muVGC_get_next_non_space(code.s, mu_string_strlen(code), i+7);
		*number_index = i;
		if (i >= mu_string_strlen(code) || (code.s[i] >= '0' && code.s[i] <= '9') == MU_FALSE) {
			muVGC_print_syntax_error(og, i);
			mu_print("expected number after '#version'\n");
			return MU_FAILURE;
		}

		size_m end_i = muVGC_get_next_empty_char(code.s, mu_string_strlen(code), i);
		for (size_m j = i; j < end_i; j++) {
			if ((code.s[j] >= '0' && code.s[j] <= '9') == MU_FALSE) {
				muVGC_print_syntax_error(og, i);
				mu_print("expected number after '#version'\n");
				return MU_FAILURE;
			}
		}
		i = end_i;
		*end = end_i;

		i = muVGC_get_next_non_space(code.s, mu_string_strlen(code), i);
		if (i >= mu_string_strlen(code) || code.s[i] == '\n') {
			return MU_SUCCESS;
		}

		end_i = muVGC_get_next_empty_char(code.s, mu_string_strlen(code), i);
		if ((end_i-i != 4) || (mu_strncmp(&code.s[i], "core", 4) != 0)) {
			muVGC_print_syntax_error(og, i);
			mu_print("expected anything after '#version N' to be 'core'\n");
			return MU_FAILURE;
		}

		i = end_i;
		end_i = muVGC_get_next_new_line(code.s, mu_string_strlen(code), end_i);
		for (size_m j = i; j < end_i; j++) {
			if (muVGC_is_character_empty(code.s[j]) == MU_FALSE) {
				muVGC_print_syntax_error(og, j);
				mu_print("expected only newline after version directive\n");
				return MU_FAILURE;
			}
		}
		*end = end_i;

		return MU_SUCCESS;
	}

	muString muVGC_macro_handle_first_words(muResult* result, muString bytecode) {
		char first_words[] = {
			// Magic number
			0x03, 0x02, 0x23, 0x07,
			// Version
			0x00, 0x00, 0x01, 0x00,
			// Generator number (using glslc's for now)
			0x0b, 0x00, 0x0d, 0x00,
			// Bound
			0x00, 0x00, 0x00, 0x00,
			// Instruction schema
			0x00, 0x00, 0x00, 0x00
		};
		bytecode = mu_string_insert_raw(bytecode, first_words, sizeof(first_words), 0);

		return bytecode;
	}

	muString muVGC_macro_handle_first_instructions(muResult* result, muString bytecode, muVGCShader shader, int64_m version) {
		char shader_capability = 0, execution_model = 0;

		switch (shader) {
			default: {
				mu_print("[muVGC] Error compiling Vulkan GLSL code; shader passed in is unknown value\n");
				*result = MU_FAILURE;
				return bytecode;
			} break;
			case MUVGC_VERTEX: case MUVGC_TESSELLATION_CONTROL: case MUVGC_TESSELLATION_EVALUATION: case MUVGC_GEOMETRY: case MUVGC_COMPUTE: {
				mu_print("[muVGC] Error compiling Vulkan GLSL code; shader passed in has not been implemented yet. Sorry\n");
				*result = MU_FAILURE;
				return bytecode;
			} break;
			case MUVGC_FRAGMENT: {
				shader_capability = 1;
				execution_model = 4;
			} break;
		}

		switch (version) {
			default: {
				mu_print("[muVGC] Error compiling Vulkan GLSL code; invalid version number\n");
				*result = MU_FAILURE;
				return bytecode;
			}

			case 110: case 120: case 130: {
				mu_print("[muVGC] Error compiling Vulkan GLSL code; version number must be at least 140\n");
				*result = MU_FAILURE;
				return bytecode;
			} break;

			case 140: case 150:
			case 330: case 400: case 410: case 420: case 430:
			case 440: case 450: case 460: break;
		}

		char b0[] = {
			// OpCapability shader_capability
			17, 0, 2, 0,
			shader_capability, 0, 0, 0,
			// %1 = OpExtInstImport "GLSL.std.450"
			11, 0, 6, 0,
			1, 0, 0, 0,
			'G', 'L', 'S', 'L',
			'.', 's', 't', 'd',
			'.', '4', '5', '0',
			0, 0, 0, 0,
			// OpMemoryModel Logical GLSL450
			14, 0, 3, 0,
			0, 0, 0, 0,
			1, 0, 0, 0,
			// OpEntryPoint Fragment %4 "main"
			15, 0, 5, 0,
			execution_model, 0, 0, 0,
			4, 0, 0, 0,
			'm', 'a', 'i', 'n',
			0, 0, 0, 0,
			// OpExecutionMode %4 OriginUpperLeft
			16, 0, 3, 0,
			4, 0, 0, 0,
			7, 0, 0, 0,
			// OpSource GLSL 450
			3, 0, 3, 0,
			2, 0, 0, 0,
			version & 0xFF, (version >> 8) & 0xFF, (version >> 16) & 0xFF, (version >> 24) & 0xFF,
			// OpSourceExtension "GL_GOOGLE_cpp_style_line_directive"
			4, 0, 10, 0,
			'G', 'L', '_', 'G',
			'O', 'O', 'G', 'L',
			'E', '_', 'c', 'p',
			'p', '_', 's', 't',
			'y', 'l', 'e', '_',
			'l', 'i', 'n', 'e',
			'_', 'd', 'i', 'r',
			'e', 'c', 't', 'i',
			'v', 'e', 0, 0,
			// OpSourceExtension "GL_GOOGLE_include_directive"
			4, 0, 8, 0,
			'G', 'L', '_', 'G',
			'O', 'O', 'G', 'L',
			'E', '_', 'i', 'n',
			'c', 'l', 'u', 'd',
			'e', '_', 'd', 'i',
			'r', 'e', 'c', 't',
			'i', 'v', 'e', 0,
		};
		bytecode = mu_string_insert_raw(bytecode, b0, sizeof(b0), mu_string_strlen(bytecode));

		return bytecode;
	}

	muString muVGC_macro_handle_version(muResult* result, muString code, const char* og, muString bytecode, muVGCShader shader) {
		size_m number_index = 0, beg = 0, end = 0;
		if (muVGC_is_version_valid(code, og, &number_index, &beg, &end) != MU_SUCCESS) {
			*result = MU_FAILURE;
			return bytecode;
		}

		int64_m version = mu_get_integer_from_string(&code.s[number_index], (end-beg)-number_index);
		muVGC_clear_code(code.s, beg, end);

		muResult res = MU_SUCCESS;
		bytecode = muVGC_macro_handle_first_words(&res, bytecode);
		if (res != MU_SUCCESS) {
			*result = MU_FAILURE;
			return bytecode;
		}

		bytecode = muVGC_macro_handle_first_instructions(&res, bytecode, shader, version);
		if (res != MU_SUCCESS) {
			*result = MU_FAILURE;
			return bytecode;
		}

		return bytecode;
	}

	muString muVGC_handle_macros(muResult* result, muString code, const char* og, muString bytecode, muVGCShader shader) {
		muResult res = MU_SUCCESS;

		bytecode = muVGC_macro_handle_version(&res, code, og, bytecode, shader);
		if (res != MU_SUCCESS) {
			*result = MU_FAILURE;
			return bytecode;
		}

		return bytecode;
	}

/* TOKEN HANDLING */

	// token type enum

	enum muVGCTokenType {
		MUVGC_TOKEN_UNKNOWN,
		MUVGC_TOKEN_KEYWORD,
		MUVGC_TOKEN_RESERVED_KEYWORD,
		MUVGC_TOKEN_IDENTIFIER,
		MUVGC_TOKEN_INTEGER_CONSTANT,
		MUVGC_TOKEN_FLOAT_CONSTANT,
		MUVGC_TOKEN_DOUBLE_CONSTANT,
		MUVGC_TOKEN_END_OF_FILE,

		MUVGC_TOKEN_PERIOD,
		MUVGC_TOKEN_PLUS,
		MUVGC_TOKEN_DASH,
		MUVGC_TOKEN_SLASH,
		MUVGC_TOKEN_ASTERIK,
		MUVGC_TOKEN_PERCENT,
		MUVGC_TOKEN_LESS_THAN_ANGLED_BRACKET,
		MUVGC_TOKEN_GREATER_THAN_ANGLED_BRACKET,
		MUVGC_TOKEN_OPEN_SQUARE_BRACKET,
		MUVGC_TOKEN_CLOSE_SQUARE_BRACKET,
		MUVGC_TOKEN_OPEN_PARENTHESIS,
		MUVGC_TOKEN_CLOSE_PARENTHESIS,
		MUVGC_TOKEN_OPEN_BRACE,
		MUVGC_TOKEN_CLOSE_BRACE,
		MUVGC_TOKEN_CARET,
		MUVGC_TOKEN_VERTICAL_BAR,
		MUVGC_TOKEN_AMPERSAND,
		MUVGC_TOKEN_TILDE,
		MUVGC_TOKEN_EQUALS,
		MUVGC_TOKEN_EXCLAMATION_POINT,
		MUVGC_TOKEN_COLON,
		MUVGC_TOKEN_SEMICOLON,
		MUVGC_TOKEN_COMMA,
		MUVGC_TOKEN_QUESTION_MARK
	};
	typedef enum muVGCTokenType muVGCTokenType;

	void muVGC_print_token_type(muVGCTokenType type) {
		switch (type) {
			default: mu_print("unknown"); break;
			case MUVGC_TOKEN_KEYWORD: mu_print("keyword"); break;
			case MUVGC_TOKEN_RESERVED_KEYWORD: mu_print("reserved keyword"); break;
			case MUVGC_TOKEN_IDENTIFIER: mu_print("identifier"); break;
			case MUVGC_TOKEN_INTEGER_CONSTANT: mu_print("integer constant"); break;
			case MUVGC_TOKEN_FLOAT_CONSTANT: mu_print("float constant"); break;
			case MUVGC_TOKEN_DOUBLE_CONSTANT: mu_print("double constant"); break;
			case MUVGC_TOKEN_END_OF_FILE: mu_print("end of file"); break;

			case MUVGC_TOKEN_PERIOD: mu_print("period"); break;
			case MUVGC_TOKEN_PLUS: mu_print("plus"); break;
			case MUVGC_TOKEN_DASH: mu_print("dash"); break;
			case MUVGC_TOKEN_SLASH: mu_print("slash"); break;
			case MUVGC_TOKEN_ASTERIK: mu_print("asterik"); break;
			case MUVGC_TOKEN_PERCENT: mu_print("percent"); break;
			case MUVGC_TOKEN_LESS_THAN_ANGLED_BRACKET: mu_print("less-than angled bracket"); break;
			case MUVGC_TOKEN_GREATER_THAN_ANGLED_BRACKET: mu_print("greater-than angled bracket"); break;
			case MUVGC_TOKEN_OPEN_SQUARE_BRACKET: mu_print("open square bracket"); break;
			case MUVGC_TOKEN_CLOSE_SQUARE_BRACKET: mu_print("close square bracket"); break;
			case MUVGC_TOKEN_OPEN_PARENTHESIS: mu_print("open parenthesis"); break;
			case MUVGC_TOKEN_CLOSE_PARENTHESIS: mu_print("close parenthesis"); break;
			case MUVGC_TOKEN_OPEN_BRACE: mu_print("open brace"); break;
			case MUVGC_TOKEN_CLOSE_BRACE: mu_print("close brace"); break;
			case MUVGC_TOKEN_CARET: mu_print("caret"); break;
			case MUVGC_TOKEN_VERTICAL_BAR: mu_print("vertical bar"); break;
			case MUVGC_TOKEN_AMPERSAND: mu_print("ampersand"); break;
			case MUVGC_TOKEN_TILDE: mu_print("tilde"); break;
			case MUVGC_TOKEN_EQUALS: mu_print("equals"); break;
			case MUVGC_TOKEN_EXCLAMATION_POINT: mu_print("exclamation point"); break;
			case MUVGC_TOKEN_COLON: mu_print("colon"); break;
			case MUVGC_TOKEN_SEMICOLON: mu_print("semicolon"); break;
			case MUVGC_TOKEN_COMMA: mu_print("comma"); break;
			case MUVGC_TOKEN_QUESTION_MARK: mu_print("question mark"); break;
		}
	}

	// token struct

	struct muVGCToken {
		muVGCTokenType type;
		size_m index;
		size_m length;
		size_m effective_length;
	};
	typedef struct muVGCToken muVGCToken;

	// token identification

	muVGCToken muVGC_get_token(const char* code, size_m codelen, size_m index) {
		muVGCToken token = { 0 };
		token.type = MUVGC_TOKEN_UNKNOWN;
		token.index = index;
		token.length = 1;
		token.effective_length = 1;

		// Return end-of-file if end of code
		if ((index >= codelen) || (code[index] == '\0')) {
			token.type = MUVGC_TOKEN_END_OF_FILE;
			return token;
		}

		// Check if it's some name
		if (
			(code[index] >= 'a' && code[index] <= 'z') ||
			(code[index] >= 'A' && code[index] <= 'Z') ||
			(code[index] == '_')
		) {
			// Get length
			while (
				(code[token.index+token.length] >= '0' && code[token.index+token.length] <= '9') ||
				(code[token.index+token.length] >= 'a' && code[token.index+token.length] <= 'z') ||
				(code[token.index+token.length] >= 'A' && code[token.index+token.length] <= 'Z') ||
				(code[token.index+token.length] == '_')
			) {
				token.length++;
			}

			// Get type
			token.type = MUVGC_TOKEN_IDENTIFIER;

			// (keywords)
			switch (token.length) {
				default: break;
				case 2: {
					if (
						(mu_strncmp(&code[token.index], "do", 2) == 0) ||
						(mu_strncmp(&code[token.index], "if", 2) == 0) ||
						(mu_strncmp(&code[token.index], "in", 2) == 0)
					) {
						token.type = MUVGC_TOKEN_KEYWORD;
					}
				} break;
				case 3: {
					if (
						(mu_strncmp(&code[token.index], "for", 3) == 0) ||
						(mu_strncmp(&code[token.index], "out", 3) == 0) ||
						(mu_strncmp(&code[token.index], "int", 3) == 0)
					) {
						token.type = MUVGC_TOKEN_KEYWORD;
					}
				} break;
				case 4: {
					if (
						(mu_strncmp(&code[token.index], "flat", 4) == 0) ||
						(mu_strncmp(&code[token.index], "case", 4) == 0) ||
						(mu_strncmp(&code[token.index], "else", 4) == 0) ||
						(mu_strncmp(&code[token.index], "void", 4) == 0) ||
						(mu_strncmp(&code[token.index], "bool", 4) == 0) ||
						(mu_strncmp(&code[token.index], "true", 4) == 0) ||
						(mu_strncmp(&code[token.index], "mat2", 4) == 0) ||
						(mu_strncmp(&code[token.index], "mat3", 4) == 0) ||
						(mu_strncmp(&code[token.index], "mat4", 4) == 0) ||
						(mu_strncmp(&code[token.index], "vec2", 4) == 0) ||
						(mu_strncmp(&code[token.index], "vec3", 4) == 0) ||
						(mu_strncmp(&code[token.index], "vec4", 4) == 0) ||
						(mu_strncmp(&code[token.index], "uint", 4) == 0) ||
						(mu_strncmp(&code[token.index], "lowp", 4) == 0)
					) {
						token.type = MUVGC_TOKEN_KEYWORD;
					}
				} break;
				case 5: {
					if (
						(mu_strncmp(&code[token.index], "const", 5) == 0) ||
						(mu_strncmp(&code[token.index], "break", 5) == 0) ||
						(mu_strncmp(&code[token.index], "while", 5) == 0) ||
						(mu_strncmp(&code[token.index], "inout", 5) == 0) ||
						(mu_strncmp(&code[token.index], "float", 5) == 0) ||
						(mu_strncmp(&code[token.index], "false", 5) == 0) ||
						(mu_strncmp(&code[token.index], "dmat2", 5) == 0) ||
						(mu_strncmp(&code[token.index], "dmat3", 5) == 0) ||
						(mu_strncmp(&code[token.index], "dmat4", 5) == 0) ||
						(mu_strncmp(&code[token.index], "ivec2", 5) == 0) ||
						(mu_strncmp(&code[token.index], "ivec3", 5) == 0) ||
						(mu_strncmp(&code[token.index], "ivec4", 5) == 0) ||
						(mu_strncmp(&code[token.index], "bvec2", 5) == 0) ||
						(mu_strncmp(&code[token.index], "bvec3", 5) == 0) ||
						(mu_strncmp(&code[token.index], "bvec4", 5) == 0) ||
						(mu_strncmp(&code[token.index], "dvec2", 5) == 0) ||
						(mu_strncmp(&code[token.index], "dvec3", 5) == 0) ||
						(mu_strncmp(&code[token.index], "dvec4", 5) == 0) ||
						(mu_strncmp(&code[token.index], "uvec2", 5) == 0) ||
						(mu_strncmp(&code[token.index], "uvec3", 5) == 0) ||
						(mu_strncmp(&code[token.index], "uvec4", 5) == 0) ||
						(mu_strncmp(&code[token.index], "highp", 5) == 0) ||
						(mu_strncmp(&code[token.index], "patch", 5) == 0)
					) {
						token.type = MUVGC_TOKEN_KEYWORD;
					}
				} break;
				case 6: {
					if (
						(mu_strncmp(&code[token.index], "buffer", 6) == 0) ||
						(mu_strncmp(&code[token.index], "shared", 6) == 0) ||
						(mu_strncmp(&code[token.index], "layout", 6) == 0) ||
						(mu_strncmp(&code[token.index], "smooth", 6) == 0) ||
						(mu_strncmp(&code[token.index], "switch", 6) == 0) ||
						(mu_strncmp(&code[token.index], "double", 6) == 0) ||
						(mu_strncmp(&code[token.index], "return", 6) == 0) ||
						(mu_strncmp(&code[token.index], "mat2x2", 6) == 0) ||
						(mu_strncmp(&code[token.index], "mat2x3", 6) == 0) ||
						(mu_strncmp(&code[token.index], "mat2x4", 6) == 0) ||
						(mu_strncmp(&code[token.index], "mat3x2", 6) == 0) ||
						(mu_strncmp(&code[token.index], "mat3x3", 6) == 0) ||
						(mu_strncmp(&code[token.index], "mat3x4", 6) == 0) ||
						(mu_strncmp(&code[token.index], "mat4x2", 6) == 0) ||
						(mu_strncmp(&code[token.index], "mat4x3", 6) == 0) ||
						(mu_strncmp(&code[token.index], "mat4x4", 6) == 0) ||
						(mu_strncmp(&code[token.index], "struct", 6) == 0) ||
						(mu_strncmp(&code[token.index], "sample", 6) == 0)
					) {
						token.type = MUVGC_TOKEN_KEYWORD;
					}
				} break;
				case 7: {
					if (
						(mu_strncmp(&code[token.index], "uniform", 7) == 0) ||
						(mu_strncmp(&code[token.index], "varying", 7) == 0) ||
						(mu_strncmp(&code[token.index], "default", 7) == 0) ||
						(mu_strncmp(&code[token.index], "precise", 7) == 0) ||
						(mu_strncmp(&code[token.index], "discard", 7) == 0) ||
						(mu_strncmp(&code[token.index], "dmat2x2", 7) == 0) ||
						(mu_strncmp(&code[token.index], "dmat2x3", 7) == 0) ||
						(mu_strncmp(&code[token.index], "dmat2x4", 7) == 0) ||
						(mu_strncmp(&code[token.index], "dmat3x2", 7) == 0) ||
						(mu_strncmp(&code[token.index], "dmat3x3", 7) == 0) ||
						(mu_strncmp(&code[token.index], "dmat3x4", 7) == 0) ||
						(mu_strncmp(&code[token.index], "dmat4x2", 7) == 0) ||
						(mu_strncmp(&code[token.index], "dmat4x3", 7) == 0) ||
						(mu_strncmp(&code[token.index], "dmat4x4", 7) == 0) ||
						(mu_strncmp(&code[token.index], "mediump", 7) == 0) ||
						(mu_strncmp(&code[token.index], "image1D", 7) == 0) ||
						(mu_strncmp(&code[token.index], "image2D", 7) == 0) ||
						(mu_strncmp(&code[token.index], "image3D", 7) == 0)
					) {
						token.type = MUVGC_TOKEN_KEYWORD;
					}
				} break;
				case 8: {
					if (
						(mu_strncmp(&code[token.index], "coherent", 8) == 0) ||
						(mu_strncmp(&code[token.index], "volatile", 8) == 0) ||
						(mu_strncmp(&code[token.index], "restrict", 8) == 0) ||
						(mu_strncmp(&code[token.index], "readonly", 8) == 0) ||
						(mu_strncmp(&code[token.index], "centroid", 8) == 0) ||
						(mu_strncmp(&code[token.index], "continue", 8) == 0) ||
						(mu_strncmp(&code[token.index], "iimage1D", 8) == 0) ||
						(mu_strncmp(&code[token.index], "uimage1D", 8) == 0) ||
						(mu_strncmp(&code[token.index], "iimage2D", 8) == 0) ||
						(mu_strncmp(&code[token.index], "uimage2D", 8) == 0) ||
						(mu_strncmp(&code[token.index], "iimage3D", 8) == 0) ||
						(mu_strncmp(&code[token.index], "uimage3D", 8) == 0)
					) {
						token.type = MUVGC_TOKEN_KEYWORD;
					}
				} break;
				case 9: {
					if (
						(mu_strncmp(&code[token.index], "attribute", 9) == 0) ||
						(mu_strncmp(&code[token.index], "writeonly", 9) == 0) ||
						(mu_strncmp(&code[token.index], "invariant", 9) == 0) ||
						(mu_strncmp(&code[token.index], "precision", 9) == 0) ||
						(mu_strncmp(&code[token.index], "sampler1D", 9) == 0) ||
						(mu_strncmp(&code[token.index], "sampler2D", 9) == 0) ||
						(mu_strncmp(&code[token.index], "sampler3D", 9) == 0) ||
						(mu_strncmp(&code[token.index], "imageCube", 9) == 0) ||
						(mu_strncmp(&code[token.index], "image2DMS", 9) == 0)
					) {
						token.type = MUVGC_TOKEN_KEYWORD;
					}
				} break;
				case 10: {
					if (
						(mu_strncmp(&code[token.index], "subroutine", 10) == 0) ||
						(mu_strncmp(&code[token.index], "isampler1D", 10) == 0) ||
						(mu_strncmp(&code[token.index], "isampler2D", 10) == 0) ||
						(mu_strncmp(&code[token.index], "isampler3D", 10) == 0) ||
						(mu_strncmp(&code[token.index], "usampler1D", 10) == 0) ||
						(mu_strncmp(&code[token.index], "usampler2D", 10) == 0) ||
						(mu_strncmp(&code[token.index], "usampler3D", 10) == 0) ||
						(mu_strncmp(&code[token.index], "iimageCube", 10) == 0) ||
						(mu_strncmp(&code[token.index], "uimageCube", 10) == 0) ||
						(mu_strncmp(&code[token.index], "iimage2DMS", 10) == 0) ||
						(mu_strncmp(&code[token.index], "uimage2DMS", 10) == 0)
					) {
						token.type = MUVGC_TOKEN_KEYWORD;
					}
				} break;
				case 11: {
					if (
						(mu_strncmp(&code[token.index], "atomic_uint", 11) == 0) ||
						(mu_strncmp(&code[token.index], "samplerCube", 11) == 0) ||
						(mu_strncmp(&code[token.index], "sampler2DMS", 11) == 0) ||
						(mu_strncmp(&code[token.index], "image2DRect", 11) == 0) ||
						(mu_strncmp(&code[token.index], "imageBuffer", 11) == 0)
					) {
						token.type = MUVGC_TOKEN_KEYWORD;
					}
				} break;
				case 12: {
					if (
						(mu_strncmp(&code[token.index], "isamplerCube", 12) == 0) ||
						(mu_strncmp(&code[token.index], "usamplerCube", 12) == 0) ||
						(mu_strncmp(&code[token.index], "isampler2DMS", 12) == 0) ||
						(mu_strncmp(&code[token.index], "usampler2DMS", 12) == 0) ||
						(mu_strncmp(&code[token.index], "iimage2DRect", 12) == 0) ||
						(mu_strncmp(&code[token.index], "uimage2DRect", 12) == 0) ||
						(mu_strncmp(&code[token.index], "iimageBuffer", 12) == 0) ||
						(mu_strncmp(&code[token.index], "uimageBuffer", 12) == 0) ||
						(mu_strncmp(&code[token.index], "image1DArray", 12) == 0) ||
						(mu_strncmp(&code[token.index], "image2DArray", 12) == 0)
					) {
						token.type = MUVGC_TOKEN_KEYWORD;
					}
				} break;
				case 13: {
					if (
						(mu_strncmp(&code[token.index], "noperspective", 13) == 0) ||
						(mu_strncmp(&code[token.index], "sampler2DRect", 13) == 0) ||
						(mu_strncmp(&code[token.index], "samplerBuffer", 13) == 0) ||
						(mu_strncmp(&code[token.index], "iimage1DArray", 13) == 0) ||
						(mu_strncmp(&code[token.index], "uimage1DArray", 13) == 0) ||
						(mu_strncmp(&code[token.index], "iimage2DArray", 13) == 0) ||
						(mu_strncmp(&code[token.index], "uimage2DArray", 13) == 0)
					) {
						token.type = MUVGC_TOKEN_KEYWORD;
					}
				} break;
				case 14: {
					if (
						(mu_strncmp(&code[token.index], "sampler1DArray", 14) == 0) ||
						(mu_strncmp(&code[token.index], "sampler2DArray", 14) == 0) ||
						(mu_strncmp(&code[token.index], "isampler2DRect", 14) == 0) ||
						(mu_strncmp(&code[token.index], "usampler2DRect", 14) == 0) ||
						(mu_strncmp(&code[token.index], "isamplerBuffer", 14) == 0) ||
						(mu_strncmp(&code[token.index], "usamplerBuffer", 14) == 0) ||
						(mu_strncmp(&code[token.index], "imageCubeArray", 14) == 0) ||
						(mu_strncmp(&code[token.index], "image2DMSArray", 14) == 0)
					) {
						token.type = MUVGC_TOKEN_KEYWORD;
					}
				} break;
				case 15: {
					if (
						(mu_strncmp(&code[token.index], "sampler1DShadow", 15) == 0) ||
						(mu_strncmp(&code[token.index], "sampler2DShadow", 15) == 0) ||
						(mu_strncmp(&code[token.index], "isampler1DArray", 15) == 0) ||
						(mu_strncmp(&code[token.index], "isampler2DArray", 15) == 0) ||
						(mu_strncmp(&code[token.index], "usampler1DArray", 15) == 0) ||
						(mu_strncmp(&code[token.index], "usampler2DArray", 15) == 0) ||
						(mu_strncmp(&code[token.index], "iimageCubeArray", 15) == 0) ||
						(mu_strncmp(&code[token.index], "uimageCubeArray", 15) == 0) ||
						(mu_strncmp(&code[token.index], "iimage2DMSArray", 15) == 0) ||
						(mu_strncmp(&code[token.index], "uimage2DMSArray", 15) == 0)
					) {
						token.type = MUVGC_TOKEN_KEYWORD;
					}
				} break;
				case 16: {
					if (
						(mu_strncmp(&code[token.index], "sampler2DMSArray", 16) == 0) ||
						(mu_strncmp(&code[token.index], "samplerCubeArray", 16) == 0)
					) {
						token.type = MUVGC_TOKEN_KEYWORD;
					}
				} break;
				case 17: {
					if (
						(mu_strncmp(&code[token.index], "samplerCubeShadow", 17) == 0) ||
						(mu_strncmp(&code[token.index], "isampler2DMSArray", 17) == 0) ||
						(mu_strncmp(&code[token.index], "usampler2DMSArray", 17) == 0) ||
						(mu_strncmp(&code[token.index], "isamplerCubeArray", 17) == 0) ||
						(mu_strncmp(&code[token.index], "usamplerCubeArray", 17) == 0)
					) {
						token.type = MUVGC_TOKEN_KEYWORD;
					}
				} break;
				case 19: {
					if (
						(mu_strncmp(&code[token.index], "sampler2DRectShadow", 19) == 0)
					) {
						token.type = MUVGC_TOKEN_KEYWORD;
					}
				} break;
				case 20: {
					if (
						(mu_strncmp(&code[token.index], "sampler1DArrayShadow", 20) == 0) ||
						(mu_strncmp(&code[token.index], "sampler2DArrayShadow", 20) == 0)
					) {
						token.type = MUVGC_TOKEN_KEYWORD;
					}
				} break;
				case 22: {
					if (
						(mu_strncmp(&code[token.index], "samplerCubeArrayShadow", 22) == 0)
					) {
						token.type = MUVGC_TOKEN_KEYWORD;
					}
				} break;
			}

			// (reserved keywords)
			if (token.type == MUVGC_TOKEN_IDENTIFIER) {
				switch (token.length) {
					default: break;
					case 3: {
						if (
							(mu_strncmp(&code[token.index], "asm", 3) == 0)
						) {
							token.type = MUVGC_TOKEN_RESERVED_KEYWORD;
						}
					} break;
					case 4: {
						if (
							(mu_strncmp(&code[token.index], "enum", 4) == 0) ||
							(mu_strncmp(&code[token.index], "this", 4) == 0) ||
							(mu_strncmp(&code[token.index], "goto", 4) == 0) ||
							(mu_strncmp(&code[token.index], "long", 4) == 0) ||
							(mu_strncmp(&code[token.index], "half", 4) == 0) ||
							(mu_strncmp(&code[token.index], "cast", 4) == 0)
						) {
							token.type = MUVGC_TOKEN_RESERVED_KEYWORD;
						}
					} break;
					case 5: {
						if (
							(mu_strncmp(&code[token.index], "class", 5) == 0) ||
							(mu_strncmp(&code[token.index], "union", 5) == 0) ||
							(mu_strncmp(&code[token.index], "short", 5) == 0) ||
							(mu_strncmp(&code[token.index], "fixed", 5) == 0) ||
							(mu_strncmp(&code[token.index], "input", 5) == 0) ||
							(mu_strncmp(&code[token.index], "hvec2", 5) == 0) ||
							(mu_strncmp(&code[token.index], "hvec3", 5) == 0) ||
							(mu_strncmp(&code[token.index], "hvec4", 5) == 0) ||
							(mu_strncmp(&code[token.index], "fvec2", 5) == 0) ||
							(mu_strncmp(&code[token.index], "fvec3", 5) == 0) ||
							(mu_strncmp(&code[token.index], "fvec4", 5) == 0) ||
							(mu_strncmp(&code[token.index], "using", 5) == 0)
						) {
							token.type = MUVGC_TOKEN_RESERVED_KEYWORD;
						}
					} break;
					case 6: {
						if (
							(mu_strncmp(&code[token.index], "common", 6) == 0) ||
							(mu_strncmp(&code[token.index], "active", 6) == 0) ||
							(mu_strncmp(&code[token.index], "inline", 6) == 0) ||
							(mu_strncmp(&code[token.index], "public", 6) == 0) ||
							(mu_strncmp(&code[token.index], "static", 6) == 0) ||
							(mu_strncmp(&code[token.index], "extern", 6) == 0) ||
							(mu_strncmp(&code[token.index], "superp", 6) == 0) ||
							(mu_strncmp(&code[token.index], "output", 6) == 0) ||
							(mu_strncmp(&code[token.index], "filter", 6) == 0) ||
							(mu_strncmp(&code[token.index], "sizeof", 6) == 0)
						) {
							token.type = MUVGC_TOKEN_RESERVED_KEYWORD;
						}
					} break;
					case 7: {
						if (
							(mu_strncmp(&code[token.index], "typedef", 7) == 0)
						) {
							token.type = MUVGC_TOKEN_RESERVED_KEYWORD;
						}
					} break;
					case 8: {
						if (
							(mu_strncmp(&code[token.index], "template", 8) == 0) ||
							(mu_strncmp(&code[token.index], "resource", 8) == 0) ||
							(mu_strncmp(&code[token.index], "noinline", 8) == 0) ||
							(mu_strncmp(&code[token.index], "external", 8) == 0) ||
							(mu_strncmp(&code[token.index], "unsigned", 8) == 0)
						) {
							token.type = MUVGC_TOKEN_RESERVED_KEYWORD;
						}
					} break;
					case 9: {
						if (
							(mu_strncmp(&code[token.index], "partition", 9) == 0) ||
							(mu_strncmp(&code[token.index], "interface", 9) == 0) ||
							(mu_strncmp(&code[token.index], "namespace", 9) == 0)
						) {
							token.type = MUVGC_TOKEN_RESERVED_KEYWORD;
						}
					} break;
					case 13: {
						if (
							(mu_strncmp(&code[token.index], "sampler3DRect", 13) == 0)
						) {
							token.type = MUVGC_TOKEN_RESERVED_KEYWORD;
						}
					} break;
				}
			}
		}

		// Check if it's an integer/float constant
		if (
			(code[index] == '.' && code[index+1] >= '0' && code[index+1] <= '9') ||
			(code[index] >= '0' && code[index] <= '9')
		) {
			if (code[index] == '.') {
				token.type = MUVGC_TOKEN_FLOAT_CONSTANT;
			} else {
				token.type = MUVGC_TOKEN_INTEGER_CONSTANT;
			}

			while (
				(code[token.index+token.length] >= '0' && code[token.index+token.length] <= '9') ||
				(code[token.index+token.length] == '.' && token.type == MUVGC_TOKEN_INTEGER_CONSTANT)
			) {
				if (code[token.index+token.length] == '.' && token.type == MUVGC_TOKEN_INTEGER_CONSTANT) {
					token.type = MUVGC_TOKEN_FLOAT_CONSTANT;
				}
				token.length++;
			}

			if (
				token.type == MUVGC_TOKEN_FLOAT_CONSTANT && 
				(code[token.index+token.length] == 'f' || code[token.index+token.length] == 'F')
			) {
				token.length++;
			} else if (
				token.type == MUVGC_TOKEN_FLOAT_CONSTANT &&
				(
					mu_strncmp(&code[token.index+token.length], "lf", 2) == 0 ||
					mu_strncmp(&code[token.index+token.length], "lF", 2) == 0 ||
					mu_strncmp(&code[token.index+token.length], "Lf", 2) == 0 ||
					mu_strncmp(&code[token.index+token.length], "LF", 2) == 0
				)
			) {
				token.type = MUVGC_TOKEN_DOUBLE_CONSTANT;
				token.length += 2;
			}
		}

		// Single-character tokens
		switch (code[token.index]) {
			default: break;
			case '.': {
				token.type = MUVGC_TOKEN_PERIOD;
			} break;
			case '+': {
				token.type = MUVGC_TOKEN_PERIOD;
			} break;
			case '-': {
				token.type = MUVGC_TOKEN_DASH;
			} break;
			case '/': {
				token.type = MUVGC_TOKEN_SLASH;
			} break;
			case '*': {
				token.type = MUVGC_TOKEN_ASTERIK;
			} break;
			case '%': {
				token.type = MUVGC_TOKEN_PERCENT;
			} break;
			case '<': {
				token.type = MUVGC_TOKEN_LESS_THAN_ANGLED_BRACKET;
			} break;
			case '>': {
				token.type = MUVGC_TOKEN_GREATER_THAN_ANGLED_BRACKET;
			} break;
			case '[': {
				token.type = MUVGC_TOKEN_OPEN_SQUARE_BRACKET;
			} break;
			case ']': {
				token.type = MUVGC_TOKEN_CLOSE_SQUARE_BRACKET;
			} break;
			case '(': {
				token.type = MUVGC_TOKEN_OPEN_PARENTHESIS;
			} break;
			case ')': {
				token.type = MUVGC_TOKEN_CLOSE_PARENTHESIS;
			} break;
			case '{': {
				token.type = MUVGC_TOKEN_OPEN_BRACE;
			} break;
			case '}': {
				token.type = MUVGC_TOKEN_CLOSE_BRACE;
			} break;
			case '^': {
				token.type = MUVGC_TOKEN_CARET;
			} break;
			case '|': {
				token.type = MUVGC_TOKEN_VERTICAL_BAR;
			} break;
			case '&': {
				token.type = MUVGC_TOKEN_AMPERSAND;
			} break;
			case '~': {
				token.type = MUVGC_TOKEN_TILDE;
			} break;
			case '=': {
				token.type = MUVGC_TOKEN_EQUALS;
			} break;
			case '!': {
				token.type = MUVGC_TOKEN_EXCLAMATION_POINT;
			} break;
			case ':': {
				token.type = MUVGC_TOKEN_COLON;
			} break;
			case ';': {
				token.type = MUVGC_TOKEN_SEMICOLON;
			} break;
			case ',': {
				token.type = MUVGC_TOKEN_COMMA;
			} break;
			case '?': {
				token.type = MUVGC_TOKEN_QUESTION_MARK;
			} break;
		}

		return token;
	}

	// final handling

	muVGCToken* muVGC_tokenize_code(const char* code, size_m codelen, const char* og, size_m* len) {
		// Intentionally, length is one less than necessary to not store EOF token
		*len = 0;

		// I do end up tokenizing twice, once to count how many tokens needed &
		// once to gather the tokens again. This could be optimized, but I can't
		// think of an immediate way...

		muVGCToken token = muVGC_get_token(code, codelen, muVGC_get_next_non_empty_char(code, codelen, 0));
		while (token.type != MUVGC_TOKEN_END_OF_FILE) {
			if (token.type == MUVGC_TOKEN_UNKNOWN) {
				muVGC_print_syntax_error(og, token.index);
				mu_print("unrecognized symbol\n");
				return MU_NULL_PTR;
			}

			token = muVGC_get_token(code, codelen, muVGC_get_next_non_empty_char(code, codelen, token.index + token.length));
			*len += 1;
		}
		
		if (*len == 0) {
			mu_print("[muVGC] Syntax error; expected at least one token after version\n");
			return MU_NULL_PTR;
		}
		muVGCToken* tokens = mu_malloc(sizeof(muVGCToken) * (*len));

		token = muVGC_get_token(code, codelen, muVGC_get_next_non_empty_char(code, codelen, 0));
		tokens[0] = token;
		size_m index = 0;
		while (token.type != MUVGC_TOKEN_END_OF_FILE) {
			token = muVGC_get_token(code, codelen, muVGC_get_next_non_empty_char(code, codelen, token.index + token.length));
			index++;
			if (token.type != MUVGC_TOKEN_END_OF_FILE) {
				tokens[index] = token;
			}
		}

		/*for (size_m i = 0; i < *len; i++) {
			muVGC_print_token_type(tokens[i].type);
			mu_print(" ( '");
			for (size_m j = 0; j < tokens[i].length; j++) {
				mu_printf("%c", code[tokens[i].index+j]);
			}
			mu_print("' )");
			mu_print("\n");
		}*/

		return tokens;
	}

	// This function exists for now because I'll most likely add a way for
	// macros to override token values without messing up original code
	// spacing, essentially taking advantage of the tokens to store the
	// original code positioning
	char* muVGC_get_token_value(const char* code, muVGCToken token) {
		return (char*)&code[token.index];
	}

/* INSTRUCTION HANDLING */

	// 3.49.2 Debug Instructions

		muString muVGC_op_name(muString bytecode, uint32_m id_target, char* name, size_m namelen) {
			size_m i = muVGC_hop_to_naming_section(bytecode);

			size_m datanamelen = namelen;
			if ((datanamelen % 4) == 0) {
				datanamelen++;
			}
			while (((datanamelen) % 4) != 0) {
				datanamelen++;
			}
			uint16_m fulllen = (datanamelen / 4) + 2;

			char b[] = {
				5, 0, MUVGC_2_BYTE_LE(fulllen),
				MUVGC_4_BYTE_LE(id_target)
			};
			bytecode = mu_string_insert_raw(bytecode, b, sizeof(b), i);
			i += sizeof(b);

			bytecode = mu_string_insert_raw(bytecode, name, namelen, i);
			i += namelen;

			char four_empty[] = { 0, 0, 0, 0 };
			return mu_string_insert_raw(bytecode, four_empty, datanamelen-namelen, i);
		}

	// 3.49.6 Type-Declaration Instructions (Get)

		muString muVGC_get_void_type(muString bytecode, uint32_m* void_type, uint32_m* global_id) {
			size_m dec = muVGC_hop_to_decoration_section(bytecode);
			size_m var = muVGC_hop_to_variable_section(bytecode);

			for (size_m i = dec; i < var;) {
				int16_m instruction = muVGC_get_halfword(&bytecode.s[i]);
				int16_m step = muVGC_get_halfword(&bytecode.s[i+2]);

				if (instruction == 19 && step == 2) {
					*void_type = muVGC_get_word(&bytecode.s[i+4]);
					return bytecode;
				}

				i += step * 4;
			}

			char b[] = {
				19, 0, 2, 0,
				MUVGC_4_BYTE_LE(*global_id)
			};
			*void_type = *global_id;
			*global_id += 1;
			return mu_string_insert_raw(bytecode, b, sizeof(b), var);
		}

		muString muVGC_get_bool_type(muString bytecode, uint32_m* bool_type, uint32_m* global_id) {
			size_m dec = muVGC_hop_to_decoration_section(bytecode);
			size_m var = muVGC_hop_to_variable_section(bytecode);

			for (size_m i = dec; i < var;) {
				int16_m instruction = muVGC_get_halfword(&bytecode.s[i]);
				int16_m step = muVGC_get_halfword(&bytecode.s[i+2]);

				if (instruction == 20 && step == 2) {
					*bool_type = muVGC_get_word(&bytecode.s[i+4]);
					return bytecode;
				}

				i += step * 4;
			}

			char b[] = {
				20, 0, 2, 0,
				MUVGC_4_BYTE_LE(*global_id)
			};
			*bool_type = *global_id;
			*global_id += 1;
			return mu_string_insert_raw(bytecode, b, sizeof(b), var);
		}

		muString muVGC_get_int_type(muString bytecode, uint32_m* int_type, uint32_m* global_id, uint32_m width, uint32_m signedness) {
			size_m dec = muVGC_hop_to_decoration_section(bytecode);
			size_m var = muVGC_hop_to_variable_section(bytecode);

			for (size_m i = dec; i < var;) {
				int16_m instruction = muVGC_get_halfword(&bytecode.s[i]);
				int16_m step = muVGC_get_halfword(&bytecode.s[i+2]);

				if (instruction == 21 && step == 4 && muVGC_get_word(&bytecode.s[i+8]) == width && muVGC_get_word(&bytecode.s[i+12]) == signedness) {
					*int_type = muVGC_get_word(&bytecode.s[i+4]);
					return bytecode;
				}

				i += step * 4;
			}

			char b[] = {
				21, 0, 4, 0,
				MUVGC_4_BYTE_LE(*global_id),
				MUVGC_4_BYTE_LE(width),
				MUVGC_4_BYTE_LE(signedness)
			};
			*int_type = *global_id;
			*global_id += 1;
			return mu_string_insert_raw(bytecode, b, sizeof(b), var);
		}

		muString muVGC_get_float_type(muString bytecode, uint32_m* float_type, uint32_m* global_id, uint32_m width) {
			size_m dec = muVGC_hop_to_decoration_section(bytecode);
			size_m var = muVGC_hop_to_variable_section(bytecode);

			for (size_m i = dec; i < var;) {
				int16_m instruction = muVGC_get_halfword(&bytecode.s[i]);
				int16_m step = muVGC_get_halfword(&bytecode.s[i+2]);

				if (instruction == 22 && step == 3 && muVGC_get_word(&bytecode.s[i+8]) == width) {
					*float_type = muVGC_get_word(&bytecode.s[i+4]);
					return bytecode;
				}

				i += step * 4;
			}

			char b[] = {
				22, 0, 3, 0,
				MUVGC_4_BYTE_LE(*global_id),
				MUVGC_4_BYTE_LE(width)
			};
			*float_type = *global_id;
			*global_id += 1;
			return mu_string_insert_raw(bytecode, b, sizeof(b), var);
		}

		muString muVGC_get_vector_type(muString bytecode, uint32_m* vec_type, uint32_m* global_id, uint32_m component_type, uint32_m component_count) {
			size_m dec = muVGC_hop_to_decoration_section(bytecode);
			size_m var = muVGC_hop_to_variable_section(bytecode);

			for (size_m i = dec; i < var;) {
				int16_m instruction = muVGC_get_halfword(&bytecode.s[i]);
				int16_m step = muVGC_get_halfword(&bytecode.s[i+2]);

				if (instruction == 23 && step == 4 && muVGC_get_word(&bytecode.s[i+8]) == component_type && muVGC_get_word(&bytecode.s[i+12]) == component_count) {
					*vec_type = muVGC_get_word(&bytecode.s[i+4]);
					return bytecode;
				}

				i += step * 4;
			}

			char b[] = {
				23, 0, 4, 0,
				MUVGC_4_BYTE_LE(*global_id),
				MUVGC_4_BYTE_LE(component_type),
				MUVGC_4_BYTE_LE(component_count)
			};
			*vec_type = *global_id;
			*global_id += 1;
			return mu_string_insert_raw(bytecode, b, sizeof(b), var);
		}

		muString muVGC_get_matrix_type(muString bytecode, uint32_m* mat_type, uint32_m* global_id, uint32_m column_type, uint32_m column_count) {
			size_m dec = muVGC_hop_to_decoration_section(bytecode);
			size_m var = muVGC_hop_to_variable_section(bytecode);

			for (size_m i = dec; i < var;) {
				int16_m instruction = muVGC_get_halfword(&bytecode.s[i]);
				int16_m step = muVGC_get_halfword(&bytecode.s[i+2]);

				if (instruction == 24 && step == 4 && muVGC_get_word(&bytecode.s[i+8]) == column_type && muVGC_get_word(&bytecode.s[i+12]) == column_count) {
					*mat_type = muVGC_get_word(&bytecode.s[i+4]);
					return bytecode;
				}

				i += step * 4;
			}

			char b[] = {
				24, 0, 4, 0,
				MUVGC_4_BYTE_LE(*global_id),
				MUVGC_4_BYTE_LE(column_type),
				MUVGC_4_BYTE_LE(column_count)
			};
			*mat_type = *global_id;
			*global_id += 1;
			return mu_string_insert_raw(bytecode, b, sizeof(b), var);
		}

		muString muVGC_get_image_type(muString bytecode, uint32_m* img_type, uint32_m* global_id, 
			uint32_m sampled_type, uint32_m dim, uint32_m depth, uint32_m arrayed, uint32_m ms, 
			uint32_m sampled, uint32_m image_format, uint32_m access_qualifier, muBool apply_access_qualifier) {

			size_m dec = muVGC_hop_to_decoration_section(bytecode);
			size_m var = muVGC_hop_to_variable_section(bytecode);

			for (size_m i = dec; i < var;) {
				int16_m instruction = muVGC_get_halfword(&bytecode.s[i]);
				int16_m step = muVGC_get_halfword(&bytecode.s[i+2]);

				if (apply_access_qualifier) {
					if (
						instruction == 25 && step == 10 && 
						muVGC_get_word(&bytecode.s[i+8]) == sampled_type && muVGC_get_word(&bytecode.s[i+12]) == dim &&
						muVGC_get_word(&bytecode.s[i+16]) == depth && muVGC_get_word(&bytecode.s[i+20]) == arrayed &&
						muVGC_get_word(&bytecode.s[i+24]) == ms && muVGC_get_word(&bytecode.s[i+28]) == sampled &&
						muVGC_get_word(&bytecode.s[i+32]) == image_format && muVGC_get_word(&bytecode.s[i+36]) == access_qualifier) {

						*img_type = muVGC_get_word(&bytecode.s[i+4]);
						return bytecode;
					}
				} else {
					if (
						instruction == 25 && step == 9 && 
						muVGC_get_word(&bytecode.s[i+8]) == sampled_type && muVGC_get_word(&bytecode.s[i+12]) == dim &&
						muVGC_get_word(&bytecode.s[i+16]) == depth && muVGC_get_word(&bytecode.s[i+20]) == arrayed &&
						muVGC_get_word(&bytecode.s[i+24]) == ms && muVGC_get_word(&bytecode.s[i+28]) == sampled &&
						muVGC_get_word(&bytecode.s[i+32]) == image_format) {

						*img_type = muVGC_get_word(&bytecode.s[i+4]);
						return bytecode;
					}
				}

				i += step * 4;
			}

			char b[] = {
				25, 0, 10, 0,
				MUVGC_4_BYTE_LE(*global_id),
				MUVGC_4_BYTE_LE(sampled_type),
				MUVGC_4_BYTE_LE(dim),
				MUVGC_4_BYTE_LE(depth),
				MUVGC_4_BYTE_LE(arrayed),
				MUVGC_4_BYTE_LE(ms),
				MUVGC_4_BYTE_LE(sampled),
				MUVGC_4_BYTE_LE(image_format),
				MUVGC_4_BYTE_LE(access_qualifier)
			};
			*img_type = *global_id;
			*global_id += 1;
			if (apply_access_qualifier != MU_TRUE) {
				b[2] = 9;
				return mu_string_insert_raw(bytecode, b, sizeof(b)-4, var);
			}
			return mu_string_insert_raw(bytecode, b, sizeof(b), var);
		}

		muString muVGC_get_function_type(
			muString bytecode, uint32_m* type, uint32_m* global_id,
			uint32_m return_type, uint32_m* parameter_types, size_m parameter_len) {

			size_m dec = muVGC_hop_to_decoration_section(bytecode);
			size_m var = muVGC_hop_to_variable_section(bytecode);

			for (size_m i = dec; i < var;) {
				int16_m instruction = muVGC_get_halfword(&bytecode.s[i]);
				int16_m step = muVGC_get_halfword(&bytecode.s[i+2]);

				if (instruction == 33 && step == 3 + parameter_len && muVGC_get_word(&bytecode.s[i+8]) == return_type) {
					muBool good = MU_TRUE;
					for (size_m j = 0; j < parameter_len; j++) {
						// Is 12 correct here? @TODO Check later
						if (muVGC_get_word(&bytecode.s[i+12+(j*4)]) != parameter_types[j]) {
							good = MU_FALSE;
							break;
						}
					}
					if (good == MU_TRUE) {
						*type = muVGC_get_word(&bytecode.s[i+4]);
						return bytecode;
					}
				}

				i += step * 4;
			}

			char* b = mu_malloc(12 + (parameter_len*4));

			b[0] = 33; b[1] = 0; MUVGC_2_BYTE_LE_SET(b, 3+parameter_len, 2)
			MUVGC_4_BYTE_LE_SET(b, *global_id, 4)
			MUVGC_4_BYTE_LE_SET(b, return_type, 8)
			for (size_m i = 0; i < parameter_len; i++) {
				MUVGC_4_BYTE_LE_SET(b, parameter_types[i], 12+(i*4))
			}

			bytecode = mu_string_insert_raw(bytecode, b, 12 + (parameter_len*4), var);
			mu_free(b);
			*type = *global_id;
			*global_id += 1;
			return bytecode;
		}

	// 3.49.9 Function Instructions

		muString muVGC_op_function(
			muString bytecode, uint32_m return_type, uint32_m function_control, uint32_m function_type, uint32_m* global_id) {

			char b[] = {
				54, 0, 5, 0,
				MUVGC_4_BYTE_LE(return_type),
				MUVGC_4_BYTE_LE(*global_id),
				MUVGC_4_BYTE_LE(function_control),
				MUVGC_4_BYTE_LE(function_type)
			};
			bytecode = mu_string_insert_raw(bytecode, b, sizeof(b), muVGC_hop_to_function_section(bytecode));

			*global_id += 1;
			return bytecode;
		}

		muString muVGC_op_function_end(muString bytecode) {
			char b[] = {
				56, 0, 1, 0
			};
			return mu_string_insert_raw(bytecode, b, sizeof(b), muVGC_hop_to_function_section(bytecode));
		}

	// 3.49.17 Control-Flow Instructions

		muString muVGC_op_label(muString bytecode, uint32_m result_id) {
			// Thanks GCC (-Woverflow)
			int n = 248;
			char b[] = {
				MUVGC_2_BYTE_LE(n), 2, 0,
				MUVGC_4_BYTE_LE(result_id)
			};
			return mu_string_insert_raw(bytecode, b, sizeof(b), muVGC_hop_to_function_section(bytecode));
		}

		muString muVGC_op_return(muString bytecode) {
			int n = 253;
			char b[] = {
				MUVGC_2_BYTE_LE(n), 1, 0
			};
			return mu_string_insert_raw(bytecode, b, sizeof(b), muVGC_hop_to_function_section(bytecode));
		}

	// Get stuff

		uint32_m muVGC_get_format(char* format, size_m formatlen) {
			switch (formatlen) {
				default: break;

				case 2: {
					if (mu_strncmp(format, "r8", 2) == 0) {
						return 15;
					}
				} break;

				case 3: {
					if (mu_strncmp(format, "rg8", 3) == 0) {
						return 13;
					} else if (mu_strncmp(format, "r16", 3) == 0) {
						return 14;
					} else if (mu_strncmp(format, "r8i", 3) == 0) {
						return 29;
					}
				} break;

				case 4: {
					if (mu_strncmp(format, "r32f", 4) == 0) {
						return 3;
					} else if (mu_strncmp(format, "r16f", 4) == 0) {
						return 9;
					} else if (mu_strncmp(format, "rg16", 4) == 0) {
						return 12;
					} else if (mu_strncmp(format, "rg8i", 4) == 0) {
						return 27;
					} else if (mu_strncmp(format, "r32i", 4) == 0) {
						return 24;
					} else if (mu_strncmp(format, "r16i", 4) == 0) {
						return 28;
					} else if (mu_strncmp(format, "r8ui", 4) == 0) {
						return 39;
					}
				} break;

				case 5: {
					if (mu_strncmp(format, "rg32f", 5) == 0) {
						return 6;
					} else if (mu_strncmp(format, "rg16f", 5) == 0) {
						return 7;
					} else if (mu_strncmp(format, "rgba8", 5) == 0) {
						return 4;
					} else if (mu_strncmp(format, "rg32i", 5) == 0) {
						return 25;
					} else if (mu_strncmp(format, "rg16i", 5) == 0) {
						return 26;
					} else if (mu_strncmp(format, "rg8ui", 5) == 0) {
						return 37;
					} else if (mu_strncmp(format, "r32ui", 5) == 0) {
						return 33;
					} else if (mu_strncmp(format, "r16ui", 5) == 0) {
						return 38;
					}
				} break;

				case 6: {
					if (mu_strncmp(format, "rgba16", 6) == 0) {
						return 10;
					} else if (mu_strncmp(format, "rgba8i", 6) == 0) {
						return 23;
					} else if (mu_strncmp(format, "rg32ui", 6) == 0) {
						return 35;
					} else if (mu_strncmp(format, "rg16ui", 6) == 0) {
						return 36;
					}
				} break;

				case 7: {
					if (mu_strncmp(format, "rgba32f", 7) == 0) {
						return 1;
					} else if (mu_strncmp(format, "rgba16f", 7) == 0) {
						return 2;
					} else if (mu_strncmp(format, "rgba32i", 7) == 0) {
						return 21;
					} else if (mu_strncmp(format, "rgba16i", 7) == 0) {
						return 22;
					} else if (mu_strncmp(format, "rgba8ui", 7) == 0) {
						return 32;
					}
				} break;

				case 8: {
					if (mu_strncmp(format, "rgb10_a2", 8) == 0) {
						return 11;
					} else if (mu_strncmp(format, "r8_snorm", 8) == 0) {
						return 20;
					} else if (mu_strncmp(format, "rgba32ui", 8) == 0) {
						return 30;
					} else if (mu_strncmp(format, "rgba16ui", 8) == 0) {
						return 31;
					}
				} break;

				case 9: {
					if (mu_strncmp(format, "rg8_snorm", 9) == 0) {
						return 18;
					} else if (mu_strncmp(format, "r16_snorm", 9) == 0) {
						return 19;
					}
				} break;

				case 10: {
					if (mu_strncmp(format, "rg16_snorm", 10) == 0) {
						return 17;
					} else if (mu_strncmp(format, "rgb10_a2ui", 10) == 0) {
						return 34;
					}
				} break;

				case 11: {
					if (mu_strncmp(format, "rgba8_snorm", 11) == 0) {
						return 5;
					}
				} break;

				case 12: {
					if (mu_strncmp(format, "rgba16_snorm", 12) == 0) {
						return 16;
					}
				} break;

				case 14: {
					if (mu_strncmp(format, "r11f_g11f_b10f", 14) == 0) {
						return 8;
					}
				} break;
			}

			return 0;
		}

/* VARIABLE HANDLING */

	// Enums

		enum muVGCBasicType {
			#define MUVGC_BASIC_TYPE_FIRST MUVGC_TYPE_VOID
			// Transparent types
			#define MUVGC_TRANSPARENT_TYPE_FIRST MUVGC_TYPE_VOID
			MUVGC_TYPE_VOID,
			MUVGC_TYPE_BOOL,
			MUVGC_TYPE_INT,
			MUVGC_TYPE_UINT,
			MUVGC_TYPE_FLOAT,
			MUVGC_TYPE_DOUBLE,
			MUVGC_TYPE_VEC2,
			MUVGC_TYPE_VEC3,
			MUVGC_TYPE_VEC4,
			MUVGC_TYPE_DVEC2,
			MUVGC_TYPE_DVEC3,
			MUVGC_TYPE_DVEC4,
			MUVGC_TYPE_BVEC2,
			MUVGC_TYPE_BVEC3,
			MUVGC_TYPE_BVEC4,
			MUVGC_TYPE_IVEC2,
			MUVGC_TYPE_IVEC3,
			MUVGC_TYPE_IVEC4,
			MUVGC_TYPE_UVEC2,
			MUVGC_TYPE_UVEC3,
			MUVGC_TYPE_UVEC4,
			MUVGC_TYPE_MAT2,
			MUVGC_TYPE_MAT3,
			MUVGC_TYPE_MAT4,
			MUVGC_TYPE_MAT2X2,
			MUVGC_TYPE_MAT2X3,
			MUVGC_TYPE_MAT2X4,
			MUVGC_TYPE_MAT3X2,
			MUVGC_TYPE_MAT3X3,
			MUVGC_TYPE_MAT3X4,
			MUVGC_TYPE_MAT4X2,
			MUVGC_TYPE_MAT4X3,
			MUVGC_TYPE_MAT4X4,
			MUVGC_TYPE_DMAT2,
			MUVGC_TYPE_DMAT3,
			MUVGC_TYPE_DMAT4,
			MUVGC_TYPE_DMAT2X2,
			MUVGC_TYPE_DMAT2X3,
			MUVGC_TYPE_DMAT2X4,
			MUVGC_TYPE_DMAT3X2,
			MUVGC_TYPE_DMAT3X3,
			MUVGC_TYPE_DMAT3X4,
			MUVGC_TYPE_DMAT4X2,
			MUVGC_TYPE_DMAT4X3,
			MUVGC_TYPE_DMAT4X4,
			#define MUVGC_TRANSPARENT_TYPE_LAST MUVGC_TYPE_DMAT4X4
			// Floating-Point Opaque Types
			#define MUVGC_FLOATING_POINT_OPAQUE_TYPE_FIRST MUVGC_TYPE_SAMPLER1D
			MUVGC_TYPE_SAMPLER1D,
			MUVGC_TYPE_IMAGE1D,
			MUVGC_TYPE_SAMPLER2D,
			MUVGC_TYPE_IMAGE2D,
			MUVGC_TYPE_SAMPLER3D,
			MUVGC_TYPE_IMAGE3D,
			MUVGC_TYPE_SAMPLERCUBE,
			MUVGC_TYPE_IMAGECUBE,
			MUVGC_TYPE_SAMPLER2DRECT,
			MUVGC_TYPE_IMAGE2DRECT,
			MUVGC_TYPE_SAMPLER1DARRAY,
			MUVGC_TYPE_IMAGE1DARRAY,
			MUVGC_TYPE_SAMPLER2DARRAY,
			MUVGC_TYPE_IMAGE2DARRAY,
			MUVGC_TYPE_SAMPLERBUFFER,
			MUVGC_TYPE_IMAGEBUFFER,
			MUVGC_TYPE_SAMPLER2DMS,
			MUVGC_TYPE_IMAGE2DMS,
			MUVGC_TYPE_SAMPLER2DMSARRAY,
			MUVGC_TYPE_IMAGE2DMSARRAY,
			MUVGC_TYPE_SAMPLERCUBEARRAY,
			MUVGC_TYPE_IMAGECUBEARRAY,
			MUVGC_TYPE_SAMPLER1DSHADOW,
			MUVGC_TYPE_SAMPLER2DSHADOW,
			MUVGC_TYPE_SAMPLER2DRECTSHADOW,
			MUVGC_TYPE_SAMPLER1DARRAYSHADOW,
			MUVGC_TYPE_SAMPLER2DARRAYSHADOW,
			MUVGC_TYPE_SAMPLERCUBESHADOW,
			MUVGC_TYPE_SAMPLERCUBEARRAYSHADOW,
			#define MUVGC_FLOATING_POINT_OPAQUE_TYPE_LAST MUVGC_TYPE_SAMPLERCUBEARRAYSHADOW
			// Signed Integer Opaque Types
			#define MUVGC_SIGNED_INTEGER_OPAQUE_TYPE_FIRST MUVGC_TYPE_ISAMPLER1D
			MUVGC_TYPE_ISAMPLER1D,
			MUVGC_TYPE_IIMAGE1D,
			MUVGC_TYPE_ISAMPLER2D,
			MUVGC_TYPE_IIMAGE2D,
			MUVGC_TYPE_ISAMPLER3D,
			MUVGC_TYPE_IIMAGE3D,
			MUVGC_TYPE_ISAMPLERCUBE,
			MUVGC_TYPE_IIMAGECUBE,
			MUVGC_TYPE_ISAMPLER2DRECT,
			MUVGC_TYPE_IIMAGE2DRECT,
			MUVGC_TYPE_ISAMPLER1DARRAY,
			MUVGC_TYPE_IIMAGE1DARRAY,
			MUVGC_TYPE_ISAMPLER2DARRAY,
			MUVGC_TYPE_IIMAGE2DARRAY,
			MUVGC_TYPE_ISAMPLERBUFFER,
			MUVGC_TYPE_IIMAGEBUFFER,
			MUVGC_TYPE_ISAMPLER2DMS,
			MUVGC_TYPE_IIMAGE2DMS,
			MUVGC_TYPE_ISAMPLER2DMSARRAY,
			MUVGC_TYPE_IIMAGE2DMSARRAY,
			MUVGC_TYPE_ISAMPLERCUBEARRAY,
			MUVGC_TYPE_IIMAGECUBEARRAY,
			#define MUVGC_SIGNED_INTEGER_OPAQUE_TYPE_LAST MUVGC_TYPE_IIMAGECUBEARRAY
			// Unsigned Integer Opaque Types
			#define MUVGC_UNSIGNED_INTEGER_OPAQUE_TYPE_FIRST MUVGC_TYPE_USAMPLER1D
			MUVGC_TYPE_USAMPLER1D,
			MUVGC_TYPE_UIMAGE1D,
			MUVGC_TYPE_USAMPLER2D,
			MUVGC_TYPE_UIMAGE2D,
			MUVGC_TYPE_USAMPLER3D,
			MUVGC_TYPE_UIMAGE3D,
			MUVGC_TYPE_USAMPLERCUBE,
			MUVGC_TYPE_UIMAGECUBE,
			MUVGC_TYPE_USAMPLER2DRECT,
			MUVGC_TYPE_UIMAGE2DRECT,
			MUVGC_TYPE_USAMPLER1DARRAY,
			MUVGC_TYPE_UIMAGE1DARRAY,
			MUVGC_TYPE_USAMPLER2DARRAY,
			MUVGC_TYPE_UIMAGE2DARRAY,
			MUVGC_TYPE_USAMPLERBUFFER,
			MUVGC_TYPE_UIMAGEBUFFER,
			MUVGC_TYPE_USAMPLER2DMS,
			MUVGC_TYPE_UIMAGE2DMS,
			MUVGC_TYPE_USAMPLER2DMSARRAY,
			MUVGC_TYPE_UIMAGE2DMSARRAY,
			MUVGC_TYPE_USAMPLERCUBEARRAY,
			MUVGC_TYPE_UIMAGECUBEARRAY
			#define MUVGC_UNSIGNED_INTEGER_OPAQUE_TYPE_LAST MUVGC_TYPE_UIMAGECUBEARRAY
			#define MUVGC_BASIC_TYPE_LAST MUVGC_TYPE_UIMAGECUBEARRAY
			#define MUVGC_TYPE_UNKNOWN 2345
		};
		typedef enum muVGCBasicType muVGCBasicType;

		const char* muVGC_global_basic_type_names[] = {
			"void",
			"bool",
			"int",
			"uint",
			"float",
			"double",
			"vec2",
			"vec3",
			"vec4",
			"dvec2",
			"dvec3",
			"dvec4",
			"bvec2",
			"bvec3",
			"bvec4",
			"ivec2",
			"ivec3",
			"ivec4",
			"uvec2",
			"uvec3",
			"uvec4",
			"mat2",
			"mat3",
			"mat4",
			"mat2x2",
			"mat2x3",
			"mat2x4",
			"mat3x2",
			"mat3x3",
			"mat3x4",
			"mat4x2",
			"mat4x3",
			"mat4x4",
			"dmat2",
			"dmat3",
			"dmat4",
			"dmat2x2",
			"dmat2x3",
			"dmat2x4",
			"dmat3x2",
			"dmat3x3",
			"dmat3x4",
			"dmat4x2",
			"dmat4x3",
			"dmat4x4",
			"sampler1D",
			"image1D",
			"sampler2D",
			"image2D",
			"sampler3D",
			"image3D",
			"samplerCube",
			"imageCube",
			"sampler2DRect",
			"image2DRect",
			"sampler1DArray",
			"image1DArray",
			"sampler2DArray",
			"image2DArray",
			"samplerBuffer",
			"imageBuffer",
			"sampler2DMS",
			"image2DMS",
			"sampler2DMSArray",
			"image2DMSArray",
			"samplerCubeArray",
			"imageCubeArray",
			"sampler1DShadow",
			"sampler2DShadow",
			"sampler2DRectShadow",
			"sampler1DArrayShadow",
			"sampler2DArrayShadow",
			"samplerCubeShadow",
			"samplerCubeArrayShadow",
			"isampler1D",
			"iimage1D",
			"isampler2D",
			"iimage2D",
			"isampler3D",
			"iimage3D",
			"isamplerCube",
			"iimageCube",
			"isampler2DRect",
			"iimage2DRect",
			"isampler1DArray",
			"iimage1DArray",
			"isampler2DArray",
			"iimage2DArray",
			"isamplerBuffer",
			"iimageBuffer",
			"isampler2DMS",
			"iimage2DMS",
			"isampler2DMSArray",
			"iimage2DMSArray",
			"isamplerCubeArray",
			"iimageCubeArray",
			"usampler1D",
			"uimage1D",
			"usampler2D",
			"uimage2D",
			"usampler3D",
			"uimage3D",
			"usamplerCube",
			"uimageCube",
			"usampler2DRect",
			"uimage2DRect",
			"usampler1DArray",
			"uimage1DArray",
			"usampler2DArray",
			"uimage2DArray",
			"usamplerBuffer",
			"uimageBuffer",
			"usampler2DMS",
			"uimage2DMS",
			"usampler2DMSArray",
			"uimage2DMSArray",
			"usamplerCubeArray",
			"uimageCubeArray"
		};

		const char* muVGC_get_basic_type_name(muVGCBasicType type) {
			return muVGC_global_basic_type_names[type];
		}

		muVGCBasicType muVGC_get_basic_type(const char* name, size_m namelen) {
			for (size_m i = MUVGC_BASIC_TYPE_FIRST; i < MUVGC_BASIC_TYPE_LAST; i++) {
				if (mu_strlen(muVGC_get_basic_type_name(i)) == namelen) {
					if (mu_strncmp(name, muVGC_get_basic_type_name(i), namelen) == 0) {
						return i;
					}
				}
			}
			return MUVGC_TYPE_UNKNOWN;
		}

	// Structs

		struct muVGCParameter {
			muVGCBasicType type;
			muVGCToken token_name;
			muBool is_array;
			size_m arraylen;
		};
		typedef struct muVGCParameter muVGCParameter;

		muBool muVGC_are_two_parameters_equivalent(const char* code, muVGCParameter p0, muVGCParameter p1) {
			return p0.type == p1.type && p0.token_name.length == p1.token_name.length &&
			mu_strncmp(muVGC_get_token_value(code, p0.token_name), muVGC_get_token_value(code, p1.token_name), p0.token_name.length) == 0 &&
			p0.is_array == p1.is_array && p0.arraylen == p1.arraylen;
		}

		struct muVGCVariable {
			muBool active;
			muVGCBasicType type;
			muVGCToken token_name;
			muBool is_array;
			size_m arraylen;
			muBool is_function;
			size_m scope;
			muBool is_function_implemented;
			muVGCParameter* parameters;
			size_m parameterlen;
			uint32_m id;
		};
		typedef struct muVGCVariable muVGCVariable;

		muVGCVariable muVGC_make_variable(
			muBool active, muVGCBasicType type, muVGCToken token_name, muBool is_array, 
			size_m arraylen, muBool is_function, size_m scope, muBool is_function_implemented,
			muVGCParameter* parameters, size_m parameterlen, uint32_m id) {
			muVGCVariable var = {0};
			var.active = active; var.type = type; var.token_name = token_name;
			var.is_array = is_array; var.arraylen = arraylen; var.is_function = is_function;
			var.scope = scope; var.is_function_implemented = is_function_implemented;
			var.parameters = parameters; var.parameterlen = parameterlen; var.id = id;
			return var;
		}

		struct muVGCVariableList {
			muVGCVariable* variables;
			size_m len;
			size_m allocated_len;
		};
		typedef struct muVGCVariableList muVGCVariableList;

	// Functions

		muVGCVariableList muVGC_intialize_empty_variable_list() {
			muVGCVariableList list = {0};
			list.variables = MU_NULL_PTR;
			list.len = 0;
			list.allocated_len = 0;
			return list;
		}

		muVGCVariableList muVGC_empty_variable_list(muVGCVariableList list) {
			if (list.variables != MU_NULL_PTR) {
				for (size_m i = 0; i < list.allocated_len; i++) {
					if (list.variables[i].parameters != MU_NULL_PTR) {
						mu_free(list.variables[i].parameters);
						list.variables[i].parameters = MU_NULL_PTR;
						list.variables[i].parameterlen = 0;
					}
				}
				mu_free(list.variables);
				list.variables = MU_NULL_PTR;
			}
			list.len = 0;
			list.allocated_len = 0;
			return list;
		}

		muVGCVariableList muVGC_add_variable(muVGCVariableList list, muVGCVariable var) {
			if (list.variables == MU_NULL_PTR) {
				list.len = 1;
				list.allocated_len = 2;
				list.variables = mu_malloc(sizeof(muVGCVariable) * list.allocated_len);
				list.variables[0] = var;
				list.variables[0].active = MU_TRUE;
				return list;
			}
			for (size_m i = 0; i < list.len; i++) {
				if (list.variables[i].active == MU_FALSE) {
					list.variables[i] = var;
					list.variables[i].active = MU_TRUE;
					return list;
				}
			}
			list.len += 1;
			if (list.len >= list.allocated_len) {
				list.allocated_len *= 2;
				list.variables = mu_realloc(list.variables, list.allocated_len * sizeof(muVGCVariable));
			}
			list.variables[list.len-1] = var;
			list.variables[list.len-1].active = MU_TRUE;
			return list;
		}

		muVGCVariableList muVGC_remove_variable(muVGCVariableList list, size_m i) {
			if (i < list.len) {
				list.variables[i].active = MU_FALSE;
				if (list.variables[i].parameters != MU_NULL_PTR) {
					mu_free(list.variables[i].parameters);
					list.variables[i].parameters = MU_NULL_PTR;
					list.variables[i].parameterlen = 0;
				}
			}
			return list;
		}

	// Declaration functions

		muString muVGC_get_transparent_type(muString bytecode, muVGCBasicType type, uint32_m* id, uint32_m* global_id) {
			switch (type) {
				default: return bytecode; break;
				case MUVGC_TYPE_VOID: {
					return muVGC_get_void_type(bytecode, id, global_id);
				} break;
				case MUVGC_TYPE_BOOL: {
					return muVGC_get_bool_type(bytecode, id, global_id);
				} break;
				case MUVGC_TYPE_INT: {
					return muVGC_get_int_type(bytecode, id, global_id, 32, 1);
				} break;
				case MUVGC_TYPE_UINT: {
					return muVGC_get_int_type(bytecode, id, global_id, 32, 0);
				} break;
				case MUVGC_TYPE_FLOAT: {
					return muVGC_get_float_type(bytecode, id, global_id, 32);
				} break;
				case MUVGC_TYPE_DOUBLE: {
					return muVGC_get_float_type(bytecode, id, global_id, 64);
				} break;
				case MUVGC_TYPE_VEC2: {
					uint32_m cmp = 0;
					bytecode = muVGC_get_float_type(bytecode, &cmp, global_id, 32);
					return muVGC_get_vector_type(bytecode, id, global_id, cmp, 2);
				} break;
				case MUVGC_TYPE_VEC3: {
					uint32_m cmp = 0;
					bytecode = muVGC_get_float_type(bytecode, &cmp, global_id, 32);
					return muVGC_get_vector_type(bytecode, id, global_id, cmp, 3);
				} break;
				case MUVGC_TYPE_VEC4: {
					uint32_m cmp = 0;
					bytecode = muVGC_get_float_type(bytecode, &cmp, global_id, 32);
					return muVGC_get_vector_type(bytecode, id, global_id, cmp, 4);
				} break;
				case MUVGC_TYPE_DVEC2: {
					uint32_m cmp = 0;
					bytecode = muVGC_get_float_type(bytecode, &cmp, global_id, 64);
					return muVGC_get_vector_type(bytecode, id, global_id, cmp, 2);
				} break;
				case MUVGC_TYPE_DVEC3: {
					uint32_m cmp = 0;
					bytecode = muVGC_get_float_type(bytecode, &cmp, global_id, 64);
					return muVGC_get_vector_type(bytecode, id, global_id, cmp, 3);
				} break;
				case MUVGC_TYPE_DVEC4: {
					uint32_m cmp = 0;
					bytecode = muVGC_get_float_type(bytecode, &cmp, global_id, 64);
					return muVGC_get_vector_type(bytecode, id, global_id, cmp, 4);
				} break;
				case MUVGC_TYPE_BVEC2: {
					uint32_m cmp = 0;
					bytecode = muVGC_get_bool_type(bytecode, &cmp, global_id);
					return muVGC_get_vector_type(bytecode, id, global_id, cmp, 2);
				} break;
				case MUVGC_TYPE_BVEC3: {
					uint32_m cmp = 0;
					bytecode = muVGC_get_bool_type(bytecode, &cmp, global_id);
					return muVGC_get_vector_type(bytecode, id, global_id, cmp, 3);
				} break;
				case MUVGC_TYPE_BVEC4: {
					uint32_m cmp = 0;
					bytecode = muVGC_get_bool_type(bytecode, &cmp, global_id);
					return muVGC_get_vector_type(bytecode, id, global_id, cmp, 4);
				} break;
				case MUVGC_TYPE_IVEC2: {
					uint32_m cmp = 0;
					bytecode = muVGC_get_int_type(bytecode, &cmp, global_id, 32, 1);
					return muVGC_get_vector_type(bytecode, id, global_id, cmp, 2);
				} break;
				case MUVGC_TYPE_IVEC3: {
					uint32_m cmp = 0;
					bytecode = muVGC_get_int_type(bytecode, &cmp, global_id, 32, 1);
					return muVGC_get_vector_type(bytecode, id, global_id, cmp, 3);
				} break;
				case MUVGC_TYPE_IVEC4: {
					uint32_m cmp = 0;
					bytecode = muVGC_get_int_type(bytecode, &cmp, global_id, 32, 1);
					return muVGC_get_vector_type(bytecode, id, global_id, cmp, 4);
				} break;
				case MUVGC_TYPE_UVEC2: {
					uint32_m cmp = 0;
					bytecode = muVGC_get_int_type(bytecode, &cmp, global_id, 32, 0);
					return muVGC_get_vector_type(bytecode, id, global_id, cmp, 2);
				} break;
				case MUVGC_TYPE_UVEC3: {
					uint32_m cmp = 0;
					bytecode = muVGC_get_int_type(bytecode, &cmp, global_id, 32, 0);
					return muVGC_get_vector_type(bytecode, id, global_id, cmp, 3);
				} break;
				case MUVGC_TYPE_UVEC4: {
					uint32_m cmp = 0;
					bytecode = muVGC_get_int_type(bytecode, &cmp, global_id, 32, 0);
					return muVGC_get_vector_type(bytecode, id, global_id, cmp, 4);
				} break;
				case MUVGC_TYPE_MAT2: {
					uint32_m cmp = 0, cmp2 = 0;
					bytecode = muVGC_get_float_type(bytecode, &cmp, global_id, 32);
					bytecode = muVGC_get_vector_type(bytecode, &cmp2, global_id, cmp, 2);
					return muVGC_get_matrix_type(bytecode, id, global_id, cmp2, 2);
				} break;
				case MUVGC_TYPE_MAT3: {
					uint32_m cmp = 0, cmp2 = 0;
					bytecode = muVGC_get_float_type(bytecode, &cmp, global_id, 32);
					bytecode = muVGC_get_vector_type(bytecode, &cmp2, global_id, cmp, 3);
					return muVGC_get_matrix_type(bytecode, id, global_id, cmp2, 3);
				} break;
				case MUVGC_TYPE_MAT4: {
					uint32_m cmp = 0, cmp2 = 0;
					bytecode = muVGC_get_float_type(bytecode, &cmp, global_id, 32);
					bytecode = muVGC_get_vector_type(bytecode, &cmp2, global_id, cmp, 4);
					return muVGC_get_matrix_type(bytecode, id, global_id, cmp2, 4);
				} break;
				case MUVGC_TYPE_MAT2X2: {
					uint32_m cmp = 0, cmp2 = 0;
					bytecode = muVGC_get_float_type(bytecode, &cmp, global_id, 32);
					bytecode = muVGC_get_vector_type(bytecode, &cmp2, global_id, cmp, 2);
					return muVGC_get_matrix_type(bytecode, id, global_id, cmp2, 2);
				} break;
				case MUVGC_TYPE_MAT2X3: {
					uint32_m cmp = 0, cmp2 = 0;
					bytecode = muVGC_get_float_type(bytecode, &cmp, global_id, 32);
					bytecode = muVGC_get_vector_type(bytecode, &cmp2, global_id, cmp, 3);
					return muVGC_get_matrix_type(bytecode, id, global_id, cmp2, 2);
				} break;
				case MUVGC_TYPE_MAT2X4: {
					uint32_m cmp = 0, cmp2 = 0;
					bytecode = muVGC_get_float_type(bytecode, &cmp, global_id, 32);
					bytecode = muVGC_get_vector_type(bytecode, &cmp2, global_id, cmp, 4);
					return muVGC_get_matrix_type(bytecode, id, global_id, cmp2, 2);
				} break;
				case MUVGC_TYPE_MAT3X2: {
					uint32_m cmp = 0, cmp2 = 0;
					bytecode = muVGC_get_float_type(bytecode, &cmp, global_id, 32);
					bytecode = muVGC_get_vector_type(bytecode, &cmp2, global_id, cmp, 2);
					return muVGC_get_matrix_type(bytecode, id, global_id, cmp2, 3);
				} break;
				case MUVGC_TYPE_MAT3X3: {
					uint32_m cmp = 0, cmp2 = 0;
					bytecode = muVGC_get_float_type(bytecode, &cmp, global_id, 32);
					bytecode = muVGC_get_vector_type(bytecode, &cmp2, global_id, cmp, 3);
					return muVGC_get_matrix_type(bytecode, id, global_id, cmp2, 3);
				} break;
				case MUVGC_TYPE_MAT3X4: {
					uint32_m cmp = 0, cmp2 = 0;
					bytecode = muVGC_get_float_type(bytecode, &cmp, global_id, 32);
					bytecode = muVGC_get_vector_type(bytecode, &cmp2, global_id, cmp, 4);
					return muVGC_get_matrix_type(bytecode, id, global_id, cmp2, 3);
				} break;
				case MUVGC_TYPE_MAT4X2: {
					uint32_m cmp = 0, cmp2 = 0;
					bytecode = muVGC_get_float_type(bytecode, &cmp, global_id, 32);
					bytecode = muVGC_get_vector_type(bytecode, &cmp2, global_id, cmp, 2);
					return muVGC_get_matrix_type(bytecode, id, global_id, cmp2, 4);
				} break;
				case MUVGC_TYPE_MAT4X3: {
					uint32_m cmp = 0, cmp2 = 0;
					bytecode = muVGC_get_float_type(bytecode, &cmp, global_id, 32);
					bytecode = muVGC_get_vector_type(bytecode, &cmp2, global_id, cmp, 3);
					return muVGC_get_matrix_type(bytecode, id, global_id, cmp2, 4);
				} break;
				case MUVGC_TYPE_MAT4X4: {
					uint32_m cmp = 0, cmp2 = 0;
					bytecode = muVGC_get_float_type(bytecode, &cmp, global_id, 32);
					bytecode = muVGC_get_vector_type(bytecode, &cmp2, global_id, cmp, 4);
					return muVGC_get_matrix_type(bytecode, id, global_id, cmp2, 4);
				} break;
				case MUVGC_TYPE_DMAT2: {
					uint32_m cmp = 0, cmp2 = 0;
					bytecode = muVGC_get_float_type(bytecode, &cmp, global_id, 64);
					bytecode = muVGC_get_vector_type(bytecode, &cmp2, global_id, cmp, 2);
					return muVGC_get_matrix_type(bytecode, id, global_id, cmp2, 2);
				} break;
				case MUVGC_TYPE_DMAT3: {
					uint32_m cmp = 0, cmp2 = 0;
					bytecode = muVGC_get_float_type(bytecode, &cmp, global_id, 64);
					bytecode = muVGC_get_vector_type(bytecode, &cmp2, global_id, cmp, 3);
					return muVGC_get_matrix_type(bytecode, id, global_id, cmp2, 3);
				} break;
				case MUVGC_TYPE_DMAT4: {
					uint32_m cmp = 0, cmp2 = 0;
					bytecode = muVGC_get_float_type(bytecode, &cmp, global_id, 64);
					bytecode = muVGC_get_vector_type(bytecode, &cmp2, global_id, cmp, 4);
					return muVGC_get_matrix_type(bytecode, id, global_id, cmp2, 4);
				} break;
				case MUVGC_TYPE_DMAT2X2: {
					uint32_m cmp = 0, cmp2 = 0;
					bytecode = muVGC_get_float_type(bytecode, &cmp, global_id, 64);
					bytecode = muVGC_get_vector_type(bytecode, &cmp2, global_id, cmp, 2);
					return muVGC_get_matrix_type(bytecode, id, global_id, cmp2, 2);
				} break;
				case MUVGC_TYPE_DMAT2X3: {
					uint32_m cmp = 0, cmp2 = 0;
					bytecode = muVGC_get_float_type(bytecode, &cmp, global_id, 64);
					bytecode = muVGC_get_vector_type(bytecode, &cmp2, global_id, cmp, 3);
					return muVGC_get_matrix_type(bytecode, id, global_id, cmp2, 2);
				} break;
				case MUVGC_TYPE_DMAT2X4: {
					uint32_m cmp = 0, cmp2 = 0;
					bytecode = muVGC_get_float_type(bytecode, &cmp, global_id, 64);
					bytecode = muVGC_get_vector_type(bytecode, &cmp2, global_id, cmp, 4);
					return muVGC_get_matrix_type(bytecode, id, global_id, cmp2, 2);
				} break;
				case MUVGC_TYPE_DMAT3X2: {
					uint32_m cmp = 0, cmp2 = 0;
					bytecode = muVGC_get_float_type(bytecode, &cmp, global_id, 64);
					bytecode = muVGC_get_vector_type(bytecode, &cmp2, global_id, cmp, 2);
					return muVGC_get_matrix_type(bytecode, id, global_id, cmp2, 3);
				} break;
				case MUVGC_TYPE_DMAT3X3: {
					uint32_m cmp = 0, cmp2 = 0;
					bytecode = muVGC_get_float_type(bytecode, &cmp, global_id, 64);
					bytecode = muVGC_get_vector_type(bytecode, &cmp2, global_id, cmp, 3);
					return muVGC_get_matrix_type(bytecode, id, global_id, cmp2, 3);
				} break;
				case MUVGC_TYPE_DMAT3X4: {
					uint32_m cmp = 0, cmp2 = 0;
					bytecode = muVGC_get_float_type(bytecode, &cmp, global_id, 64);
					bytecode = muVGC_get_vector_type(bytecode, &cmp2, global_id, cmp, 4);
					return muVGC_get_matrix_type(bytecode, id, global_id, cmp2, 3);
				} break;
				case MUVGC_TYPE_DMAT4X2: {
					uint32_m cmp = 0, cmp2 = 0;
					bytecode = muVGC_get_float_type(bytecode, &cmp, global_id, 64);
					bytecode = muVGC_get_vector_type(bytecode, &cmp2, global_id, cmp, 2);
					return muVGC_get_matrix_type(bytecode, id, global_id, cmp2, 4);
				} break;
				case MUVGC_TYPE_DMAT4X3: {
					uint32_m cmp = 0, cmp2 = 0;
					bytecode = muVGC_get_float_type(bytecode, &cmp, global_id, 64);
					bytecode = muVGC_get_vector_type(bytecode, &cmp2, global_id, cmp, 3);
					return muVGC_get_matrix_type(bytecode, id, global_id, cmp2, 4);
				} break;
				case MUVGC_TYPE_DMAT4X4: {
					uint32_m cmp = 0, cmp2 = 0;
					bytecode = muVGC_get_float_type(bytecode, &cmp, global_id, 64);
					bytecode = muVGC_get_vector_type(bytecode, &cmp2, global_id, cmp, 4);
					return muVGC_get_matrix_type(bytecode, id, global_id, cmp2, 4);
				} break;
			}
		}

/* STATEMENT TYPE HANDLING */

	// Statement types

	enum muVGCStatementType {
		MUVGC_STATEMENT_UNKNOWN=0,
		MUVGC_STATEMENT_FUNCTION_IMPLEMENTATION=1,
		MUVGC_STATEMENT_SCOPE_OPEN=2,
		MUVGC_STATEMENT_SCOPE_CLOSE=3

		#define MUVGC_STATEMENT_FIRST MUVGC_STATEMENT_FUNCTION_IMPLEMENTATION
		#define MUVGC_STATEMENT_LAST  MUVGC_STATEMENT_SCOPE_CLOSE
	};
	typedef enum muVGCStatementType muVGCStatementType;

	// @DEBUG
	void muVGC_print_statement_type(muVGCStatementType type) {
		switch (type) {
			default: mu_print("unknown"); break;
			case MUVGC_STATEMENT_FUNCTION_IMPLEMENTATION: mu_print("function implementation"); break;
			case MUVGC_STATEMENT_SCOPE_OPEN: mu_print("scope open"); break;
			case MUVGC_STATEMENT_SCOPE_CLOSE: mu_print("scope close"); break;
		}
	}

	// Statement type handling

	muResult muVGC_check_statement_type(muResult* result,
		muVGCStatementType type, muVGCToken* tokens, 
		size_m token_len, const char* code, const char* og, size_m* length) {

		switch (type) {
			default: {
				muVGC_print_syntax_error(og, tokens[0].index);
				mu_print("unexpected token '");
				muVGC_print_token_type(tokens[0].type);
				mu_print("\n");
				*result = MU_FAILURE;
				return MU_FAILURE;
			} break;

			case MUVGC_STATEMENT_FUNCTION_IMPLEMENTATION: {
				// A A(...
				if (token_len > 3) {
					if (
						(tokens[0].type == MUVGC_TOKEN_KEYWORD || tokens[0].type == MUVGC_TOKEN_IDENTIFIER) &&
						(tokens[1].type == MUVGC_TOKEN_IDENTIFIER) &&
						(tokens[2].type == MUVGC_TOKEN_OPEN_PARENTHESIS)
					) {
						// A A(...,... ...)
						size_m i = 3;
						while (tokens[i].type != MUVGC_TOKEN_CLOSE_PARENTHESIS) {
							// Qualifiers
							size_m qualifier_count = 0;
							while (
								tokens[i+qualifier_count].type == MUVGC_TOKEN_KEYWORD &&
								((tokens[i+qualifier_count].length == 5 && mu_strncmp(muVGC_get_token_value(code, tokens[i+qualifier_count]), "const", 5) == 0) ||
								(tokens[i+qualifier_count].length == 2 && mu_strncmp(muVGC_get_token_value(code, tokens[i+qualifier_count]), "in", 2) == 0) ||
								(tokens[i+qualifier_count].length == 3 && mu_strncmp(muVGC_get_token_value(code, tokens[i+qualifier_count]), "out", 3) == 0) ||
								(tokens[i+qualifier_count].length == 5 && mu_strncmp(muVGC_get_token_value(code, tokens[i+qualifier_count]), "inout", 5) == 0) ||
								(tokens[i+qualifier_count].length == 7 && mu_strncmp(muVGC_get_token_value(code, tokens[i+qualifier_count]), "precise", 7) == 0))
							) {
								qualifier_count++;
							}
							if (qualifier_count > 2) {
								muVGC_print_syntax_error(og, tokens[i+3].index);
								mu_print("too many storage qualifiers\n");
								*result = MU_FAILURE;
								return MU_FAILURE;
							}
							i += qualifier_count;

							// Type
							if (tokens[i].type != MUVGC_TOKEN_KEYWORD && tokens[i].type != MUVGC_TOKEN_IDENTIFIER) {
								muVGC_print_syntax_error(og, tokens[i].index);
								mu_print("expected keyword or identifier\n");
								*result = MU_FAILURE;
								return MU_FAILURE;
							}
							i++;

							// Name
							if (tokens[i].type != MUVGC_TOKEN_IDENTIFIER) {
								muVGC_print_syntax_error(og, tokens[i].index);
								mu_print("expected identifier\n");
								*result = MU_FAILURE;
								return MU_FAILURE;
							}
							i++;

							// Array
							if (tokens[i].type == MUVGC_TOKEN_OPEN_SQUARE_BRACKET) {
								if (tokens[i+1].type != MUVGC_TOKEN_INTEGER_CONSTANT) {
									muVGC_print_syntax_error(og, tokens[i+1].index);
									mu_print("expected integer after '['\n");
									*result = MU_FAILURE;
									return MU_FAILURE;
								}
								if (tokens[i+2].type != MUVGC_TOKEN_CLOSE_SQUARE_BRACKET) {
									muVGC_print_syntax_error(og, tokens[i+2].index);
									mu_print("expected ']' after integer\n");
									*result = MU_FAILURE;
									return MU_FAILURE;
								}
								i += 3;
							}

							// End of parameter
							if (tokens[i].type == MUVGC_TOKEN_COMMA) {
								i++;
							} else if (tokens[i].type != MUVGC_TOKEN_CLOSE_PARENTHESIS) {
								muVGC_print_syntax_error(og, tokens[i].index);
								mu_print("expected comma or close parenthesis\n");
								*result = MU_FAILURE;
								return MU_FAILURE;
							}
						}
						// A A(){...
						// A A();
						if (tokens[i+1].type != MUVGC_TOKEN_SEMICOLON && tokens[i+1].type != MUVGC_TOKEN_OPEN_BRACE) {
							muVGC_print_syntax_error(og, tokens[i+1].index);
							mu_print("expected semicolon or open brace\n");
							*result = MU_FAILURE;
							return MU_FAILURE;
						} else if (tokens[i+1].type == MUVGC_TOKEN_OPEN_BRACE) {
							*length = i+2;
							return MU_SUCCESS;
						}
						return MU_FAILURE;
					}
				}
				return MU_FAILURE;
			} break;

			case MUVGC_STATEMENT_SCOPE_OPEN: {
				if (tokens[0].type == MUVGC_TOKEN_OPEN_BRACE) {
					*length = 1;
					return MU_SUCCESS;
				}
				return MU_FAILURE;
			} break;

			case MUVGC_STATEMENT_SCOPE_CLOSE: {
				if (tokens[0].type == MUVGC_TOKEN_CLOSE_BRACE) {
					*length = 1;
					return MU_SUCCESS;
				}
				return MU_FAILURE;
			} break;
		}
	}

	muString muVGC_execute_statement_type(
		muResult* result, muVGCStatementType type, muVGCToken* tokens, 
		size_m token_len, const char* code, const char* og, muString bytecode,
		size_m* scope_count, uint32_m* global_id, muVGCVariableList* varlist) {

		//muResult res = MU_SUCCESS;

		switch (type) {
			default: *result = MU_FAILURE; return bytecode; break;

			case MUVGC_STATEMENT_FUNCTION_IMPLEMENTATION: {
				// @TODO check for variable name duplication here

				muVGCBasicType return_type = muVGC_get_basic_type(muVGC_get_token_value(code, tokens[0]), tokens[0].length);
				if (return_type == MUVGC_TYPE_UNKNOWN) {
					// @TODO add struct checking
					muVGC_print_syntax_error(og, tokens[0].index);
					mu_print("unrecognized type specified\n");
					*result = MU_FAILURE;
					return bytecode;
				}
				if (return_type < MUVGC_TRANSPARENT_TYPE_FIRST || return_type > MUVGC_TRANSPARENT_TYPE_LAST) {
					muVGC_print_syntax_error(og,tokens[0].index);
					mu_print("only transparent types can be used as a return value\n");
					*result = MU_FAILURE;
					return bytecode;
				}

				uint32_m return_type_id = 0;
				bytecode = muVGC_get_transparent_type(bytecode, return_type, &return_type_id, global_id);
				if (return_type_id == 0) {
					// This should never trigger but still
					muVGC_print_syntax_error(og, tokens[0].index);
					mu_print("failed to declare type\n");
					*result = MU_FAILURE;
					return bytecode;
				}

				// @TODO Find a clean way (or way at all) to gather parameters
				size_m parameter_count = 0;
				uint32_m function_type = 0;
				bytecode = muVGC_get_function_type(bytecode, &function_type, global_id, return_type_id, MU_NULL_PTR, 0);
				bytecode = muVGC_op_function(bytecode, return_type_id, 0, function_type, global_id);
				size_m function_id = *global_id - 1;
				bytecode = muVGC_op_name(bytecode, function_id, muVGC_get_token_value(code, tokens[1]), tokens[1].length);
				bytecode = muVGC_op_label(bytecode, *global_id);
				*global_id += 1;
				if (return_type == MUVGC_TYPE_VOID) {
					bytecode = muVGC_op_return(bytecode);
				}
				bytecode = muVGC_op_function_end(bytecode);

				for (size_m i = 0; i < varlist->len; i++) {
					if (varlist->variables[i].active == MU_TRUE && 
						varlist->variables[i].token_name.length == tokens[1].length &&
						mu_strncmp(muVGC_get_token_value(code, varlist->variables[i].token_name), muVGC_get_token_value(code, tokens[1]), tokens[1].length) == 0) {

						if (varlist->variables[i].is_function == MU_FALSE) {
							muVGC_print_syntax_error(og, tokens[1].index);
							mu_print("variable declared again as function\n");
							*result = MU_FAILURE;
							return bytecode;
						}

						if (varlist->variables[i].is_function_implemented == MU_TRUE) {
							muVGC_print_syntax_error(og, tokens[1].index);
							mu_print("function implemented numerous times\n");
							*result = MU_FAILURE;
							return bytecode;
						}

						if (varlist->variables[i].type != return_type) {
							muVGC_print_syntax_error(og, tokens[1].index);
							mu_print("function redeclared with different return type\n");
							*result = MU_FAILURE;
							return bytecode;
						}

						if (varlist->variables[i].parameterlen != parameter_count) {
							muVGC_print_syntax_error(og, tokens[1].index);
							mu_print("function redeclared with different number of parameters\n");
							*result = MU_FAILURE;
							return bytecode;
						}

						// @TODO check for parameter equivalence
						/*for (size_m j = 0; j < parameter_count; j++) {
							if (muVGC_are_two_parameters_equivalent(code, varlist->variables[i].parameters[j], ))
						}*/
					}
				}

				*varlist = muVGC_add_variable(*varlist, muVGC_make_variable(MU_TRUE, return_type, tokens[1], MU_FALSE, 0, MU_TRUE, 0, MU_TRUE, MU_NULL_PTR, 0, function_id));

				*scope_count += 1;
				return bytecode;
			} break;

			case MUVGC_STATEMENT_SCOPE_OPEN: {
				*scope_count += 1;
				return bytecode;
			} break;

			case MUVGC_STATEMENT_SCOPE_CLOSE: {
				if (scope_count == 0) {
					muVGC_print_syntax_error(og, tokens[0].index);
					mu_print("too many close braces\n");
					*result = MU_FAILURE;
					return bytecode;
				}
				*scope_count -= 1;
				return bytecode;
			} break;
		}
	}

/* STATEMENT HANDLING */

	// Statement retrieval

	struct muVGCStatement {
		muVGCStatementType type;
		size_m index;
		size_m length;
	};
	typedef struct muVGCStatement muVGCStatement;

	muVGCStatement muVGC_get_statement(
		muResult* result, muVGCToken* tokens, size_m token_len, size_m total_token_len, const char* code, const char* og) {

		muVGCStatement statement = { 0 };
		statement.type = MUVGC_STATEMENT_UNKNOWN;
		muResult res = MU_SUCCESS;

		for (muVGCStatementType type = MUVGC_STATEMENT_FIRST; type <= MUVGC_STATEMENT_LAST; type++) {
			if (muVGC_check_statement_type(&res, type, tokens, token_len, code, og, &statement.length) == MU_SUCCESS) {
				if (res != MU_SUCCESS) {
					*result = MU_FAILURE;
					return statement;
				}

				statement.type = type;
				statement.index = total_token_len-token_len;
				return statement;
			}
			if (res != MU_SUCCESS) {
				*result = MU_FAILURE;
				return statement;
			}
		}

		muVGC_print_syntax_error(og, tokens[0].index);
		mu_print("unrecognized statement\n");

		*result = MU_FAILURE;
		return statement;
	}

	muVGCStatement* muVGC_get_statements(
		muVGCToken* tokens, size_m token_len, const char* code, const char* og, size_m* statement_length) {

		// Similar issue to retrieving tokens, as I have to do the process twice

		muResult res = MU_SUCCESS;
		size_m statement_len = 0;

		for (size_m i = 0; i < token_len;) {
			muVGCStatement statement = muVGC_get_statement(&res, &tokens[i], token_len-i, token_len, code, og);

			if (res != MU_SUCCESS) {
				return MU_NULL_PTR;
			}
			statement_len++;
			i += statement.length;
		}

		if (statement_len == 0) {
			// Not exactly sure what would ever cause this, but allowing malloc to call will
			// cause an immediate crash, so, yeah
			mu_print("[muVGC] Syntax error; expected at least one statement after version\n");
			return MU_NULL_PTR;
		}
		muVGCStatement* statements = mu_malloc(sizeof(muVGCStatement) * statement_len);

		size_m index = 0;
		for (size_m i = 0; i < token_len;) {
			muVGCStatement statement = muVGC_get_statement(&res, &tokens[i], token_len-i, token_len, code, og);

			if (res != MU_SUCCESS) {
				mu_free(statements);
				return MU_NULL_PTR;
			}
			statements[index] = statement;
			index++;
			i += statement.length;
		}

		*statement_length = statement_len;
		return statements;
	}

	// Statement execution

	muString muVGC_execute_function(
		muResult* result, muString bytecode, muVGCStatement* statements, size_m statement_len,
		muVGCToken* tokens, size_m token_len, const char* code, const char* og,
		uint32_m* global_id, muVGCVariableList* varlist) {

		size_m scope_count = 0;
		muResult res = MU_SUCCESS;
		size_m i = 1;

		bytecode = muVGC_execute_statement_type(&res, statements[0].type, tokens, token_len, code, og, bytecode, &scope_count, global_id, varlist);
		if (res != MU_SUCCESS) {
			*result = MU_FAILURE;
			return bytecode;
		}

		while (scope_count > 0 && i < token_len && tokens[i].type != MUVGC_TOKEN_END_OF_FILE) {
			bytecode = muVGC_execute_statement_type(&res, statements[i].type, &tokens[i], token_len-i, code, og, bytecode, &scope_count, global_id, varlist);
			if (res != MU_SUCCESS) {
				*result = MU_FAILURE;
				return bytecode;
			}

			i++;
		}

		if (scope_count > 0 && (i >= token_len || tokens[i].type == MUVGC_TOKEN_END_OF_FILE)) {
			muVGC_print_syntax_error(og, tokens[token_len-1].index);
			mu_print("expected a close brace before end of file\n");
			*result = MU_FAILURE;
			return bytecode;
		}

		return bytecode;
	}

	muString muVGC_declare_main_function(
		muResult* result, muString bytecode, muVGCStatement* statements, size_m statement_len,
		muVGCToken* tokens, size_m token_len, const char* code, const char* og,
		uint32_m* global_id, muVGCVariableList* varlist) {

		muBool found_main = MU_FALSE;
		for (size_m i = 0; i < statement_len; i++) {
			if (statements[i].type == MUVGC_STATEMENT_FUNCTION_IMPLEMENTATION &&
				tokens[statements[i].index+1].length == 4 &&
				mu_strncmp(muVGC_get_token_value(code, tokens[statements[i].index+1]), "main", 4) == 0) {

				if (found_main == MU_TRUE) {
					muVGC_print_syntax_error(og, tokens[statements[i].index+1].index);
					mu_print("multiple entry point 'main' functions declared\n");
					*result = MU_FAILURE;
					return bytecode;
				}
				found_main = MU_TRUE;

				if ((tokens[statements[i].index].length != 4) ||
					(mu_strncmp(muVGC_get_token_value(code, tokens[statements[i].index]), "void", 4) != 0)) {

					muVGC_print_syntax_error(og, tokens[statements[i].index].index);
					mu_print("entry point 'main' function declared as something else than void\n");
					*result = MU_FAILURE;
					return bytecode;
				}

				if ((tokens[statements[i].index+3].type != MUVGC_TOKEN_CLOSE_PARENTHESIS)) {
					muVGC_print_syntax_error(og, tokens[statements[i].index+3].index);
					mu_print("entry point 'main' function declared with parameters\n");
					*result = MU_FAILURE;
					return bytecode;
				}

				muResult res = MU_SUCCESS;
				bytecode = muVGC_execute_function(&res, bytecode, statements, statement_len, tokens, token_len, code, og, global_id, varlist);
				if (res != MU_SUCCESS) {
					*result = MU_FAILURE;
					return bytecode;
				}
			}
		}

		if (found_main == MU_FALSE) {
			mu_print("[muVGC] Error while compiling; no entry point 'main' function found\n");
			*result = MU_FAILURE;
			return bytecode;
		}

		return bytecode;
	}

	muString muVGC_execute_statements(
		muResult* result, muString bytecode, muVGCStatement* statements, size_m statement_len,
		muVGCToken* tokens, size_m token_len, const char* code, const char* og,
		uint32_m* global_id, muVGCVariableList* varlist) {

		muResult res = MU_SUCCESS;

		bytecode = muVGC_declare_main_function(&res, bytecode, statements, statement_len, tokens, token_len, code, og, global_id, varlist);
		if (res != MU_SUCCESS) {
			*result = MU_FAILURE;
			return bytecode;
		}

		return bytecode;
	}

/* API-LEVEL FUNCS */

	MUDEF muString mu_compile_vulkan_glsl(muResult* result, const char* code, muVGCShader shader) {
		if (result != MU_NULL_PTR) {
			*result = MU_SUCCESS;
		}
		muResult res = MU_SUCCESS;

		muString code_str = mu_string_create((char*)code);
		muString bytecode_str = mu_string_create_raw((char*)"\0", 1);
		bytecode_str = mu_string_delete(bytecode_str, 0, 1);

		// Handle comments

		code_str = muVGC_handle_comments(&res, code_str);
		if (res != MU_SUCCESS) {
			if (result != MU_NULL_PTR) {
				*result = MU_FAILURE;
			}

			code_str = mu_string_destroy(code_str);
			bytecode_str = mu_string_destroy(bytecode_str);
			return (muString){ 0 };
		}

		// Handle macros

		bytecode_str = muVGC_handle_macros(&res, code_str, code, bytecode_str, shader);
		if (res != MU_SUCCESS) {
			if (result != MU_NULL_PTR) {
				*result = MU_FAILURE;
			}

			code_str = mu_string_destroy(code_str);
			bytecode_str = mu_string_destroy(bytecode_str);
			return (muString){ 0 };
		}

		// Tokenize code

		size_m token_len = 0;
		muVGCToken* tokens = muVGC_tokenize_code(code_str.s, mu_string_strlen(code_str), code, &token_len);
		if (tokens == MU_NULL_PTR) {
			if (result != MU_NULL_PTR) {
				*result = MU_FAILURE;
			}

			code_str = mu_string_destroy(code_str);
			bytecode_str = mu_string_destroy(bytecode_str);
			return (muString){ 0 };
		}

		// Statement-ize code

		size_m statement_len = 0;
		muVGCStatement* statements = muVGC_get_statements(tokens, token_len, code_str.s, code, &statement_len);
		if (statements == MU_NULL_PTR) {
			if (result != MU_NULL_PTR) {
				*result = MU_FAILURE;
			}

			mu_free(tokens);
			code_str = mu_string_destroy(code_str);
			bytecode_str = mu_string_destroy(bytecode_str);
			return (muString){ 0 };
		}

		// Start variable list

		muVGCVariableList varlist = muVGC_intialize_empty_variable_list();

		// Execute statements

		uint32_m global_id = 2;
		bytecode_str = muVGC_execute_statements(&res, bytecode_str, statements, statement_len, tokens, token_len, code_str.s, code, &global_id, &varlist);
		if (res != MU_SUCCESS) {
			if (result != MU_NULL_PTR) {
				*result = MU_FAILURE;
			}

			mu_free(statements);
			mu_free(tokens);
			code_str = mu_string_destroy(code_str);
			bytecode_str = mu_string_destroy(bytecode_str);
			return (muString){ 0 };
		}

		// Deallocate and return

		varlist = muVGC_empty_variable_list(varlist);
		mu_free(statements);
		mu_free(tokens);
		code_str = mu_string_destroy(code_str);
		// (+ set max bound)
		MUVGC_4_BYTE_LE_SET(bytecode_str.s, global_id, 12)
		return bytecode_str;
	}

/* end */

#ifdef __cplusplus
}
#endif

#endif /* MUVGC_IMPLEMENTATION */

/*
------------------------------------------------------------------------------
This software is available under 2 licenses -- choose whichever you prefer.
------------------------------------------------------------------------------
ALTERNATIVE A - MIT License
Copyright (c) 2023 Hum
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
------------------------------------------------------------------------------
ALTERNATIVE B - Public Domain (www.unlicense.org)
This is free and unencumbered software released into the public domain.
Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
software, either in source code form or as a compiled binary, for any purpose,
commercial or non-commercial, and by any means.
In jurisdictions that recognize copyright laws, the author or authors of this
software dedicate any and all copyright interest in the software to the public
domain. We make this dedication for the benefit of the public at large and to
the detriment of our heirs and successors. We intend this dedication to be an
overt act of relinquishment in perpetuity of all present and future rights to
this software under copyright law.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
------------------------------------------------------------------------------
*/
