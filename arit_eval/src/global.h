#ifndef GLOBAL_H
#define GLOBAL_H

extern unsigned int G_STRING_ITERATOR ;
 
typedef union {
  int partinal;
  struct expression* expr[2];
} Data;
 
typedef struct expression {
  char op;
  Data data;
} Expr;

#endif
