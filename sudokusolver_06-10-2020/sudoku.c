#include <stdio.h>
#include <stdlib.h>

#include "useful.h"

int get_grid(int target[9][9], int ac, char **av);
int gridcmp(int tocmp[9][9], int i, int j);
int is_modifiable(int grid[9][9], int i, int j);
int check_all(int grid[9][9], int i, int j);
int check_row(int grid[9][9], int i, int j);
int check_col(int grid[9][9], int i, int j);

void arrcpy(int arr1[9][9], int arr2[9][9]);
void print_grid(int target[9][9], int is_loading);
void resolve(int old[9][9]);
void advance(int *i);

int main(int ac, char **av)
{
	int grid[9][9];
	int grid_res = 0;

	grid_res = get_grid(grid, ac, av);

	if(grid_res == 0)
		resolve(grid);

	return 0;
}

void resolve(int old[9][9])
{
	/* loops vriables */
	int i = 0;
	int j = 0;
	int k = 1;

	/* conditions variables */
	int placable = 0;

	/* new grid */
	int grid[9][9];

	/* copy array */
	arrcpy(old, grid);

	while(i < 9)
	{
		j = 0;
		while(j < 9)
		{
			if (is_modifiable(old, i, j) == 1)
			{
				placable = 0;	
				while(placable == 0 && grid[i][j] < 10)
				{
					grid[i][j] += 1;
					print_grid(grid, 1);
					placable = check_all(grid, i, j);
				}
				if (grid[i][j] == 10)
				{
					grid[i][j] = 0;
				
				}
				else if(placable == 1)
				{
					/* advance */
				}
			}
			j++;
		}
		i++;
	}
}

int check_all(int grid[9][9], int i, int j)
{
	int to_return = 0;
	int row = check_row(grid, i, j);
	int col = check_col(grid, i, j);
	
	if(row == 1 && col == 1)
		to_return = 1;

	return to_return;
}

int check_row(int grid[9][9], int i, int j)
{
	int to_return = 1;

	/* loops variables */
	int k = 0;

	while(k < 9) 
	{
		if (grid[i][k] == grid[i][j] && i != k)
			to_return = 0;
		k++;
	}
	return to_return;
}

int check_col(int grid[9][9], int i, int j)
{
	int to_return = 1;

	/* loops variables */
	int k = 0;

	while(k < 9)
	{
		if (grid[k][j] == grid[i][j])
			to_return = 0;
		k++;
	}
	return to_return;
}

void advance(int *i)
{
	if(*i != 8)
		*i += + 1;
	else
		*i = 0;
}

int is_modifiable(int grid[9][9], int i, int j)
{
	int to_return = 0;
	
	if(grid[i][j] == 0)
		to_return = 1;

	return to_return;
}


int gridcmp(int tocmp[9][9], int i, int j)
{
	int to_return = 0;

	if(tocmp[i][j] != 0)
		to_return = 1;

	return to_return;
}


void arrcpy(int arr1[9][9], int arr2[9][9])
{
	/* loops variables */
	int i = 0;
	int j = 0;

	while(i < 9)
	{
		j = 0;
		while(j < 9)
		{
			arr2[i][j] = arr1[i][j];
			j++;
		}
		i++;
	}
}

void print_grid(int target[9][9], int is_loading)
{
	/* loops variables */
	int i = 0;
	int j = 0;

	printf("\033[H\033[J\n");
	while(i < 9)
	{
		j = 0;

		/* 3 lines gap */
		if (i % 3 == 0 && i != 0)
			printf("------------------------------\n");

		while(j < 9)
		{
			/* 3 numbers gap */
			if (j % 3 == 0 && j != 0)
				printf("|  ");

			if (target[i][j] != 0)
				printf("%d  ", target[i][j]);
			else
				printf(".  ");
			
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n");

	if(is_loading == 1)
		printf("Tring to solve...\n\n");
}

int get_grid(int target[9][9], int ac, char **av)
{
	/* to return 0 if good everything good, else 1 */
	int status = 0;

	/* loops variables */
	int i = 0;
	int j = 0;
	int cnt = 0;

	/* temporary char */
	char temp;

	/* grid (file) */
	FILE *fp;

	if(ac < 2 || strcmp(av[1], "-h") == 0)
	{
		printf("\nUsage: %s [-h] input_file outpout_file\n\n", av[0]);
		status = 1;
	}
	else
	{
		fp = fopen(av[1], "r");

		if (fp == NULL)
 		{
			printf("Cannot open the file  %s\n", av[1]);
			status = 1;
		}
		else
		{
			while(i < 9)
			{
				j = 0;
				while(j < 9)
				{
					temp = fgetc(fp);
					if(temp != '\n' && temp != '\r')
					{
						target[i][j] = uf_ctoi(temp);
						cnt++;
						j++;
					}
				}
				i++;
			}
			fclose(fp);
		}
	}
	return status;
}
