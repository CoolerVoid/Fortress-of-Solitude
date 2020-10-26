#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "mem_ops.h"
#include "global.h"

 
void parse_error(const char* string);
char Get_char(const char* string, char c);
int Get_int(const char* string);
Expr* expression(const char* string); 
Expr* context(const char* string, Expr* expr);
Expr* context_tail(const char* string, Expr* expr); 
Expr* part(const char* string, Expr* expr); 
Expr* part_tail(const char* string, Expr* expr);
