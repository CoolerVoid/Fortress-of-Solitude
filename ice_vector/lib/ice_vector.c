#include <stdio.h>
#include <stdlib.h>
#include "ice_vector.h"
#include "mem_ops.h"


void ice_vector_init(ice_vector *v)
{
	v->limit = ice_vector_LIMIT;
	v->max = 0;
	v->elements = ice_xmallocarray(v->limit, sizeof(void *));
}

int ice_vector_max(ice_vector *v)
{
	return v->max;
}

void ice_vector_resize(ice_vector *v, int limit)
{
 	void **elements = ice_xreallocarray(v->elements, limit, sizeof(void *) ); //using OpenBSD function reallocarray() at mem_ops.c

    	if (elements) 
	{
        	v->elements = elements;
        	v->limit = limit;
    	}
}

void ice_vector_write(ice_vector *v, int index, void *element)
{
	if (index >= 0 && index < v->max)
		v->elements[index] = element;
}

void ice_vector_swap(ice_vector *v, int index, int index2)
{
	void *tmp= v->elements[index];
	v->elements[index]  =  v->elements[index2];
	v->elements[index2] =  tmp;
}

void ice_vector_add(ice_vector *v, void *element)
{
	if (v->limit == v->max)
        	ice_vector_resize(v, v->limit * 2);

    	v->elements[v->max++] = element;
}


void *ice_vector_view(ice_vector *v, int index)
{
	if (index >= 0 && index < v->max)
        	return v->elements[index];

	return NULL;
}

void ice_vector_free(ice_vector *v)
{
	ICE_XFREE(v->elements);
}

void ice_vector_remove(ice_vector *v, int index)
{
	int i=0;

	if (index < 0 || index >= v->max)
        	return;

    	v->elements[index] = NULL;


	i = index;
    	while (i < v->max - 1) 
	{
        	v->elements[i] = v->elements[i + 1];
        	v->elements[i + 1] = NULL;
		i++;
    	}

    	v->max--;

    	if (v->max > 0 && v->max == v->limit / 4)
        	ice_vector_resize(v, v->limit / 2);
}

void ice_vector_pop(ice_vector *v)
{
	ice_vector_remove(v,v->max);
}


int ice_cmp_str(const void *a, const void *b)
{
// TODO improve this function
	size_t sizemax=strnlen(*(char **)a,ICE_MAX_LEN_STR_CMP);	
	return strncmp(*(char **)a, *(char **)b, sizemax);
}



int ice_cmp_int(const void *a, const void *b) 
{ 
	const int *ia = (const int *)a; 
	const int *ib = (const int *)b;
	return *ia  - *ib;  
}

int ice_cmp_double(const void *a, const void *b)
{
	double ia = *(double*)a; 
	double ib = *(double*)b;

	if (ia < ib) 
		return -1;

	if (ia > ib) 
		return  1;

	return 0;
} 

int ice_cmp_float(const void *a, const void *b)
{
	double ia = *(float*)a; 
	double ib = *(float*)b;

	if (ia < ib) 
		return -1;

	if (ia > ib) 
		return  1;

	return 0;
} 




