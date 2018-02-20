/*Code for the Assignment 1
 * Submitted by : Karan Kotabagi
 * University ID : 2000217137
 * /

/*------------------------------------------------------------------------
 * xsh_hello - Print the output as specified Hello<string>, Welcome to the world of Xinu
 *------------------------------------------------------------------------
 */
#include <xinu.h>
#include <string.h>
#include <stdio.h>

shellcmd xsh_hello(int nargs, char *args[]) {

if (nargs < 2)
{
fprintf(stderr, "%s: too few arguments\n",args[0]);
return 1;
}

/* Check argument count and throw the message if there are more than 2 arguments*/

	if (nargs > 2) {
		fprintf(stderr, "%s: too many arguments\n", args[0]);
		return 1;
	}
//print the output if there are correct arguments 
	if (nargs == 2) {
	printf("Hello %s, Welcome to the world of Xinu!!",args[1]);
	}
}

