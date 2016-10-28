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

//Function that gets coordinates for ships
void get_coordinates(int *height, int *width, char board[][10], char *ship_name) {
  int h = 11, w = 11;
  while ((h < 0) || (h > BOARD_SIZE-1) || (w < 0) || (w < BOARD_SIZE-1) || !(board[h][w] == '~')) {
    printf("Enter the coordinates for %s: ", ship_name);
    scanf("%d%d", &h, &w);
    if (board[h][w] == '~') {
      break; }
  }
  *height = h;
  *width = w;
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

//Function that makes sure ships don't go off the board
int is_out(int height, int width, int ship_size, char direction) {
  if (direction == 'u') {
    if (height - ship_size < 0) {
      return 1; }
  }
  if (direction == 'd') {
    if (height + ship_size > BOARD_SIZE-1) {
      return 1; }
  }
  if (direction == 'l') {
    if (width - ship_size < 0) {
      return 1; }
  }
  if (direction == 'r') {
    if (width + ship_size > BOARD_SIZE - 1) {
      return 1; }
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

      //Determines if there is any overlap between ships
      int overlap = is_other_ship(board, *height, *width, ship_size, direction);
      int out = is_out(*height, *width, ship_size, direction);
      printf("Overlap: %d\n", overlap); //For debugging. Delete later
      printf("Out: %d\n", out);

      //Checks if up is valid placement
      if (direction == 'u') {
        if (out || overlap) {
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
        if (out || overlap) {
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
        if (out || overlap) {
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
        if (out || overlap) {
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
}

//Function that allows the user to manually place their ships
void manually_place_ships(char board[][10]) {
  int height = 11, width = 11;
  char direction = '\0';

  //Places the carrier on the board
  display_board(board);
  get_coordinates(&height, &width, board, "Carrier");
  place_ship('c', &height, &width, CARRIER, board);

  //Places the battleship on the board
  display_board(board);
  get_coordinates(&height, &width, board, "Battleship");
  place_ship('b', &height, &width, BATTLESHIP, board);

  //Places the cruiser on the board
  display_board(board);
  get_coordinates(&height, &width, board, "Cruiser");
  place_ship('r', &height, &width, CRUISER, board);

  //Places the submarine on the board
  display_board(board);
  get_coordinates(&height, &width, board, "Submarine");
  place_ship('s', &height, &width, SUBMARINE, board);

  //Places the destroyer on the board
  display_board(board);
  get_coordinates(&height, &width, board, "Destroyer");
  place_ship('d', &height, &width, DESTROYER, board);

}

//Function that generates random coordinates
void generate_random_coordinates(int *h, int *w, char board[][10]) {
  int overlap = 1;
  while ((*h < 0) || (*h > BOARD_SIZE-1) || (*w < 0) || (*w > BOARD_SIZE-1) || overlap) {
    *h = rand() % 9;
    *w = rand() % 9;
    if (board[*h][*w] == '~') {
      overlap = 0; }
  }
}

//Function that generates a random directions
void generate_random_direction(char *direction) {
  int random = 0;
  random = rand() % 4 + 1;

  switch (random) {
    case 1: *direction = 'u';
            break;
    case 2: *direction = 'd';
            break;
    case 3: *direction = 'l';
            break;
    case 4: *direction = 'r';
            break;
  }
}

//Function that randomly places a ships
void place_random_ships(int *h, int *w, int ship_size, char ship_name, char *direction, char board[][10]) {
  int out = 1, overlap = 1;
  do {
    //Generates random coordinate and direction
    generate_random_coordinates(h, w, board);
    generate_random_direction(direction);
    //Checks if valid
    overlap = is_other_ship(board, *h, *w, ship_size, *direction);
    out = is_out(*h, *w, ship_size, *direction);

  } while (out || overlap);

  if (*direction == 'u') {
    for (int i=0; i<ship_size; i++) {
      board[*h-i][*w] = ship_name; }
  }
  if (*direction == 'd') {
    for (int i=0; i<ship_size; i++) {
      board[*h+i][*w] = ship_name; }
  }
  if (*direction == 'l') {
    for (int i=0; i<ship_size; i++) {
      board[*h][*w-i] = ship_name; }
  }
  if (*direction == 'r') {
    for (int i=0; i<ship_size; i++) {
      board[*h][*w+i] = ship_name; }
  }

}

//Function that randomly places ships on the board
void randomly_place_ships(char board[][10]) {
  //Variables declared
  int h = 11, w = 11;
  char direction = '\0';

  //Places carrier randomly
  place_random_ships(&h, &w, CARRIER, 'c', &direction, board);
  //Places battleship randomly
  place_random_ships(&h, &w, BATTLESHIP, 'b', &direction, board);
  //Places cruiser randomly
  place_random_ships(&h, &w, CRUISER, 'r', &direction, board);
  //Places submarine randomly
  place_random_ships(&h, &w, SUBMARINE, 's', &direction, board);
  //Places destroyer randomly
  place_random_ships(&h, &w, DESTROYER, 'd', &direction, board);

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
//
//
//
//
//
//
