#ifndef _BASE_TYPE_H_
#define _BASE_TYPE_H_

// Base type
typedef char b_1;
typedef unsigned char ub_1;
typedef short b_2;
typedef unsigned short ub_2;
typedef int b_4;
typedef unsigned int ub_4;
typedef long long b_8;
typedef unsigned long long ub_8;

typedef float fb_4;
typedef double fb_8;

// Base string type
typedef char ch_1;

// Base bool type
typedef enum {
    false_v, true_v
} bool_;

#define null_v 0

// Higher level type
typedef ub_4 size_;
typedef void none_;
typedef void *obj_;
typedef b_4 type_;

// High level data type
typedef enum {
    NORMAL_STYLE = 0x00000010,
    FLOAT_STYLE = 0x00000020,
    STRING_STYLE = 0x00000030,
    OBJECT_STYLE = 0x00000040
} eht_;

#define UNSIGNED_SIGN 0x00001000

// Low level data type
typedef enum {
    INVALID = 0x00000000,

    B_1 = 0x00000001 | NORMAL_STYLE,
    UB_1 = B_1 | UNSIGNED_SIGN,
    B_2 = 0x00000002 | NORMAL_STYLE,
    UB_2 = B_2 | UNSIGNED_SIGN,
    B_4 = 0x00000004 | NORMAL_STYLE,
    UB_4 = B_4 | UNSIGNED_SIGN,
    B_8 = 0x00000008 | NORMAL_STYLE,
    UB_8 = B_8 | UNSIGNED_SIGN,

    FB_4 = 0x00000004 | FLOAT_STYLE,
    FB_8 = 0x00000008 | FLOAT_STYLE,

    STR = 0x00000000 | STRING_STYLE,

    OBJ = 0x00000000 | OBJECT_STYLE
} evt_;

typedef enum {
    REFERENCE_VARIABLE = 0x00010000,

    P_B_1 = REFERENCE_VARIABLE | B_1,
    P_UB_1 = REFERENCE_VARIABLE | UB_1,
    P_B_2 = REFERENCE_VARIABLE | B_2,
    P_UB_2 = REFERENCE_VARIABLE | UB_2,
    P_B_4 = REFERENCE_VARIABLE | B_4,
    P_UB_4 = REFERENCE_VARIABLE | UB_4,
    P_B_8 = REFERENCE_VARIABLE | B_8,
    P_UB_8 = REFERENCE_VARIABLE | UB_8,

    P_FB_4 = REFERENCE_VARIABLE | FB_4,
    P_FB_8 = REFERENCE_VARIABLE | FB_8,

    P_STR = REFERENCE_VARIABLE | STR,

    P_OBJ = REFERENCE_VARIABLE | OBJ,
} p_evt_;

// Data type info mask
#define LEGNTH_SIGN        0x0000000F
#define STYLE_SIGN        0x000000F0
#define EVT_SIGN        0x0000FFFF
// No reference mask defined. Reference is not necessary
// for upper layer application, that is reference can not
// be seen in upper layer.

// Get data type info
#define _UNSIGNED(TYPE)                \
    ((TYPE) & UNSIGNED_SIGN)

#define _LEN(TYPE)                \
    ((TYPE) & LEGNTH_SIGN)

#define _STYLE(TYPE)                \
    ((TYPE) & STYLE_SIGN)

#define _EVT(TYPE)                \
    ((evt_)((TYPE) & EVT_SIGN))

// Delete object or object array
#define _DEL(POINT)     \
    { \
        if (POINT) \
        { \
            delete POINT; \
            POINT = null_v; \
        } \
    }

#define _DEL_ARR(POINT)     \
    { \
        if (POINT) \
        { \
            delete[] POINT;     \
            POINT = null_v; \
        } \
    }

#endif // _BASE_TYPE_H_
