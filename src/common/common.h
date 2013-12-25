#ifndef COMMON_H_
#define COMMON_H_

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

typedef char ch_1;

typedef enum {
    false_v,
    true_v
} bool_;

#define null_v 0

typedef ub_4 size_;
typedef b_4 ret_;
typedef void *obj_;
typedef fb_8 max_v_;
typedef b_4 type_;

#define __del(POINT) { \
		delete POINT; \
		POINT = null_v; \
	}

#define __del_arr(POINT) { \
		delete[] POINT;	 \
		POINT = null_v; \
	}

#endif // COMMON_H_