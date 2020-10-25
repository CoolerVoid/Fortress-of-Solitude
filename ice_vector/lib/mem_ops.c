#include "mem_ops.h"

// based in OpenBSD reallocarray() function http://man.openbsd.org/reallocarray.3
void *ice_xmallocarray (size_t nmemb, size_t size) 
{
	if ((nmemb >= MUL_NO_OVERFLOW || size >= MUL_NO_OVERFLOW) && nmemb > 0 && SIZE_MAX / nmemb < size) 
	{
		ICE_DEBUG("integer overflow block");
		exit(0);
	}

	void *ptr = malloc (nmemb*size);

	if (ptr == NULL)
	{	
		ICE_DEBUG("Error in size %lu\n",size);
		exit(0);
	}
	return ptr;
}

// based in OpenBSD reallocarray() function http://man.openbsd.org/reallocarray.3
void *ice_xreallocarray (void *ptr, size_t nmemb, size_t size) 
{
	if ((nmemb >= MUL_NO_OVERFLOW || size >= MUL_NO_OVERFLOW) && nmemb > 0 && SIZE_MAX / nmemb < size) 
	{
		ICE_DEBUG("integer overflow block");
		exit(0);
	}

	void *p = realloc (ptr, nmemb*size);

	if (p == NULL)
	{
		ICE_DEBUG("Error in size %lu\n",size);
		exit(0);
	}

	return p;
}

void ice_xfree(void **ptr) 
{
	assert(ptr);
	if( ptr != NULL )
        {
		free(*ptr);
		*ptr=NULL;	
        }
	
}





