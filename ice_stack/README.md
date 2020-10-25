# Ice Stack lib
Open Source Stack library implemented using singly linked list, you can carry your custom data...


First step, understand before run
--

Study the example in src/main.c to understand how to use...
Study calls to know how to use  lib...  lib/ice\_stack.h

any doubts... create issue or send me a e-mail...

Second step, testing!
--


Look this following commands to run:
```
$ git clone https://github.com/CoolerVoid/ice_stack
$ cd ice_stack
$ make
$ ./bin/test_stack
$ cat src/main.c
```

look this following:
```c

#include <stdio.h>
#include <stdlib.h>
#include "../lib/ice_stack.h"

// your custom data here
struct data {
    char *label;
    int line;
};

typedef struct data data;

// ur custom data
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

// custom func to lkiberate heap
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
```


Reference:
--
https://en.wikipedia.org/wiki/The\_C\_Programming\_Language  (good book)

https://en.wikipedia.org/wiki/Stack_%28abstract_data_type%29
