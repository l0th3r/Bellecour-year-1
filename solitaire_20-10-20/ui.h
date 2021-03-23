#ifndef _SOL_UI_
#define _SOL_UI_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <ncurses.h>

extern WINDOW * win_top;
extern WINDOW * win_pla;

void ui_init();
void ui_refresh();
void ui_close();
void ui_print_board();
void debug(char* str);


#endif