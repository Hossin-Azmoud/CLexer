#ifndef NODE_H
#define NODE_H
#include <lexer/Token.h>
typedef struct Node Node;

typedef struct Node {
    Token *data;
    Node *next;
	Node *prev;
} Node;

void free_node(Node *node);

#endif // NODE_H
