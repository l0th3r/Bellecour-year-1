#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	int j = 0;
	dynamic_int_array *cpy;

	if(end > darray->size)
		end = darray->size + 1;

	cpy = create_dynamic_int_array(end - start - 1);

	while(j < cpy->size || i < end)
	{
		cpy->array[j] = darray->array[i];
		j++;
		i++;
	}

	return cpy;
}

dynamic_int_array* copy_dynamic_int_array(const dynamic_int_array* darray)
{
	dynamic_int_array *cpy = sub_dynamic_int_array(darray, 0, darray->size + 1);
	return cpy;
}

/* EX 09 */

char* read_file(const char* path)
{
	FILE * fp;
	char *to_return;
	char temp;
	size_t len = 1;
	int i = 0;

	to_return = malloc(len * sizeof(char));

	fp = fopen(path, "r");

	if(fp != NULL)
	{
		do
		{
			to_return = realloc(to_return, len++ * sizeof(char));
			temp = fgetc(fp);
			to_return[i] = temp;
			i++;
		}
		while(temp != EOF);
		to_return = realloc(to_return, len++ * sizeof(char));
		to_return[i] = '\0';
	}

	return to_return;
}

/* EX 10 */
typedef struct {int number; char * file_path; char * text; int * link;} interactive_story_paragraph;

interactive_story_paragraph* create_interactive_story(char* folder_path, int paragraph_count)
{
	interactive_story_paragraph* to_return = malloc(paragraph_count * sizeof(interactive_story_paragraph));

	/* loops variables */
	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;
	int m = 0;

	/* declare temporary pointers */
	char *ctemp;
	int *ltemp;

	while(i < paragraph_count)
	{
		/* allocate */
		ctemp = malloc(sizeof(char));
		ltemp = malloc(sizeof(int));

		to_return[i].number = i;

		/* while not assigned, = NULL */
		to_return[i].link = NULL;
		
		/*allocate for getting sprintf*/
		to_return[i].file_path = malloc( (strlen(folder_path) + 20) * sizeof(char));

		/* convert number to str */
		sprintf(to_return[i].file_path, "%s/%d%c",folder_path, i, '\0');

		to_return[i].text = read_file(to_return[i].file_path);

		j = 0;
		l = 0;
		while(to_return[i].text[j] != '\0')
		{
			if(to_return[i].text[j] == '*')
			{
				k = 0;
				j++;
				while(to_return[i].text[j] != '*')
				{
					ctemp = realloc(ctemp, (k + 1) * sizeof(char));
					ctemp[k] = to_return[i].text[j];
					k++;
					j++;
				}
				ctemp = realloc(ctemp, (k + 1) * sizeof(char));
				ctemp[k] = '\0';

				ltemp = realloc(ltemp, (l + 1) * sizeof(int));
				ltemp[l] = atoi(ctemp);

				l++;
				j++;
			}
			else
				j++;
		}

		/* add 0 at the end */
		ltemp = realloc(ltemp, (l + 1) * sizeof(int));
		ltemp[l] = 0;
		l++;

		m = 0;
		while(ltemp[m] != 0)
		{
			to_return[i].link = realloc(to_return[i].link, (m + 1) * sizeof(int));
			to_return[i].link[m] = ltemp[m];
			m++;
		}

		/* add 0 at the end */
		to_return[i].link = realloc(to_return[i].link, (m + 1) * sizeof(int));
		to_return[i].link[m] = 0;

		free(ctemp);
		free(ltemp);
		i++;
	}

	return to_return;
}







/* REMOVE */
int main(void)
{
	int i = 0;
	int j = 0;

	interactive_story_paragraph* ip = create_interactive_story("./toile", 46);

	while(i < 46)
	{
		printf("\n{\n\n");

		printf("number = %d\n", ip[i].number);
		printf("file path = %s\n", ip[i].file_path);
		printf("link = ");
		j = 0;
		while(ip[i].link[j] != 0)
		{
			printf("%d, ", ip[i].link[j]);
			j++;		
		}

		printf("\n\n}\n");
		
		i++;
	}
	
	return 0;
}
/* REMOVE */

