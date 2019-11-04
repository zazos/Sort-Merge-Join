#include <stdio.h>
#include <stdlib.h>
#include "../include/relation.h"

void swap(tuple * a, tuple * b)
{
    tuple  temp  = *a;
    *a = *b;
    *b = temp;

}

int64_t partition(relation * rel, int64_t start, int64_t end)
{
	uint64_t pivot = rel -> tuples[end].key;

	int64_t i = start - 1;

	for (int64_t j = start ; j <= end - 1; j++)
	{
		if (rel -> tuples[j].key < pivot)
		{
			i++;
			swap(&rel -> tuples[i], &rel -> tuples[j]);
		}
	}
	swap(&rel -> tuples[i+1], &rel -> tuples[end]);

	return (i+1);
}

// Sort keys from relation in range start to end
void Quicksort(relation * rel, int64_t start, int64_t end)
{

    if(rel == NULL)
    {
        perror("Quicksort error:");
        exit(-1);
    }
    if (start < end)
    {
        int64_t partition_index = partition(rel, start, end);
        Quicksort(rel, start, partition_index - 1);
        Quicksort(rel, partition_index + 1, end);
    }

}
