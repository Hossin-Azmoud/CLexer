#include <Structures/Node.h>

void free_node(Node *node)
{
	if (node) {
		free_raw_token(node->data);
		free(node);
	}
}
