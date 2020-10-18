/*
 * rexp.c
 *
 *  Created on: 28-Sep-2019
 *      Author: usmana
 */

#include <stdlib.h>
#include <stdio.h>
#include "rdp.h"
#include "tdp.h"
#include "exptree.h"

int main(int argc, char* argv[]) {
	bool quit = false;

	while (quit != true) {
		printf("Please enter a regular expression (enter \"quit\" to exit): ");
		char input[128];
		scanf("%s", input);

		if (strncmp(input, "quit", 128) == 0) {
			break;
			quit = true;
		}

		printf("You entered: %s\n\n", input);

		printf("Recursive driven parsing activated...\n");
		Tree rdp = RDParser(input);
		if (rdp != NULL) {
			printf("Parsing complete!\n\n");

			// If parsing is successful these trees will be the same.
			printf("Parse tree for %s using recursive driven parsing:\n",
					input);
			print(rdp);

			printf("\n\n");
		} else {
			printf("\n");
		}

		printf("Table driven parsing activated...\n");
		Tree tdp = TDParser(input);
		if (tdp != NULL) {
			printf("Parsing complete!\n\n");
			printf("Parse tree for %s using table driven parsing:\n", input);
			print(tdp);

			printf("\n\n");
		} else {
			printf("\n");
		}

		printf("Building expression tree...\n");
		Tree exptree = ExpTree(rdp);
		if (exptree != NULL) {
			printf("Expression tree complete!\n\n");
			printf("Expression tree in prefix notation:\n");
			printExpression(exptree);

			printf("\n\n");
		} else {
			printf("\n");
		}

	}

}
