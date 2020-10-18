/*
 * exptree.h
 *
 *  Created on: 14-Oct-2019
 *      Author: usmana
 *
 * Builds an expression tree from a given parse tree.
 */

#ifndef EXPTREE_H_
#define EXPTREE_H_

#include "tree.h"
#include "rdp.h"
#include <ctype.h>


/**
 * Interprets parse tree as an expression tree by condensing the given parse tree by getting rid
 * of single successor and empty nodes and combining operands and operators.
 *
 * Operator precedence:
 * 	1. Closure
 * 	2. Concatenation
 * 	3. Union
 */
extern Tree buildExpressionTree(Tree parseTree);

/**
 * Takes a parse tree and returns an expression tree if well formed.
 */
extern Tree ExpTree(Tree parseTree);

/**
 * Traverses the tree with preorder traversal and prints tree in prefix notation.
 */
extern void printExpression(Tree this);


#endif /* EXPTREE_H_ */
