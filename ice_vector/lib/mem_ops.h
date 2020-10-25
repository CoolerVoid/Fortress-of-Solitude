#include <stdio.h>	
#include <sys/types.h>
#include <string.h>		
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <stdint.h>
#define ICE_XFREE(x) ice_xfree((void **)&x); 
#define MUL_NO_OVERFLOW	((size_t)1 << (sizeof(size_t)*4))
// set DEBUG ON
#define BUGVIEW_ICE 1
#define ICE_DEBUG(x, s...) do { \
 if (!BUGVIEW_ICE) { break; } \
 time_t t = time(NULL); \
 char *d = ctime(&t); \
 fprintf(stderr, "\n--- DEBUG-START ---\n\n %.*s %s[%d] %s(): \n", \
 (int)strlen(d) - 1, d, __FILE__, \
 __LINE__, __FUNCTION__); \
 fprintf(stderr, x, ## s); \
 fprintf(stderr,"\n\n--- DEBUG-END ---\n"); \
} while (0);

// based in OpenBSD reallocarray() function http://man.openbsd.org/reallocarray.3
void *ice_xmallocarray (size_t nmemb, size_t size); 
void *ice_xreallocarray (void *ptr, size_t nmemb, size_t size);
void ice_xfree(void **ptr);
