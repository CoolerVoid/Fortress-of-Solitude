#include "parser.h"
 
void parse_error(const char* string) 
{
  	DEBUG("Unexpected symbol '%c' at position %u.\n\n", string[G_STRING_ITERATOR], G_STRING_ITERATOR);

  	exit(1);
}
 
char Get_char(const char* string, char c) 
{
  	if(string[G_STRING_ITERATOR] != c) 
    		parse_error(string);
  	
  	++G_STRING_ITERATOR;

	return c;
}
 

int Get_int(const char* string) 
{
  	int num=0;
 
  	if(!isdigit(string[G_STRING_ITERATOR])) 
   		parse_error(string);
 
	num = (int)strtol(string+G_STRING_ITERATOR, (char **)NULL, 10); 

  	while(isdigit(string[G_STRING_ITERATOR])) 
    		++G_STRING_ITERATOR;
  
  	return num;
}

 
Expr* expression(const char* string) 
{
	Expr* expr;
 
	if(string[G_STRING_ITERATOR] == '(' || isdigit(string[G_STRING_ITERATOR])) 
	{
    		expr = (Expr*)xmalloc(sizeof(Expr));
    		expr = part(string, expr);
    		expr = part_tail(string, expr);

    		return expr;
  	} else 
    		parse_error(string);
 	

	return NULL; 
}
 
  
Expr* context(const char* string, Expr* expr) 
{
  	if(string[G_STRING_ITERATOR] == '(') 
	{
    		expr->op = Get_char(string, '(');
    		expr->data.expr[0] = expression(string);
    		Get_char(string, ')');

  	} else if(isdigit(string[G_STRING_ITERATOR])) {
    		expr->op = 'x';
    		expr->data.partinal = Get_int(string);
  	}

  	return expr;
}
 
Expr* context_tail(const char* string, Expr* expr) 
{
  	Expr* new_expr;
 
  	switch(string[G_STRING_ITERATOR]) 
	{
  		case '*':
  		case '/':
    			new_expr = (Expr*)xmalloc(sizeof(Expr));
    			new_expr->data.expr[1] = (Expr*)xmalloc(sizeof(Expr));	
    			new_expr->op = Get_char(string, string[G_STRING_ITERATOR]);
    			new_expr->data.expr[0] = expr; 
    			new_expr->data.expr[1] = context(string, new_expr->data.expr[1]);
    			new_expr = context_tail(string, new_expr);
    			return new_expr;

  		case '+':
  		case '-':
  		case ')':

  		case 0:
    			return expr;

  		default:
    			parse_error(string);
  	}

	return NULL;
}
 
Expr* part(const char* string, Expr* expr) 
{
  	if(string[G_STRING_ITERATOR] == '(' || isdigit(string[G_STRING_ITERATOR])) 
	{
    		expr = context(string, expr);
    		expr = context_tail(string, expr);
    		return expr;
  	} else 
    		parse_error(string);
  	

	return NULL;
}
 
Expr* part_tail(const char* string, Expr* expr) 
{
  	Expr* new_expr;
 
  	switch(string[G_STRING_ITERATOR]) 
	{
  		case '+':

  		case '-':
    			new_expr = (Expr*)xmalloc(sizeof(Expr));
    			new_expr->data.expr[1] = (Expr*)xmalloc(sizeof(Expr));
    			new_expr->op = Get_char(string, string[G_STRING_ITERATOR]);
    			new_expr->data.expr[0] = expr;
    			new_expr->data.expr[1] = part(string, new_expr->data.expr[1]);
    			new_expr = part_tail(string, new_expr);
    			return new_expr;

  		case ')':

  		case 0:
    			return expr;

  		default:
    			parse_error(string);
  	}

	return NULL;
}
 
