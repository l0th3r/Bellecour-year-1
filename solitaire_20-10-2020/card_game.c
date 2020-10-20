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

int get_random(int end);

void draw_card(struct Card *target, int *target_len, int is_hidden);
void face_up(struct Card *target, int *target_len);
void make_deck();
void wait(int time);
void print_card(int card_id);


void face_up(struct Card *target, int *target_len)
{
	int i = 0;

	while (i < *target_len)
	{
		target[i].hidden = 0;
		deck[target[i].id].hidden = 0;
		i++;
	}
}

/* get the targetted hand, and the number of cards the hand have
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
	if (hidden == 1)
		printf("hidden");
	else if (suit == 1 || suit == 2)
		printf(COLOR_RED "%s %s" COLOR_RESET, str_val, suit_to_display);
	else
		printf("%s %s", str_val, suit_to_display);

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

			/* set the value to 10 for jack, queen and king, 11 for the As */
			if (pos_suite == 0) deck[pos_deck].value = 11;
			else if(pos_suite < 10) deck[pos_deck].value = pos_suite + 1; /* arrays start at 0 :) */
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

/* time in seconds */
void wait(int time)
{
	fflush(stdout);
	sleep(time);
}
