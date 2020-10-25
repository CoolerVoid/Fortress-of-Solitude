/* Doubly Linked List implementation */

#include "ice_doubly_linked.h"

// alocation tasks, use this in future
void ice_dl_xfree(void **ptr) 
{
	assert(ptr);
	if( ptr != NULL )
        {
		free(*ptr);
		*ptr=NULL;	
        }
	
}


void *ice_dl_xmalloc_fatal(size_t size) 
{
	ICE_DL_DEBUG("\n Memory error...\n dbg size: %lu\n",size);

	exit(0);
}

void *ice_dl_xmalloc(size_t size) 
{
	void *ptr = malloc(size);

	if (ptr == NULL) 
		return ice_dl_xmalloc_fatal(size);

	return ptr;
}


ice_dl_node* ice_create_dl_node(int position, void * data) 
{
	struct ice_dl_node* New_node = (struct ice_dl_node*)ice_dl_xmalloc(sizeof(struct ice_dl_node));
	New_node->position = position;
	New_node->data = data;
	New_node->prev = NULL;
	New_node->next = NULL;

	return New_node;
}


ice_dl_node *Get_head_dl_position(ice_dl_node *in)
{
	
	while(in->prev != NULL) 
		in = in->prev;
	return in;	

}


// Insert element in last position
ice_dl_node *Insert_dl_in_last(ice_dl_node *in,int position, void * data) 
{
	ice_dl_node* New_node = ice_create_dl_node(position, data);

	if(in == NULL) 
	{
		in = New_node;
		return in;
	}

	while(in->next != NULL) 
		in = in->next; 

	in->next = New_node;
	New_node->prev = in;
	return New_node;
}

ice_dl_node *Delete_dl_by_position(int position, ice_dl_node * list,void (*lambda)(void *argvs) )
{
	ice_dl_node *head = Get_head_dl_position(list);
	ice_dl_node *current = head;            
  	ice_dl_node *previous = current;   
	ice_dl_node *tmp=NULL;

	while(current != NULL)
	{           
		if(current->position == position)
		{     
			previous = current->prev;
			previous->next=current->next;
			tmp=current->next;
			tmp->prev=previous;
      			if(current == head)
				head = current->next;
			lambda(current->data);
      			free(current);
      			return tmp;
    		}                               
    		previous = current;             
    		current = current->next;        
  	}

 	return current;

}                              



// List FIFO debug
void fifo_dl_list_dbg(ice_dl_node* in) 
{
	struct ice_dl_node* temp = in;

	ICE_DL_DEBUG(" ");

	while(temp != NULL) 
	{
		printf("%d ",temp->position);
		temp = temp->next;
	}

	puts(" ");
}


// List LIFO debug
void lifo_dl_list_dbg(ice_dl_node* in) 
{
	struct ice_dl_node* temp = in;

	ICE_DL_DEBUG(" ");

	if(temp == NULL) 
		return; 

	while(temp->next != NULL) 
		temp = temp->next;

	while(temp != NULL) 
	{
		printf("%d ",temp->position);
		temp = temp->prev;
	}
	puts(" ");
}




// List FIFO debug
void inter_fifo_dl_list(ice_dl_node* in,void (*lambda)(void *argvs)) 
{
	struct ice_dl_node* temp = in;

	while(temp != NULL) 
	{
		lambda(temp->data);
		temp = temp->next;
	}
}

// List LIFO debug
void inter_lifo_dl_list(ice_dl_node* in,void (*lambda)(void *argvs)) 
{
	struct ice_dl_node* temp = in;

	if(temp == NULL) 
		return; 

	while(temp->next != NULL) 
		temp = temp->next;

	while(temp != NULL) 
	{
		lambda(temp->data);
		temp = temp->prev;
	}
}



// Clear heap memory
void ice_clear_dl(ice_dl_node* in,void (*lambda)(void *argvs)) 
{
	ice_dl_node *temp = Get_head_dl_position(in);
	ice_dl_node *temp2 = NULL;


	if(temp == NULL) 
		return; 

	while(temp->next != NULL) 
	{
		temp2 = temp->next;

		if(temp != NULL)
		{
			lambda(temp->data);
			free(temp);
			temp = temp2;
		}
	}

	if(temp2!=NULL)
	{
		lambda(temp2->data);
		free(temp2);
	}
}
