#include "../includes.h"

void shuffle_deck(Deck_t* target)
{
    time_t t;
    int i = 0;
    int err = 0;

    Deck_t* d_temp = create_classic_52();
    Card_t c_tmp;

    /* generate seed for random */
    srand((unsigned)time(&t));

    while(i < target->size - 5 && err == 0)
    {
        c_tmp = get_random_card(d_temp);
        if(c_tmp.suit == -1)
            err++;
        else
            target->pile[i] = c_tmp;
        i++;
    }

    dest_deck(d_temp);
}

Card_t get_random_card(Deck_t* src)
{
    int is_good = 0;
    int counter = 0;
    int rnd;
    Card_t temp;

    while(is_good == 0)
    {
        if(counter < src->size)
        {
            rnd = rnd_nb(src->size - 1);
            temp = src->pile[rnd];

            if(temp.is_used == 0)
            {
                src->pile[rnd].is_used = 1;
                is_good = 1;
            }
            counter++;
        }
        else
        {
            temp = create_card(0, -1, 0);
            is_good = 1;
        }
    }

    return temp;
}

int rnd_nb(int cap)
{
    return rand() % cap;
}