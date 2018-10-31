/*
 * CS 261 Data Structures
 * Assignment 6
 * Name: 
 * Date: 
 */

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

int hashFunction1(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += key[i];
    }
    return r;
}

int hashFunction2(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += (i + 1) * key[i];
    }
    return r;
}

/**
 * Creates a new hash table link with a copy of the key string.
 * @param key Key string to copy in the link.
 * @param value Value to set in the link.
 * @param next Pointer to set as the link's next.
 * @return Hash table link allocated on the heap.
 */
HashLink* hashLinkNew(const char* key, int value, HashLink* next)
{
    HashLink* link = malloc(sizeof(HashLink));
    link->key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(link->key, key);
    link->value = value;
    link->next = next;
    return link;
}

/**
 * Free the allocated memory for a hash table link created with hashLinkNew.
 * @param link
 */
static void hashLinkDelete(HashLink* link)
{
    free(link->key);
    free(link);
}

/**
 * Initializes a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param map
 * @param capacity The number of table buckets.
 */
void hashMapInit(HashMap* map, int capacity)
{
    map->capacity = capacity;
    map->size = 0;
    map->table = malloc(sizeof(HashLink*) * capacity);
    for (int i = 0; i < capacity; i++)
    {
        map->table[i] = NULL;
    }
}

/**
 * Removes all links in the map and frees all allocated memory. You can use
 * hashLinkDelete to free the links.
 * @param map
 */
void hashMapCleanUp(HashMap* map)
{
    // FIX-ME: implement  -- DONE -- 
	HashLink* upNext;
	HashLink* ptr;

	for (int i = 0; i < hashMapCapacity(map); i++)
	{
		ptr = map->table[i];
		while(ptr != NULL)
		{
			upNext = ptr->next;
			hashLinkDelete(ptr);
			ptr = upNext;
		}
	}
	free(map->table);
	map->size = 0;

	
}

/**
 * Creates a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param capacity The number of buckets.
 * @return The allocated map.
 */
HashMap* hashMapNew(int capacity)
{
    HashMap* map = malloc(sizeof(HashMap));
    hashMapInit(map, capacity);
    return map;
}

/**
 * Removes all links in the map and frees all allocated memory, including the
 * map itself.
 * @param map
 */
void hashMapDelete(HashMap* map)
{
    hashMapCleanUp(map);
    free(map);
}

/**
 * Returns a pointer to the value of the link with the given key. Returns NULL
 * if no link with that key is in the table.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return Link value or NULL if no matching link.
 */
int* hashMapGet(HashMap* map, const char* key)
{
    // FIX-ME: implement -- DONE --
	assert(key != NULL);
	assert(map != NULL);

	int index = HASH_FUNCTION(key)%hashMapCapacity(map);

	if (index < 0)
		index += map->capacity;

	HashLink * listIterator = map->table[index];

	if (listIterator != NULL)
	{
		while (listIterator != NULL)
		{
			if (*listIterator->key == *key)
			{
				int * returnValue = &listIterator->value;
				return returnValue;
			}

			listIterator = listIterator->next;
		}
		return NULL;
	}
	
	return NULL;

}

/**
 * Resizes the hash table to have a number of buckets equal to the given
 * capacity. After allocating the new table, all of the links need to be
 * rehashed into it because the capacity has changed.
 * 
 * Remember to free the old table and any old links if you use hashMapPut to
 * rehash them.
 * 
 * @param map
 * @param capacity The new number of buckets.
 */
void resizeTable(HashMap* map, int capacity)
{
    // FIX-ME: implement --DONE--
	HashMap * newHM = hashMapNew(capacity);
	HashLink * iterator;

	for(int i = 0; i < map->capacity; i++)
	{
		iterator = map->table[i];

		while (iterator != NULL)
		{
			hashMapPut(newHM, iterator->key, iterator->value);
			iterator = iterator->next;
		}
	}
	
	hashMapCleanUp(map);
	hashMapInit(map, capacity);

	for (int i = 0; i < newHM->capacity; i++)
	{
		iterator = newHM->table[i];

		while (iterator != NULL)
		{
			hashMapPut(map, iterator->key, iterator->value);
			iterator = iterator->next;
		}
	}

	hashMapDelete(newHM);
	
}

/**
 * Updates the given key-value pair in the hash table. If a link with the given
 * key already exists, this will just update the value. Otherwise, it will
 * create a new link with the given key and value and add it to the table
 * bucket's linked list. You can use hashLinkNew to create the link.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @param value
 */
void hashMapPut(HashMap* map, const char* key, int value)
{
    // FIX-ME: implement --DONE--
	assert(map != NULL);
	assert(key != NULL);

	if(hashMapContainsKey(map,key) == 1)
	{
		int * toReplace = hashMapGet(map, key);
		*toReplace += value;
		return;
	}

	int index = HASH_FUNCTION(key)%hashMapCapacity(map);

	if (index < 0)
		index += hashMapCapacity(map);

	HashLink * newLink = hashLinkNew(key, value, NULL);

	if (map->table[index] == NULL)
	{
		map->table[index] = newLink;
		map->size++;

		if (hashMapTableLoad(map) >= MAX_TABLE_LOAD)
		{
			int resize = 2 * hashMapCapacity(map);
			resizeTable(map, resize);
		}
		return;	
	}

	HashLink * iterator = map->table[index];

	while(iterator->next != NULL)
	{
		iterator = iterator->next;
	}

	iterator->next = newLink;
	map->size++;
}

/**
 * Removes and frees the link with the given key from the table. If no such link
 * exists, this does nothing. Remember to search the entire linked list at the
 * bucket. You can use hashLinkDelete to free the link.
 * @param map
 * @param key
 */
void hashMapRemove(HashMap* map, const char* key)
{
    // FIX-ME: implement --DONE--
	int index = HASH_FUNCTION(key)%hashMapCapacity(map);

	if (index < 0)
		index += map->capacity;

	HashLink * iterator = map->table[index];
	

	if(strcmp(iterator->key, key) == 0) //if it's the first value of the linked list
	{
		HashLink * upNext = iterator->next;
		hashLinkDelete(iterator);
		map->table[index] = upNext;
		map->size--;
		return;
	}

	HashLink * previous = iterator;
	iterator = iterator->next;
	HashLink * next = iterator->next;

	while(iterator != NULL)
	{
		if(strcmp(iterator->key, key) == 0)
		{
			hashLinkDelete(iterator);
			map->size--;
			previous->next = next;
			return;
		}
		previous = iterator;
		iterator = iterator->next;
		next = iterator->next;
	}
}

/**
 * Returns 1 if a link with the given key is in the table and 0 otherwise.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return 1 if the key is found, 0 otherwise.
 */
int hashMapContainsKey(HashMap* map, const char* key)
{
    // FIX-ME: implement --DONE--

	assert(map != NULL);
	assert(key != NULL);

	int index = HASH_FUNCTION(key)%hashMapCapacity(map);

	if (index < 0)
		index += hashMapCapacity(map);

	HashLink * iterator = map->table[index];


	while(iterator != NULL && iterator->key != NULL)
	{
		if (strcmp(iterator->key, key) == 0)
			return 1;

		//if (iterator->key == key)
		//	return 1;
		
		iterator = iterator->next;
	}

	return 0;
}

/**
 * Returns the number of links in the table.
 * @param map
 * @return Number of links in the table.
 */
int hashMapSize(HashMap* map)
{
	return map->size;
}

/**
 * Returns the number of buckets in the table.
 * @param map
 * @return Number of buckets in the table.
 */
int hashMapCapacity(HashMap* map)
{
	return map->capacity;
}

/**
 * Returns the number of table buckets without any links.
 * @param map
 * @return Number of empty buckets.
 */
int hashMapEmptyBuckets(HashMap* map)
{
	int emptyBuckets = 0;
	
	for(int i = 0; i<hashMapCapacity(map); i++)
	{
		if (map->table[i] == NULL)
			emptyBuckets++;
	}
	return emptyBuckets;
}

/**
 * Returns the ratio of (number of links) / (number of buckets) in the table.
 * Remember that the buckets are linked lists, so this ratio tells you nothing
 * about the number of empty buckets. Remember also that the load is a floating
 * point number, so don't do integer division.
 * @param map
 * @return Table load.
 */
float hashMapTableLoad(HashMap* map)
{
	// FIX-ME: implement --DONE--
	float load = (float)hashMapSize(map) / (float)hashMapCapacity(map);
	return load;
}

/**
 * Prints all the links in each of the buckets in the table.
 * @param map
 */
void hashMapPrint(HashMap* map)
{
    for (int i = 0; i < map->capacity; i++)
    {
        HashLink* link = map->table[i];
        if (link != NULL)
        {
            printf("\nBucket %i ->", i);
            while (link != NULL)
            {
                printf(" (%s, %d) ->", link->key, link->value);
                link = link->next;
            }
        }
    }
    printf("\n");
}