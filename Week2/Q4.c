/* CS261- Assignment 1 - Q.4*/
/* Name:
 * Date:
 * Solution description:
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>

struct student{
	int id;
	int score;
};

void sort(struct student* students, int n){
     /*Sort the n students based on their score*/ 
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n - 1; j++)
		{
			if ((students + j)->score > (students + j + 1)->score)
			{
				struct student temp = *(students + j);
				*(students + j) = *(students + j + 1);
				*(students + j + 1) = temp;
			}
		}
	}
}

int main(){
    /*Declare an integer n and assign it a value.*/
	int n;
	n = 20;

    /*Allocate memory for n students using malloc.*/
	struct student *ptr;
	ptr = (struct student*)malloc(n * sizeof(struct student));
    
    /*Generate random and unique IDs and random scores for the n students, using rand().*/
	int idAvailable[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};

	for (int i = 0; i < n; i++)
	{
		int possibleID = 0;

		while (possibleID == 0)
		{
			possibleID = rand() % 20 + 1;
			possibleID = idAvailable[possibleID - 1];
		}

		idAvailable[possibleID - 1] = 0;

		(ptr + i)->id = possibleID;
		(ptr + i)->score = rand() % 100 + 1;
	}

    /*Print the contents of the array of n students.*/
	for (int i = 0; i < n; i++)
	{
		printf("%d %d\n", (ptr + i)->id, (ptr + i)->score);
	}
	printf("\n");

    /*Pass this array along with n to the sort() function*/
	sort(ptr, n);
    
    /*Print the contents of the array of n students.*/
	for (int i = 0; i < n; i++)
	{
		printf("%d %d\n", (ptr + i)->id, (ptr + i)->score);
	}

    return 0;
}
