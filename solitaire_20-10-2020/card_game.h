#ifndef CARDGAME
#define CARDGAME


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

char* print_card(int card_id);

void draw_card(struct Card *target, int *target_len, int is_hidden);
void face_up(struct Card *target, int *target_len);
void make_deck();
void wait(int time);


#endif