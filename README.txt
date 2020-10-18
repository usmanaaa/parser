Authors: Usman Amin

This bundle includes the following:

- rexp.c: Executable to run the project.

- rdp.[ch]: Implementation for recursive descent parser.

- tdp.[ch]: Implementation for table driven parser.

- exptree.[ch]: Code for converting a parse tree to an expression tree.

- tree.[ch]: Implementation for an n-ary tree.
  
- stack.[ch]: Implementation of a simple' unbounded stack that can store any type of object (Source: https://www.techiedelight.com/stack-implementation-using-linked-list/).

This project implements a recursive-descent parser and a table-driven parser for the context-free grammar of regular expressions, and builds an expression tree from the parse tree.

****HOW TO RUN****

1. Unzip CSC173project.zip

2. Using the command line interface change directories to the unzipped folder.

3. Compile the executable rexp.c by entering:

	clang -o rexp rdp.c tdp.c exptree.c tree.c stack.c rexp.c

4. Run by entering:
	./rexp