#ifndef _SOLITAIRE_
#define _SOLITAIRE_

#include "card_lib/includes.h"
#include "ui.h"
#include "interact.h"

typedef struct
{
    Card_t select;
    int selected_c;
    int selected_l;
} Player_t;

Board_t* init_board(void);
Deck_t* init_deck(void);
Player_t* init_player(void);

/* set up the board */
void start_board();

/* return 1 if the selected card is usable */
int check_selection();

/* reset the bord and deck */
void reset_game();

#endif