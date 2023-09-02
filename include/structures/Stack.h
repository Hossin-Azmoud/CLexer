#ifndef STACK_H
#define STACK_H
#include <structures/Node.h>

#define IS_EMPTY(s) (s->count == 0)
typedef struct stack_s Stack;
Stack  *stack_new();
int    stack_push(Stack *stack, Token *data);
Token  *stack_pop(Stack *stack);
void   stack_dump(Stack *stack);
void   free_stack(Stack *stack);
#endif // STACK_H
