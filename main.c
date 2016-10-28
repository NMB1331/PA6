#include "battleship_functions.h"
#include "battleship_functions.c"

int main(void) {
  //Variables initialized; seed created for rand()
  srand((unsigned int) (time NULL));
  char player_board[10][10];
  char computer_board[10][10];
  int height = 0, width = 0;
  char direction = '\0';

  initialize_game_board(player_board);
  manually_place_ships(player_board);


  return 0;
}

/*
NOTES:
  -modify place_ship to be more like the random placement (create function to get/check direction)
  -modify print_board() to not print ship locations for player 2
  -check_if_ship_sunk should take a single character input, and just check the array for that character

*/
