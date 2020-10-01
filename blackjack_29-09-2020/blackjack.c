#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

int get_random(int end);
int ask_continue();
int ask_to_bet(int money);

void make_deck();
void wait(int time);
void print_card(int card_id);
void start_deal(int *pl_nb, int *dl_nb);

struct Card
{	
	/* position in the deck */
	int id;

	/* what the card is worth */
	int value;

	/* clubs = 0, diamonds = 1, hearts = 2, spades = 3*/
	int suit;

	/* position of the card on the suit from 0 to 12 (0 is As 12 is king) */
	int position;

	/* if 1, the card has been used */
	int used;
};
/* make a deck of 52 cards. */
struct Card deck[52];
struct Card player_cards[15];
struct Card dealer_cards[15];


int main(int ac, char **av)
{
	int player_money = 100;
	int quit_game = 0;
	int player_bet = 0;
	int pl_cards_nb = 0; /*number of cards the player have*/
	int dl_cards_nb = 0; /*number of cards the dealer have*/

	system("clear");
	printf("\n\nHello, welcome to BlackJack :)\n\n");
	printf("If you dont know the rules, you can check them here\n");
	printf("en.wikipedia.org/wiki/Blackjack\n\n");

	while (quit_game == 0)
	{		
		/* BET */
		player_bet = ask_to_bet(player_money);

		
		/* GAME  */
		printf("\nThe round start.\n");
		make_deck();
		
		start_deal(&pl_cards_nb, &dl_cards_nb);


		/* END */
		/* quit_game = ask_continue();
		system("clear");*/
		quit_game = 1;
	}

	return 0;
}

void start_deal(int *pl_nb, int *dl_nb)
{

	printf("Dealing...\n");

	wait(1);
	
	/*HERE*/
	*nb = 10;

}

void print_card(int card_id)
{
	int id = deck[card_id].id;
	int val = deck[card_id].value;
	int suit = deck[card_id].suit;
	int pos = deck[card_id].position;

	printf("card position = %d\n", pos);
}


void make_deck()
{
	int pos_deck = 0; /*position 0 to 51 (there is 52 cars)*/
	int pos_house = 0; /*position 0 to 3 (there is 4 houses)*/
	int pos_suite = 0; /*position 0 to 12 (there is 13 cars per houses)*/

	/*loop throught all the houses*/
	while(pos_house < 4)
	{
		while(pos_suite < 13)
		{
			deck[pos_deck].id = pos_deck;

			/* set the value to 10 for jack, queen and king*/
			if(pos_suite < 10) deck[pos_deck].value = pos_suite + 1; /* arrays start at 0 :) */
			else deck[pos_deck].value = 10;

			deck[pos_deck].suit = pos_house;
			deck[pos_deck].position = pos_suite;
			deck[pos_deck].used = 0;

			pos_suite++;
			pos_deck++;
		}
		pos_suite = 0;
		pos_house++;
	}
}

int get_random(int end)
{
	int num;

	srand(time(0));
	num = rand() % end;
	return num;
}

void wait(int time)
{
	fflush(stdout);
	sleep(time);
}


int ask_to_bet(int money)
{
	int had_bet = 0;
	int bet = 0;

	printf("\nYou currently have %d$\n", money);
	printf("Place your bets: ");

	do
	{
		scanf("%d", &bet);
		if (bet > 0 && bet <= money) had_bet = 1;
		else
		{
			printf("\nThat is not possible, try again: ");
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
	
	printf("\nDo you want to stop here ? [yes=1/no=0]\n");
	while (had_choosed == 0)
	{
		scanf("%d", &awnser);
		if (awnser == 1 || awnser == 0) had_choosed = 1;

		else printf("\nThat is not possible, try again :\n");
	}
	return awnser;
}
