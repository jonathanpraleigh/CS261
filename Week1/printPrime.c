/*********************************************************************
** Program Filename: printPrime.c
** Author: Jon Raleigh
** Date: 7/2/17
** Description: Prints prime numbers until the user prompts the program to stop.
** Input: the character "q"
** Output: Prime numbers
*********************************************************************/
#include<stdio.h>

int main()
{
	int dividend, divisor, fail;
	char escape = 'a';

	printf("(q to quit) Primes: ");

	dividend = 1;

	while (escape != 'q')
	{
		dividend++;
		fail = 0;

		for (divisor = 2; divisor <= dividend / 2; divisor++)
		{
			if (dividend % divisor == 0)
			{
				fail = 1;
				break;
			}
		}

		if (fail == 0)
		{
			printf("%d ", dividend);
			escape = getchar();
		}
	}

	return 0;
}