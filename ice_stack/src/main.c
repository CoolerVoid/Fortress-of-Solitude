#include <stdio.h>
#include <stdlib.h>
#include "../lib/ice_stack.h"


struct data {
    char *label;
    int line;
};

typedef struct data data;

void *form_data(char * label, int line)
{
	data *in=malloc(sizeof(data));

	in->label = strdup(label);
        in->line = line;

	return (void *)in;
}

void inter_data(void *argv)
{
	data *in=(data *)argv;

	if(in != NULL)
		printf("Label: %s\n line: %d\n", in->label,in->line);
}


void free_data(void *argv)
{
	data *in=(data *)argv;

	if(in != NULL)
	{
		free(in->label);
		in->label=NULL;
		in->line=0;
		free(in);
		in=NULL;
	}
}


int main() 
{
	IceStack S = init_ice_stack();

	puts("\nInsert elements with custom data\n");

	ice_stack_push(S, form_data("hulk",2));
	ice_stack_push(S, form_data("batman",4));
	ice_stack_push(S, form_data("spiderman",8));
	ice_stack_push(S, form_data("Dredd",32));
	ice_stack_push(S, form_data("Spock",16));

	ice_stack_inter_reverse_traversal(S,inter_data);

	puts("\nRemove elements / free all heap\n");

	while (!ice_stack_empty(S))
		ice_stack_pop(S,free_data);

	free(S);
}
