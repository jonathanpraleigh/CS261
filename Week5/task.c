/*
 * CS 261 Assignment 5
 * Name: 
 * Date: 
 */

#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

/**
 * Creates a new task with the given priority and name.
 * @param priority
 * @param name
 * @return  The new task.
 */
Task* taskNew(int priority, char* name)
{
    // FIXME: implement -- DONE --
	Task * initTask = (struct Task *)malloc(sizeof(struct Task));
	
	strcpy(initTask->name, name);
	initTask->priority = priority;

    return initTask;
}

/**
 * Frees a dynamically allocated task.
 * @param task
 */
void taskDelete(Task* task)
{
    free(task);
}

/**
 * Casts left and right to Task pointers and returns
 * -1 if left's priority < right's priority,
 *  1 if left's priority > right's priority,
 *  0 if left's priority == right's priority.
 * @param left  Task pointer.
 * @param right  Task pointer.
 * @return 
 */
int taskCompare(void* left, void* right)
{
    // FIXME: implement -- DONE --

	assert(left != NULL);
	assert(right != NULL);

	struct Task * lTask = left;
	struct Task * rTask = right;

	if (lTask->priority < rTask->priority)
	{
		return -1;
	}
	
	if(lTask->priority > rTask->priority)
	{
		return 1;
	}

	return 0;

}

/**
 * Prints a task as a (priority, name) pair.
 * @param value  Task pointer.
 */
void taskPrint(void* value)
{
    Task* task = (Task*)value;
    printf("(%d, %s)", task->priority, task->name);
}
