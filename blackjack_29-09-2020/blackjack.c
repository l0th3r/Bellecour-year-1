#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int get_random(int end);
int draw_card();
int ask_continue();
int ask_to_bet(int money);

struct Cards 
{	
	int id;
	int value;
	char suit[10];
};

int main(int ac, char **av)
{
	printf("\n\nHello, welcome to BlackJack :)\n\n");
	printf("If you dont know the rules, you can check them here\n");
	printf("en.wikipedia.org/wiki/Blackjack\n\n");
	
	
	int player_money = 100;
	int quit_game = 0;
	int player_bet = 0;
	
	while (quit_game == 0)
	{		
		/* BET */
		player_bet = ask_to_bet(player_money);

		
		/* GAME  */

		printf("\n\ncard value = %d\n\n", draw_card());

		/* CONTINUE */
		quit_game = ask_continue();
		system("clear");
	}

	return 0;
}

int draw_card()
{
	struct Cards card1;

	card1.value = get_random(10);
	strcpy(card1.suit, "spades");

	return card1.value;
}


int get_random(int end)
{
	int num;
	srand(time(0));
	num = rand() % end;
	return num;
}


int ask_to_bet(int money)
{
	int had_bet = 0;
	int bet = 0;

	printf("\nYou currently have %d$\n", money);
	printf("How much do you want to bet ?\n");

	do
	{
		scanf("%d", &bet);
		if (bet > 0 && bet <= money) had_bet = 1;
		else
		{
			printf("\nThat is not possible, try again :\n");
		}
	}
	while (had_bet == 0);
	
	printf("\nYou have betted %d$\n", bet);
	return bet;
}

int ask_continue()
{	
	int awnser;
	int had_choosed = 0;
	
	printf("Do you wish to continue ? [yes=0/no=1]\n");
	while (had_choosed == 0)
	{
		scanf("%d", &awnser);
		if (awnser == 1 || awnser == 0)
		{
			had_choosed = 1;
		}
		else
		{
			printf("\nThat is not possible, try again :\n");
		}
	}
	return awnser;
}
