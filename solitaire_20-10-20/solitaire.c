#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#include "card_game.h"
#include "ui.h"

int main(int ac, char** av)
{
    /* setup the UI */
    ui_init();

    /* setup cards */
    make_deck();
    make_board();
    ui_print_board();

    ui_close();
    return 0;
}

int str_len(char* str)
{
    int i = 0;
    while(str[i] != '\0')
        i++;

    return i;
}