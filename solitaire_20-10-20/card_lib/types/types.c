#include "../includes.h"

Card_t create_card(int id, int suit, int position)
{
	Card_t card;

	card.id = id;
	card.suit = suit;
	card.position = position;
	card.hidden = 0;
	card.is_used = 0;

	return card;
}

Deck_t* create_deck(int length, int joker_len, int gap_start, int gap_end)
{
	int i = 0;
	int j = 0;
	int k = 0;

	Deck_t *deck = malloc(sizeof(Deck_t));

	if(deck)
	{
		/* allocate the pile */
		deck->pile = malloc(sizeof(Card_t) * (length + joker_len));

		if(deck->pile)
		{
			/* create cards */
			/* loop through suits */
			while(j < 4)
			{	
				/* loop through each suit */
				k = 0;
				while(k < 13)
				{
					/* only if the card is not in the gap */
					if(k < gap_start - 1 || k > gap_end - 1)
					{
						deck->pile[i] = create_card(i, j, k);
						i++;
					}
					k++;
				}
				j++;
			}

			/* create joker cards */
			j = 0;
			while(j < joker_len)
			{
				deck->pile[i] = create_card(i, 4, j);
				j++;
				i++;
			}
		}

		deck->size = length + joker_len;
		deck->j_nb = joker_len;
	}
	return deck;
}

Board_t* create_board(size_t col_amount, size_t row_amount, size_t side_size)
{
	int i = 0;
	int err = 0;
	Board_t* to_return;

	/* allocate board */
	to_return = malloc(sizeof(Board_t));

	if(to_return)
	{
		to_return->side = malloc(sizeof(Card_t) * side_size);

		if(to_return->side)
		{
			/* allocate each cols */
			to_return->pile = malloc(sizeof(Card_t) * col_amount);

			if(to_return->pile)
			{
				/* allocate each col's row */
				while(i < col_amount)
				{
					to_return->pile[i] = malloc(sizeof(Card_t) * row_amount);

					/* check allocation */
					if(!to_return->pile[i])
						err++;

					i++;
				}

				/* if malloc failed*/
				if(err > 0)
				{
					i = 0;
					while(i < col_amount)
					{
						free(to_return->pile[i]);
						i++;
					}
					free(to_return->pile);
					free(to_return);
				}
				else
				{
					to_return->side_s = side_size;
					to_return->col_s = col_amount;
					to_return->row_s = row_amount;
				}
			}
			else
			{
				free(to_return->side);
				free(to_return);
			}
		}
		else
			free(to_return);
	}

	return to_return;
}

Deck_t* create_classic_52()
{
	return create_deck(52, 0, 14, -1);
}

Deck_t* create_classic_32()
{
	return create_deck(32, 0, 2, 6);
}

Hand_t create_hand(int cap)
{
	Hand_t hand;

	hand.pile = malloc(sizeof(Card_t));
	hand.count = 0;
	hand.cap = cap;

	return hand;
}

void dest_deck(Deck_t* target)
{
	free(target->pile);
	free(target);
}

void dest_hand(Hand_t* target)
{
	free(target->pile);
	free(target);
}

void dest_board(Board_t* target)
{
	int i = 0;
	while(i < target->col_s)
	{
		free(target->pile[i]);
		i++;
	}
	free(target->pile);
	free(target);
}