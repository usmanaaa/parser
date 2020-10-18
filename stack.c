/*
 * stack.c
 *
 * A simple stack implementation using a linked list found online.
 * Source: https://www.techiedelight.com/stack-implementation-using-linked-list/
 */

#include "stack.h"

// A linked list node
struct Node {
	void* data;				// integer data
	Node next;		// pointer to the next node
};

// Utility function to add an element x in the stack
void push(Stack top, void* x) // insert at the beginning
{
	// Allocate the new node in the heap
	Node node = NULL;
	node = (Node) malloc(sizeof(struct Node));

	// check if stack (heap) is full. Then inserting an element would
	// lead to stack overflow
	if (!node) {
		printf("\nHeap Overflow");
		exit(1);
	}

	// set the data in allocated node
	node->data = x;

	// Set the .next pointer of the new node to point to the current
	// top node of the list
	node->next = *top;

	// update top pointer
	*top = node;
}

// Utility function to check if the stack is empty or not
int isEmpty(Node top) {
	return top == NULL;
}

// Utility function to return top element in a stack
void* peek(Node top) {
	// check for empty stack
	if (!isEmpty(top))
		return top->data;
	else
		exit(EXIT_FAILURE);
}

// Utility function to pop top element from the stack
void pop(Stack top) // remove at the beginning
{
	Node node;

	// check for stack underflow
	if (*top == NULL) {
		printf("\nStack Underflow");
		exit(1);
	}

	node = *top;

	// update the top pointer to point to the next node
	*top = (*top)->next;

	// free allocated memory
	free(node);
}

//// main function
//int main(void) {
//	Node top = NULL;
//
//	push(&top, 1);
//	push(&top, 2);
//	push(&top, 3);
//
//	printf("Top element is %d\n", peek(top));
//
//	pop(&top);
//	pop(&top);
//	pop(&top);
//
//	if (isEmpty(top))
//		printf("Stack is empty");
//	else
//		printf("Stack is not empty");
//
//	return 0;
//}
