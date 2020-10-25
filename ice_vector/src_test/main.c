#include <stdio.h>
#include <stdlib.h>

#include "../lib/ice_vector.h"

int main(void)
{
    int i=0;

    ice_vector v;
    ice_vector_init(&v);

// insert elements in vector
    ice_vector_add(&v, "pacman");
    ice_vector_add(&v, "ghost");
    ice_vector_add(&v, "ball");
    ice_vector_add(&v, "triangle");
    ice_vector_add(&v, "square");
    ice_vector_add(&v, "avenger");
    ice_vector_add(&v, "dragon");
    ice_vector_add(&v, "dog");

    puts("First example show all elements");

    while (i < ice_vector_max(&v))
    {
        printf("%s \n", (char *) ice_vector_view(&v, i));
	i++;
    }

    puts("\nTest swap element, Edit and remove");

// change vector positions, this is cool to use in sort algorithms
    ice_vector_swap(&v, 0,1);
    ice_vector_swap(&v, 2,3);
    ice_vector_remove(&v, 7);
    ice_vector_write(&v, 3, "ball3");

    i=0;

    while (i < ice_vector_max(&v))
    {
        printf("%s \n", (char *) ice_vector_view(&v, i));
	i++;
    }

    i=0;

// example to use with quick sort
    puts("\nTest QuickSort with string");

    qsort(v.elements, v.max, sizeof(void *), ice_cmp_str);

    while (i < v.max)
    {
        printf("%s \n", (char *) v.elements[i]);
	i++;
    }
   

   puts("\nTest bsearch function");

   char *find = "avenger";
   char *search = *(char **)bsearch (&find, v.elements, v.max, sizeof (void *), ice_cmp_str);

   if(search != NULL) 
      printf("Found item in position %s\n", search);
   else 
      printf("Element = %s could not be found\n", find);
 
// free heap
    ice_vector_free(&v);

    return 0;
}
