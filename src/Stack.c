#include <Structures/Stack.h>

Stack *stack_new()
{
	Stack *stack = malloc(sizeof(Stack));
	if (stack == NULL) {
		fprintf(stderr, "Could not allocate the stack...");
		return NULL;
	}

	stack->tail     = NULL;
	stack->head     = NULL;
	stack->tail_sec = NULL;
	stack->count    = 0;
	return stack;
}

void *stack_pop(Stack *stack)
{
	Node *cache = NULL;
	void *data  = NULL;

	if (stack->head == NULL) {
		return NULL;
	}

	data  = malloc(sizeof(*stack->head->data));

	if (stack->count == 1) {
		*data = *(stack->head->data);
		free_node(stack->head);
		stack->head = NULL;
		stack->tail = NULL;
		return data;
	}

	if (stack->count > 1) {
		*data = *(stack->tail->data);
		cache = stack->tail->prev;
		free_node(stack->tail);
		stack->tail = cache;
		stack->tail->next = NULL;
		return data;
	}

	return NULL;
}

int stack_push(Stack *stack, void *data)
{
	Node *node = malloc(sizeof(Node));
	
	if (!node) {
		fprintf(stderr, "Could not allocate a node in the push operation.\n");
		return 0;
	}

	node->data = data;
	node->next = NULL;
	node->prev = NULL;

	if (!(stack->tail) && !(stack->head)) {
		stack->head = node;
		stack->tail = node;
		stack->count++;
		return 1;
	}

	node->prev        = stack->tail;
	stack->tail->Next = node;
	stack->tail       = node;
	stack->count++;
	return 1;
}

void free_stack(Stack *stack)
{
	Node *curr, *tmp;

	if (stack) {
		curr = stack->head;

		while (curr != NULL) {
			tmp = curr->Next;
			free_node(curr);
			curr = tmp;
		}

		free(stack);
		stack = NULL;
	}
}
