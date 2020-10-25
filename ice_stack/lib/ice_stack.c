#include "ice_stack.h"


void *icestack_xmalloc_fatal(size_t size) 
{
	ICESTACK_DEBUG("\n Memory error...\n Size: %lu\n",size);

	exit(0);
}

void *icestack_xmalloc(size_t size) 
{
	void *ptr = malloc(size);

	if (ptr == NULL) 
		return icestack_xmalloc_fatal(size);

	return ptr;
}

IceStack init_ice_stack() 
{
	IceStack sp = (IceStack) icestack_xmalloc(sizeof(IceStackType));
	sp->top=NULL;
	return sp;
}

int ice_stack_empty(IceStack S) 
{
	return (S->top == NULL);
} 

void ice_stack_push(IceStack S, void *in) 
{
	icestack_NodePtr np = (icestack_NodePtr) icestack_xmalloc(sizeof(icestack_Node));
	np->data=in;
	np->next=S->top;
	S->top=np;
}

void *ice_stack_pop(IceStack S,void (*lambda)(void *argvs) ) 
{
	if (ice_stack_empty(S)) 
		return NULL;

	void *hold = S->top->data;

	icestack_NodePtr temp = S->top;
	S->top = S->top->next;
	lambda(temp->data);
	free(temp);

	return hold;
}

void ice_stack_inter_reverse_traversal( IceStack S, void (*lambda)(void *argvs))
{
	IceStack temp=S;
	void *ptr=(void *)S->top;


	while(temp->top!=NULL)
	{

		lambda(temp->top->data);
		temp->top = temp->top->next;
	}


	S->top=(icestack_NodePtr)ptr;
}


