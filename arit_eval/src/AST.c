#include "AST.h"

// this function evaluate the arithmetic expression

int Run_exp(Expr* expr) 
{
	int ret=0;
 /*
	Please read this https://en.wikipedia.org/wiki/Order_of_operations
	don't change nothing here
*/
	switch(expr->op) 
	{
  		case '(':
    			ret=Run_exp(expr->data.expr[0]);
    			XFREE(&expr->data.expr[0]);
    			break;

  		case '*':
			ret=safe_mul( Run_exp(expr->data.expr[0]),Run_exp(expr->data.expr[1]) );
    			XFREE(&expr->data.expr[0]);
    			XFREE(&expr->data.expr[1]);
    			break;

  		case '/':
    			ret=safe_div(Run_exp(expr->data.expr[0]),Run_exp(expr->data.expr[1]));
    			XFREE(&expr->data.expr[0]);
    			XFREE(&expr->data.expr[1]);
    		break;

  		case '+':
    			ret=safe_add(Run_exp(expr->data.expr[0]),Run_exp(expr->data.expr[1]));
    			XFREE(&expr->data.expr[0]);
    			XFREE(&expr->data.expr[1]);
    		break;

  		case '-':
    			ret=safe_sub(Run_exp(expr->data.expr[0]),Run_exp(expr->data.expr[1]));
    			XFREE(&expr->data.expr[0]);
    			XFREE(&expr->data.expr[1]);
    		break;

  		case 'x':
    			ret=expr->data.partinal;
    		break;

  		default:
    			exit(1);
  	}

	return ret;
}
 
