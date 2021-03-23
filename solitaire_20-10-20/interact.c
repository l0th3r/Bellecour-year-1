#include "solitaire.h"


void game_loop()
{
    int is_good = 0;

    while(is_good == 0)
    {
        ui_print_board();
        board_choice();
    }
}

int board_choice()
{
    Player_t* player = init_player();
    int choice;
    choice = wgetch(win_pla);
    
    switch(choice)
	{
	    case 259:
            if(player->selected_l > 0)
            {
                player->selected_l--;
            }
		break;
		case 258:
            if(player->selected_l < 12)
            {
                player->selected_l++;
            }
		break;
        case 260:
            if(player->selected_c > 0)
            {
                player->selected_c--;
            }
        break;
        case 261:
            if(player->selected_c < 9)
            {
                player->selected_c++;
            }
		break;
        case 10:
            select_card(player->selected_l, player->selected_c);
        break;
    }

    return choice;
}

void select_card(int l, int c)
{
    Board_t* board = init_board();
    Player_t* player = init_player();

    /* check if selection is to select */
    if(board->pile[c][l].suit != -1 && player->select.suit == -1)
    {
        player->selected_l = l;
        player->selected_c = c;

        player->select = board->pile[c][l];
    }
    else if(player->select.suit != -1 && board->pile[c][l].suit != -1)
        player->select = create_card(0, -1, 0);
    else if(board->pile[c][l].suit == -1 && player->select.suit != -1) /* check if selection to place card */
    {
        if(l > 0)
        {
            /* check if the card abouve is +1 */
            if((board->pile[c][l - 1].position - 1) == player->select.position)
            {
                board->pile[c][l] = player->select;
                player->select = create_card(0, -1, 0);
            }
        }
    }
}