
#ifndef __ICE_QUEUE_H__
#define __ICE_QUEUE_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

// set DEBUG ON
#define ICE_QUEUE_BUGVIEW 1
#define ICE_QUEUE_DEBUG(x, s...) do { \
 if (!ICE_QUEUE_BUGVIEW) { break; } \
 time_t t = time(NULL); \
 char *d = ctime(&t); \
 fprintf(stderr, "\n---Ice Queue DEBUG-START ---\n\n %.*s %s[%d] %s(): \n", \
 (int)strlen(d) - 1, d, __FILE__, \
 __LINE__, __FUNCTION__); \
 fprintf(stderr, x, ## s); \
 fprintf(stderr,"\n\n---Ice Queue DEBUG-END ---\n"); \
} while (0);

typedef struct ice_queue_node {
	void *data;
	struct ice_queue_node *next;
} Ice_Node_queue, *Ice_NodePtr_queue;

typedef struct ice_queueType {
	Ice_NodePtr_queue head, tail;
} Ice_QueueType, *Ice_Queue;


void *ice_queue_xmalloc_fatal(size_t size); 
void *ice_queue_xmalloc(size_t size);

Ice_Queue ice_init_queue(); 
int ice_queue_empty(Ice_Queue Q); 
void ice_enqueue(Ice_Queue Q, void* d); 
void ice_dequeue(Ice_Queue Q, void (*lambda)(void *argvs));

void ice_traversal_queue(Ice_Queue Q, void (*lambda)(void *argvs));



#endif
