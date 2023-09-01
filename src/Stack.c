#include <Structures/Stack.h>

// NOTE (#1): Private structure.
typedef struct stack_s {
	Node   *__base, *__top;
	size_t  count;
} Stack;

Stack *stack_new()
{
	Stack *stack = malloc(sizeof(Stack));

	if (stack == NULL) {
		fprintf(stderr, "Could not allocate the stack...");
		return NULL;
	}

	stack->__top    = NULL;
	stack->__base   = NULL;
	stack->count    = 0;

	return stack;
}

Token *stack_pop(Stack *stack)
{
	Node  *temp = NULL;
	Token *data = NULL;

	if (stack->__base == NULL) {
		return NULL;
	}

	data  = malloc(sizeof(Token));
	if (stack->count == 1) {
		data->type  = stack->__top->data->type;
		data->value = strdup(stack->__top->data->value);
		free_node(stack->__top);
		stack->__base = NULL;
		stack->__top = NULL;
		stack->count--;
		return data;
	}

	if (stack->count > 1) {
		data->type  = stack->__top->data->type;
		data->value = strdup(stack->__top->data->value);
		temp        = stack->__top->prev;
		free_node(stack->__top);
		stack->__top = temp;
		stack->__top->next = NULL;
		stack->count--;
		return data;
	}

	// If it is an empty stack..
	return NULL;
}

int stack_push(Stack *stack, Token *data)
{
	Node *node = malloc(sizeof(Node));
	
	if (!node) {
		fprintf(stderr, "Could not allocate a node in the push operation.\n");
		return 0;
	}

	node->data =tokendup(data);
	node->next = NULL;
	node->prev = NULL;

	if (!(stack->__top) && !(stack->__base)) {
		stack->__base = node;
		stack->__top = node;
		stack->count++;
		return 1;
	}

	node->prev        = stack->__top;
	stack->__top->next = node;
	stack->__top       = node;
	stack->count++;
	return 1;
}

void free_stack(Stack *stack)
{
	Node *curr = NULL, *tmp = NULL;

	if (stack) {
		curr = stack->__base;

		while (curr != NULL) {
			tmp = curr->next;
			free_node(curr);
			curr = tmp;
		}

		free(stack);
		stack = NULL;
	}
}

void stack_dump(Stack *stack)
{
	Node   *curr = stack->__base;
	size_t size = stack->count;

	while (curr) {
		printf("(%s)", (curr->data->value));
		size--;

		if (size != 0)
			printf(" -> ");

		curr = curr->next;
	}

	putchar('\n');
}

