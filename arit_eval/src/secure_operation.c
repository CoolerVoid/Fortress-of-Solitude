#include "secure_operation.h"

int safe_add(int a, int b)
{
	if( ((b > 0) && (a > (INT_MAX - b))) || ((b < 0) && (a < (INT_MAX - b))) )
		return 0;
	else
		return a+b;
}

int safe_sub(int a, int b)
{
	if( (b > 0 && a < INT_MIN + b) || (b < 0 && a > INT_MAX + b) )
		return 0;
	else
		return a-b;
}

int safe_mul(int a, int b)
{
	if (a > 0) 
	{
      		if(b > 0) 
		{ 
        		if (a > (INT_MAX / b)) 
          			return 0; 
      		} else {
        		if (b < (INT_MIN / a))  
          			return 0; 
		}
    	} else {  
      		if (b > 0) 
		{
        		if (a < (INT_MIN / b)) 
          			return 0; 
                } else {  
        		if ( (a != 0) && (b < (INT_MAX / a))) 
          			return 0; 
		}		
      	}	

	return a*b;
}


// TODO improve that
int safe_div(int a, int b)
{
	if(b == 0) 
      		return 0; 
    	else if (a == INT_MIN && b == -1)     
      		return 0; 
    	else 
		return a/b; 
}
