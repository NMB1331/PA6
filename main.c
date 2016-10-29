#include "battleship_functions.h"
#include "battleship_functions.c"

int main(void) {
  //Variables initialized; seed created for rand()
  srand((unsigned int) (time NULL));
  char player_board[10][10], player_sunk_ships[5];
  char computer_board[10][10], computer_sunk_ships[5];
  int height = 0, width = 0, counter = 0;
  char direction = '\0';

  initialize_game_board(player_board);
  initialize_game_board(computer_board);
  randomly_place_ships(player_board);
  randomly_place_ships(computer_board);
  display_board(player_board, PLAYER1);
  display_board(computer_board, PLAYER2);

  //For debugging
  while (counter < 10)
  {
    play_shot(computer_board, PLAYER1);
    display_board(computer_board, PLAYER2);
    counter++;
  }



  return 0;
}

/*
NOTES:
  -modify print_board() to not print ship locations for player 2
  -check_if_ship_sunk should take a single character input, and just check the array for that character

*/
