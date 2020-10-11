#include <stdio.h>
#include <stdlib.h>

#include "useful.h"

int get_grid(int target[9][9], int ac, char **av);

void print_grid(int target[9][9], int is_loading);
void resolve(int grid[9][9]);

int main(int ac, char **av)
{
	int grid[9][9];
	int grid_res = 0;

	grid_res = get_grid(grid, ac, av);

	if (grid_res == 0)
		resolve(grid);

	return 0;
}

void resolve(int grid[9][9])
{
	
}

void print_grid(int target[9][9], int is_loading)
{
	/* loops variables */
	int i = 0;
	int j = 0;

	printf("\033[H\033[J\n");
	while (i < 9)
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

	if (is_loading == 1)
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

	/* grid (memory) */
	int test[9][9];

	/* temporary char */
	char temp;

	/* grid (file) */
	FILE *fp;

	if (ac < 2 || strcmp(av[1], "-h") == 0)
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
					if (temp != '\n' && temp != '\r')
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
