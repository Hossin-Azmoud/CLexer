#ifndef STACK_H
#define STACK_H
#include <Structures/Node.h>

typedef struct stack_s {
	Node   *head, *tail;
	size_t count;
} Stack;

Stack *stack_new();
int  stack_push(Stack *stack, void *data);
void *stack_pop(Stack *stack);
void  free_stack(Stack *stack);
#endif // STACK_H
