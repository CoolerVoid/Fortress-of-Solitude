#include "ice_queue.h"


void *ice_queue_xmalloc_fatal(size_t size) 
{
	ICE_QUEUE_DEBUG("\n Memory error...\n Size: %lu\n",size);

	exit(0);
}

void *ice_queue_xmalloc(size_t size) 
{
	void *ptr = malloc(size);

	if (ptr == NULL) 
		return ice_queue_xmalloc_fatal(size);

	return ptr;
}

Ice_Queue ice_init_queue() 
{
	Ice_Queue qp = (Ice_Queue) ice_queue_xmalloc(sizeof(Ice_QueueType));
	qp->head = NULL;
	qp->tail = NULL;
	return qp;
} 

int ice_queue_empty(Ice_Queue Q) 
{
	return (Q->head == NULL);
} 

void ice_enqueue(Ice_Queue Q, void *d) 
{
	Ice_NodePtr_queue np = (Ice_NodePtr_queue) ice_queue_xmalloc(sizeof(Ice_Node_queue));
	np->data = d;
	np->next = NULL;

	if (ice_queue_empty(Q)) 
	{
		Q->head = np;
		Q->tail = np;
	} else {
		Q->tail->next = np;
		Q->tail = np;
	}
} 


void ice_dequeue(Ice_Queue Q, void (*lambda)(void *argvs)) 
{
	if (ice_queue_empty(Q)) 
	{
		printf("\nAttempt to remove from an empty queue\n");
		exit(1);
	}
	void *hold = Q->head->data;
	Ice_NodePtr_queue temp = Q->head;
	Q->head = Q->head->next;
	if (Q -> head == NULL) 
		Q->tail = NULL;
	lambda(hold);
	free(temp);
} 



void ice_traversal_queue(Ice_Queue Q, void (*lambda)(void *argvs))
{
	void *ptr=(void *)Q->head;
	Ice_Queue temp = Q;

	while(temp->head->next!=NULL)
	{
		lambda(temp->head->data);
		temp->head=temp->head->next;

	//	if (temp->head == NULL) 
	//		temp->tail = NULL;
	}

	lambda(temp->head->data);

	Q->head=(Ice_NodePtr_queue)ptr;

}
