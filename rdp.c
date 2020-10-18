/*
 * rdp.c
 *
 * Created on: 28-Sep-2019
 * Author: usmana
 */

#include "rdp.h"

// Global variable that tokenizes input.
char *nextToken;

/**
 * Checks if the given char matches the char nextToken is pointing to. Consumes input.
 */
bool matchTerminal(char c) {
	if (*nextToken == c) {
		nextToken++;
		return true;
	} else {
		return false;
	}
}

/**
 * Decides which production to choose by returning whether nextToken matches the given char. Does not
 * consume input.
 */
int lookahead(char c) {
	return *nextToken == c;
}

/**
 * Function representing productions for E:
 * <E> -> <C> <ET>
 */
Tree E() {

	Tree CTree = C();
	if (CTree == NULL) {
		return NULL;
	}

	Tree ETTree = ET();
	if (ETTree == NULL) {
		return NULL;
	}

	// return tree with E as root and subtree C and subtree E() as children
	Tree ETree = newTree("E");
	addChild(ETree, CTree, 0);
	addChild(ETree, ETTree, 1);
	return ETree;

}

/**
 * Function representing productions for ET:
 * <ET> -> | <E>
 * <ET> -> empty
 */
Tree ET() {

	if (lookahead('|')) {

		if (!matchTerminal('|')) {
			return NULL;
		}
		Tree u = newTree("|");

		Tree ETree = E();
		if (ETree == NULL) {
			return false;
		}

		Tree ETTree = newTree("ET");
		addChild(ETTree, u, 0);
		addChild(ETTree, ETree, 1);
		// return tree with ET as root and | and subtree E() as children
		return ETTree;
	}

	else {
		// return tree with ET as root and empty string as a child.
		Tree ETTree = newTree("ET");
		addChild(ETTree, newTree("empty"), 0);
		return ETTree;
	}
}

/**
 * Function representing productions for C:
 * <C> -> <S> <CT>
 */
Tree C() {

	Tree STree = S();
	if (STree == NULL) {
		return NULL;
	}

	Tree CTTree = CT();
	if (CTTree == NULL) {
		return NULL;
	}

	Tree CTree = newTree("C");
	addChild(CTree, STree, 0);
	addChild(CTree, CTTree, 1);
	return CTree;
}

/**
 * Function representing productions for CT:
 * <CT> -> . <C>
 * <CT> -> empty
 */
Tree CT() {

	if (lookahead('.')) {
		if (!matchTerminal('.')) {
			return NULL;
		}
		Tree concat = newTree(".");

		Tree CTree = C();
		if (CTree == NULL) {
			return NULL;
		}

		Tree CTTree = newTree("CT");
		addChild(CTTree, concat, 0);
		addChild(CTTree, CTree, 1);
		return CTTree;

	}

	else {
		// return tree with CT as root and empty string as a child.
		Tree CTTree = newTree("CT");
		addChild(CTTree, newTree("empty"), 0);
		return CTTree;
	}
}

/**
 * Function representing productions for S:
 * <S> -> <A> <ST>
 */
Tree S() {

	Tree ATree = A();
	if (ATree == NULL) {
		return NULL;
	}

	Tree STTree = ST();
	if (STTree == NULL) {
		return NULL;
	}

	// return tree with S as root and subtree A and ST as children.
	Tree STree = newTree("S");
	addChild(STree, ATree, 0);
	addChild(STree, STTree, 1);
	return STree;

}

/**
 * Function representing productions for ST:
 * <ST> -> * <ST>
 * <ST> -> empty
 */
Tree ST() {

	if (lookahead('*')) {
		if (!matchTerminal('*')) {
			return NULL;
		}
		Tree closure = newTree("*");

		Tree STree = ST();
		if (STree == NULL) {
			return NULL;
		}

		// return tree with ST as root and * and subtree ST as child
		Tree STFinal = newTree("ST");
		addChild(STFinal, closure, 0);
		addChild(STFinal, STree, 1);
		return STFinal;

	}

	else {
		// return tree with ST as root and empty string as child.
		Tree STree = newTree("ST");
		addChild(STree, newTree("empty"), 0);
		return STree;
	}

}

/**
 * Function representing productions for A:
 * <A> -> ( <E> )
 * <A> -> <X>
 */
Tree A() {

	if (lookahead('(')) {
		if (!matchTerminal('(')) {
			return NULL;
		}
		Tree oparen = newTree("(");

		Tree ETree = E();
		if (ETree == NULL) {
			return NULL;
		}

		if (!matchTerminal(')')) {
			return NULL;
		}
		Tree cparen = newTree(")");

		// return tree with A as a root and ( and subtree E and ) as children
		Tree ATree = newTree("A");
		addChild(ATree, oparen, 0);
		addChild(ATree, ETree, 1);
		addChild(ATree, cparen, 2);
		return ATree;

	} else {
		Tree XTree = X();
		if (XTree == NULL) {
			return NULL;
		}
		// return tree with A as root and subtree X as child.
		Tree ATree = newTree("A");
		addChild(ATree, XTree, 0);
		return ATree;
	}
}

/**
 * Function representing productions for X:
 * <X> -> any lowercase letter
 */
Tree X() {

	if (islower(*nextToken)) {
		char *tokenLetter = (char*) malloc(sizeof(char));
		*tokenLetter = *nextToken;
		Tree letter = newTree(tokenLetter);
		matchTerminal(*nextToken);

		// return tree with X() as root with letter as child.
		Tree XTree = newTree("X");
		addChild(XTree, letter, 0);
		return XTree;
	} else {
		return NULL;

	}

}

/**
 * Parses the input and returns a tree if parsed correctly and NULL if not.
 */
Tree RDParser(char *input) {
	nextToken = input;

	Tree parsed = E();

	// A parsed input should be completely consumed i.e. length is 0.
	if (strnlen(nextToken, 255) != 0) {
		printf("Input not valid.\n");
		return NULL;
	} else {
		return parsed;
	}

}


//
//
//int main(int arc, char* argv[]) {
//
//	Tree tree = RDParser("a|b.c*");
//	print(tree);
////	printTreePostorder(tree);
//
//}
