# Ice Stack lib
ICE Queue lib is a Open Source C library to help in Queue creation(enqueue, dequeue and have options to carry custom user elements in queue).

The operations of a queue make it a first-in-first-out (FIFO) data structure. In a FIFO data structure, the first element added to the queue will be the first one to be removed. This is equivalent to the requirement that once a new element is added, all elements that were added before have to be removed before the new element can be removed. 


First step, understand before run
--

Study the example in src/main.c to understand how to use...
Study calls to know how to use  lib...  lib/ice\_queue.h

any doubts... create issue or send me a e-mail...

Second step, testing!
--


Look this following commands to run:
```
$ git clone https://github.com/CoolerVoid/ice_queue
$ cd ice_queue
$ make
$ ./bin/test_queue
$ cat src/main.c
```

look this following:
```lang=c

// this is a example how you can use the lib ice qeue
#include <stdio.h>
#include <stdlib.h>
#include "../lib/ice_queue.h"

// your custom data here
struct data {
    char *label;
    int line;
};

typedef struct data data;

// your custom data here
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

// your custom free heap func here
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
	Ice_Queue S = ice_init_queue();

	puts("\nInsert elements with custom data\n");

	ice_enqueue(S, form_data("hulk",2));
	ice_enqueue(S, form_data("batman",4));
	ice_enqueue(S, form_data("spiderman",8));
	ice_enqueue(S, form_data("Dredd",32));
	ice_enqueue(S, form_data("Spock",16));

	puts("List elements");
	ice_traversal_queue(S,inter_data);

	puts("\nRemove elements / free all heap\n");

	// clean heap in order of queue, and show data of queue in order to remove...
	while (!ice_queue_empty(S))
	{
		inter_data(S->head->data);
		ice_dequeue(S,free_data);
	}

	free(S);
}

```



Reference:
--
https://en.wikipedia.org/wiki/The\_C\_Programming\_Language  (good book)

https://en.wikipedia.org/wiki/Queue_(abstract_data_type)
