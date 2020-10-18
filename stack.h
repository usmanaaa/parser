/*
 * stack.h
 *
 * A simple stack implementation using a linked list found online.
 * Source: https://www.techiedelight.com/stack-implementation-using-linked-list/
 */

#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct Node* Node;
typedef struct Node** Stack;

extern void push(Stack top, void* x);
extern int isEmpty(Node top);
extern void* peek(Node top);
extern void pop(Stack top);

#endif /* STACK_H_ */
