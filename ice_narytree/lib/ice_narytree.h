#ifndef __ICE_NARYTREE_H__
#define __ICE_NARYTREE_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

// set DEBUG ON
#define ICETREE_BUGVIEW 1
#define ICETREE_DEBUG(x, s...) do { \
 if (!ICETREE_BUGVIEW) { break; } \
 time_t t = time(NULL); \
 char *d = ctime(&t); \
 fprintf(stderr, "\n---Ice Tree DEBUG-START ---\n\n %.*s %s[%d] %s(): \n", \
 (int)strlen(d) - 1, d, __FILE__, \
 __LINE__, __FUNCTION__); \
 fprintf(stderr, x, ## s); \
 fprintf(stderr,"\n\n---Ice Tree DEBUG-END ---\n"); \
} while (0);

// colors macro
#define RED "\033[22;31m"
#define YELLOW "\033[01;33m"
#define CYAN "\033[22;36m"
#define GREEN "\033[22;32m"
#define LAST "\033[0m"


#define XFREE_ICETREE(x) icetree_xfree((void **)x);

struct icetreenode  {
    void *data;
    struct icetreenode *next;
    struct icetreenode *child;
    int position;
};

typedef struct icetreenode ice_tree_node;

// for mem use
void icetree_xfree(void **ptr); 
volatile void *icetree_burn_mem(volatile void *, int , size_t );
void *icetree_xmalloc_fatal(size_t ); 
void *icetree_xmalloc (size_t ); 
void traversal_and_destroy(ice_tree_node *,void (*lambda)(void *argvs));

// tree functions
ice_tree_node * new_node(int,void *);
ice_tree_node * append_sibling(ice_tree_node *, int,void *);
ice_tree_node * append_child(ice_tree_node *, int, void *);
ice_tree_node * search_in_tree_per_position(ice_tree_node *, int);
ice_tree_node * insert_child_before(ice_tree_node *,int , int, void *); 
ice_tree_node * insert_sibling_before(ice_tree_node *,int , int, void *);
void interate_traversal_tree(ice_tree_node *,void (*lambda)(void *argvs));
void traversal_tree_dbg(ice_tree_node *);
bool remove_node_childs_by_position(ice_tree_node *, int ,void (*lambda)(void *argvs));

#endif
