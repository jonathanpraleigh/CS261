/*
 * CS 261 Assignment 5
 * Name: 
 * Date: 
 */

#include "dynamicArray.h"
#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Loads into heap a list from a file with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listLoad(DynamicArray* heap, FILE* file)
{
	const int FORMAT_LENGTH = 256;
    char format[FORMAT_LENGTH];
    snprintf(format, FORMAT_LENGTH, "%%d, %%%d[^\n]", TASK_NAME_SIZE);
    
    Task temp;
    while (fscanf(file, format, &temp.priority, &temp.name) == 2)
    {
        dyHeapAdd(heap, taskNew(temp.priority, temp.name), taskCompare);
    }
}

/**
 * Writes to a file all tasks in heap with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listSave(DynamicArray* heap, FILE* file)
{
    for (int i = 0; i < dySize(heap); i++)
    {
        Task* task = dyGet(heap, i);
        fprintf(file, "%d, %s\n", task->priority, task->name);
    }
}

/**
 * Prints every task in heap.
 * @param heap
 */
void listPrint(DynamicArray* heap)
{
    DynamicArray* temp = dyNew(1);
    dyCopy(heap, temp);
     while (dySize(temp) > 0)
    {
        Task* task = dyHeapGetMin(temp);
        printf("\n");
        taskPrint(task);
        printf("\n");
        dyHeapRemoveMin(temp, taskCompare);
    }
    dyDelete(temp);
}

/**
 * Handles the given command.
 * @param list
 * @param command
 */
void handleCommand(DynamicArray* list, char command)
{
    // FIXME: Implement
	
	char *taskDescription = malloc(sizeof(char) * 256);
	char *fileName = malloc(sizeof(char) * 256);
	int *taskPriority;
	FILE *inputFile;
	FILE *outputFile;

	
	switch(command)
	{
		case'l':
			printf("FILENAME: ");
			fgets(fileName, 50, stdin);

			char *pos;
			if ((pos = strchr(fileName, '\n')) != NULL)
				*pos = '\0';
		
			inputFile = fopen(fileName, "r");
			if (inputFile == 0)
			{
				printf("Cannot open %s\n", fileName);
					return;
			}
			printf("BEFORE LISTLOAD\n"); //REMOVE AFTER TESTING...
			listLoad(list, inputFile);
			printf("AFTER LIST LOAD\n"); //REMOVE AFTER TESTING...
			printf("Loaded...\n");
			fclose(inputFile);
			break;

		case's':
			printf("\nOUTPUT FILENAME: ");
			fgets("%s", 256, fileName);

			listSave(list, outputFile);
			fclose(outputFile);
			break;

		case'a':
			printf("\nPlease enter the task: ");
			fgets(taskDescription, 256, stdin);
			printf("\nPlease enter the priority: ");
			scanf("%d", taskPriority);
			
			Task *newTask = taskNew(taskPriority, taskDescription);
			dyHeapAdd(list, newTask, taskCompare);
			break;

		case'g':
			if (!dyStackIsEmpty(list))
			{
				printf("Task #1: %s\n", ((struct Task *)dyHeapGetMin(list))->name);
			}
			else
				printf("Your list has no tasks. Add some.\n");
			break;

		case'r':
			if (!dyStackIsEmpty(list))
			{
				dyHeapRemoveMin(list, taskCompare);
			}
			else
				printf("The list is already empty.\n");
			break;

		case'p':
			taskPrint(list);
			break;

		case'e':
			break;

		default:
			printf("Not an option.\n");
			break;
	}


}

int main()
{
    // Implement
    printf("\n\n** TO-DO LIST APPLICATION **\n\n");
    DynamicArray* list = dyNew(8);
    char command = ' ';
    do
    {
        printf("Press:\n"
               "'l' to load to-do list from a file\n"
               "'s' to save to-do list to a file\n"
               "'a' to add a new task\n"
               "'g' to get the first task\n"
               "'r' to remove the first task\n"
               "'p' to print the list\n"
               "'e' to exit the program\n"
        );
        command = getchar();
        // Eat newlines
        while (getchar() != '\n');
        handleCommand(list, command);
    }
    while (command != 'e');
 /* free dynamically allocated List pointers in array to avoid memory leaks */
         /* Fix it */

    dyDelete(list);
    return 0;
}