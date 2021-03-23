#include "solitaire.h"

WINDOW * win_top;
WINDOW * win_pla;

void ui_print_board()
{
    int i = 0;
    int j = 0;
    int k = 4;
    int selected_c;
    int selected_l;
    char* temp;

    /* get board and player */
    Board_t* board = init_board();
    Player_t* player = init_player();

    start_color();
    keypad(win_pla, true);
    curs_set(0);
    init_pair(1, COLOR_RED, COLOR_BLACK);

    selected_l = player->selected_l;
    selected_c = player->selected_c;

    /* print side slots */
    i = 0;
    k += (9 * 5); /* jump 3 cards slots */
    while(i < board->side_s)
    {
        temp = get_card(board->side[i]);
        mvwprintw(win_pla, j + 2, k, "%s", temp);
        i++;
        k+=9;
    }

    mvwprintw(win_pla, j + 2, 4, "Selected card: %s", get_card(player->select));

    /* print board slots */
    i = 0;
    k = 4;
    while(i < board->col_s)
    {
        j = 0;
        while(j < board->row_s)
        {
            if(selected_c == i && selected_l == j)
                wattron(win_pla, A_REVERSE);
            
            temp = get_card(board->pile[i][j]);
                
            if(board->pile[i][j].suit > 0 && board->pile[i][j].suit < 3)
                wattron(win_pla, COLOR_PAIR(1));

            mvwprintw(win_pla, j + 4, k, "%s", temp);

            wattroff(win_pla, COLOR_PAIR(1));
            wattroff(win_pla, A_REVERSE);
            j++;
        }
        k += 9;
        i++;
    }
    wrefresh(win_pla);
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

void debug(char* str)
{
    mvwprintw(win_top, 3, 50, "*** DEBUG = %s ***", str);
    wrefresh(win_top);
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
    /* deallocates memory and end ncurses  */
	endwin();
}