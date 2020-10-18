/*
 * rdp.h
 *
 *  Created on: 05-Oct-2019
 *      Author: usmana
 */

#ifndef RDP_H_
#define RDP_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "tree.h"

/**
 * Checks if the given char matches the char nextToken is pointing to. Consumes input.
 */
extern bool matchTerminal(char c);

/**
 * Decides which production to choose by returning whether nextToken matches the given char. Does not
 * consume input.
 */
extern int lookahead(char c);

// Functions representing the productions of the grammar for regular expressions
/**
 * Function representing productions for E:
 * <E> -> <C> <ET>
 */
extern Tree E();

/**
 * Function representing productions for ET:
 * <ET> -> | <E>
 * <ET> -> empty
 */
extern Tree ET();

/**
 * Function representing productions for C:
 * <C> -> <S> <CT>
 */
extern Tree C();

/**
 * Function representing productions for CT:
 * <CT> -> . <C>
 * <CT> -> empty
 */
extern Tree CT();

/**
 * Function representing productions for S:
 * <S> -> <A> <ST>
 */
extern Tree S();

/**
 * Function representing productions for ST:
 * <ST> -> * <ST>
 * <ST> -> empty
 */
extern Tree ST();

/**
 * Function representing productions for A:
 * <A> -> ( <E> )
 * <A> -> <X>
 */
extern Tree A();

/**
 * Function representing productions for X:
 * <X> -> any lowercase letter
 */
extern Tree X();

/**
 * Parses the input and returns a tree if parsed correctly and NULL if not.
 */
extern Tree RDParser(char *input);


#endif /* RDP_H_ */
