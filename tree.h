/*
 * tree.h
 *
 *  Created on: 16-Oct-2019
 *      Author: usmana
 */

#ifndef TREE_H_
#define TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Tree* Tree;

// Declaration
struct Tree {
	char *label;
	Tree children[5];
	int size;
};

/**
 * Constructor for an empty n-ary tree.
 */
extern Tree newTree(char *label);

/**
 * Adds child to the children array of parent at the specified index.
 */
extern void addChild(Tree parent, Tree child, int index);

/**
 * Takes a tree and returns true if it has no children and false otherwise.
 */
extern bool isLeaf(Tree this);

/**
 * Print function: two functions, a top level pretty print function with no identation paramter
 * and an internal function with that parameter called from the toplevel function
 * with identation 0.
 *
 * print each node on a separate line and have the children of a node indented
 * relative to their parent.
 */
extern void print(Tree this);
extern void printTree(Tree this, int indent);

#endif /* TREE_H_ */
