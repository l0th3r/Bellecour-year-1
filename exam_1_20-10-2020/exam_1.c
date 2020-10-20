#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* EX 01 */
int sum_first_integers(int n)
{
	int to_return = 0;

	if(n < 0)
		to_return = -1;
	else if(n > 0)
	{
		
		/* Check if the next is overflow */
		if(n >= INT_MAX - 2)
			to_return = -1;
		else	
			to_return = n + sum_first_integers(n - 1);

	}

	return to_return;
}

/* EX 02 */
int sum_int_array(const int* array, size_t size)
{
	int to_return = 0;
	int i = 0;

	while(i < size)
	{
		to_return += array[i];
		i++;
	}

	return to_return;
}

/* EX 03 */
int min_int_array(const int* array, size_t size)
{
	int to_return = INT_MAX;
	int i = 0;

	while(i < size)
	{
		if(array[i] < to_return)
			to_return = array[i];
		i++;
	}

	return to_return;
}

int max_int_array(const int* array, size_t size)
{
	int to_return = INT_MIN;
	int i = 0;

	while(i < size)
	{
		if(array[i] > to_return)
			to_return = array[i];
		i++;
	}

	return to_return;
}

void min_max_int_array(const int* array, size_t size, int *min, int *max)
{
	int minimum = INT_MAX;
	int maximum = INT_MIN;
	int i = 0;

	while(i < size)
	{
		if(array[i] < minimum)
			minimum = array[i];
		if(array[i] > maximum)
			maximum = array[i];
		i++;
	}

	*min = minimum;
	*max = maximum;
}

/* EX 04 */
void heap_10M()
{
	void *p = malloc(10000);

	printf("Allocated !\n");
	free(p);
}


/* EX 05 */
typedef struct {int *array; size_t size;} dynamic_int_array;

dynamic_int_array* create_dynamic_int_array(size_t size)
{
	int *arr = malloc(size * sizeof(int));
	int i = 0;
	dynamic_int_array *to_return = malloc(sizeof(dynamic_int_array));

	while(i < size)
	{
		/* TO 0 */
		arr[i] = 1;
		i++;
	}

	(*to_return).array = arr;
	(*to_return).size = size;

	return to_return;
}

void destroy_dynamic_int_array(dynamic_int_array* darray)
{
	free((*darray).array);
	free(darray);
}

/* EX 06 */
int dynamic_int_array_get(const dynamic_int_array* darray, size_t index)
{
	int to_return = 0;

	if(index < (*darray).size)
		to_return = (*darray).array[index];

	return to_return;
}

size_t dynamic_int_array_add(dynamic_int_array *darray, int value)
{
	(*darray).array = realloc((*darray).array, (*darray).size + sizeof(int));
	(*darray).size += 1;
	(*darray).array[(*darray).size - 1] = value;

	return (*darray).size - 1;
}

/* EX 07 */
void dynamic_int_array_set(dynamic_int_array* darray, size_t index, int value)
{
	int i = 0;

	if(index >= darray->size)
	{
		i = darray->size;
	
		(*darray).array = realloc((*darray).array, (index + 1) * sizeof(int));
		darray->size += index - darray->size;

		
		while(i < index)
		{
			if(i == index - 1)
				darray->array[i] = value;
			else
				darray->array[i] = 0;
				
			i++;
		}
	}
	else
		darray->array[index] = value;
}

int dynamic_int_array_remove(dynamic_int_array* darray, size_t index)
{
	int to_return = darray->array[index];
	int i = 0;

	while(i < darray->size - 1)
	{
		if(i >= index)
			darray->array[i] = darray->array[i + 1];
		i++;
	}
	
	(*darray).array = realloc((*darray).array, (darray->size - 1) * sizeof(int));
	darray->size -= 1;
	
	return to_return;
}

/* EX 08 */
dynamic_int_array* sub_dynamic_int_array(const dynamic_int_array* darray, size_t start, size_t end)
{
	int i = start;
	dynamic_int_array *cpy = create_dynamic_int_array(end-start + 1);

	while(i < end)
	{
		cpy->array[i] = darray->array[i];
		i++;
	}

	return cpy;
}


/* REMOVE */
int main(void)
{
	int i = 0;
	dynamic_int_array *pt = create_dynamic_int_array(10);
	dynamic_int_array *cp;
	dynamic_int_array_set(pt, 15, 20);

	cp = sub_dynamic_int_array(pt, 10, pt->size);


	while(i < cp->size)
	{
		printf("%d, ", cp->array[i]);
		i++;
	}


	printf("\nres = %d\n", dynamic_int_array_remove(pt, 14));

	destroy_dynamic_int_array(pt);

	return 0;
}
/* REMOVE */

