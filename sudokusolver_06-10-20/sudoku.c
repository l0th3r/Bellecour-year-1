#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int uf_atoi(char *str);
int uf_ctoi(char c);
int get_arg(int target[9][9], int ac, char **av);
int get_out(int target[9][9], char **av);
int gridcmp(int tocmp[9][9], int i, int j);
int is_modifiable(int grid[9][9], int i, int j);
int check_all(int grid[9][9], int i, int j);
int check_row(int grid[9][9], int i, int j);
int check_col(int grid[9][9], int i, int j);
int check_square(int grid[9][9], int i, int j);
int check_grid(int target[9][9]);
int check_in_out(int in[9][9], int out[9][9]);

void arrcpy(int arr1[9][9], int arr2[9][9]);
void print_grid(int target[9][9], int is_loading);
void resolve(int old[9][9], int grid[9][9]);
void advance(int *i, int *j);
void backtrack(int grid[9][9], int old[9][9], int *i, int *j);
void print_help(char *str);
void print_usage(char *str);
void print_no_solve();
void uf_split_atoi(int *target, char *str, int len);
void print_loading();

/* grid (file) */
FILE *fp;
FILE *out;
char *out_name;

/* flags variables */
int f_slow = 1;
int f_debug = 0;
int f_very = 0;

/* used for the loading animation */
int count = 0;
/* is there a solution */
int is_solvable = 1;

int main(int ac, char **av)
{
	int input[9][9];
	int output[9][9];

	int arg_res = 0;

	arg_res = get_arg(input, ac, av);

	if(arg_res == 0)
	{
		resolve(input, output);

		/* extract the result */
		get_out(output, av);

		/* print one last time to show the result */
		print_grid(output, 0);
	}

	return 0;
}

void resolve(int old[9][9], int grid[9][9])
{
	/* loops vriables */
	int i = 0;
	int j = 0;

	/* conditions variables */
	int placable = 0;
	int stop = 0;
	int is_exit = 0;

	/* copy array */
	arrcpy(old, grid);

	print_grid(grid, 1);
	
	while(i < 9 && is_exit == 0)
	{
		if (is_modifiable(old, i, j) == 1 && stop == 0)
		{
			placable = 0;
			while(placable == 0 && grid[i][j] <= 10)
			{
				grid[i][j] += 1;

				if(f_slow == 1)
				{
					fflush(stdout);
					if(f_very == 1)
						usleep(100000);

					count++;
					print_grid(grid, 1);
				}
				
				placable = check_all(grid, i, j);
				
				if(f_debug == 1)
				{
					printf("---------- DEBUG -----------\n\n");
					printf("Current place (x:%d, y:%d) = %d\n", i, j, grid[i][j]);
					printf("Current is right = %d\n", placable);
					printf("Iteration counter = %d\n", count);
					printf("\n---------- DEBUG -----------\n\n");
				}
			}

			if (grid[i][j] == 10)
			{
				if(i == 0 && j == 0)
				{
					stop = 1;
					is_exit = 1;
					is_solvable = 0;
				}
				else
					backtrack(grid, old, &i, &j);
			}
			else if(placable == 1)
				advance(&i, &j);
		}
		else if(stop == 0)
			advance(&i, &j);
	}
}

void backtrack(int grid[9][9], int old[9][9], int *i, int *j)
{
	int is_good = 0;

	/* set this case to 0 */
	grid[*i][*j] = 0;

	while(is_good == 0)
	{
		if(*j == 0)
		{
			*j = 8;
			*i -= 1;
		}
		else
			*j -= 1;
		
		if (is_modifiable(old, *i, *j) == 1)
			is_good = 1;
	}
}

int check_all(int grid[9][9], int i, int j)
{
	int to_return = 0;
	int row = check_row(grid, i, j);
	int col = check_col(grid, i, j);
	int square = check_square(grid, i, j);
	
	if(row == 1 && col == 1 && square == 1)
		to_return = 1;

	return to_return;
}

int check_square(int grid[9][9], int i, int j)
{
	int to_return = 1;

	/* get for row and col, the start of the square 0 or 3 or 6 
	 * exemple: if both = 0 that is the first square */
	int row_start = i - (i % 3);
	int col_start = j - (j % 3);

	/* loops variables */
	int row = 0;
	int col = 0;

	while(row < 3)
	{
		col = 0;
		while(col < 3)
		{
			/* go through the square and exept if the one checked is the current one to compare */
			if(grid[row + row_start][col + col_start] == grid[i][j] && row + row_start != i && col + col_start != j)
				to_return = 0;
			col++;
		}
		row++;
	}

	return to_return;
}

int check_row(int grid[9][9], int i, int j)
{
	int to_return = 1;

	/* loops variables */
	int k = 0;

	while(k < 9) 
	{
		if (grid[i][k] == grid[i][j] && j != k)
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
		if (grid[k][j] == grid[i][j] && i != k)
			to_return = 0;
		k++;
	}
	return to_return;
}

void advance(int *i, int *j)
{
	if(*j == 8)
	{
		*j = 0;
		*i += 1;
	}
	else
		*j += 1;
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

	/* clear stdout */
	printf("\033[H\033[J\n");

	if(is_loading == 1)
		print_loading();
	
	while(i < 9)
	{
		j = 0;

		/* 3 lines gap */
		if (i % 3 == 0 && i != 0)
			printf("-------- + --------- + --------\n");

		while(j < 9)
		{
			/* 3 numbers gap */
			if (j % 3 == 0 && j != 0)
				printf("|  ");

			/* print values but spaces when its 10 and 0 */
			if (target[i][j] != 0 && target[i][j] != 10)
				printf("%d  ", target[i][j]);
			else
				printf("   ");
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n");

	if(is_loading == 0)
	{
		if(is_solvable == 1)
			printf("This is the solution.\n\n");
		else
			print_no_solve();
		printf("Use the flag [-h] to see all options.\n\n");
	}
}

void print_loading()
{
	char temp;

	switch(count % 4)
	{
		case 0:
			temp = '|';
		break;
		case 1:
			temp = '/';
		break;
		case 2:
			temp = '-';
		break;
		case 3:
			temp = 92;
		break;
	}
	printf("Loading %c\n\n", temp);
}

int get_out(int target[9][9], char **av)
{
	/* to return 0 if good everything good, else 1 */
	int status = 0;

	/* loops variables */
	int i = 0;
	int j = 0;

	if(is_solvable == 1)
	{
		out = fopen(out_name, "w");
		while(i < 9)
		{
			j = 0;
			while(j < 9)
			{
				fprintf(out, "%d", target[i][j]);
				j++;
			}
			fprintf(out, "\n");
			i++;
		}
		fclose(out);
	}
	else
		print_no_solve();
	

	return status;
}

int get_arg(int target[9][9], int ac, char **av)
{
	/* to return 0 if good everything good, else 1 */
	int status = 0;
	int check_sol = 0;

	/*temp file*/
	int temp_arr[9][9];

	/* loops variables */
	int i = 0;
	int j = 0;
	int arg = 0;

	char temp;
	
	if(ac == 1)
	{
		print_usage(av[0]);
		status = 1;
	}
	else if(ac == 2 && strcmp(av[1], "-h") != 0)
	{
		print_usage(av[0]);
		status = 1;
	}
	else if(ac == 2 && strcmp(av[1], "-h") == 0)
	{
		printf("\nYou can run %s with some options.", av[0]);
		printf("\nThose optionals arguments come after files argument.\n");
		print_usage(av[0]);	
		printf("FLAGS:");
		printf("\n-slow or -fast:\n");
		printf("\n	-slow = display the grid to see the resolution.");
		printf("\n	-fast = dont display the grid, just output the file.");
		printf("\n	-veryslow = refresh time is slower so you can read better (pretty nice with -debug).");
		printf("\n	default = -slow.\n\n");
		printf("\n-debug or -nodebug:\n");
		printf("\n	-debug = display some debugs informations (-slow is needed risk of glitches).");
		printf("\n	-nodebug = dont display debugs informations.");
		printf("\n	default = -nodebug.\n\n");
		printf("FILE:");
		printf("\nformat:\n");
		printf("\n	The file must contain 9 rows of 9 numbers between 0 and 9.");
		printf("\n	No spaces, or other than numbers.");
		printf("\n	The content is a sudoku grid, so if you put 0, its a blank square.");
		printf("\n	If you put a number greater than 0, this number is not gonna change.");
		printf("\n	Careful to use a valid grid, or the program will not use it.");
		printf("\n\n	exemple of a valid file content to solve:\n\n");
		printf("	003050800\n");
		printf("	800900020\n");
		printf("	926008045\n");
		printf("	009400000\n");
		printf("	730005100\n");
		printf("	680001079\n");
		printf("	068024000\n");
		printf("	042000607\n");
		printf("	009080054\n");
		printf("\n\n");
		status = 1;
	}
	else
	{
		fp = fopen(av[1], "r");
		out = fopen(av[2], "r");

		if(fp == NULL)
		{
			printf("\nCannot find '%s' as input (sudoku grid) file.\n", av[1]);
			print_help(av[0]);
			status = 1;
		}

		/* get name of the output file */
		out_name = av[2];
	
		/* check if the file have a solvable grid */
		if(out == NULL)
			check_sol = 1;

		/* go though flags */
		if (ac > 3)
		{
			arg = 3;
			/* check flags and change settings */
			while(arg < ac)
			{
				if(strcmp(av[arg], "-fast") == 0)
				{
					f_slow = 0;
				}
				if(strcmp(av[arg], "-slow") == 0)
				{
					f_slow = 1;
				}
				if(strcmp(av[arg], "-debug") == 0 && f_slow == 1)
				{
					f_debug = 1;
				}
				if(strcmp(av[arg], "-nodebug") == 0)
				{
					f_debug = 0;
				}
				if(strcmp(av[arg], "-veryslow") == 0)
				{
					f_very = 1;
				}
				arg++;
			}
		}

		if(status == 0)
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
						j++;
					}
				}
				i++;
			}
			fclose(fp);
		}
	}

	/* Check if the grid has a solution */
	if (check_sol == 1 && status == 0)
	{
		status = check_grid(target);
		if(status == 1)
			print_no_solve();
	}
	else if(check_sol == 0 && status == 0)
	{
		/* We are there because the output file already exist so we are gonna check if 
		* it contain a solved grid of the input file */
		i = 0;
		while(i < 9)
		{
			j = 0;
			while(j < 9)
			{
				temp = fgetc(out);
				if(temp != '\n' && temp != '\r')
				{
					temp_arr[i][j] = uf_ctoi(temp);
					j++;
				}
			}
			i++;
		}
		/* return 1 if the  */
		status = check_in_out(target, temp_arr);
		if(status == 1)
			printf("\nYou already have a solved version of '%s' in '%s'.\n\n", av[1], av[2]);
	}

	return status;
}

/* this funtion check if the out array is a solved version of the in array */
int check_in_out(int in[9][9], int out[9][9])
{
	/* variables to return */
	int to_return = 1;

	/* loops variables */
	int i = 0;
	int j = 0;

	/* first we check if the out array have the same start grid as in array */
	while(i < 9)
	{
		j = 0;
		while(j < 9)
		{
			if(in[i][j] != 0)
			{
				if(in[i][j] != out[i][j])
					to_return = 0;
			}

			if(out[i][j] == 0)
				to_return = 0;
			j++;
		}
		i++;
	}

	return to_return;
}

int check_grid(int target[9][9])
{
	/* return 0 if the grid is good else 1 */
	int to_return = 0;

	/* loops variables */
	int i = 0;
	int j = 0;

	/* Check if the grid have an error */
	while(i < 9)
	{
		j = 0;
		while(j < 9)
		{
			if(target[i][j] != 0)
			{
				if(check_all(target, i, j) == 0)
					to_return = 1;
			}
			j++;
		}
		i++;
	}

	return to_return;	
}

void print_help(char *str)
{
	printf("If you need help you can type %s -h\n\n", str);
}

void print_no_solve()
{
	printf("\n\nThis grid can't be solved.\n\n");
}

void print_usage(char *str)
{
	printf("\nUsage: %s <input_file> <outpout_file> [flags]\n", str);
	printf("\nOr, to get help you can do: %s -h\n\n", str);
}

int uf_atoi(char *str)
{
	int to_return = 0;
	int i = 0;

	while (str[i] != '\0')
	{
		to_return = to_return * 10 + str[i] - '0';
		i++;
	}

	return to_return;
}

int uf_ctoi(char c)
{
	int to_return;

	to_return = c - '0';

	return to_return;
}

void uf_split_atoi(int *target, char *str, int len)
{
	int i = 0;

	while (i < len)
	{
		target[i] = str[i] - '0';
		i++;
	}
}
