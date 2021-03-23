#ifndef CARD_TYPES
#define CARD_TYPES

/* create types */
typedef struct
{	
	/* position in the deck */
	int id;

	/*empty = -1, clubs = 0, diamonds = 1, hearts = 2, spades = 3, joker = 4 */
	int suit;

	/* position of the card on the suit from 0 to 12 (0 is As 12 is king) */
	int position;
	
	/* 1 if the card should be hidden */
	int hidden;

	/* 1 if the card is placed or still in the deck */
	int is_used;
} Card_t;

typedef struct
{
	Card_t* pile;
	size_t size;
	size_t j_nb;
} Deck_t;

typedef struct
{
	Card_t* pile;
	size_t cap;
	size_t count;
} Hand_t;

typedef struct
{
	Card_t** pile; 	/* main board, pile[col][row] */
	Card_t* side; 	/* side cards */
	size_t side_s; 	/* amount of side cards */
	size_t col_s; 	/* amount of colomns */
	size_t row_s; 	/* amount of rows */
} Board_t;

/* allocate */
Card_t create_card(int id, int suit, int position);
Deck_t* create_deck(int length, int joker_len, int gap_start, int gap_end);
Board_t* create_board(size_t col_amount, size_t row_amount, size_t side_size);
Deck_t* create_classic_52();
Deck_t* create_classic_32();

/* destroy */
void dest_deck(Deck_t* target);
void dest_hand(Hand_t* target);
void dest_board(Board_t* target);

#endif