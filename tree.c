/*
 * tree.c
 *
 *  Created on: 16-Oct-2019
 *      Author: usmana
 */

#include "tree.h"

/**
 * Constructor for an empty n-ary tree.
 */
Tree newTree(char *label) {
	Tree this = (Tree) malloc(sizeof(struct Tree));
	for (int i = 0; i < 5; i++) {
		this->children[i] = NULL;
	}

	this->label = label;

	return this;
}

/**
 * Adds child to the children array of parent at the specified index.
 */
void addChild(Tree parent, Tree child, int index) {
	parent->children[index] = child;
}

/**
 * Takes a tree and returns true if it has no children and false otherwise.
 */
bool isLeaf(Tree this) {
	bool isleaf = true;
	for (int i = 0; i < 5; i++) {
		if (this->children[i] != NULL) {
			isleaf = false;
		}
	}
	return isleaf;
}


/**
 * Print function: two functions, a top level pretty print function with no identation paramter
 * and an internal function with that parameter called from the toplevel function
 * with identation 0.
 *
 * print each node on a separate line and have the children of a node indented
 * relative to their parent.
 */
void print(Tree this) {
	printTree(this, 0);
}
void printTree(Tree this, int indent) {
	if (this != NULL) {
		for (int i = 0; i < indent; i++) {
			printf(" ");
		}
		printf("%s\n", this->label);
		printTree(this->children[0], indent + 2);
		printTree(this->children[1], indent + 2);
		printTree(this->children[2], indent + 2);

	}

}
