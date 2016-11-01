#include "battleship_functions.h"
#include "battleship_functions.c"

int main(void) {
  //Variables initialized; seed created for rand()
  srand((unsigned int) (time NULL));
  char player_board[10][10], p1_remaining_ships[5] = {'c', 's', 'r', 'b', 'd'};
  char computer_board[10][10], p2_remaining_ships[5] = {'c', 's', 'r', 'b', 'd'};
  Stats p1_stats = {0,0,0,0.0};
  Stats p2_stats = {0,0,0,0.0};

  //Sets up the games
  initialize_game_board(player_board);
  initialize_game_board(computer_board);
  place_player_ships(player_board);
  //system("pause");
  //system("cls");
  randomly_place_ships(computer_board);
  int current_player = select_who_starts_first();

  //Plays the game
  while (!is_winner(player_board) && !is_winner(computer_board)) {
    if (current_player == 1)
    {
      play_shot(computer_board, PLAYER1);
      display_board(computer_board, PLAYER2);
      notify_player_ship_sunk(computer_board, p2_remaining_ships);
      current_player = 2;
      //system("pause");
      //system("cls");
    }
    else if (current_player == 2)
    {
      play_shot(player_board, PLAYER2);
      display_board(player_board, PLAYER1);
      current_player = 1;
      //system("pause");
      //system("cls");
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
  -prompt player to choose ship locations or have them be random
  -


AI:
  -create float probability array, adjust after every shot
  -have the computer shoot at the highest probability
  -recalculate based on hit, miss, sink
  -switch between hunt/target mode

  -have the computer tell the user when a ship has been sunk, and which one
  -give the computer some AI (teach it to shoot accurrately after a hit)


  -also, add code to output stats to file
  -clean up print statements, clear screen (make it pretty!)
  -"beautify" code
*/
