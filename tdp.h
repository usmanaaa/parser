/*
 * tdp.h
 *
 *  Created on: 10-Oct-2019
 *      Author: usmana
 */

#ifndef TDP_H_
#define TDP_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"
#include "tree.h"

/**
 * Checks if the given char matches the char nextToken is pointing to.
 */
extern bool match(char c);

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
extern void fillTable();

/**
 * Takes a non terminal and terminal and returns an int from its entry in the parse table.
 */
extern int parseTable(char* category, char terminal);

/**
 * Driver function that interprets the table. Uses stack to push and pop the bodies of the grammar
 * as needed until input is completely consumed.
 */
extern Tree driver(char* input);

/**
 * Takes a string and returns its parse tree using table driven parsing.
 */
extern Tree TDParser(char* input);


#endif /* TDP_H_ */
