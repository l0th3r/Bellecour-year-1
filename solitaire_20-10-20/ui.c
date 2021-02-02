#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <ncurses.h>

#include "card_game.h"

struct Card board[10][15];

WINDOW * win_top;
WINDOW * win_pla;

void ui_init();
void ui_refresh();
void ui_close();
void ui_print_board();

void ui_print_board()
{
    int i = 0;
    int j = 0;
    int k = 5;
    int is_good = 0;
    int selected_c = 1;
    int selected_l = 1;
    int choice;
    char* temp;

    start_color();
    keypad(win_pla, true);
    init_pair(1, COLOR_RED, COLOR_BLACK);

    while(is_good == 0)
    {
        i = 0;
        k = 5;
        while(i < 10)
        {
            j = 0;
            while(j < 13)
            {
                if(selected_c == i && selected_l == j)
                    wattron(win_pla, A_REVERSE);
                
                temp = print_card(board[i][j].id);
                if(board[i][j].suit > 0 && board[i][j].suit < 3)
                    wattron(win_pla, COLOR_PAIR(1));

                mvwprintw(win_pla, j + 2, k, "%s", temp);
                wattroff(win_pla, COLOR_PAIR(1));
                wattroff(win_pla, A_REVERSE);
                j++;
            }
            k += 9;
            i++;
        }

        wrefresh(win_pla);

        choice = wgetch(win_pla);

        switch(choice)
		{
			case 259:
                if(selected_l > 0)
                    selected_l--;
				break;
			case 258:
                if(selected_l < 12)
                    selected_l++;
				break;
            case 260:
                if(selected_c > 0)
                    selected_c--;
				break;
            case 261:
                if(selected_c < 9)
                    selected_c++;
				break;
            default:
				break;
		}
		if(choice == 10)
			is_good = 1;
    }
    free(temp);
}

void ui_init()
{
    int height;
    int width;
    WINDOW * main;

    /* ncurses init */
    initscr();
	noecho();
	cbreak();
    curs_set(0);

    getmaxyx(stdscr, height, width);

    main = newwin(height, width, 0, 0);
    box(main, 0, 0);
    refresh();

    mvwprintw(main, 2, 2, "Welcome in the solitaire game !");
    mvwprintw(main, 3, 2, "The solitaire is a Simple Simon.");
    mvwprintw(main, 4, 2, "You can check the rules here: wikipedia.org/wiki/Simple_Simon_(solitaire)#Rules");
    mvwprintw(main, 6, 2, "You can move with the arrow keys and press enter to select a card.");
    mvwprintw(main, 7, 2, "Press enter to continue...");

    keypad(main, true);
    wrefresh(main);

    while(wgetch(main) != 10);

    delwin(main);
    refresh();
    /* setup random seed */
    srand(time(NULL));

    win_top = newwin(0, 0, 0, 0);
    win_pla = newwin(0, 0, 0, 0);

    ui_refresh();
}

void ui_refresh()
{
    int height;
    int width;
    int top_w;
    int top_h;
    int pla_w;
    int pla_h;

    getmaxyx(stdscr, height, width);

    top_w = width;
    top_h = 10;
    pla_w = width;
    pla_h = height - top_h - 1;

    delwin(win_top);
    delwin(win_pla);

	win_top = newwin(top_h, top_w, 0, 0);
    box(win_top, 0, 0);

    win_pla = newwin(pla_h, pla_w, top_h, 0);
    box(win_pla, 0, 0);


    mvwprintw(win_top, 1, 2, "Controls:");
    mvwprintw(win_top, 2, 2, "Go up: up arrow");
    mvwprintw(win_top, 3, 2, "Go down: down arrow");
    mvwprintw(win_top, 4, 2, "Go right: right arrow");
    mvwprintw(win_top, 5, 2, "Go left: left arrow");
    mvwprintw(win_top, 7, 2, "You can check the rules here: wikipedia.org/wiki/Simple_Simon_(solitaire)#Rules");

    refresh();
    wrefresh(win_top);
    wrefresh(win_pla);
}

void ui_close()
{
    /* deallocates memory and ends ncurses  */
	endwin();
}