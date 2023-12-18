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
	MUVGC_FRAGMENT
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

/* useful funcs */

// to be implemented in mus eventually

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

size_m muVGC_get_line_of_code(const char* s, size_m index) {
	size_m len = mu_strlen(s);
	size_m linecount = 0;
	for (size_m i = 0; i < len; i++) {
		if (s[i] == '\n') {
			linecount++;
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
		}
		if (i == index) {
			return char_count;
		}
	}
	return char_count;
}

// https://stackoverflow.com/a/7022827
int muVGC_get_int_from_string(const char* s, size_m len) {
	int ret = 0;
	size_m i = 0;
	int mul = 1;
	while (i != len) {
		if (s[i] == '-') {
			mul = -1;
		} else {
			ret = (ret*10) + (s[i] - '0');
		}
		i++;
	}
	return ret*mul;
}

void muVGC_print_syntax_error(const char* s, size_m index) {
	mu_print("[muVGC] Syntax error (line %zu, character %zu); ", muVGC_get_line_of_code(s, index), muVGC_get_character(s, index));
}

char muVGC_get_execution_model(muVGCShader shader) {
	switch (shader) {
		default: return 0; break;
		case MUVGC_VERTEX: return 0; break;
		case MUVGC_FRAGMENT: return 4; break;
	}
}

uint32_m muVGC_get_word(const char* b) {
	const unsigned char* ub = (const unsigned char*)b;
	return ub[0] + (ub[1] << 8) + (ub[2] << 16) + (ub[3] << 24);
}
int muVGC_get_halfword(const char* b) {
	const unsigned char* ub = (const unsigned char*)b;
	return ub[0] + (ub[1] << 8);
}

/* token stuff */

enum muVGCTokenType {
	MUVGC_TOKEN_UNKNOWN=0,
	MUVGC_TOKEN_END_OF_FILE,

	MUVGC_TOKEN_NAME,
	MUVGC_TOKEN_INTEGER,
	MUVGC_TOKEN_DECIMAL,

	MUVGC_TOKEN_MACRO_STATEMENT,

	MUVGC_TOKEN_OPEN_PARENTHESIS,
	MUVGC_TOKEN_CLOSE_PARENTHESIS,
	MUVGC_TOKEN_OPEN_CURLY_BRACKET,
	MUVGC_TOKEN_CLOSE_CURLY_BRACKET,
	MUVGC_TOKEN_OPEN_BRACKET,
	MUVGC_TOKEN_CLOSE_BRACKET,

	MUVGC_TOKEN_EQUALS,
	MUVGC_TOKEN_SEMICOLON,
	MUVGC_TOKEN_COMMA
};
typedef enum muVGCTokenType muVGCTokenType;

void muVGC_print_token_type(muVGCTokenType type) {
	switch (type) {
		default: mu_print("unknown"); break;
		case MUVGC_TOKEN_END_OF_FILE: mu_print("end of file"); break;
		case MUVGC_TOKEN_NAME: mu_print("name"); break;
		case MUVGC_TOKEN_INTEGER: mu_print("integer"); break;
		case MUVGC_TOKEN_DECIMAL: mu_print("decimal"); break;
		case MUVGC_TOKEN_MACRO_STATEMENT: mu_print("macro statement"); break;
		case MUVGC_TOKEN_OPEN_PARENTHESIS: mu_print("open parenthesis"); break;
		case MUVGC_TOKEN_CLOSE_PARENTHESIS: mu_print("close parenthesis"); break;
		case MUVGC_TOKEN_OPEN_CURLY_BRACKET: mu_print("open curly bracket"); break;
		case MUVGC_TOKEN_CLOSE_CURLY_BRACKET: mu_print("close curly bracket"); break;
		case MUVGC_TOKEN_OPEN_BRACKET: mu_print("open bracket"); break;
		case MUVGC_TOKEN_CLOSE_BRACKET: mu_print("close bracket"); break;
		case MUVGC_TOKEN_EQUALS: mu_print("equals"); break;
		case MUVGC_TOKEN_SEMICOLON: mu_print("semicolon"); break;
		case MUVGC_TOKEN_COMMA: mu_print("comma"); break;
	}
}

struct muVGCToken {
	size_m i;
	size_m length;
	size_m effective_length;
	muVGCTokenType type;
};
typedef struct muVGCToken muVGCToken;

muBool muVGC_is_character_a_break(char c) {
	return c == ' ' || c == '\n' || c == '\t';
}

muVGCToken muVGC_get_next_token(const char* code, size_m codelen, muVGCToken prev_token) {
	if (prev_token.i + 1 >= codelen) {
		prev_token.i = codelen;
		prev_token.type = MUVGC_TOKEN_END_OF_FILE;
		return prev_token;
	}
	prev_token.i += prev_token.length;
	prev_token.length = 1;
	prev_token.effective_length = 0;
	while (prev_token.i < codelen && muVGC_is_character_a_break(code[prev_token.i])) {
		prev_token.i++;
	}

	if (
		(code[prev_token.i] >= 'a' && code[prev_token.i] <= 'z') ||
		(code[prev_token.i] >= 'A' && code[prev_token.i] <= 'Z')
	) {
		prev_token.type = MUVGC_TOKEN_NAME;
		while (
			prev_token.i + prev_token.length < codelen &&
			(
				(code[prev_token.i+prev_token.length] >= 'a' && code[prev_token.i+prev_token.length] <= 'z') ||
				(code[prev_token.i+prev_token.length] >= 'A' && code[prev_token.i+prev_token.length] <= 'Z') ||
				(code[prev_token.i+prev_token.length] >= '0' && code[prev_token.i+prev_token.length] <= '9')
			)
		) {
			prev_token.length++;
		}
		return prev_token;
	} else if (code[prev_token.i] >= '0' && code[prev_token.i] <= '9') {
		prev_token.type = MUVGC_TOKEN_INTEGER;
		while (
			prev_token.i + prev_token.length < codelen &&
			code[prev_token.i+prev_token.length] >= '0' && code[prev_token.i+prev_token.length] <= '9'
		) {
			prev_token.length++;
		}
		if (prev_token.i + prev_token.length < codelen && code[prev_token.i+prev_token.length] == '.') {
			prev_token.type = MUVGC_TOKEN_DECIMAL;
			if (prev_token.i + prev_token.length + 1 < codelen) {
				prev_token.length++;
				while (
					prev_token.i + prev_token.length < codelen &&
					code[prev_token.i+prev_token.length] >= '0' && code[prev_token.i+prev_token.length] <= '9'
				) {
					prev_token.length++;
				}
			}
		}
		return prev_token;
	}

	switch (code[prev_token.i]) {
		default: {
			prev_token.type = MUVGC_TOKEN_UNKNOWN;
			return prev_token;
		} break;
		case '\0': {
			prev_token.i = codelen;
			prev_token.type = MUVGC_TOKEN_END_OF_FILE;
			return prev_token;
		} break;
		case '#': {
			prev_token.type = MUVGC_TOKEN_MACRO_STATEMENT;
			prev_token.length = 1;
			while (prev_token.i + prev_token.effective_length < codelen && code[prev_token.i+prev_token.effective_length] != '\n') {
				prev_token.effective_length++;
			}
			return prev_token;
		} break;
		case '(': {
			prev_token.type = MUVGC_TOKEN_OPEN_PARENTHESIS;
			prev_token.length = 1;
			while (prev_token.i + prev_token.effective_length < codelen && code[prev_token.i+prev_token.effective_length] != ')') {
				prev_token.effective_length++;
			}
			prev_token.effective_length++;
			return prev_token;
		} break;
		case ')': {
			prev_token.type = MUVGC_TOKEN_CLOSE_PARENTHESIS;
			prev_token.length = 1;
			return prev_token;
		} break;
		case '{': {
			prev_token.type = MUVGC_TOKEN_OPEN_CURLY_BRACKET;
			prev_token.length = 1;
			while (prev_token.i + prev_token.effective_length < codelen && code[prev_token.i+prev_token.effective_length] != '}') {
				prev_token.effective_length++;
			}
			prev_token.effective_length++;
			return prev_token;
		} break;
		case '}': {
			prev_token.type = MUVGC_TOKEN_CLOSE_CURLY_BRACKET;
			prev_token.length = 1;
			return prev_token;
		} break;
		case '[': {
			prev_token.type = MUVGC_TOKEN_OPEN_BRACKET;
			prev_token.length = 1;
			while (prev_token.i + prev_token.effective_length < codelen && code[prev_token.i+prev_token.effective_length] != ']') {
				prev_token.effective_length++;
			}
			prev_token.effective_length++;
			return prev_token;
		} break;
		case ']': {
			prev_token.type = MUVGC_TOKEN_CLOSE_BRACKET;
			prev_token.length = 1;
			return prev_token;
		} break;
		case '=': {
			prev_token.type = MUVGC_TOKEN_EQUALS;
			prev_token.length = 1;
			return prev_token;
		} break;
		case ';': {
			prev_token.type = MUVGC_TOKEN_SEMICOLON;
			prev_token.length = 1;
			return prev_token;
		} break;
		case ',': {
			prev_token.type = MUVGC_TOKEN_COMMA;
			prev_token.length = 1;
			return prev_token;
		} break;
	}
}

/* section funcs */

muString muVGC_handle_first_words_section(muResult* result, muString str) {
	char first_words[] = {
		// Magic number: 0x07230203 (SPIR-V)
		0x03, 0x02, 0x23, 0x07,
		// Version: v1.0.0
		0, 0, 0x01, 0,
		// Generator: 0b00 0d00 (god knows what this means)
		0x0b, 0, 0x0d, 0,
		// Bound: 1 (will increase as we compile)
		1, 0, 0, 0,
		// Schema: 0 (we're not doing any fancy schema stuff)
		0, 0, 0, 0
	};
	str = mu_string_create_raw(first_words, sizeof(first_words));
	return str;
}

muString muVGC_handle_beginning_instructions_section(muResult* result, muString str, muString code_str, muVGCShader shader) {
	char beginning_commands[] = {
		// OpCapability Shader
		17, 0, 2, 0, 
		1, 0, 0, 0,
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
		// OpEntryPoint SHADER %4 "main" { %9 }
		15, 0, 5, 0,
		muVGC_get_execution_model(shader), 0, 0, 0,
		4, 0, 0, 0,
		'm', 'a', 'i', 'n',
		0, 0, 0, 0,
	};
	str = mu_string_insert_raw(str, beginning_commands, sizeof(beginning_commands), mu_string_strlen(str));

	// Specify the origin of the screen to the upper-left for fragment shaders
	if (shader == MUVGC_FRAGMENT) {
		char cmd[] = {
			// OpExecutionMode %4 OriginUpperLeft
			16, 0, 3, 0,
			4, 0, 0, 0,
			7, 0, 0, 0,
		};
		str = mu_string_insert_raw(str, cmd, sizeof(cmd), mu_string_strlen(str));
	}

	// Get version for next instructions

	size_m codelen = mu_string_strlen(code_str);
	muVGCToken token = { 0 };
	token.i = 0;
	token.length = 0;
	token.type = MUVGC_TOKEN_END_OF_FILE;

	if (0 >= codelen) {
		muVGC_print_syntax_error(code_str.s, 0);
		mu_print("expected '#version' at beginning of file, but first token is type '");
		muVGC_print_token_type(MUVGC_TOKEN_END_OF_FILE);
		mu_print("'\n");
		*result = MU_FAILURE;
		return str;
	}

	token = muVGC_get_next_token(code_str.s, codelen, token);
	if (token.type != MUVGC_TOKEN_MACRO_STATEMENT) {
		muVGC_print_syntax_error(code_str.s, token.i);
		mu_print("expected '#version' at beginning of file, but first token is type '");
		muVGC_print_token_type(token.type);
		mu_print("'\n");
		*result = MU_FAILURE;
		return str;
	}

	token = muVGC_get_next_token(code_str.s, codelen, token);
	if (token.type != MUVGC_TOKEN_NAME) {
		muVGC_print_syntax_error(code_str.s, token.i);
		mu_print("expected '#version' at beginning of file, but token after '#' is type '");
		muVGC_print_token_type(token.type);
		mu_print("'\n");
		*result = MU_FAILURE;
		return str;
	}
	if (token.length != 7 || (mu_strncmp(&code_str.s[token.i], "version", 7) != 0)) {
		muVGC_print_syntax_error(code_str.s, token.i);
		mu_print("expected '#version' at beginning of file, but directive is '");
		for (size_m i = 0; i < token.length; i++) {
			mu_printf("%c", code_str.s[token.i+i]);
		}
		mu_print("'\n");
		*result = MU_FAILURE;
		return str;
	}

	token = muVGC_get_next_token(code_str.s, codelen, token);
	if (token.type != MUVGC_TOKEN_INTEGER) {
		muVGC_print_syntax_error(code_str.s, token.i);
		mu_print("expected token type '");
		muVGC_print_token_type(MUVGC_TOKEN_INTEGER);
		mu_print("' after '#version', but token type is '");
		muVGC_print_token_type(token.type);
		mu_print("'\n");
		*result = MU_FAILURE;
		return str;
	}
	// @TODO more thorough testing for a valid GLSL version
	int glsl_version = muVGC_get_int_from_string(&code_str.s[token.i], token.length);
	if (glsl_version < 140) {
		muVGC_print_syntax_error(code_str.s, token.i);
		mu_printf("version must be 140 or higher, but version is %i.\n", glsl_version);
		*result = MU_FAILURE;
		return str;
	}

	// More instructions
	char beginning_commands_2[] = {
		// OpSource GLSL 450
		3, 0, 3, 0,
		2, 0, 0, 0,
		glsl_version & 0xFF, (glsl_version >> 8) & 0xFF, (glsl_version >> 16) & 0xFF, (glsl_version >> 24) & 0xFF,
		// OpSourceExtension "GL_GOOGLE_cpp_style_line_directive" (@TODO might be wise to not include, figure out!)
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
		// OpSourceExtension "GL_GOOGLE_include_directive" (again probably not wise to include)
		4, 0, 8, 0,
		'G', 'L', '_', 'G',
		'O', 'O', 'G', 'L',
		'E', '_', 'i', 'n',
		'c', 'l', 'u', 'd',
		'e', '_', 'd', 'i',
		'r', 'e', 'c', 't',
		'i', 'v', 'e', 0,
	};
	str = mu_string_insert_raw(str, beginning_commands_2, sizeof(beginning_commands_2), mu_string_strlen(str));

	return str;
}

/* section hopping functions (all hop to the end of the given section btw) */

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

/* useful section functions */

void muVGC_name(uint32_m global_id, muString* bytecode, const char* name, size_m namelen) {
	size_m i = muVGC_hop_to_naming_section(*bytecode);

	// OpName %global_id "name"

	size_m datanamelen = namelen;
	if ((datanamelen % 4) == 0) {
		datanamelen++;
	}
	while (((datanamelen) % 4) != 0) {
		datanamelen++;
	}
	uint16_m fulllen = (datanamelen / 4) + 2;

	char opnamebytes[] = {
		5, 0, fulllen & 0xFF, (fulllen >> 8) & 0xFF,
		global_id & 0xFF, (global_id >> 8) & 0xFF, (global_id >> 16) & 0xFF, (global_id >> 24) & 0xFF
	};
	*bytecode = mu_string_insert_raw(*bytecode, opnamebytes, sizeof(opnamebytes), i);
	i += sizeof(opnamebytes);

	*bytecode = mu_string_insert_raw(*bytecode, (char*)name, namelen, i);
	i += namelen;

	char four_empty[] = { 0, 0, 0, 0 };
	*bytecode = mu_string_insert_raw(*bytecode, four_empty, datanamelen - namelen, i);
}

/* useful general functions */

size_m muVGC_get_instruction(muString bytecode, char* instruction, muBool* boolmap, size_m len) {
	for (size_m i = 20; i < mu_string_strlen(bytecode);) {
		int step = muVGC_get_halfword(&bytecode.s[i+2]);

		if (step == 0) {
			break;
		}
		if (len > (step * 4)) {
			i += step * 4;
			continue;
		}

		muBool equals = MU_TRUE;
		for (size_m j = 0; j < len; j++) {
			if ((boolmap[j]) && (bytecode.s[i+j] != instruction[j])) {
				equals = MU_FALSE;
				break;
			}
		}
		if (equals == MU_TRUE) {
			return i;
		}

		i += step * 4;
	}

	return 0;
}

uint32_m muVGC_get_type(muString* bytecode, const char* type, size_m typelen, size_m* global_id) {
	switch (typelen) {
		default: break;
		case 4: {
			if (mu_strncmp(type, "void", 4) == 0) {
				uint32_m u32_gi = (uint32_m)*global_id;
				char bytes[] = {
					19, 0, 2, 0,
					u32_gi & 0xFF, (u32_gi >> 8) & 0xFF, (u32_gi >> 16) & 0xFF, (u32_gi >> 24) & 0xFF
				};
				muBool boolmap[] = {
					1, 1, 1, 1,
					0, 0, 0, 0
				};
				size_m instr = muVGC_get_instruction(*bytecode, bytes, boolmap, sizeof(bytes));
				if (instr == 0) {
					size_m var_section = muVGC_hop_to_variable_section(*bytecode);

					*bytecode = mu_string_insert_raw(*bytecode, bytes, sizeof(bytes), var_section);
					*global_id += 1;
					return u32_gi;
				} else {
					return muVGC_get_word(&bytecode->s[instr+4]);
				}
			}
		} break;
	}

	return 0;
}

uint32_m muVGC_get_function_type(muString* bytecode, uint32_m type, char* args, size_m arglen, size_m* global_id) {
	uint32_m u32_gi = (uint32_m)*global_id;

	char bytes[] = {
		// @TODO this may cause problems
		33, 0, 3+arglen, 0,
		u32_gi & 0xFF, (u32_gi >> 8) & 0xFF, (u32_gi >> 16) & 0xFF, (u32_gi >> 24) & 0xFF,
		type & 0xFF, (type >> 8) & 0xFF, (type >> 16) & 0xFF, (type >> 24) & 0xFF
	};
	muBool boolmap[] = {
		1, 1, 1, 1,
		0, 0, 0, 0,
		1, 1, 1, 1
	};

	size_m instr = muVGC_get_instruction(*bytecode, bytes, boolmap, sizeof(bytes));
	if ((instr == 0) || (instr != 0 && arglen > 0 && mu_strncmp(&bytecode->s[instr], args, arglen) != 0)) {
		size_m var_section = muVGC_hop_to_variable_section(*bytecode);
		*bytecode = mu_string_insert_raw(*bytecode, bytes, sizeof(bytes), var_section);
		*global_id += 1;
		return u32_gi;
	}

	return muVGC_get_word(&bytecode->s[instr+4]);
}

uint32_m muVGC_get_function(muString* bytecode, uint32_m return_type, uint32_m func_type, size_m* global_id) {
	uint32_m u32_gi = (uint32_m)*global_id;

	char bytes[] = {
		54, 0, 5, 0,
		return_type & 0xFF, (return_type >> 8) & 0xFF, (return_type >> 16) & 0xFF, (return_type >> 24) & 0xFF,
		u32_gi & 0xFF, (u32_gi >> 8) & 0xFF, (u32_gi >> 16) & 0xFF, (u32_gi >> 24) & 0xFF,
		0, 0, 0, 0,
		func_type & 0xFF, (func_type >> 8) & 0xFF, (func_type >> 16) & 0xFF, (func_type >> 24) & 0xFF
	};
	muBool boolmap[] = {
		1, 1, 1, 1,
		1, 1, 1, 1,
		0, 0, 0, 0,
		1, 1, 1, 1,
		1, 1, 1, 1
	};

	size_m instr = muVGC_get_instruction(*bytecode, bytes, boolmap, sizeof(bytes));
	if (instr == 0) {
		size_m func_section = muVGC_hop_to_function_section(*bytecode);
		*bytecode = mu_string_insert_raw(*bytecode, bytes, sizeof(bytes), func_section);
		*global_id += 1;
		return u32_gi;
	}

	return muVGC_get_word(&bytecode->s[instr+8]);
}

// no param functions

void muVGC_op_label(muString* bytecode, size_m* global_id) {
	uint32_m u32_gi = (uint32_m)*global_id;

	uint16_m in = 248;
	char bytes[] = {
		in & 0xFF, (in >> 8) & 0xFF, 2, 0,
		u32_gi & 0xFF, (u32_gi >> 8) & 0xFF, (u32_gi >> 16) & 0xFF, (u32_gi >> 24) & 0xFF
	};

	*bytecode = mu_string_insert_raw(*bytecode, bytes, sizeof(bytes), muVGC_hop_to_function_section(*bytecode));
	*global_id += 1;
}

void muVGC_op_function_end(muString* bytecode, size_m* global_id) {
	char bytes[] = {
		56, 0, 1, 0,
	};
	*bytecode = mu_string_insert_raw(*bytecode, bytes, sizeof(bytes), muVGC_hop_to_function_section(*bytecode));
}

// very general functions

// @TODO handle args
uint32_m muVGC_declare_function(muResult* result, muString* bytecode, muString code, size_m* global_id, muVGCToken token) {
	uint32_m type = muVGC_get_type(bytecode, &code.s[token.i], token.length, global_id);
	if (type == 0) {
		// @TODO try declaring type first
		muVGC_print_syntax_error(code.s, token.i);
		mu_print("unrecognized type '");
		for (size_m i = 0; i < token.length; i++) {
			mu_printf("%c", code.s[token.i+i]);
		}
		mu_print("' specified for function return type\n");
		*result = MU_FAILURE;
		return 0;
	}

	uint32_m func_type = muVGC_get_function_type(bytecode, type, MU_NULL_PTR, 0, global_id);
	uint32_m func = muVGC_get_function(bytecode, type, func_type, global_id);

	token = muVGC_get_next_token(code.s, mu_string_strlen(code), token);
	muVGC_name(func, bytecode, &code.s[token.i], token.length);
	muVGC_op_label(bytecode, global_id);
	muVGC_op_function_end(bytecode, global_id);
	return func;
}

/* error functions */

/* @TODO
function syntax: TYPE NAME(ARGS){...}
redeclaration
*/

muResult muVGC_error_unrecognized_token(muString str) {
	muVGCToken token = { 0 };
	token.i = 0;
	token.length = 0;
	token.type = MUVGC_TOKEN_UNKNOWN;

	for (size_m i = 0; i < mu_string_strlen(str) && token.type != MUVGC_TOKEN_END_OF_FILE;) {
		token = muVGC_get_next_token(str.s, mu_string_strlen(str), token);
		i = token.i;

		if (token.type == MUVGC_TOKEN_UNKNOWN) {
			muVGC_print_syntax_error(str.s, token.i);
			mu_print("unrecognized token '");
			for (size_m i = 0; i < token.length; i++) {
				mu_printf("%c", str.s[token.i+i]);
			}
			mu_print("'\n");
			return MU_FAILURE;
		}
	}

	return MU_SUCCESS;
}

muResult muVGC_error_bracket_counting(muString str) {
	muVGCToken token = { 0 };
	token.i = 0;
	token.length = 0;
	token.type = MUVGC_TOKEN_UNKNOWN;

	int64_m brackets = 0;
	muVGCToken last_bracket_token = { 0 };
	int64_m curly_brackets = 0;
	muVGCToken last_curly_bracket_token = { 0 };
	int64_m parentheses = 0;
	muVGCToken last_parenthesis_token = { 0 };

	for (size_m i = 0; i < mu_string_strlen(str) && token.type != MUVGC_TOKEN_END_OF_FILE;) {
		token = muVGC_get_next_token(str.s, mu_string_strlen(str), token);
		i = token.i;

		switch (token.type) {
			default: break;
			case MUVGC_TOKEN_OPEN_BRACKET: brackets++; last_bracket_token = token; break;
			case MUVGC_TOKEN_CLOSE_BRACKET: brackets--; break;
			case MUVGC_TOKEN_OPEN_CURLY_BRACKET: curly_brackets++; last_curly_bracket_token = token; break;
			case MUVGC_TOKEN_CLOSE_CURLY_BRACKET: curly_brackets--; break;
			case MUVGC_TOKEN_OPEN_PARENTHESIS: parentheses++; last_parenthesis_token = token; break;
			case MUVGC_TOKEN_CLOSE_PARENTHESIS: parentheses--; break;
		}

		if (brackets < 0 || curly_brackets < 0 || parentheses < 0) {
			muVGC_print_syntax_error(str.s, token.i);
			mu_print("unexpected extra ");
			muVGC_print_token_type(token.type);
			mu_print("\n");
			return MU_FAILURE;
		}
	}

	if (brackets > 0) {
		muVGC_print_syntax_error(str.s, last_bracket_token.i);
		muVGC_print_token_type(last_bracket_token.type);
		mu_print(" never closes\n");
		return MU_FAILURE;
	}
	if (curly_brackets > 0) {
		muVGC_print_syntax_error(str.s, last_curly_bracket_token.i);
		muVGC_print_token_type(last_curly_bracket_token.type);
		mu_print(" never closes\n");
		return MU_FAILURE;
	}
	if (parentheses > 0) {
		muVGC_print_syntax_error(str.s, last_parenthesis_token.i);
		muVGC_print_token_type(last_parenthesis_token.type);
		mu_print(" never closes\n");
		return MU_FAILURE;
	}

	return MU_SUCCESS;
}

/* stage functions */

muResult muVGC_scan_for_errors(muString str) {
	if (muVGC_error_unrecognized_token(str) != MU_SUCCESS) {
		return MU_FAILURE;
	}
	if (muVGC_error_bracket_counting(str) != MU_SUCCESS) {
		return MU_FAILURE;
	}

	return MU_SUCCESS;
}

muString muVGC_clear_code(muResult* result, muString str) {
	// Not sure if this entirely matches how GLSL's comments are handled
	for (size_m i = 0; i < mu_string_strlen(str); i++) {
		size_m orig_i = i;
		if (mu_here(str.s, "/*", i)) {
			i += 2;
			while ((i < mu_string_strlen(str)) && (mu_here(str.s, "*/", i) == MU_FALSE)) {
				i++;
			}
			if (i >= mu_string_strlen(str)) {
				muVGC_print_syntax_error(str.s, orig_i);
				mu_print("comment beginning with '/*' never has a corresponding end '*/'\n");
				*result = MU_FAILURE;
				return str;
			}
			i += 2;
			str = mu_string_delete(str, orig_i, i);
		}
		i = orig_i;
		if (mu_here(str.s, "//", i)) {
			while (i < mu_string_strlen(str) && str.s[i] != '\n') {
				i++;
			}
			str = mu_string_delete(str, orig_i, i);
		}
		i = orig_i;
	}

	return str;
}

// @TODO this
muString muVGC_preprocess(muResult* result, muString str) {
	return str;
}

muString muVGC_specify_functions(muResult* result, muString str, size_m* global_id, muString* bytecode) {
	muVGCToken token = { 0 };
	token.i = 0;
	token.length = 0;
	token.type = MUVGC_TOKEN_UNKNOWN;

	// find main function and set as entry point
	muVGCToken main_token = { 0 };
	muBool found_main_function = MU_FALSE;

	for (size_m i = 0; i < mu_string_strlen(str);) {
		token = muVGC_get_next_token(str.s, mu_string_strlen(str), token);
		i = token.i;

		if (token.type == MUVGC_TOKEN_NAME && token.length == 4 && mu_strncmp(&str.s[token.i], "void", 4) == 0) {
			token = muVGC_get_next_token(str.s, mu_string_strlen(str), token);
			i = token.i;

			if (token.type != MUVGC_TOKEN_NAME) {
				muVGC_print_syntax_error(str.s, token.i);
				mu_print("expected token '");
				muVGC_print_token_type(MUVGC_TOKEN_NAME);
				mu_print("' after 'void', but got token '");
				muVGC_print_token_type(token.type);
				mu_print("'\n");
				*result = MU_FAILURE;
				return str;
			}

			if (token.length == 4 && mu_strncmp(&str.s[token.i], "main", 4) == 0) {
				found_main_function = MU_TRUE;
				main_token = token;
				main_token.i -= main_token.length + 1;

				token = muVGC_get_next_token(str.s, mu_string_strlen(str), token);
				i = token.i;
				if (token.type != MUVGC_TOKEN_OPEN_PARENTHESIS) {
					muVGC_print_syntax_error(str.s, token.i);
					mu_print("expected token '");
					muVGC_print_token_type(MUVGC_TOKEN_OPEN_PARENTHESIS);
					mu_print("' after 'void main', but got token '");
					muVGC_print_token_type(token.type);
					mu_print("'\n");
					*result = MU_FAILURE;
					return str;
				}

				token = muVGC_get_next_token(str.s, mu_string_strlen(str), token);
				i = token.i;
				if (token.type != MUVGC_TOKEN_CLOSE_PARENTHESIS) {
					muVGC_print_syntax_error(str.s, token.i);
					mu_print("expected token '");
					muVGC_print_token_type(MUVGC_TOKEN_CLOSE_PARENTHESIS);
					mu_print("' after 'void main(', but got token '");
					muVGC_print_token_type(token.type);
					mu_print("'; no arguments can be provided to the main function\n");
					*result = MU_FAILURE;
					return str;
				}
			}
		}
	}

	if (found_main_function == MU_FALSE) {
		muVGC_print_syntax_error(str.s, token.i);
		mu_print("expected void main function declaration before end of file\n");
		*result = MU_FAILURE;
		return str;
	}

	// Declare main function

	muResult res = MU_SUCCESS;
	muVGC_declare_function(&res, bytecode, str, global_id, main_token);
	if (res != MU_SUCCESS) {
		*result = MU_FAILURE;
		return str;
	}

	return str;
}

/* API-level funcs */

// @TODO test if shader enum is valid
MUDEF muString mu_compile_vulkan_glsl(muResult* result, const char* code, muVGCShader shader) {
	muString str = { 0 };
	muString empty_str = { 0 };
	muString code_str = mu_string_create((char*)code);
	muResult res = MU_SUCCESS;
	size_m global_id = 2;
	
	if (result != MU_NULL_PTR) {
		*result = MU_SUCCESS;
	}

	// scan for errors
	if (muVGC_scan_for_errors(code_str) != MU_SUCCESS) {
		if (result != MU_NULL_PTR) {
			*result = MU_FAILURE;
		}
		code_str = mu_string_destroy(code_str);
		return empty_str;
	}

	// clear code of comments
	code_str = muVGC_clear_code(&res, code_str);
	if (res != MU_SUCCESS) {
		if (result != MU_NULL_PTR) {
			*result = MU_FAILURE;
		}
		code_str = mu_string_destroy(code_str);
		return empty_str;
	}

	// process all preprocessing directives/instructions
	code_str = muVGC_preprocess(&res, code_str);
	if (res != MU_SUCCESS) {
		if (result != MU_NULL_PTR) {
			*result = MU_FAILURE;
		}
		code_str = mu_string_destroy(code_str);
		return empty_str;
	}

	// Note: creates string
	str = muVGC_handle_first_words_section(&res, str);
	if (res != MU_SUCCESS) {
		if (result != MU_NULL_PTR) {
			*result = MU_FAILURE;
		}
		str = mu_string_destroy(str);
		code_str = mu_string_destroy(code_str);
		return empty_str;
	}

	str = muVGC_handle_beginning_instructions_section(&res, str, code_str, shader);
	if (res != MU_SUCCESS) {
		if (result != MU_NULL_PTR) {
			*result = MU_FAILURE;
		}
		str = mu_string_destroy(str);
		code_str = mu_string_destroy(code_str);
		return empty_str;
	}

	// specify functions' existences
	code_str = muVGC_specify_functions(&res, code_str, &global_id, &str);
	if (res != MU_SUCCESS) {
		if (result != MU_NULL_PTR) {
			*result = MU_FAILURE;
		}
		str = mu_string_destroy(str);
		code_str = mu_string_destroy(code_str);
		return empty_str;
	}

	// set bound
	str.s[12] = global_id & 0xFF;
	str.s[13] = (global_id >> 8) & 0xFF;
	str.s[14] = (global_id >> 16) & 0xFF;
	str.s[15] = (global_id >> 24) & 0xFF;

	code_str = mu_string_destroy(code_str);
	return str;
}

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
