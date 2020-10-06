#include <stdio.h>
#include <stdlib.h>

#include "useful.h"

int get_grid(int *target, int ac, char **av);

int main(int ac, char **av)
{
	int target[81];
	int grid_res = 0;

	grid_res = get_grid(target, ac, av);
	
	return 0;
}

int get_grid(int *target, int ac, char **av)
{
	int temp[9];
	int status = 0;
	char *line = NULL;
	
	FILE *fp;
	size_t len = 0;
	size_t nread;

	if (ac < 2)
	{
		printf("Usage: %s <file to use>\n", av[0]);
		status = 1;
	}
	else
	{
		fp = fopen(av[1], "r");

		if (fp == NULL)
 		{
			printf("Cannot open the file  %s\n", av[0]);
			status = 1;
		}

		while ((nread = getline(&line, &len, fp)) != -1)
		{
			uf_split_atoi(target, line, 9);
			
		}
		free(line);
	}
	return status;
}
