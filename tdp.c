/*
 * tdp.c
 *
 *  Created on: 10-Oct-2019
 *      Author: usmana
 */

#include "tdp.h"

char *nextToken;
char buffer[128];

char postFix[128];

int Table[8][6];

/**
 * Checks if the given char matches the char nextToken is pointing to.
 */
bool match(char c) {
	if (*nextToken == c) {
		nextToken++;
		return true;
	} else {
		return false;
	}
}

/**
 * Creates the grammar's corresponding parse table. Uses int double array
 *
 *
 *	    0	1	2	3	4	5
 * 	    |	.	*	(	)	letter
 *
 * 0 E: 			1		1
 * 1 ET:2	3	3	3	3	3
 * 2 C:				4		4
 * 3 CT:6	5	6	6	6	6
 * 4 S: 			7		7
 * 5 ST:9	9	8	9	9	9
 * 6 A:				10		11
 * 7 X:						12
 */
void fillTable() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 6; j++) {
			Table[i][j] = -1;
		}
	}
	Table[0][3] = 1;
	Table[0][5] = 1;

	Table[1][0] = 2;
	Table[1][1] = 3;
	Table[1][2] = 3;
	Table[1][3] = 3;
	Table[1][4] = 3;
	Table[1][5] = 3;

	Table[2][3] = 4;
	Table[2][5] = 4;

	Table[3][0] = 6;
	Table[3][1] = 5;
	Table[3][2] = 6;
	Table[3][3] = 6;
	Table[3][4] = 6;
	Table[3][5] = 6;

	Table[4][3] = 7;
	Table[4][5] = 7;

	Table[5][0] = 9;
	Table[5][1] = 9;
	Table[5][2] = 8;
	Table[5][3] = 9;
	Table[5][4] = 9;
	Table[5][5] = 9;

	Table[6][3] = 10;
	Table[6][5] = 11;

	Table[7][5] = 12;

}

/**
 * Takes a non terminal and terminal and returns an int from its entry in the parse table.
 */
int parseTable(char* category, char terminal) {

	if (strncmp(category, "E", 255) == 0) {
		if (terminal == '(') {
			return Table[0][3];
		} else if (islower(terminal)) {
			return Table[0][5];
		} else {
			return -1;
		}
	} else if (strncmp(category, "ET", 255) == 0) {
		if (terminal == '|') {
			return Table[1][0];
		} else {
			return 3;
		}
	} else if (strncmp(category, "C", 255) == 0) {
		if (terminal == '(') {
			return Table[2][3];
		} else if (islower(terminal)) {
			return Table[2][5];
		} else {
			return -1;
		}
	} else if (strncmp(category, "CT", 255) == 0) {
		if (terminal == '.') {
			return Table[3][1];
		} else {
			return 6;
		}
	} else if (strncmp(category, "S", 255) == 0) {
		if (terminal == '(') {
			return Table[4][3];
		} else if (islower(terminal)) {
			return Table[4][5];
		} else {
			return -1;
		}
	} else if (strncmp(category, "ST", 255) == 0) {
		if (terminal == '*') {
			return Table[5][2];
		} else {
			return 9;
		}
	} else if (strncmp(category, "A", 255) == 0) {
		if (terminal == '(') {
			return Table[6][3];
		} else if (islower(terminal)) {
			return Table[6][5];
		} else {
			return -1;
		}
	} else if (strncmp(category, "X", 255) == 0) {
		if (islower(terminal)) {
			return Table[7][5];
		} else {
			return -1;
		}
	} else {
		printf("Syntactic Category not found.\n");
		return -1;
	}
}

/**
 * Driver function that interprets the table. Uses stack to push and pop the bodies of the grammar
 * as needed until input is completely consumed.
 */
Tree driver(char* input) {
	nextToken = input;
	Node stack = NULL;
	Tree start = newTree("E");

	push(&stack, start);

	while (!isEmpty(stack)) {
		Tree top = peek(stack);

		if (isupper(*(top->label))) { // If the label of the tree is uppercase it must be a non terminal
			int action = parseTable(top->label, *nextToken); // Entry in parse table.
			if (action == 1) {
				Tree CTree = newTree("C");
				Tree ETTree = newTree("ET");
				addChild(top, CTree, 0);
				addChild(top, ETTree, 1);
				pop(&stack);
				push(&stack, ETTree);
				push(&stack, CTree);
			}

			else if (action == 2) {
				Tree u = newTree("|");
				Tree ETree = newTree("E");
				addChild(top, u, 0);
				addChild(top, ETree, 1);
				pop(&stack);
				push(&stack, ETree);
				push(&stack, u);
			}

			else if (action == 4) {
				Tree STree = newTree("S");
				Tree CTTree = newTree("CT");
				addChild(top, STree, 0);
				addChild(top, CTTree, 1);
				pop(&stack);
				push(&stack, CTTree);
				push(&stack, STree);
			}

			else if (action == 5) {
				Tree concat = newTree(".");
				Tree CTree = newTree("C");
				addChild(top, concat, 0);
				addChild(top, CTree, 1);
				pop(&stack);
				push(&stack, CTree);
				push(&stack, concat);
			}

			else if (action == 7) {
				Tree ATree = newTree("A");
				Tree STTree = newTree("ST");
				addChild(top, ATree, 0);
				addChild(top, STTree, 1);
				pop(&stack);
				push(&stack, STTree);
				push(&stack, ATree);
			}

			else if (action == 8) {
				Tree closure = newTree("*");
				Tree STTree = newTree("ST");
				addChild(top, closure, 0);
				addChild(top, STTree, 1);
				pop(&stack);
				push(&stack, STTree);
				push(&stack, closure);
			}

			else if (action == 10) {
				Tree oparen = newTree("(");
				Tree ETree = newTree("E");
				Tree cparen = newTree(")");
				addChild(top, oparen, 0);
				addChild(top, ETree, 1);
				addChild(top, cparen, 2);
				pop(&stack);
				push(&stack, cparen);
				push(&stack, ETree);
				push(&stack, oparen);
			}

			else if (action == 11) {
				Tree XTree = newTree("X");
				addChild(top, XTree, 0);
				pop(&stack);
				push(&stack, XTree);
			}

			else if (action == 12) {
				char *tokenLetter = (char*) malloc(sizeof(char));
				*tokenLetter = *nextToken;
				Tree letter = newTree(tokenLetter);
				addChild(top, letter, 0);
				pop(&stack);
				push(&stack, letter);
			}

			else if ((action == 3) | (action == 6) | (action == 9)) {
				addChild(top, newTree("empty"), 0);
				pop(&stack);
			}

			else {
				printf("Input not valid.\n");
				break;
			}

		}

		else if (*top->label == *nextToken) {
			match(*nextToken);
			pop(&stack);
		}

		else {
			printf("Input not valid.\n");
			break;
		}

	}

	return start;

}

/**
 * Takes a string and returns its parse tree using table driven parsing.
 */
Tree TDParser(char* input) {
	fillTable();
	Tree parsed = driver(input);

	// A parsed input should be completely consumed i.e. length is 0.
	if (strnlen(nextToken, 255) != 0) {
		printf("Input not valid.\n");
		return NULL;
	} else {
		return parsed;
	}
}

//
//int main(int argc, char* argv[]) {
//	Tree test = TDParser("a*.b");
////	if(test==NULL){
////		printf("This works");
////	}
//	print(test);
//
//}
