/*
 * exptree.c
 *
 *  Created on: 13-Oct-2019
 *      Author: usmana
 */

#include "exptree.h"

/**
 * Interprets parse tree as an expression tree by condensing the given parse tree by getting rid
 * of single successor and empty nodes and combining operands and operators.
 *
 * Operator precedence:
 * 	1. Closure
 * 	2. Concatenation
 * 	3. Union
 */
Tree buildExpressionTree(Tree parseTree) {
	char *category = parseTree->label;

	if (strncmp(category, "E", 128) == 0) {
		Tree CTree = buildExpressionTree(parseTree->children[0]);
		Tree ETTree = buildExpressionTree(parseTree->children[1]);
		if (ETTree == NULL) {
			return CTree;
		} else {
			Tree u = newTree("UNION");
			addChild(u, CTree, 0);
			addChild(u, ETTree, 1);
			return u;
		}

	}

	else if (strncmp(category, "C", 128) == 0) {
		Tree STree = buildExpressionTree(parseTree->children[0]);
		Tree CTTree = buildExpressionTree(parseTree->children[1]);
		if (CTTree == NULL) {
			return STree;
		} else {

			Tree concat = newTree("CONCAT");
			addChild(concat, STree, 0);
			addChild(concat, CTTree, 1);
			return concat;
		}

	}
//
	else if (strncmp(category, "S", 128) == 0) {
		Tree ATree = buildExpressionTree(parseTree->children[0]);
		Tree STTree = buildExpressionTree(parseTree->children[1]);
		if (STTree == NULL) {
			return ATree;
		} else {
			addChild(STTree, ATree, 0);
			return STTree;
		}
	}

	else if (strncmp(category, "A", 128) == 0) {
		if (*(parseTree->children[0]->label) == '(') {
			Tree ETree = buildExpressionTree(parseTree->children[1]);
			return ETree;
		} else {
			Tree atomic = newTree("ATOMIC");
			Tree XTree = buildExpressionTree(parseTree->children[0]);
			addChild(atomic, XTree, 0);
			return atomic;
		}
	}

	else if (strncmp(category, "X", 128) == 0) {
		return newTree(parseTree->children[0]->label);
	}

	else if (strncmp(category, "ST", 128) == 0) {
		if (strncmp(parseTree->children[0]->label, "empty", 128) == 0) {
			return NULL;
		} else {
			Tree closure = newTree("CLOSURE");
			Tree STTree = buildExpressionTree(parseTree->children[1]);
			addChild(closure, STTree, 0);
			return closure;
		}
	}

	else if (strncmp(category, "CT", 128) == 0) {
		if (strncmp(parseTree->children[0]->label, "empty", 128) == 0) {
			return NULL;
		} else {
			Tree CTree = buildExpressionTree(parseTree->children[1]);
			return CTree;
		}
	}

	else if (strncmp(category, "ET", 128) == 0) {
		if (strncmp(parseTree->children[0]->label, "empty", 128) == 0) {
			return NULL;
		} else {
			Tree ETree = buildExpressionTree(parseTree->children[1]);
			return ETree;
		}
	} else {
		printf("No tree found.\n");
		return NULL;
	}

}

/**
 * Takes a parse tree and returns an expression tree if well formed.
 */
Tree ExpTree(Tree parseTree){

	if(parseTree!=NULL){
		return buildExpressionTree(parseTree);
	} else{
		printf("Input not valid.\n");
		return NULL;
	}
}

/**
 * Traverses the tree with preorder traversal and prints tree in prefix notation.
 */
void printExpression(Tree this) {
	if (this != NULL) {
		if (islower(*(this->label))) {
			printf("%s ", this->label);
		} else {
			printf("(%s ", this->label);
		}
		printExpression(this->children[0]);
		printExpression(this->children[1]);
		if (!islower(*(this->label))) {
			printf(")");
		}

	}

}

//int main(int argc, char* argv[]) {
//
//	Tree test = TDParser("a|b.c*");
//	Tree expressionTree = buildExpressionTree(test);
//	printExpression(expressionTree);
//	printf("\n");
//
//}
