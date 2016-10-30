#include "battleship_functions.h"
#include "battleship_functions.c"

int main(void) {
  //Variables initialized; seed created for rand()
  srand((unsigned int) (time NULL));
  char player_board[10][10], player_sunk_ships[5];
  char computer_board[10][10], computer_sunk_ships[5];
  int height = 0, width = 0, current_player = 0;

  //Sets up the games
  initialize_game_board(player_board);
  initialize_game_board(computer_board);
  manually_place_ships(player_board);
  randomly_place_ships(computer_board);
  current_player = select_who_starts_first();

  //Plays the game
  while (!is_winner(player_board) && !is_winner(computer_board)) {
    if (current_player == 1)
    {
      play_shot(computer_board, PLAYER1);
      display_board(computer_board, PLAYER2); //Displays the computer's board
      current_player = 2;
    }
    else if (current_player == 2)
    {
      play_shot(player_board, PLAYER2);
      display_board(player_board, PLAYER1); //Displays the player's board
      current_player = 1;
    }
  }

  //Determines who the winner is
  if (is_winner(computer_board))
  {
    printf("Congratulations! Player 1 wins!\n");
  }
  if (is_winner(player_board))
  {
    printf("Damn! The computer won!\n");
    printf("The machines are rising...\n");
  }

  return 0;
}

/*
NOTES:
  -give the computer some AI (teach it to shoot accurrately after a hit)
  -perhaps teach it to, upon a hit, start guessing around the hit
  -once it gets 2 in a row, guess in a line until the ship is sunk

  -also, add code to output stats to file
  -clean up print statements, clear screen (make it pretty!)
  -"beautify" code
*/
