#ifndef _SOL_INTERACT_
#define _SOL_INTERACT_

void game_loop();

int board_choice();

/* define player's selected card */
/* l = board's line, c = board's colomn */
void select_card(int l, int c);

#endif