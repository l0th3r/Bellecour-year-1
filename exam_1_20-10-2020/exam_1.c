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
		to_return = n + sum_first_integers(n - 1);
		
		if(to_return < n)
			to_return = -1;
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

	while(i < size)	{
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
	int err = 0;
	void *p = malloc(10000);

	if(!p)
		err = 1;

	if(err == 1)
		printf("Failed to allocate.\n");
	else
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
		arr[i] = 0;
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
	(*darray).array = realloc((*darray).array, (*darray).size * sizeof(int));
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

	cpy = create_dynamic_int_array(end - start);

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
			to_return = realloc(to_return, ++len * sizeof(char));
			temp = fgetc(fp);
			to_return[i] = temp;
			i++;
		}
		while(temp != EOF);
		to_return = realloc(to_return, ++len * sizeof(char));
		to_return[i] = '\0';
	}
	else
	{
		to_return = realloc(to_return, 2 * sizeof(char));
		to_return[0] = 3;
		to_return[1] = '\0';	
	}

	return to_return;
}

/* EX 10 */
typedef struct {int number; char * file_path; char * text; int * links;} interactive_story_chapter;

interactive_story_chapter * create_interactive_story(char* folder_path, int chapter_count)
{
	interactive_story_chapter* to_return = malloc(chapter_count * sizeof(interactive_story_chapter));

	/* loops variables */
	int i = 0;

	while(i < chapter_count)
	{
		to_return[i].number = i;

		/* while not assigned, = NULL */
		to_return[i].links = NULL;
		
		/*allocate for getting sprintf*/
		to_return[i].file_path = malloc((strlen(folder_path) + 20) * sizeof(char));

		/* convert number to str */
		sprintf(to_return[i].file_path, "%s/%d%c",folder_path, i, '\0');

		/* text is empty so NULL pointer*/
		to_return[i].text = NULL;

		i++;
	}

	return to_return;
}

/* EX 11 */
void interactive_story_chapter_load(interactive_story_chapter* chapter)
{
	/* loops variables */
	int j = 0;
	int k = 0;
	int l = 0;
	int m = 0;

	/* declare temporary pointers */
	char *ctemp;
	int *ltemp;
	char *ttemp;

	printf("\nLoading file %s...", chapter->file_path);

	/* test if the file exist */
	ttemp = read_file(chapter->file_path);

	/* check if the text isn't alredy loaded and that the target file exist */
	if(ttemp[0] != 3 && chapter->text == NULL)
	{
		/* get text */
		chapter->text = read_file(chapter->file_path);

		/* allocate */
		ctemp = malloc(sizeof(char));
		ltemp = malloc(sizeof(int));

		while(chapter->text[j] != '\0')
		{
			if(chapter->text[j] == '*')
			{
				k = 0;
				j++;
				while(chapter->text[j] != '*')
				{
					ctemp = realloc(ctemp, (k + 1) * sizeof(char));
					ctemp[k] = chapter->text[j];
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
			chapter->links = realloc(chapter->links, (m + 1) * sizeof(int));
			chapter->links[m] = ltemp[m];
			m++;
		}

		/* add 0 at the end */
		chapter->links = realloc(chapter->links, (m + 1) * sizeof(int));
		chapter->links[m] = 0;

		free(ctemp);
		free(ltemp);

		printf("\nThe file is loaded.\n");
	}
	else
		printf("\nWARNING: the file %s can't be loaded or the file is already loaded.\n", chapter->file_path);

	free(ttemp);
}

void interactive_story_load_all(interactive_story_chapter* story, int chapter_count)
{
	int i = 0;

	while(i < chapter_count)
	{
		interactive_story_chapter_load(&story[i]);
		i++;
	}
}

/* EX 12 */
void interactive_story_chapter_print(const interactive_story_chapter* chapter)
{
	if(chapter->text == NULL)
		printf("\nERROR: text is not loaded in this chapter.\n");
	else
		printf("\n%s\n", chapter->text);
}

void interactive_story_chapter_load_print(interactive_story_chapter * chapter)
{
	if(chapter->text == NULL)
	{
		interactive_story_chapter_load(chapter);
		interactive_story_chapter_print(chapter);
	}
}

/* EX 13 */
int interactive_story_chapter_scan_player_choice(const interactive_story_chapter* chapter)
{
	/* variable to return */
	int to_return = 0;
	
	/* conditions variables */
	int is_good = 0;

	/* temporary variables */
	int temp;

	/* loops variables */
	int i = 0;

	/* conditions to ask the player */
	if(chapter->links == NULL)
		printf("\nERROR: This chapter is not loaded. Game Aborted.\n");
	else if(chapter->links[0] == 0)
		printf("\nThanks for playing, the story is over !\n");
	else
	{
		while(is_good == 0)
		{
			/* ask the player */
			printf("\nWhere to go next ? (number): ");
			scanf("%d", &temp);
			printf("\nYou choose %d", temp);

			i = 0;
			while(chapter->links[i] != 0)
			{
				if(chapter->links[i] == temp)
				{
					to_return = temp;
					is_good = 1;
				}
				i++;
			}
			if(is_good == 0)
				printf("\n%d is not a valid option.\n\n", temp);
		}
	}

	return to_return;
}

/* EX 14 */
void interactive_story_chapter_unload(interactive_story_chapter* chapter)
{
	free(chapter->links);
	chapter->links = NULL;

	free(chapter->text);
	chapter->text = NULL;
}

void destroy_interactive_story(interactive_story_chapter* story, int chapters_count)
{
	int i = 0;

	while(i < chapters_count)
	{
		interactive_story_chapter_unload(&story[i]);

		free(story[i].file_path);
		(story[i]).file_path = NULL;

		i++;
	}
	free(story);
}

