#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define COLOR_RED "\x1b[1;31m"
#define COLOR_RESET "\x1b[0m"

struct Card
{	
	/* position in the deck */
	int id;

	/* what the card is worth */
	int value;

	/* clubs = 0, diamonds = 1, hearts = 2, spades = 3*/
	int suit;

	/* position of the card on the suit from 0 to 12 (0 is As 12 is king) */
	int position;

	/* 1 if the card has been used */
	int used;
	
	/* 1 if the card should be hidden */
	int hidden;
};

/* make a deck of 52 cards. */
struct Card deck[52];
struct Card player_hand[15];
struct Card dealer_hand[15];

int get_random(int end);
int ask_continue();
int ask_to_bet(int money);
int check_split();
int play_round(int *no_finish, int *pl_bet, int *pl_money, int *pl_nb, int round_count);

void check_score(int *pl_money, int *no_finsh, int *bet, int pl_score, int dl_score, int *quit_round);
void print_money(int money);
void print_bet(int bet);
void draw_card(struct Card *target, int *target_len, int is_hidden);
void face_up(struct Card *target, int *target_len);
void make_deck();
void clear_hands();
void wait(int time);
void print_card(int card_id);
void start_deal(int *pl_nb, int *dl_nb);
void get_dealer_hand(int *len, int *dl_score);
void get_player_hand(int *len, int *pl_score);
void handle_pl_win(int score);
void handle_pl_lose(int score);

int main(int ac, char **av)
{
	int player_money = 100;
	int quit_game = 0;
	int player_bet = 0;
	int quit_round = 0;
	int round_count = 0;
	int no_finish = 0;

	int pl_hand_nb = 0; /*number of cards the player have*/
	int dl_hand_nb = 0; /*number of cards the dealer have*/
	int player_score = 0;
	int dealer_score = 0;

	printf("\n\nHello, welcome to BlackJack :)\n\n");
	printf("If you dont know the rules, you can check them here\n");
	printf("en.wikipedia.org/wiki/Blackjack\n\n");

	while (quit_game == 0)
	{		
		printf("\nThe round start.\n");
		/* BET */
		player_bet = ask_to_bet(player_money);
		player_money -= player_bet;
		
		/* GAME  */
		printf("\n____________________________\n");
		printf("\nThe round start.\n");

		clear_hands();
		make_deck();
		
		start_deal(&pl_hand_nb, &dl_hand_nb);


		while (quit_round == 0)
		{
			/* clear standard outpout */
			system("clear");
			
			print_bet(player_bet);	
			printf("Round number %d\n", round_count + 1);
			
			/* Display all cards */
			get_dealer_hand(&dl_hand_nb, &dealer_score);
			get_player_hand(&pl_hand_nb, &player_score);
			
			check_score(&player_money, &no_finish, &player_bet, player_score, dealer_score, &quit_round);			

			if (quit_round == 0) 
			{
				quit_round = play_round(&no_finish, &player_bet, &player_money, &pl_hand_nb, round_count);
				round_count++;				
			}

			if(quit_round == 1 && no_finish == 0)
			{
				printf("Dealer turn...\n");
				
				face_up(dealer_hand, &dl_hand_nb);
				while(dealer_score < 17)
				{
					system("clear");
					print_bet(player_bet);	

					draw_card(dealer_hand, &dl_hand_nb, 0);
					get_dealer_hand(&dl_hand_nb, &dealer_score);
					get_player_hand(&pl_hand_nb, &player_score);
				}

				
				check_score(&player_money, &no_finish, &player_bet, player_score, dealer_score, &quit_round);			
			}
		}

		
		print_money(player_money);
		printf("The round is over.\n");
		/* END */
		quit_game = ask_continue();
	}

	return 0;
}

void start_deal(int *pl_nb, int *dl_nb)
{
	printf("Dealing...\n");

	/* add initials cards */
	draw_card(dealer_hand, dl_nb, 0);
	draw_card(player_hand, pl_nb, 0);	
	draw_card(player_hand, pl_nb, 0);
	draw_card(dealer_hand, dl_nb, 1);
}

int play_round(int *no_finish, int *pl_bet, int *pl_money, int *pl_nb, int round_count)
{
	int good_to_use = 0;
	int to_return = 0;
	char player_choice[10];
	int is_split_possible = check_split();

	printf("____________________________\n\n");
	printf("- hit\n");
	printf("- stand\n");
	/* printf("- double\n"); */
	/* if (is_split_possible == 1) printf("- split\n"); */
	if (round_count == 0) printf("- surrend\n");
	
	printf("\n");
	while(good_to_use == 0)
	{
		printf("Make your decision : ");
		scanf("%s", player_choice);
		
		if (is_split_possible == 1)
		{
			if (strcmp(player_choice, "split") == 0)
			{
				/* SPLIT */
			}
		}
		if (round_count == 0)
		{
			if (strcmp(player_choice, "surrend") == 0)
			{
				*pl_money += *pl_bet / 2;
				*no_finish = 1;
				to_return = 1;
				good_to_use = 1;
				printf("\nYou cashed in half your bet.");
			}
		}
		if(strcmp(player_choice, "hit") == 0)
		{
			draw_card(player_hand, pl_nb, 0);	
			good_to_use = 1;
		}
		if (strcmp(player_choice, "double") == 0)
		{
			/* DOUBLE */
		}
		if (strcmp(player_choice, "stand") == 0)
		{
			to_return = 1;
			good_to_use = 1;
		}
		if (good_to_use == 0) printf("\nThat is not possible...\n");
		return to_return;
	}
}

void check_score(int *pl_money, int *no_finsh, int *bet, int pl_score, int dl_score, int *quit_round)
{
	int pl_lose = 0;
	int dl_lose = 0;

	if (pl_score == 21)
	{
		handle_pl_win(pl_score);
		*pl_money += *bet * 2;
		dl_lose = 1;		
	}
	else if (dl_score == 21)
	{
		handle_pl_lose(pl_score);
		pl_lose = 1;	
	}

	else if (pl_score > 21)
	{
		handle_pl_lose(pl_score);
		pl_lose = 1;
	}
	else if (dl_score > 21)
	{
		handle_pl_win(pl_score);
		*pl_money += *bet * 2;
		dl_lose = 1;
	}

	if (*quit_round == 1 && pl_lose == 0 && dl_lose == 0)
	{
		if (pl_score > dl_score)
		{
			handle_pl_win(pl_score);
			*pl_money += *bet * 2;
			dl_lose = 1;
		}
		else if (dl_score > pl_score)
		{
			handle_pl_lose(pl_score);
			pl_lose = 1;
		}
		else
		{
			*pl_money += *bet * 2;
			handle_pl_win(pl_score);
		}
	}

	if (pl_lose == 1 || dl_lose == 1) *quit_round = 1;
}

void handle_pl_lose(int score)
{
	printf("\nYou lost! with: %d\n", score);
}

void handle_pl_win(int score)
{
	printf("\nYou win! with: %d\n", score);
}

int check_split()
{
	int to_return = 0;

	/* check if the first and the second card are the same */
	if(player_hand[0].position == player_hand[1].position) to_return = 1;

	return to_return; 
}

void face_up(struct Card *target, int *target_len)
{
	int i = 0;

	while (i < *target_len)
	{
		target[i].hidden = 0;
		deck[target[i].id].hidden = 0;
		i++;
	}
}

/* get the hand to target, and the number of cards the hand have
 * the function add another card to the targetted hand */
void draw_card(struct Card *target, int *target_len, int is_hidden)
{
	int drawn_card = -1;
	int random_num;

	while (drawn_card < 0)
	{
		random_num = get_random(51);

		if (deck[random_num].used == 0) drawn_card = deck[random_num].id;
	}

	target[*target_len].id = deck[random_num].id;
	target[*target_len].value = deck[random_num].value;
	target[*target_len].suit = deck[random_num].suit;
	target[*target_len].position = deck[random_num].position;
	target[*target_len].used = deck[random_num].used;
	target[*target_len].hidden = is_hidden;

	deck[random_num].used = 1;
	deck[random_num].hidden = is_hidden;
	*target_len += 1;
}

void print_card(int card_id)
{
	int id = deck[card_id].id;
	int val = deck[card_id].value;
	int suit = deck[card_id].suit;
	int pos = deck[card_id].position;
	int is_used = deck[card_id].used;
	int hidden = deck[card_id].hidden;

	char suit_to_display[4];
	char str_val[3];

	/* set suit to display */
	switch(suit)
	{
		case 0:
			strcpy(suit_to_display, "♣");
			break;
		case 1:
			strcpy(suit_to_display, "♦");
			break;
		case 2:
			strcpy(suit_to_display, "♥");
			break;
		case 3:
			strcpy(suit_to_display, "♠");
			break;
		default:
			strcpy(suit_to_display, "♠");
	}

	/* set card to display */
	switch (pos)
	{
		case 0:
			strcpy(str_val, "As");
			break;
		case 10:
			strcpy(str_val, "J");
			break;
		case 11:
			strcpy(str_val, "Q");
			break;
		case 12:
			strcpy(str_val, "K");
			break;
		default:
			sprintf(str_val, "%d", val);
	}	
	
	
	
	printf("| ");
	if (hidden == 1) printf("hidden");

	else if (suit == 1 || suit == 2) printf(COLOR_RED "%s %s" COLOR_RESET, str_val, suit_to_display);

	else printf("%s %s", str_val, suit_to_display);
	printf(" | ");
}


void make_deck()
{
	int pos_deck = 0; /*position 0 to 51 (there is 52 cars)*/
	int pos_house = 0; /*position 0 to 3 (there is 4 houses)*/
	int pos_suite = 0; /*position 0 to 12 (there is 13 cars per houses)*/

	/*loop throught all the houses*/
	while(pos_house < 4)
	{
		while(pos_suite < 13)
		{
			deck[pos_deck].id = pos_deck;

			/* set the value to 10 for jack, queen and king, 11 for the As */
			if (pos_suite == 0) deck[pos_deck].value = 11;
			else if(pos_suite < 10) deck[pos_deck].value = pos_suite + 1; /* arrays start at 0 :) */
			else deck[pos_deck].value = 10;

			deck[pos_deck].suit = pos_house;
			deck[pos_deck].position = pos_suite;
			deck[pos_deck].used = 0;
			deck[pos_deck].hidden = 0;

			pos_suite++;
			pos_deck++;
		}
		pos_suite = 0;
		pos_house++;
	}
}

int get_random(int end)
{
	int num;

	srand(time(0));
	num = rand() % end;
	return num;
}

/* count cards, score and print them, return the total of the dealer */
void get_dealer_hand(int *len, int *dl_score)
{
	int i = 0;
	int j = 0;
	int total = 0;
	int as_count = 0;

	printf("\nDealer's hand, %d cards:\n\n", *len);
	while (i < *len)
	{
		print_card(dealer_hand[i].id);
		if(dealer_hand[i].hidden == 0) total += dealer_hand[i].value;
		if(dealer_hand[i].position == 0) as_count++;
		i++;
	}

	/* check if the dealer have some As, if yes,
 	* for each As, when the score is above 21, it pass
 	* an As at 1 (score - 10) */
	if (as_count > 0)
	{
		while (j <= as_count)
		{
			if (total > 21) total -= 10;
			j++;
		}
	}

	printf("\n\ntotal: %d", total);
	printf("\n\n");
	*dl_score = total;
}

/* same as get_dealer_hand but for the player */
void get_player_hand(int *len, int *pl_score)
{
	int i = 0;
	int j = 0;
	int total = 0;
	int as_count = 0;

	printf("\nYour hand, %d cards:\n\n", *len);
	while(i < *len)
	{
		print_card(player_hand[i].id);
		total += player_hand[i].value;
		if(player_hand[i].position == 0) as_count++;
		i++;
	}
	
	/* same as in get_dealer_hand */
	if (as_count > 0)
	{
		while (j < as_count)
		{
			if  (total > 21) total -= 10;
			j++;
		}
	}

	printf("\n\ntotal: %d", total);
	printf("\n\n");
	*pl_score = total;
}

void wait(int time)
{
	fflush(stdout);
	sleep(time);
}


int ask_to_bet(int money)
{
	int had_bet = 0;
	int bet = 0;

	printf("Place your bets: ");
	print_money(money);
	do
	{
		scanf("%d", &bet);
		if (bet > 0 && bet <= money) had_bet = 1;
		else
		{
			printf("\nThat is not possible, try again: ");
		}
	}
	while (had_bet == 0);

	print_bet(bet);
	return bet;
}

void print_money(int money)
{
	printf("\nYou currently have %d$\n", money);
}

void print_bet(int bet)
{
	printf("\nYou have betted %d$\n", bet);
}

int ask_continue()
{	
	int awnser;
	int had_choosed = 0;
	
	printf("\nDo you want to stop here ? [yes=1/no=0]\n");
	while (had_choosed == 0)
	{
		scanf("%d", &awnser);
		if (awnser == 1 || awnser == 0) had_choosed = 1;

		else printf("\nThat is not possible, try again :\n");
	}
	return awnser;
}

void clear_hands()
{
	int i = 0;

	while (i < 15)
	{
		dealer_hand[i].id = 0;
		dealer_hand[i].value = 0;
		dealer_hand[i].suit = 0;
		dealer_hand[i].position = 0;
		dealer_hand[i].used = 0;
		dealer_hand[i].hidden = 0;
		i++;
	}

	i = 0;

	while (i < 15)
	{
		player_hand[i].id = 0;
		player_hand[i].value = 0;
		player_hand[i].suit = 0;
		player_hand[i].position = 0;
		player_hand[i].used = 0;
		player_hand[i].hidden = 0;
		i++;
	}

	i = 0;

	while (i < 52) 
	{
		deck[i].hidden = 0;
		i++;
	}
}
