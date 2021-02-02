#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int ac, char **av) {
  
  printf("\nWelcome at the Roulette game !\n\n");

  int stop = 0;
  int playerMoney = 100;

	//while the player want to continue
  while (stop == 0) {

		int playerChoice = 0;
		int betPlaced = 0;
    int playerBet = 0;
		int isColored = 0;

		//generate the random number
    srand(time(0));
    int randNumber = rand() % (36 + 1);

    printf("You currently have %d$\n", playerMoney);

		//check if the player as enough money
    if (playerMoney < 1) {
      printf("You can't play with %d$\n", playerMoney);
      printf("\nSee you later !\n\n");
      return 0;
    }

    printf("Place your bets !\n");

		//while no bets have been placed
    while (betPlaced == 0) {
			scanf("%d", &playerBet);
	
			//check if the placed bet is superior as player money or inferior to 1
			if (playerBet > playerMoney || playerBet < 1) {
        printf("You dont have the money for that...\n");
        printf("Try again :\n");
      } else {
        betPlaced = 1;
      }
    }

    printf("\nYou betted %d$\n", playerBet);

		//ask the player on what he want to bet 
    printf("\nNow, do you want to bet on a color or a number ? [color = 1 number = 0]\n");
    scanf("%d", &isColored);

    if (isColored == 1) {

			//EVEN = BLACK on roulette
			//ODD = RED on roulette

      printf("What color do you bet on ? [red or black]\n");

      char playerGuess[6];
      int isPlayerGuessEven = 0;
      int goodToUse = 0;
			int isResultEven = 0;

			//while the user guess is not valid
      while (goodToUse == 0) {

        scanf("%s", playerGuess);
        printf("\nYou guessed %s\n", playerGuess);

        if (strcmp(playerGuess, "red") == 0) {
          goodToUse = 1;
        } else if (strcmp(playerGuess, "black") == 0) {
          isPlayerGuessEven = 1;
          goodToUse = 1;
        } else {
          printf("And that is not a valid color, we need 'red' or 'black'\n");
          printf("\nTry again :\n");
        }
      }

			//set if random number is even
      if (randNumber % 2 == 0) {
        isResultEven = 1;
      }

			// vv Dev purpose only vv
			
			//printf("\n\nTO GUESS : %d\n", randNumber);
			//printf("\nPLAYER ASKED : %s\n", playerGuess);
			//printf("\nIS RESULT EVEN (BLACK) : %d\n", isResultEven);
			//printf("\nIS PLAYER GUESS EVEN (BLACK) : %d\n\n", isPlayerGuessEven);
			
			// ^^ Dev purpose only ^^

			//check if the result match the random number
      if (isPlayerGuessEven == 1 && isResultEven == 1) {
        printf("\nAnd you were right ! You have won %d$ ", playerBet * 2);
        playerMoney += playerBet * 3;
      } else if (isPlayerGuessEven == 0 && isResultEven == 0) {
        printf("\nAnd you were right ! You have won %d$ ", playerBet * 2);
        playerMoney += playerBet * 3;
      } else {
        printf("\nAnd you were wrong... You have lost %d$ ", playerBet);
        playerMoney -=  playerBet;
      }

    } else {

      printf("What number do you bet on ?\n");
      
      int playerGuess;
      int goodToUse = 0;

			//while the user guess is not valid
      while (goodToUse == 0) {

        scanf("%d", &playerGuess);
        printf("\nYou guessed %d\n", playerGuess);

				//check if player's guess is valid (bewteen 0 and 36)
        if (playerGuess > 36 || playerGuess < 0) {
          printf("And that is not a valid number, we need a number between 0 and 36\n");
          printf("\nTry again :\n");
        } else {
          goodToUse = 1;
        }
      }

			//verify the result (compare player's guess and the random number)
      if (randNumber == playerGuess) {
      	printf("\nAnd you were right ! You have won %d$ ", playerBet * 37);
      	playerMoney += playerBet * 3;
      } else {
        printf("\nAnd you were wrong... You have lost %d$ ", playerBet);
        playerMoney -=  playerBet;
      }

    }

    printf("The Number to guess was %d.\n", randNumber);

    printf("\nYou currently have %d$ left.\n", playerMoney);

    printf("Do you wish to continue ? [yes = 1 no = 0]\n");
    
		//ask the player if he want to continue
    scanf("%d", &playerChoice);
    if (playerChoice != 1) {
      stop = 1;
    }
  }

  return 0;
}