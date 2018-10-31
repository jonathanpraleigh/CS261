/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
	pre: s is not null		
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: s is not null	
	post:	
*/
int isBalanced(char* s)
{	
	DynArr *stack;
	stack = newDynArr(2);

	int i = 0;

	while (nextChar(s) != '\0')
	{
		if (s[i] == '(' || s[i] == '{' || s[i] == '[')
		{
			pushDynArr(stack, s[i]);
		}

		if (s[i] == ')' || s[i] == '}' || s[i] == ']')
		{
			char flipped;
			
			if (s[i] == ')')
				flipped = '(';
			if (s[i] == '}')
				flipped = '{';
			if (s[i] == ']')
				flipped = '[';

			if (topDynArr(stack) != flipped)
			{
				deleteDynArr(stack);
				return 0;
			}
			popDynArr(stack);
		}

		i++;
	}
	
	if (sizeDynArr(stack) == 0)
	{
		deleteDynArr(stack);
		return 1;
	}
	
	deleteDynArr(stack);
	return 0;
	
}

int main(int argc, char* argv[]){
	
	char* s=argv[1];	
	int res;
	
	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	return 0;	
}

