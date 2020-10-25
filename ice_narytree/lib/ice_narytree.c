#include "ice_narytree.h"

// alocation tasks, use this in future
void icetree_xfree(void **ptr) 
{
	assert(ptr);
	if( ptr != NULL )
        {
		free(*ptr);
		*ptr=NULL;	
        }
	
}

// use this in the future   
volatile void *icetree_burn_mem(volatile void *dst, int c, size_t len) 
{
	volatile char *buf;
   
	for(buf = (volatile char *)dst;  len;  buf[--len] = c);

	return dst;
}


void *icetree_xmalloc_fatal(size_t size) 
{
	ICETREE_DEBUG("\n Memory error...\n Size: %lu\n",size);

	exit(0);
}

void *icetree_xmalloc(size_t size) 
{
	void *ptr = malloc(size);

	if (ptr == NULL) 
		return icetree_xmalloc_fatal(size);

	return ptr;
}




void traversal_and_destroy(ice_tree_node *root,void (*lambda)(void *argvs))
{
	if(root == NULL) 
		return;

	traversal_and_destroy(root->next,lambda);
	traversal_and_destroy(root->child,lambda);

	lambda(root->data);
	root->data=NULL;
    	free(root);
	root=NULL;
	// XFREE_ICETREE(root);
}


// based on glib n-ary tree
void interate_traversal_tree(ice_tree_node *root, void (*lambda)(void *argvs))
{

	if(root != NULL) 
	{
		lambda(root->data);
		// TREE_DEBUG("Node Value : %d\n",root->position);
		interate_traversal_tree(root->next,lambda);
		// TREE_DEBUG("The Child have the position: ");
		interate_traversal_tree(root->child,lambda);
	} 
}



ice_tree_node * search_in_tree_per_position(ice_tree_node *root, int position) 
{
	ice_tree_node *current = root;

	if(current!=NULL)
	{
 		if(current->position == position) 
			return current;
	
		ice_tree_node *test1=search_in_tree_per_position(current->next,position);	
		ice_tree_node *test2=search_in_tree_per_position(current->child,position);
	
		if(test1!=NULL && test1->position == position)
			return test1;

		if(test2 != NULL && test2->position == position)
			return test2;

//		if(test1!=NULL)
//			free(test1);
//		if(test2!=NULL)
//			free(test2);
	}

	return current;
}



bool remove_node_childs_by_position(ice_tree_node *root, int position,void (*lambda)(void *argvs)) 
{
	ice_tree_node *current = root;
	
	current=search_in_tree_per_position(current,position);
	traversal_and_destroy(current->child,lambda);	
	current->child=NULL;

   	return true;
}


ice_tree_node * insert_sibling_before(ice_tree_node *root, int position,int new_position, void *data) 
{
	ice_tree_node *current = root;

	current=search_in_tree_per_position(current,position);

	return(current->next = new_node(new_position,data));

}


ice_tree_node * insert_child_before(ice_tree_node *root, int position,int new_position, void *data) 
{
	ice_tree_node *current = root;


	current=search_in_tree_per_position(current,position);

    	if(current->child)
		return append_sibling(current->child, new_position,data);
	else
       		return(current->child=new_node(new_position,data));
   	
}

void traversal_tree_dbg(ice_tree_node *root)
{
	if(root != NULL) 
	{
		ICETREE_DEBUG("Node Value : %d\n",root->position);
		traversal_tree_dbg(root->next);
		ICETREE_DEBUG("Child:");
		traversal_tree_dbg(root->child);
	} 
}


ice_tree_node * new_node(int position, void *data)
{
	ice_tree_node *new_node = icetree_xmalloc(sizeof(ice_tree_node));

	if(new_node) 
	{
		new_node->next = NULL;
		new_node->child = NULL;
		new_node->data = data;
		new_node->position = position;
    	}

	return new_node;
}

ice_tree_node * append_sibling(ice_tree_node * n, int position,void *data)
{
	if(n == NULL)
		return NULL;

    	while(n->next)
		n = n->next;

	return(n->next = new_node(position,data));
}

ice_tree_node * append_child(ice_tree_node * n, int position, void *data)
{
	if(n == NULL)
		return NULL;

    	if(n->child)
		return append_sibling(n->child, position,data);
	else
		return (n->child = new_node(position,data));
}


