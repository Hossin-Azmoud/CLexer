#include <Structures/Stack.h>

// NOTE (#1): Private structure.
typedef struct stack_s {
	Node   *head, *tail;
	size_t count;
} Stack;

Stack *stack_new()
{
	Stack *stack = malloc(sizeof(Stack));
	if (stack == NULL) {
		fprintf(stderr, "Could not allocate the stack...");
		return NULL;
	}

	stack->tail     = NULL;
	stack->head     = NULL;
	stack->count    = 0;
	return stack;
}

Token *stack_pop(Stack *stack)
{
	Node  *temp = NULL;
	Token *data = NULL;

	if (stack->head == NULL) {
		return NULL;
	}

	data  = malloc(sizeof(Token));

	if (stack->count == 1) {
		data->type  = stack->tail->data->type;
		data->value = strdup(stack->tail->data->value);
		free_node(stack->tail);
		stack->head = NULL;
		stack->tail = NULL;
		stack->count--;
		return data;
	}

	if (stack->count > 1) {
		data->type  = stack->tail->data->type;
		data->value = strdup(stack->tail->data->value);
		temp        = stack->tail->prev;
		free_node(stack->tail);
		stack->tail = temp;
		stack->tail->next = NULL;
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

	if (!(stack->tail) && !(stack->head)) {
		stack->head = node;
		stack->tail = node;
		stack->count++;
		return 1;
	}

	node->prev        = stack->tail;
	stack->tail->next = node;
	stack->tail       = node;
	stack->count++;
	return 1;
}

void free_stack(Stack *stack)
{
	Node *curr = NULL, *tmp = NULL;

	if (stack) {
		curr = stack->head;

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
	Node   *curr = stack->head;
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

