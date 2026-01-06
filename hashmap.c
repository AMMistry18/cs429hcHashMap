#include "hashmap.h"
#include <stddef.h>
#include <stdlib.h>

unsigned int intToIntHashFunction(int key){
	uint8_t *bytes = (uint8_t *) &key;
	uint32_t hash = 2166136261u;

	for (int i = 0; i < sizeof(int); i++) {
		hash ^= bytes[i];
		hash *= 16777619;
	}
	return hash;
}

void rehash(struct IntToIntHashMap* hmap, int key, int value)
{
	int hash = intToIntHashFunction(key)%hmap->length;
	struct linkedNode *temp = &hmap->hashTable[hash];
	if (temp -> taken == 0)
	{
		temp->val = value;
		temp->key = key;
		temp->taken = 1;
		temp->next = NULL;
	}
	else
	{
		while (temp -> next != NULL)
		{
			temp = temp->next;
		}

		struct linkedNode *newNode = malloc(sizeof(struct linkedNode));
		newNode->val = value;
		newNode->key = key;
		newNode->taken = 1;
		newNode->next = NULL;

		temp->next = newNode;
	}
	hmap->count += 1;
}

struct IntToIntHashMap* createIntToIntHashMap(int numBuckets){
	struct IntToIntHashMap* map = malloc(sizeof(struct IntToIntHashMap));
	map->length = numBuckets;
	map->hashTable = calloc(numBuckets, sizeof(struct linkedNode));
	map->count = 0;
	return map;
}

void intToIntHashMapInsert(struct IntToIntHashMap* hmap, int key, int value){
	unsigned int uhash = intToIntHashFunction(key);
	int hash = uhash%hmap->length;
	struct linkedNode *temp = &hmap->hashTable[hash];
	if (temp -> taken == 0)
	{
		temp->val = value;
		temp->key = key;
		temp->taken = 1;
		temp->next = NULL;
	}
	else
	{
		while (temp -> next != NULL)
		{
			if (temp->key == key)
			{
				temp->val = value;
				return;
			}
			temp = temp->next;
		}

		struct linkedNode *newNode = malloc(sizeof(struct linkedNode));
		newNode->val = value;
		newNode->key = key;
		newNode->taken = 1;
		newNode->next = NULL;

		temp->next = newNode;
	}
	hmap->count += 1;
	if ((double)(hmap->count) / (double)(hmap->length) >= 0.75)
	{
		int oldLen = hmap->length;
        struct linkedNode *oldTable = hmap->hashTable;

        hmap->length *= 2;
        hmap->hashTable = calloc(hmap->length, sizeof(struct linkedNode));
        hmap->count = 0;

        for (int i = 0; i < oldLen; i++) {
            struct linkedNode *curr = &oldTable[i];
            if (curr->taken != 0) {
                rehash(hmap, curr->key, curr->val);
                struct linkedNode *n = curr->next;
                while (n!= NULL) {
                    struct linkedNode *toFree = n;
                    rehash(hmap, n->key, n->val);
                    n = n->next;
                    free(toFree);
                }
            }
        }
        free(oldTable);
	}
}

int intToIntHashMapGet(struct IntToIntHashMap* hmap, int key){
	int hash = intToIntHashFunction(key)%hmap->length;
	struct linkedNode *temp = &hmap->hashTable[hash];

    while (temp != NULL && temp->taken != 0) {
        if (temp->key == key) return temp->val;
        temp = temp->next;
    }
    return -1;
}

void intToIntHashMapRemove(struct IntToIntHashMap* hmap, int key){
	int hash = intToIntHashFunction(key)%hmap->length;
	struct linkedNode *temp = &hmap->hashTable[hash];
	if (temp->taken == 0)return;

	if (temp->key == key)
	{
		if (temp->next != NULL)
		{
			struct linkedNode *toDelete = temp->next;
            *temp = *toDelete;
            free(toDelete);
		}
		else
		{
			temp->taken = 0;
		}
		hmap->count--;
		return;
	}

	while (temp->next != NULL && temp->next->key != key)
	{
		temp = temp->next;
	}
	if (temp->next != NULL)
	{
		struct linkedNode *toDelete = temp->next;
        temp->next = toDelete->next;
        free(toDelete);
        hmap->count--;
	}
}

void destroyIntToIntHashMap(struct IntToIntHashMap* hmap){
	for (int i = 0; i < hmap->length; i++)
	{
		struct linkedNode *temp = hmap->hashTable[i].next;
		while (temp != NULL)
		{
			struct linkedNode *t = temp->next;
			free(temp);
			temp = t;
		}
	}
	free(hmap->hashTable);
	free(hmap);
}


int strToIntHashFunction(char* key){
	//TODO: fill this in
	return 0;
}

struct StrToIntHashMap* createStrToIntHashMap(int numBuckets){
	//TODO: fill this in
	return 0;
}

void strToIntHashMapInsert(struct StrToIntHashMap* hmap, char* key, int value){
	//TODO: fill this in
}

int strToIntHashMapGet(struct StrToIntHashMap* hmap, char* key){
	//TODO: fill this in
	return 0;
}

void strToIntHashMapRemove(struct StrToIntHashMap* hmap, char* key){
	//TODO: fill this in
}

void destroyStrToIntHashMap(struct StrToIntHashMap* hmap){
	//TODO: fill this in
}


