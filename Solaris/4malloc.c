#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#define SIZE 1024

typedef struct node {
	char* str;
	struct node* next;
} node_t; 

void append(node_t** head, char* str) {
	node_t* new_node = (node_t *)malloc(sizeof(node_t));

	new_node->str = (char *)malloc(sizeof(char) * (strlen(str) + 1));
	strcpy(new_node->str, str);
	
	new_node->next = (*head);
	(*head) = new_node;
	
	return;
}

void printList(node_t *node) {
	while (node != NULL) {
		printf("%s", node->str);
		node = node->next;
	}
	return;
}

int main() {
	node_t* head = NULL;
	char buf[SIZE] = { 0 };
	
	fgets(buf, SIZE, stdin);
	while (buf[0] != '.') {
		append(&head, buf);
		fgets(buf, SIZE, stdin);
	}
	printList(head);
	exit(EXIT_SUCCESS);

}