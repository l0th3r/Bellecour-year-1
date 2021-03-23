#include "solitaire.h"

Board_t* init_board(void);

int main(int ac, char** av)
{
    time_t t;
    
    init_deck();
    srand((unsigned)time(&t));

    ui_init();

    game_loop();

    ui_close();
    return 0;
}

void start_board()
{
    int i = 0;
    int j = 0;
    int k = 0;
    int cap;

    Deck_t* deck = init_deck();
    Board_t* board = init_board();

    /* fill side with empty cards */
    while(i < board->side_s)
    {
        board->side[i] = create_card(0, -1, 0);
        i++;
    }

    i = 0;
    while(i < board->col_s)
    {
        if(i < 3)
            cap = 8;
        else if(cap > 1)
            cap -= 1;

        j = 0;
        /* loop to place cards */
        while(j < cap)
        {
            board->pile[i][j] = deck->pile[k];
            deck->pile[k].is_used = 1;
            j++;
            k++;
        }
        /* place other slots as empty */
        while(j < board->row_s)
        {
            board->pile[i][j] = create_card(0, -1, 0);
            j++;
        }
        i++;
    }
}

Board_t* init_board(void)
{
    static Board_t* board = NULL;

    if (!board)
    {
        board = create_board(10, 13, 4);
        start_board();
    }

    return board;
}

Deck_t* init_deck(void)
{
    static Deck_t* deck = NULL;

    if (!deck)
    {
        deck = create_classic_52();
        shuffle_deck(deck);
    }

    return deck;
}

Player_t* init_player(void)
{
    static Player_t* player = NULL;

    if (!player)
    {
        player = malloc(sizeof(Player_t));
        if(player)
        {
            player->selected_c = 0;
            player->selected_l = 0;
            player->select = create_card(0, -1, 0);
        }
    }

    return player;
}

void reset_game()
{
    free(init_board());
    free(init_deck());

    init_board();
    init_deck();
}

int str_len(char* str)
{
    int i = 0;
    while(str[i] != '\0')
        i++;

    return i;
}