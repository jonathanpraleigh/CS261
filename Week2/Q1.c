/* CS261- Assignment 1 - Q.1*/
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

struct student* allocate(){
     
	struct student* ptr;	

	/*Allocate memory for ten students*/
	ptr = (struct student*) malloc(10 * sizeof(struct student));
     	/*return the pointer*/
	return ptr;
}

void generate(struct student* students){
     /*Generate random and unique ID and scores for ten students, ID being between 1 and 10, scores between 0 and 100*/
     	int idAvailable[] = {1,2,3,4,5,6,7,8,9,10};
	
	for (int i = 0; i < 10; i++ )
     	{
		int possibleID = 0;
		
		while (possibleID == 0)
		{
			possibleID = rand() % 10 + 1;	
			possibleID = idAvailable[possibleID - 1];
		}
		
		idAvailable[possibleID - 1] = 0;

		(students + i)->id = possibleID; 
		(students + i)->score = rand() % 100 + 1;
   	}
		
}

void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
	for (int i = 0; i < 10; i++)
	{
		printf("%d %d\n", (students + i)->id, (students + i)->score);
	}
}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the ten students*/
	int minimum = 100, maximum = 0, average = 0;

	for (int i = 0; i < 10; i++)
	{
		if ((students + i)->score < minimum)
			minimum = (students + i)->score;
		
		if ((students + i)->score > maximum)
			maximum = (students + i)->score;

		average += (students + i)->score;
	}

	average = average / 10;

	printf("Minimum: %d Maximum: %d Average: %d\n", minimum, maximum, average);
}

void deallocate(struct student* stud){
     /*Deallocate memory from stud*/

	free(stud);
}


int main(){
    struct student* stud = NULL;
  
    /*call allocate*/
	stud = allocate();
    
	/*call generate*/
	generate(stud);

    /*call output*/
	output(stud);

    /*call summary*/
	summary(stud);
    
    /*call deallocate*/
	deallocate(stud);

    return 0;
}
