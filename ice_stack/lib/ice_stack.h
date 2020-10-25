
#ifndef __ICE_STACK_H__
#define __ICE_STACK_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

// set DEBUG ON
#define ICESTACK_BUGVIEW 1
#define ICESTACK_DEBUG(x, s...) do { \
 if (!ICESTACK_BUGVIEW) { break; } \
 time_t t = time(NULL); \
 char *d = ctime(&t); \
 fprintf(stderr, "\n---Ice Stack DEBUG-START ---\n\n %.*s %s[%d] %s(): \n", \
 (int)strlen(d) - 1, d, __FILE__, \
 __LINE__, __FUNCTION__); \
 fprintf(stderr, x, ## s); \
 fprintf(stderr,"\n\n---Ice Stack DEBUG-END ---\n"); \
} while (0);

typedef struct icestack_node {
	void *data;
	struct icestack_node *next;
} icestack_Node, *icestack_NodePtr;

typedef struct icestackType {
	icestack_NodePtr top;
} IceStackType, *IceStack;


void *icestack_xmalloc_fatal(size_t size); 
void *icestack_xmalloc(size_t size); 
IceStack init_ice_stack(); 
int ice_stack_empty(IceStack S); 
void ice_stack_push(IceStack S, void *in); 
void *ice_stack_pop(IceStack S,void (*lambda)(void *argvs) );
void ice_stack_inter_reverse_traversal( IceStack S, void (*lambda)(void *argvs));

#endif
