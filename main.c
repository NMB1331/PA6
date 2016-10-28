#include "battleship_functions.h"
#include "battleship_functions.c"

int main(void) {
  //Variables initialized; seed created for rand()
  srand((unsigned int) (time NULL));
  char player_board[10][10];
  char computer_board[10][10];
  int height = 0, width = 0;
  char direction = '\0';

  initialize_game_board(computer_board);
  randomly_place_ships(computer_board);
  display_board(computer_board);



  return 0;
}

/*
NOTES:
  -add logic to check if space has already been taken by another ship
  -modify print_board() to not print ship locations for player 2
  -when the player is placing ships, make them start over if they go out (add length of ship to first point in direction of ship)
  -check_if_ship_sunk should take a single character input, and just check the array for that character
  -.....fucking shit. Possibly change all of the 10's to 9's
*/
