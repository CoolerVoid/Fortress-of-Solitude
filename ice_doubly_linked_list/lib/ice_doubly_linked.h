#ifndef ___ICE_DOUBLY_LINKED_H__
#define ___ICE_DOUBLY_LINKED_H__

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>



// set DEBUG ON
#define ICE_DL_BUGVIEW 1
#define ICE_DL_DEBUG(x, s...) do { \
 if (!ICE_DL_BUGVIEW) { break; } \
 time_t t = time(NULL); \
 char *d = ctime(&t); \
 fprintf(stderr, "\n---Ice doubly linked list DEBUG-START ---\n\n %.*s %s[%d] %s(): \n", \
 (int)strlen(d) - 1, d, __FILE__, \
 __LINE__, __FUNCTION__); \
 fprintf(stderr, x, ## s); \
 fprintf(stderr,"\n\n---Ice doubly linked list DEBUG-END ---\n"); \
} while (0);

// colors macro
#define RED "\033[22;31m"
#define YELLOW "\033[01;33m"
#define CYAN "\033[22;36m"
#define GREEN "\033[22;32m"
#define LAST "\033[0m"


#define XFREE_ICE_DL(x) ice_dl_xfree((void **)x);

void ice_dl_xfree(void **ptr); // nd improve that function
void *ice_dl_xmalloc_fatal(size_t size); 
void *ice_dl_xmalloc(size_t size); 

struct ice_dl_node  {
	void *data;		// custom user input data
	struct ice_dl_node* next;
	struct ice_dl_node* prev;
	int position;		// number reference
};

typedef struct ice_dl_node ice_dl_node;

void ice_doubly_linked_init(void);
ice_dl_node * ice_create_dl_node(int position,void * data);
ice_dl_node *Get_head_dl_position(ice_dl_node *in);
ice_dl_node * Insert_dl_in_last(ice_dl_node* in,int position, void * data);
ice_dl_node *Delete_dl_by_position(int position, ice_dl_node * list,void (*lambda)(void *argvs));

void fifo_dl_list_dbg(ice_dl_node* in); 
void lifo_dl_list_dbg(ice_dl_node* in);
void inter_fifo_dl_list(ice_dl_node* in,void (*lambda)(void *argvs)); 
void inter_lifo_dl_list(ice_dl_node* in,void (*lambda)(void *argvs));
void ice_clear_dl(ice_dl_node* in,void (*lambda)(void *argvs));

#endif
