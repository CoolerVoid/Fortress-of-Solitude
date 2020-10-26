#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "arithmetic_eval.h" 

 
int main(int argc, char** argv) 
{
	if(argc > 1) 	
    		printf("%d\n", arit_eval(argv[1]));
    		
  	return 0;
}
