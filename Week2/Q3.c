/* CS261- Assignment 1 - Q.3*/
/* Name:
 * Date:
 * Solution description:
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>


void sort(int* number, int n){
     /*Sort the given array number , of length n*/     
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n-1; j++)
		{
			if (*(number + j) > *(number + j + 1))
			{
				int temp = *(number + j);
				*(number + j) = *(number + j + 1);
				*(number + j + 1) = temp;
			}
		}
	}
}

int main(){
    /*Declare an integer n and assign it a value of 20.*/
	int n = 20;
    
    /*Allocate memory for an array of n integers using malloc.*/
	int *ptr;

	ptr = (int*)malloc(n * sizeof(int));

    /*Fill this array with random numbers, using rand().*/
    for (int i = 0; i < n; i++)
    {
		*(ptr + i) = rand() % 100 + 1;
    }

    /*Print the contents of the array.*/
	for (int i = 0; i < n; i++)
	{
		printf("%d\n", *(ptr + i));
	}
	printf("\n");

    /*Pass this array along with n to the sort() function of part a.*/
	sort(ptr, n);
	
    /*Print the contents of the array.*/    
	for (int i = 0; i < n; i++)
	{
		printf("%d\n", *(ptr + i));
	}

    return 0;
}
