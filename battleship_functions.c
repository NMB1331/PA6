#include "battleship_functions.h"

//Function that resets the game board (fills with '~')
void initialize_game_board(char board[10][10]) {
  for (int i=0; i<BOARD_SIZE; i++) {
    for (int j=0; j<BOARD_SIZE; j++) {
      board[i][j] = '~'; }
  }
}

//Function that prints the game board
void display_board(char board[10][10]) {
  for (int i=0; i<BOARD_SIZE; i++) {
    for (int j=0; j<BOARD_SIZE; j++) {
      printf("%c", board[i][j]); }
    printf("\n");
  }
  printf("\n");
}

//Determines who starts first
int select_who_starts_first(void) {
  //Variables declared; Secret number and computer guess chosen
  int user_guess = 0, random_number = rand() % 10 + 1, computer_guess = 0;
  while (computer_guess == 0 || computer_guess == random_number) {
    computer_guess = rand() % 10 + 1; }
  //User guess made
  printf("To see who starts first, we're going to play a guessing game!\n");
  printf("We're going to pick numbers between 1 and 10, and see who's closer.\n");
  printf("The computer guessed %d\n", computer_guess);
  while (user_guess == computer_guess || user_guess <= 0 || user_guess > 10) {
    printf("Enter a guess: ");
    scanf("%d", &user_guess); }
  //Result calculated; winner returned
  printf("The secret number was %d!\n", random_number);
  if (abs(random_number - user_guess) < abs(random_number - computer_guess)) {
    printf("You won! You'll go first\n");
    //system("cls");
    return PLAYER1;
  }
  else if (abs(random_number - user_guess) > abs(random_number - computer_guess)) {
    printf("Sorry, you lost! The computer goes first\n");
    //system("cls");
    return PLAYER2;
  }
  else {
    printf("Something went wrong...\n");
    return 0;
  }

}

//Function that ensures no ships overlap
int is_other_ship(char board[][10], int height, int width, int ship_size, char direction) {
  if (direction == 'd') {
    for (int i=0; i<ship_size; i++) {
      if (board[height+i][width] != '~') {
        return 1; }
    }
}
  if (direction == 'u') {
    for (int i=0; i<ship_size; i++) {
      if (board[height-i][width] != '~') {
        return 1; }
    }
}
  if (direction == 'l') {
    for (int i=0; i<ship_size; i++) {
      if (board[height][width-i] != '~') {
        return 1; }
    }
}
  if (direction == 'r') {
    for (int i=0; i<ship_size; i++) {
      if (board[height][width+i] != '~') {
        return 1; }
    }
}
  return 0;

}


//Function that places ships, given direction, ship size, and ship name, and board
void place_ship(char ship_name, int *height, int *width, int ship_size, char board[][10]) {
  char direction = '\0';
  int direction_check = 0;

  do {
      //Gets the direction to place the ship; ensures user enters valid direction
      while (1) {
      printf("Direction: %c\n", direction);
      printf("Do you want to go up, down, left, or right? ['u', 'd', 'l', 'r'] ");
      scanf(" %c", &direction);
      if (direction == 'u' || direction == 'd' || direction == 'l' || direction == 'r') {
        break; }
      }

      int overlap = is_other_ship(board, *height, *width, ship_size, direction);
      printf("Overlap: %d\n", overlap); //For debugging. Delete later

      //Checks if up is valid placement
      if (direction == 'u') {
        if (*height - ship_size < 0 || overlap) {
          printf("Uh oh! You can't go up!\n");
          direction_check = 0;
          direction = '\0'; }
        //If up is valid, places ship above initial point
        else if (*height - ship_size >= 0) {
          for (int i=0; i<ship_size; i++) {
            board[*height-i][*width] = ship_name; }
            direction_check = 1;
        }
      }
      //Checks if down is valid placement
      else if (direction == 'd') {
        if (*height + ship_size > 10 || overlap) {
          printf("Uh oh! You can't go down!\n");
          direction = '\0';
          direction_check = 0; }
        //If down is valid, positions ship below initial point
        else if (*height + ship_size <= 10) {
          for (int i=0; i<ship_size; i++) {
            board[*height+i][*width] = ship_name; }
            direction_check = 1;
        }
      }
      //Checks if left is valid placement
      else if (direction == 'l') {
        if (*width - ship_size < 0 || overlap) {
          printf("Uh oh! You can't go left!\n");
          direction = '\0';
          direction_check = 0; }
        //If left is valid, positions ship left of initial point
        else if (*width - ship_size >= 0) {
          for (int i=0; i<ship_size; i++) {
            board[*height][*width-i] = ship_name; }
            direction_check = 1;
        }
      }
      //Checks if right is valid placement
      else if (direction == 'r') {
        if (*width + ship_size > 10 || overlap) {
          printf("Uh oh! You can't go right!\n");
          direction = '\0';
          direction_check = 0; }
        //If right is valid, postions ship right of initial point
        else if (*width + ship_size <= 10) {
          for (int i=0; i<ship_size; i++) {
            board[*height][*width+i] = ship_name; }
            direction_check = 1;
        }
      }


    } while (direction_check == 0);
    //Resets height and width to be used for other ships
    *height = 11;
    *width = 11;

}

//Function that allows the user to manually place their ships
void manually_place_ships(char board[][10]) {
  int height = 11, width = 11;
  char direction = '\0';

  //Places the carrier on the board
  display_board(board);
  while (height > 10 || height < 0 || width > 10 || width < 0) {
    printf("Enter first coordinate for the Carrier: ");
    scanf("%d%d", &height, &width); }
  place_ship('c', &height, &width, CARRIER, board);

  //Places the battleship on the board
  display_board(board);
  while (height > 10 || height < 0 || width > 10 || width < 0) {
    printf("Enter first coordinate for the Battleship: ");
    scanf("%d%d", &height, &width); }
  place_ship('b', &height, &width, BATTLESHIP, board);

  //Places the cruiser on the board
  display_board(board);
  while (height > 10 || height < 0 || width > 10 || width < 0) {
    printf("Enter first coordinate for the Cruiser: ");
    scanf("%d%d", &height, &width); }
  place_ship('r', &height, &width, CRUISER, board);

  //Places the submarine on the board
  display_board(board);
  while (height > 10 || height < 0 || width > 10 || width < 0) {
    printf("Enter first coordinate for the Submarine: ");
    scanf("%d%d", &height, &width); }
  place_ship('s', &height, &width, SUBMARINE, board);

  //Places the destroyer on the board
  display_board(board);
  while (height > 10 || height < 0 || width > 10 || width < 0) {
    printf("Enter first coordinate for the Destroyer: ");
    scanf("%d%d", &height, &width); }
  place_ship('d', &height, &width, DESTROYER, board);

}

//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
