/* CS261- Assignment 1 - Q. 0*/
/* Name:
 * Date:
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>

void fooA(int* iptr){
     /*Print the value pointed to by iptr*/
	printf("%d\n", *iptr);

     /*Print the address pointed to by iptr*/
	printf("%d\n", &*iptr);

     /*Print the address of iptr itself*/
	printf("%d\n", &iptr);
}

int main(){
    
    /*declare an integer x*/
	int numberToPass = 9090909;
    
    /*print the address of x*/
	printf("\n%d\n", &numberToPass);

    /*Call fooA() with the address of x*/
	fooA(&numberToPass);

    /*print the value of x*/
	printf("%d\n", numberToPass);

    return 0;
}
