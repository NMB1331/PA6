#include "battleship_functions.h"

//Function that welcomes the user, and explains the game
void welcome_screen(void)
{
  printf("Welcome to Battleship, the classic naval strategy game!\n");
  printf("The goal of the game is to sink the other player's ships...before he sinks yours.\n");
  printf("You will be prompted to manually place your ships on the board, or \nhave the computer do it randomly.\n");
  printf("The board measures 9 x 9, with coordinate choices ranging from 0-9.\n");
  printf("When entering coordinates, enter the height (y-axis) first, and then \nthe width (x-axis).\n");
  printf("After placing your ships, you will play a game to determine who goes first.\n");
  printf("After that, the fun begins! You will enter the coordinates of a shot.\n");
  printf("If the shot is a hit, then an 'X' will appear. Otherwise, an 'M' will appear.\n");
  printf("You and the computer will shoot back and forth until someone loses all their ships.\n");
  printf("The player who destroys their opponents fleet first wins!\n");
  printf("Have fun!\n");
  printf("\n");
}

//Function that resets the game board (fills with '~')
void initialize_game_board(char board[10][10])
{
  for (int i=0; i<BOARD_SIZE; i++)
  {
    for (int j=0; j<BOARD_SIZE; j++)
    {
      board[i][j] = '~';
    }
  }
}

//Function that prints the game board
void display_board(char board[10][10], int player_number)
{
  if (player_number == 1)
  {
    printf("YOUR BOARD: \n");
    for (int i=0; i<BOARD_SIZE; i++)
    {
      for (int j=0; j<BOARD_SIZE; j++)
      {
        printf("%c ", board[i][j]);
      }
      printf("\n");
    }
    printf("\n");
  }
  else if (player_number == 2)
  {
    printf("COMPUTER'S BOARD:\n");
    for (int i=0; i<BOARD_SIZE; i++)
    {
      for (int j=0; j<BOARD_SIZE; j++)
      {
        if (board[i][j] == '~' || board[i][j] == 'X' || board[i][j] == 'M')
        {
          printf("%c ", board[i][j]);
        }
        else
        {
          printf("~ ");
        }
      }
      printf("\n");
    }
    printf("\n");
  }
  }

//Determines who starts first
int select_who_starts_first(void)
{
  //Variables declared; Secret number and computer guess chosen
  int user_guess = 0, random_number = rand() % 10 + 1, computer_guess = 0;
  while (computer_guess == 0 || computer_guess == random_number)
  {
    computer_guess = rand() % 10 + 1;
  }
  //User guess made
  printf("This is supposed to be random, but...I thought a game would be more fun!\n");
  printf("To see who starts first, we're going to play a guessing game!\n");
  printf("We're going to pick numbers between 1 and 10, and see who's closer.\n");
  printf("The computer guessed %d\n", computer_guess);
  while (user_guess == computer_guess || user_guess <= 0 || user_guess > 10)
  {
    printf("Enter a guess: ");
    scanf("%d", &user_guess);
  }
  //Result calculated; winner returned
  printf("The secret number was %d!\n", random_number);
  if (abs(random_number - user_guess) < abs(random_number - computer_guess))
  {
    printf("You won! You'll go first\n");
    return PLAYER1;
  }
  else if (abs(random_number - user_guess) > abs(random_number - computer_guess))
  {
    printf("Sorry, you lost! The computer goes first\n");
    return PLAYER2;
  }
  else
  {
    printf("Something went wrong...\n");
    return 0;
  }

}

//Function that gets coordinates for ships
void get_coordinates(int *height, int *width, char board[][10])
{
  int h = 11, w = 11;
  while ((h < 0) || (h > BOARD_SIZE-1) || (w < 0) || (w < BOARD_SIZE-1) || !(board[h][w] == '~'))
  {
    printf("Enter the coordinates: ");
    scanf("%d%d", &h, &w);
    if (board[h][w] == '~')
    {
      break;
    }
  }
  *height = h;
  *width = w;
}

//Function that gets the direction of a ship
void get_direction(char *direction)
{
  while (1)
  {
  printf("Do you want to go up, down, left, or right? ['u', 'd', 'l', 'r'] ");
  scanf(" %c", direction);
  if (*direction == 'u' || *direction == 'd' || *direction == 'l' || *direction == 'r')
  {
    break;
  }
  }
}

//Function that ensures no ships overlap
int is_other_ship(char board[][10], int height, int width, int ship_size, char direction)
{
  if (direction == 'd')
  {
    for (int i=0; i<ship_size; i++)
    {
      if (board[height+i][width] != '~')
      {
        return 1;
      }
    }
  }
  if (direction == 'u')
  {
    for (int i=0; i<ship_size; i++)
    {
      if (board[height-i][width] != '~')
      {
        return 1;
      }
    }
  }
  if (direction == 'l')
  {
    for (int i=0; i<ship_size; i++)
    {
      if (board[height][width-i] != '~')
      {
        return 1;
      }
    }
  }
  if (direction == 'r')
  {
    for (int i=0; i<ship_size; i++)
    {
      if (board[height][width+i] != '~')
      {
        return 1;
      }
    }
  }
  return 0;

}

//Function that makes sure ships don't go off the board
int is_out(int height, int width, int ship_size, char direction)
{
  if (direction == 'u')
  {
    if (height - ship_size < 0)
    {
      return 1;
    }
  }
  if (direction == 'd')
  {
    if (height + ship_size > BOARD_SIZE-1)
    {
      return 1;
    }
  }
  if (direction == 'l')
  {
    if (width - ship_size < 0)
    {
      return 1;
    }
  }
  if (direction == 'r')
  {
    if (width + ship_size > BOARD_SIZE - 1)
    {
      return 1;
    }
  }
  return 0;
}

//Function that places ships, given direction, ship size, and ship name, and board
void place_ship(int *h, int *w, int ship_size, char ship_name, char *direction, char board[][10])
{
  int out = 1, overlap = 1;
  do
  {
    //Gets coordinates and direction
    get_coordinates(h, w, board);
    get_direction(direction);
    //Checks if valid
    overlap = is_other_ship(board, *h, *w, ship_size, *direction);
    out = is_out(*h, *w, ship_size, *direction);

  } while (out || overlap);

  if (*direction == 'u')
  {
    for (int i=0; i<ship_size; i++)
    {
      board[*h-i][*w] = ship_name;
    }
  }
  if (*direction == 'd') {
    for (int i=0; i<ship_size; i++) {
      board[*h+i][*w] = ship_name; }
  }
  if (*direction == 'l')
  {
    for (int i=0; i<ship_size; i++)
    {
      board[*h][*w-i] = ship_name;
    }
  }
  if (*direction == 'r')
  {
    for (int i=0; i<ship_size; i++)
    {
      board[*h][*w+i] = ship_name;
    }
  }

}

//Function that allows the user to manually place their ships
void manually_place_ships(char board[][10])
{
  //Variables declared
  int h = 11, w = 11;
  char direction = '\0';

  display_board(board, PLAYER1);
  //Places carrier
  printf("CARRIER\n");
  place_ship(&h, &w, CARRIER, 'c', &direction, board);
  display_board(board, PLAYER1);
  //Places battleship
  printf("BATTLESHIP\n");
  place_ship(&h, &w, BATTLESHIP, 'b', &direction, board);
  display_board(board, PLAYER1);
  //Places cruiser
  printf("CRUISER\n");
  place_ship(&h, &w, CRUISER, 'r', &direction, board);
  display_board(board, PLAYER1);
  //Places submarine
  printf("SUBMARINE\n");
  place_ship(&h, &w, SUBMARINE, 's', &direction, board);
  display_board(board, PLAYER1);
  //Places destroyer
  printf("DESTROYER\n");
  place_ship(&h, &w, DESTROYER, 'd', &direction, board);
  display_board(board, PLAYER1);

}

//Function that generates random coordinates
void generate_random_coordinates(int *h, int *w, char board[][10])
{
  int overlap = 1;
  while ((*h < 0) || (*h > BOARD_SIZE-1) || (*w < 0) || (*w > BOARD_SIZE-1) || overlap)
  {
    *h = rand() % 9;
    *w = rand() % 9;
    if (board[*h][*w] == '~') {
      overlap = 0; }
  }
}

//Function that generates a random directions
void generate_random_direction(char *direction)
{
  int random = 0;
  random = rand() % 4 + 1;

  switch (random)
  {
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
void place_random_ships(int *h, int *w, int ship_size, char ship_name, char *direction, char board[][10])
{
  int out = 1, overlap = 1;
  do
  {
    //Generates random coordinate and direction
    generate_random_coordinates(h, w, board);
    generate_random_direction(direction);
    //Checks if valid
    overlap = is_other_ship(board, *h, *w, ship_size, *direction);
    out = is_out(*h, *w, ship_size, *direction);

  } while (out || overlap);

  if (*direction == 'u')
  {
    for (int i=0; i<ship_size; i++)
    {
      board[*h-i][*w] = ship_name;
    }
  }
  if (*direction == 'd')
  {
    for (int i=0; i<ship_size; i++)
    {
      board[*h+i][*w] = ship_name;
    }
  }
  if (*direction == 'l')
  {
    for (int i=0; i<ship_size; i++)
    {
      board[*h][*w-i] = ship_name;
    }
  }
  if (*direction == 'r')
  {
    for (int i=0; i<ship_size; i++)
    {
      board[*h][*w+i] = ship_name;
    }
  }

}

//Function that randomly places ships on the board
void randomly_place_ships(char board[][10])
{
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

//Function that places a players ships, either randomly or manually
void place_player_ships(char board[][10])
{
  int manual_or_random = 0;
  do
  {
    printf("Enter 1 to manually select your ship's locations, or 2 for random ones: ");
    scanf("%d", &manual_or_random);
  } while(manual_or_random != 1 && manual_or_random != 2);
  if (manual_or_random == 1)
  {
    manually_place_ships(board);
  }
  else if (manual_or_random == 2)
  {
    randomly_place_ships(board);
    printf("The lazy way. I dig it. Here's your board: \n");
    display_board(board, PLAYER1);
  }
}


//Function that gets shot coordinates from the user
void get_shot(int *h, int *w, char board[][10])
{
  int height = 11, width = 11;
  do
  {
    printf("Enter the coordinates for a shot: ");
    scanf("%d%d", &height, &width);
  }
  while(height < 0 || height > (BOARD_SIZE-1) || width < 0 || width > (BOARD_SIZE-1) || board[height][width] == 'X' || board[height][width] == 'M');
  *h = height;
  *w = width;
}

//Function that generates random shot coordinates
void get_random_shot(int *h, int *w, char board[][10])
{
  int height = 11, width = 11;
  do
  {
    height = rand() % 9;
    width = rand() % 9;
  } while(board[height][width] == 'X' || board[height][width] == 'M');
  *h = height;
  *w = width;
}

//Function that checks if a shot is a hit or miss
int check_shot(int height, int width, char board[][10])
{
  if (board[height][width] == '~')
  {
    return MISS;
  }
  else if (board[height][width] == 'c' || board[height][width] == 'b' || board[height][width] == 'r' || board[height][width] == 's' || board[height][width] == 'd' )
  {
    return HIT;
  }
  else
  {
    printf("ERROR CHECKING SHOT\n");
    return -1;
  }
}

//Function that updates the board after a shot ('X' for hit, 'M' for miss)
void update_board(int height, int width, char board[][10])
{
  if (check_shot(height, width, board) == HIT)
  {
    printf("Hit!\n");
    board[height][width] = 'X';
  }
  else if (check_shot(height, width, board) == MISS)
  {
    printf("Miss!\n");
    board[height][width] = 'M';
  }
  else
  {
    printf("ERROR UPDATING BOARD\n");
  }
}

//Function that plays one round ("a shot")
void play_shot(char board[][10], int player_number)
{
  int height = 0, width = 0;
  if (player_number == 1)
  {
    get_shot(&height, &width, board);
    update_board(height, width, board);
  }
  else if (player_number == 2)
  {
    get_random_shot(&height, &width, board);
    printf("Computer shot: %d,%d\n", height, width);
    update_board(height, width, board);
  }

}

//Function that checks if a ship is sunk
int check_if_ship_sunk(char board[][10], char ship_name)
{
  if (ship_name == '\0')
  {
    return 0;
  }

  for (int i=0; i< BOARD_SIZE; i++)
  {
    for (int j=0; j< BOARD_SIZE; j++)
    {
      if (board[i][j] == ship_name)
      {
        return 0;
      }
    }
  }
  return 1;
}

//Function that notifies the player if they sunk a ship_name
//(Checks all remaining ships; if one has been sunk, notifies player and removes from list of remaining)
void notify_player_ship_sunk(char board[][10], char remaining_ships[5])
{
  char sunk_ship = '\0';
  for (int i=0; i<NUM_SHIPS; i++)
  {
    char current_letter = remaining_ships[i];
    if (check_if_ship_sunk(board, current_letter))
    {
      sunk_ship = current_letter;
      remaining_ships[i] = '\0';
      break;
    }
  }
  switch(sunk_ship)
  {
    case 'c': printf("Carrier destroyed!\n");
              break;
    case 'r': printf("Cruiser destroyed!\n");
              break;
    case 'd': printf("Destroyer destroyed!\n");
              break;
    case 's': printf("Submarine destroyed!\n");
              break;
    case 'b': printf("Battleship destroyed!\n");
              break;
    default: printf("No ships sunk\n");
  }
}

//Function that checks if there is a winner (checks if every ship sunk)
int is_winner(char board[][10])
{
  if (check_if_ship_sunk(board, 'c') && check_if_ship_sunk(board, 'b') && check_if_ship_sunk(board, 'r') && check_if_ship_sunk(board, 's') && check_if_ship_sunk(board, 'd'))
  {
    return 1;
  }
  else
  {
  return 0;
  }
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
