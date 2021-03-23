#ifndef CARD_MANIPULATE
#define CARD_MANIPULATE

/* shuffle the deck passed as argument */
void shuffle_deck(Deck_t* target);

/* return a random not used card from deck */
Card_t get_random_card(Deck_t* src);

/* return random number between 0 and cap argument */
/* REQUIRE MANUAL SRAND */
int rnd_nb(int cap);

#endif