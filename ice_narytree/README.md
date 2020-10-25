# ice n-ary tree C library
Ice_narytree is a open source C library to help in Generic tree(n-ary tree) and resources to carry custom data, common functions(n-ary, traversal, search,create, insert childs/siblings,remove childs, destroy trees...)

You can use trees to solve file system problems, static analysis problems,  like recursive tree with N points with childs...
<img align="right" width="240" height="220" src="https://raw.githubusercontent.com/CoolerVoid/icenarytree/master/doc/wide-shot-isolated-tree-covered-snow-snowy-area-just-like-fairytale_181624-5468.jpg">

In computer science, a tree is a widely used abstract data type that simulates a hierarchical tree structure, with a root value and subtrees of children with a parent node, represented as a set of linked nodes. A tree data structure can be defined recursively as a collection of nodes (starting at a root node), where each node is a data structure consisting of a value, together with a list of references to nodes (the "children"), with the constraints that no reference is duplicated, and none points to the root.

First step, understand before run
--

Study the src/main.c to understand how to use...
Study calls to know how to use  lib...  lib/icenarytree.h

any doubts... create issue or send me a e-mail...
<img align="right" width="240" height="220" src="https://upload.wikimedia.org/wikipedia/commons/5/5f/Tree_%28computer_science%29.svg">

Second step, testing!
--


Look this following commands to run:
```
$ git clone https://github.com/CoolerVoid/ice_narytree
$ cd ice_narytree
$ make
$ ./bin/test_tree
$ cat src/main.c
```

No memory leaks
--

Look this content(tested with valgrind)
```
$ cat heap_log/valgrind_output.txt | tail 
 ==63855== 
==63855== HEAP SUMMARY:
==63855==     in use at exit: 0 bytes in 0 blocks
==63855==   total heap usage: 47 allocs, 47 frees, 10,399 bytes allocated
==63855== 
==63855== All heap blocks were freed -- no leaks are possible
==63855== 
==63855== For counts of detected and suppressed errors, rerun with: -v
==63855== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

Example:
```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../lib/ice_narytree.h"



// user custom data to use in NODE of n-ary tree
struct data {
    bool taint;
    char *label;
    char *exp;
    char *var_name;
    int line;
};


typedef struct data data;


void *form_data(bool taint, char * label, char *exp, char *varname, int line)
{
	data *in=malloc(sizeof(data));

	in->label = strdup(label);
	in->var_name = strdup(varname);
        in->exp = strdup (exp);
        in->line = line;
        in->taint = taint;

	return (void *)in;
}

void inter_data(void *argv)
{
	data *in=(data *)argv;

	if(in != NULL)
	{

		printf("Label: %s\n var_name: %s\n Expression: %s\n", in->label,in->var_name,in->exp);
		printf("Line: %d\n ",in->line);
	}
}



void inter_free_treeleafs(void *argv)
{
	data *in=(data *)argv;

	if(in != NULL)
	{
		free(in->label);
		in->label=NULL;

		free(in->var_name);
		in->var_name=NULL;
	
		free(in->exp);
		in->exp=NULL;
		in->line=0;
		in->taint=NULL;
		free(in);
		in=NULL;
	}
}



int main()
{

	// Insert data in nodes
	void *A=form_data(false,"attribute","x=0","x",10);
	ice_tree_node *root = new_node(0,A);

	void *B=form_data(false,"attribute","x+=2","x",11);
        append_child(root, 1,B);

	void *C=form_data(false,"attribute","x+=8","x",12);
        append_child(root, 2,C);

	void *D=form_data(false,"attribute","z+=8","z",14);
	append_sibling(root, 3,D);

	void *E=form_data(false,"attribute","z+=12","z",15);
        append_child(root, 4,E);

	// Show all data of N-ARY TREE
    	traversal_tree_dbg(root);

	//Search by POSITION NODE
	ice_tree_node *ret=search_in_tree_per_position(root,3);
	if(ret != NULL && ret->position != 0)
		printf("\nResult found: %d \n",ret->position);

	//INSERT NODE BEFORE
	void *F=form_data(false,"sum","y+=2","y",16);
	insert_child_before(root,2,5,F);


	void *G=form_data(false,"sum","k+=2","y",17);
	insert_child_before(root,3,6,G);


	// Delete childs of node by position
	if(remove_node_childs_by_position(root,2,inter_free_treeleafs)==true)
		puts("its ok item remove item 12 and childs like 16\n");

	// CUSTOM SHOW ALL DATA
	interate_traversal_tree(root,inter_data);
	
	// liberate heap memory, destroy all tree
	traversal_and_destroy(root,inter_free_treeleafs);

	return 0;
}

```



Next resources:
--

* Functions to renderize tree using graphviz library (Its cool to debug the tree).
* Cmake config file to install in system library...
* Insert other functions...


References:
--
https://en.wikipedia.org/wiki/Tree_(data_structure)

https://www.amazon.com/Programming-Language-2nd-Brian-Kernighan/ (The best C book)
