/**
 * @file debug.h
 *
 * This file holds useful macros for debugging purposes.
 */

/// Set this to 1 to enable debugging mode or 0 to disable debugging mode
#define USE_DEBUG (0)

#if USE_DEBUG == 1
/// Print debug information
#  define PDEBUG(fmt, ...) \
	fprintf(stderr, "%s(), %s:%d: " fmt,			\
		__func__, __FILE__, __LINE__, ##__VA_ARGS__)
/// Add debug exclusive code
#  define IFDEBUG(x) x
#else
/// Does not print debug information
#  define PDEBUG(fmt, ...)
/// Does not add debug exclusive code
#  define IFDEBUG(x)
#endif

