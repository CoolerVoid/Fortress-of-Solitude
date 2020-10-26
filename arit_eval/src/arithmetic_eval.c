#include "arithmetic_eval.h"

int arit_eval(char *in)
{
	if(strnlen(in,1025)>1024)
	{
		DEBUG("Error:\n Arithmetic expression is very large \n");
		return 0;
	}

	Expr* expr=NULL;
    	expr=expression(in);

	int ret=Run_exp(expr);	

    	XFREE(&expr);

	return ret;

}

