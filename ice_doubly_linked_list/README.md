# ice_doubly_linked_list
ICE doubly linked list is a Open Source C library to help in two-way linked lists creation, you can carry your custom data and common functions(insert,delete, traversal each element, destroy).

In computer science, a doubly linked list is a linked data structure that consists of a set of sequentially linked records called nodes. Each node contains three fields: two link fields (references to the previous and to the next node in the sequence of nodes) and one data field.(by wikipedia) 

<img align="center" width="640" height="90" src="https://upload.wikimedia.org/wikipedia/commons/thumb/5/5e/Doubly-linked-list.svg/610px-Doubly-linked-list.svg.png">

First step, understand before run
--

Study the src/main.c to understand how to use...
Study calls to know how to use  lib...  lib/ice\_doubly\_linked.h

any doubts... create issue or send me a e-mail...

Second step, testing!
--


Look this following commands to run:
```
$ git clone https://github.com/CoolerVoid/ice_doubly_linked_list
$ cd ice_doubly_linked_list
$ make
$ ./bin/test_doubly_linked
$ cat src/main.c
```

Example:
```c
#include <stdio.h>
#include <stdlib.h>
#include "../lib/ice_doubly_linked.h"

// user custom data to use in NODE of Doubly linked List
struct data {
    char *label;
    char *var_name;
};


typedef struct data data;

// your custom function here for your data
void *form_data(char * label, char *varname)
{
	data *in=malloc(sizeof(data));

	in->label = strdup(label);
	in->var_name = strdup(varname);

	return (void *)in;
}

// your custom interate func here
void inter_data(void *argv)
{
	data *in=(data *)argv;

	if(in != NULL)
		printf("Label: %s\n var_name: %s\n", in->label,in->var_name);
}

// your func to liberate your custom data
void inter_free(void *argv)
{
	data *in=(data *)argv;

	if(in != NULL)
	{
		free(in->label);
		in->label=NULL;

		free(in->var_name);
		in->var_name=NULL;
	
		free(in);
		in=NULL;
	}
}


int main(void) 
{
	void *A=form_data("hulk","green");
	// create a doubly linked list, var 'n' is a linked list
	ice_dl_node *n=ice_create_dl_node(0,A);

	void *B=form_data("spider","red");
	Insert_dl_in_last(n,2,B);

	void *C=form_data("daredevil","red");
	Insert_dl_in_last(n,4,C);

	void *D=form_data("wolverine","yellow");
	Insert_dl_in_last(n,6,D);

	void *E=form_data("hellboy","red");
	Insert_dl_in_last(n,8,E);

	void *F=form_data("deadpool","dark red");
	Insert_dl_in_last(n,10,F);

	// list positions
	fifo_dl_list_dbg(n); 
	lifo_dl_list_dbg(n);

	// remove position 8
	puts("Delete position 8");
	Delete_dl_by_position(8,n,inter_free);

	// custom list inter to show data
	inter_fifo_dl_list(n,inter_data);
	puts("----------------------------");	
	inter_lifo_dl_list(n,inter_data);

	// liberate heap memory
	ice_clear_dl(n,inter_free);

}

```


Reference:
--
https://en.wikipedia.org/wiki/The\_C\_Programming\_Language

https://en.wikipedia.org/wiki/Doubly\_linked\_list
