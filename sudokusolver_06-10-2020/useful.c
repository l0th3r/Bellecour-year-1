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
