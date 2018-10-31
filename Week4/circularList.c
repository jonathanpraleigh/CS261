#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList * list)
{
	list->size = 0;

	list->sentinel = (struct Link *)malloc(sizeof(struct Link));

	list->sentinel->next = list->sentinel;

	list->sentinel->prev = list->sentinel;
}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
	struct Link * ptr = (struct Link *)malloc(sizeof(struct Link));
	
	ptr->next = NULL;
	
	ptr->prev = NULL;
	
	ptr->value = value;
	
	return ptr;
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	struct Link * ptr = createLink(value);

	link->next->prev = ptr;
	
	ptr->prev = link;
	
	ptr->next = link->next;
	
	link->next = ptr;
	
	list->size += 1;

}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
	assert(link != list->sentinel);

	assert(list->size != 0);

	//printf("%d", list->size);

	struct Link * nextPtr = link->next;

	struct Link * prevPtr = link->prev;

	nextPtr->prev = link->prev; //problem here?
	
	prevPtr->next = link->next; //trying this out

	free(link);

	list->size -= 1;
}

/**
 * Allocates and initializes a list.
 */
struct CircularList* circularListCreate()
{
	struct CircularList* list = malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list)
{
	while (list->size > 0)
	{
		circularListRemoveFront(list);
	}

	free(list->sentinel);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{
	addLinkAfter(list, list->sentinel, value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
	addLinkAfter(list, list->sentinel->prev, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
	assert(list->sentinel->next != list->sentinel);

	return(list->sentinel->next->value);
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
	assert(list->sentinel->next != list->sentinel);

	return (list->sentinel->prev->value);
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
	assert(list->sentinel->next != list->sentinel && list->sentinel->prev != list->sentinel);

	removeLink(list, list->sentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
	assert(list->sentinel->next != list->sentinel);

	removeLink(list, list->sentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
	return(list->size == 0);
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
	assert(list->sentinel->next != list->sentinel);

	struct Link * ptr = list->sentinel->next;

	while(ptr != list->sentinel)
	{	
		TYPE display = ptr->value;

		printf("%f\n", display);

		ptr = ptr->next;
	}
}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
	struct Link * frontIndex = list->sentinel->next;
	
	struct Link * backIndex = list->sentinel;

	while(frontIndex != backIndex)
	{
		struct Link * ptr = frontIndex->next;
		frontIndex->next = frontIndex->prev;
		frontIndex->prev = ptr;
		frontIndex = ptr;
	}

	frontIndex = list->sentinel->next;

	list->sentinel->next = list->sentinel->prev;
	
	list->sentinel->prev = frontIndex;

}
