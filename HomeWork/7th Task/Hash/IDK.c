#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include<math.h>
#include"IDK.h"

void init(int a, int b)
{
	hashTable = (int**)malloc(a * sizeof(int*));
	for (int i = 0; i < a; i++) hashTable[i] = (int*)malloc(b * sizeof(int));

	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < b; j++) hashTable[i][j] = 0;
	}
}


int hash_func(int key)
{
	if (key < 0) key *= -1;
	if (key > n)
	{
		int tmp = key, k = 0;

		while (tmp > 0)
		{
			tmp /= n;
			k++;
		}
		k = pow(10, k - 1); // k - (amount of signs of n/10)
		key /= k;
	}
	return key - 1;
}

void add(struct hash a)
{
	int key;
	key = hash_func(a.key);
	for (int j = 0; j < ptr; j++)
	{
		if (hashTable[key][j] == 0)
		{
			hashTable[key][j] = a.value;
			return 1;
		}
	}
	rebalance(0);
	hashTable[key][ptr - 1] = a.value;
	return 1;
}

int rebalance(unsigned int choice)
{
	int i, j;
	if (choice == 0)
	{
		ptr++;
		for (i = 0; i < n; i++) hashTable[i] = (int*)realloc(hashTable[i], ptr * sizeof(int));

		for (i = 0; i < n; i++) hashTable[i][ptr - 1] = 0;

		return 0;
	}

	int k = 0;
	if (choice == 1)
	{
		for (i = 0; i < n; i++)
		{
			if (hashTable[i][ptr - 1] != 0) k++;    // checks whether to reduce the array of pointers
		}
		if (k > 1) return 1;

		ptr--;

		int **tmp = (int**)malloc(n * sizeof(int*));
		for (i = 0; i < n; i++) tmp[i] = (int*)malloc(ptr * sizeof(int));

		for (i = 0; i < n; i++)
		{
			for (j = 0; j < ptr; j++) tmp[i][j] = hashTable[i][j];
		}

		//for (i = 0; i < n; i++) free(hashTable[i]);

		//hashTable = (int**)malloc(n * sizeof(int*));

		for (i = 0; i < n; i++) hashTable[i] = (int*)malloc(ptr * sizeof(int));

		for (i = 0; i < n; i++)
		{
			for (j = 0; j < ptr; j++) hashTable[i][j] = tmp[i][j];
		}

		for (i = 0; i < n; i++) free(tmp[i]);
		free(tmp);

		return 0;
	}
}

void find(struct hash a)
{
	int key;
	key = hash_func(a.key);
	for (int j = 0; j < ptr; j++)
	{
		if (hashTable[key][j] != 0)
		{
			printf("%d", hashTable[key][j]);
			printf("%c", ' ');
		}
		else break;
	}
}

void delite(struct hash a)
{
	int key, x;
	key = hash_func(a.key);
	for (int i = 0; i < n; i++)
	{
		if (hashTable[key][i] == a.value)
		{
			hashTable[key][i] = 0;
			for (int j = i; j < n - 1; j++)
			{
				hashTable[key][j] = hashTable[key][j + 1];
			}
		}
	}
	hashTable[key][ptr - 1] = a.value;
	x = rebalance(1);
	if (x == 1) hashTable[key][ptr - 1] = 0;
}

void myFree()
{
	for (int i = 0; i < n; i++)
	{
		free(hashTable[i]);
	}
	free(hashTable);
}