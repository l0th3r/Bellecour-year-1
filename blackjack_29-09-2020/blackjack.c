#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define COLOR_RED "\x1b[1;31m"
#define COLOR_RESET "\x1b[0m"

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

	/* 1 if the card has been used */
	int used;
	
	/* 1 if the card should be hidden */
	int hidden;
};

/* make a deck of 52 cards. */
struct Card deck[52];
struct Card player_hand[15];
struct Card dealer_hand[15];

int get_random(int end);
int ask_continue();
int ask_to_bet(int money);

void draw_card(struct Card *target, int *target_pos, int is_hidden);
void make_deck();
void wait(int time);
void print_card(int card_id);
void start_deal(int *pl_nb, int *dl_nb);
int get_dealer_hand(int *len);
int get_player_hand(int *len);

int main(int ac, char **av)
{
	int player_money = 100;
	int quit_game = 0;
	int player_bet = 0;
	int quit_round = 0;

	int pl_hand_nb = 0; /*number of cards the player have*/
	int dl_hand_nb = 0; /*number of cards the dealer have*/
	int player_score = 0;
	int dealer_score = 0;

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
		
		start_deal(&pl_hand_nb, &dl_hand_nb);
		
		
		while (quit_round == 0)
		{
			quit_round = 1;
		}

		get_dealer_hand(&dl_hand_nb);
		get_player_hand(&pl_hand_nb);

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

	/* add initials cards */
	draw_card(dealer_hand, dl_nb, 0);
	draw_card(player_hand, pl_nb, 0);
	draw_card(player_hand, pl_nb, 0);	
	draw_card(dealer_hand, dl_nb, 1);
}

/* get the hand to target, and the number of cards the hand have
 * the function add another card to the targetted hand */
void draw_card(struct Card *target, int *target_len, int is_hidden)
{
	int drawn_card = -1;
	int random_num;

	while (drawn_card < 0)
	{
		random_num = get_random(51);

		if (deck[random_num].used == 0) drawn_card = deck[random_num].id;
	}

	target[*target_len].id = deck[random_num].id;
	target[*target_len].value = deck[random_num].value;
	target[*target_len].suit = deck[random_num].suit;
	target[*target_len].position = deck[random_num].position;
	target[*target_len].used = deck[random_num].used;
	target[*target_len].hidden = is_hidden;

	deck[random_num].used = 1;
	deck[random_num].hidden = is_hidden;
	*target_len += 1;
}

void print_card(int card_id)
{
	int id = deck[card_id].id;
	int val = deck[card_id].value;
	int suit = deck[card_id].suit;
	int pos = deck[card_id].position;
	int is_used = deck[card_id].used;
	int hidden = deck[card_id].hidden;

	char suit_to_display[4];
	char str_val[3];

	/* set suit to display */
	switch(suit)
	{
		case 0:
			strcpy(suit_to_display, "♣");
			break;
		case 1:
			strcpy(suit_to_display, "♦");
			break;
		case 2:
			strcpy(suit_to_display, "♥");
			break;
		case 3:
			strcpy(suit_to_display, "♠");
			break;
		default:
			strcpy(suit_to_display, "♠");
	}

	/* set card to display */
	switch (pos)
	{
		case 0:
			strcpy(str_val, "As");
			break;
		case 10:
			strcpy(str_val, "J");
			break;
		case 11:
			strcpy(str_val, "Q");
			break;
		case 12:
			strcpy(str_val, "K");
			break;
		default:
			sprintf(str_val, "%d", val);
	}	
	
	
	
	printf("| ");
	if (hidden == 1) printf("hidden");
	else if (suit == 1 || suit == 2) printf(COLOR_RED "%s %s" COLOR_RESET, str_val, suit_to_display);
	else printf("%s %s", str_val, suit_to_display);
	printf(" | ");
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
			deck[pos_deck].hidden = 0;

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


int get_dealer_hand(int *len)
{
	int i = 0;
	int j = 0;
	int total = 0;
	int as_count = 0;

	printf("\nDealer's hand, %d cards :\n", *len);
	while (i < *len)
	{
		print_card(dealer_hand[i].id);
		total += dealer_hand[i].value;
		i++;
	}

	/* check if the dealer have some As, if yes,
 	* for each As, when the score is above 21, it pass
 	* an As at 1 (score - 10) */
	if (as_count > 0)
	{
		while (j < as_count)
		{
			if (total > 21) total -= 10;
			j++;
		}
	}

	printf("\ntotal: %d", total);
	printf("\n\n");
	return total;
}

int get_player_hand(int *len)
{
	int i = 0;
	int j = 0;
	int total = 0;
	int as_count = 0;

	printf("\nYour hand, %d cards :\n", *len);
	while(i < *len)
	{
		print_card(player_hand[i].id);
		total += player_hand[i].value;
		i++;
	}

	if (as_count > 0)
	{
		while (j < as_count)
		{
			if  (total > 21) total -= 10;
			j++;
		}
	}

	printf("\ntotal: %d", total);
	printf("\n\n");
	return total;
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
