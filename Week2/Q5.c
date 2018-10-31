/* CS261- Assignment 1 - Q.5*/
/* Name: Jon Raleigh
 * Date: 7/9/17
 * Solution description: C string manipulation. Changing
 */
 
#include <stdio.h>
#include <stdlib.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch)
{
     return ch-'a'+'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch)
{
     return ch-'A'+'a';
}

void sticky(char* word)
{
     /*Convert to sticky caps*/
	for (int i = 0; word[i] != '\0'; i++)
	{
		if (i % 2 == 0)
		{
			if (word[i] >= 'a' && word[i] <= 'z')
			{
				word[i] = toUpperCase(word[i]);
			}
		}

		if (i % 2 == 1)
		{
			if (word[i] >= 'A' && word[i] <= 'Z')
			{
				word[i] = toLowerCase(word[i]);
			}
		}

	}
}

int main()
{
    /*Read word from the keyboard using scanf*/
	char word[20];
	scanf("%s", &word);
    
    /*Call sticky*/
	sticky(word);

    /*Print the new word*/
	printf("%s\n", word);
    
    return 0;
}
