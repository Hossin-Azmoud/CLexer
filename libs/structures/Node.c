#include <structures/Node.h>

void free_node(Node *node)
{
	if (node) {
		token_free(node->data);
		free(node);
	}
}
