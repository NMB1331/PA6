#ifndef BATTLESHIP_H

#define BATTLESHIP_H
#define BOARD_SIZE 10
#define PLAYER1 1
#define PLAYER2 2
#define CARRIER 5
#define BATTLESHIP 4
#define CRUISER 3
#define SUBMARINE 3
#define DESTROYER 2
#define HIT 1
#define MISS 0
#define NUM_SHIPS 5

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct stats
{
  int num_hits;
  int num_misses;
  int total_shots;
  double hit_miss_ratio;
} Stats;

//Game setup functions
/*************************************************************
* Function: welcome_screen                                  *
* Date Created: 10/25/2016                                  *
* Date Last Modified: 10/25/2016                            *
* Description: Welcomes player, prints game rules           *
* Input parameters: None                                    *
* Returns: None                                             *
* Preconditions: None                                       *
* Postconditions: None                                      *
*************************************************************/
void welcome_screen(void);

/*************************************************************                   X
* Function: initialize_game_board                           *
* Date Created: 10/25/2016                                  *
* Date Last Modified: 10/25/2016                            *
* Description: Initializes the game board ('~')             *
* Input parameters: 2D char array board, width 10           *
* Returns: None                                             *
* Preconditions: None                                       *
* Postconditions: None                                      *
*************************************************************/
void initialize_game_board(char board[][10]);

/*************************************************************                   X
* Function: display_board                                   *
* Date Created: 10/25/2016                                  *
* Date Last Modified: 10/25/2016                            *
* Description: Prints out the game board                    *
* Input parameters: char array board, width 10               *
* Returns: None                                             *
* Preconditions: None                                       *
* Postconditions: None                                      *
*************************************************************/
void display_board(char board[][10], int player_number);

/*************************************************************                   X
* Function: select_who_starts_first                         *
* Date Created: 10/25/2016                                  *
* Date Last Modified: 10/25/2016                            *
* Description: Randomly determines first player (roll die!) *
* Input parameters: None                                    *
* Returns: 1 if player 1 goes first, 2 if player 2          *
* Preconditions: None                                       *
* Postconditions: None                                      *
*************************************************************/
int select_who_starts_first(void);

//Ship placement functions

/*************************************************************                   X
* Function: get_coordinates                                 *
* Date Created: 10/27/2016                                  *
* Date Last Modified: 10/27/2016                            *
* Description: Gets ship coordinates from the user          *
* Input parameters: Board array, height/width ptr, string ship name
* Returns: None                                             *
* Preconditions: None                                       *
* Postconditions: None                                      *
*************************************************************/
void get_coordinates(int *height, int *width, char board[][10]);

/*************************************************************                   X
* Function: get_coordinates                                 *
* Date Created: 10/27/2016                                  *
* Date Last Modified: 10/27/2016                            *
* Description: Gets ship direction from the user            *
* Input parameters: Char pointer direction                  *
* Returns: None                                             *
* Preconditions: None                                       *
* Postconditions: None                                      *
*************************************************************/
void get_direction(char *direction);

/*************************************************************                   X
* Function: place_ship                                      *
* Date Created: 10/27/2016                                  *
* Date Last Modified: 10/27/2016                            *
* Description: Places a ship on the board                   *
* Input parameters: Int array board, width 10, ship size, height,
                    width, ship name
* Returns: None                                             *
* Preconditions: None                                       *
* Postconditions: None                                      *
*************************************************************/
void place_ship(int *h, int *w, int ship_size, char ship_name, char *direction, char board[][10]);

/*************************************************************                   X
* Function: is_other_ship                                   *
* Date Created: 10/27/2016                                  *
* Date Last Modified: 10/27/2016                            *
* Description: Checks if there's another ship in the direcion
* Input parameters: char board[][10], int *height, int *width, int ship_size char direction
* Returns: 1 if there's another ship, 0 otherwise           *
* Preconditions: None                                       *
* Postconditions: None                                      *
*************************************************************/
int is_other_ship(char board[][10], int height, int width, int ship_size, char direction);

/*************************************************************                   X
* Function: is_out                                          *
* Date Created: 10/27/2016                                  *
* Date Last Modified: 10/27/2016                            *
* Description: Checks if a ship will be off the board
* Input parameters: char board[][10], int *height, int *width, int ship_size char direction
* Returns: 1 if out, 0 otherwise           *
* Preconditions: None                                       *
* Postconditions: None                                      *
*************************************************************/
int is_out(int height, int width, int ship_size, char direction);

/*************************************************************                   X
* Function: manually_place_ships                            *
* Date Created: 10/25/2016                                  *
* Date Last Modified: 10/25/2016                            *
* Description: Allows the player to place ships             *
* Input parameters: Int array board, width 10               *
* Returns: None                                             *
* Preconditions: None                                       *
* Postconditions: None                                      *
*************************************************************/
void manually_place_ships(char board[][10]);

/*************************************************************                   X
* Function: place_player_ships                              *
* Date Created: 10/25/2016                                  *
* Date Last Modified: 11/1/2016                             *
* Description: Allows the player to place ships (manually or randomly)
* Input parameters: Int array board, width 10               *
* Returns: None                                             *
* Preconditions: None                                       *
* Postconditions: None                                      *
*************************************************************/
void place_player_ships(char board[][10]);


//Random ship placement functions

/*************************************************************                   X
* Function: generate_random_coordinates                     *
* Date Created: 10/25/2016                                  *
* Date Last Modified: 10/25/2016                            *
* Description: Generates random coordinates                 *
* Input parameters: Char array board, int height/width pointers,
                    direction ptr, ship size
* Returns: None                                             *
* Preconditions: None                                       *
* Postconditions: None                                      *
*************************************************************/
void generate_random_coordinates(int *h, int *w, char board[][10]);

/*************************************************************                   X
* Function: generate_random_direction                       *
* Date Created: 10/25/2016                                  *
* Date Last Modified: 10/25/2016                            *
* Description: Generates random direction for ship          *
* Input parameters: Char array board, int height/width pointers
* Returns: None                                             *
* Preconditions: None                                       *
* Postconditions: None                                      *
*************************************************************/
void generate_random_direction(char *direction);

/*************************************************************                   X
* Function: place_random_ships                              *
* Date Created: 10/27/2016                                  *
* Date Last Modified: 10/27/2016                            *
* Description: Places a ship randomly                       *
* Input parameters: Fucking everything and the kitchen sink *
* Returns: None                                             *
* Preconditions: None                                       *
* Postconditions: None                                      *
*************************************************************/
void place_random_ships(int *h, int *w, int ship_size, char ship_name, char *direction, char board[][10]);

/*************************************************************                   X
* Function: randomly_place_ships                            *
* Date Created: 10/25/2016                                  *
* Date Last Modified: 10/25/2016                            *
* Description: Randomly places ships (for AI)               *
* Input parameters: Char array board, width 10              *
* Returns: None                                             *
* Preconditions: None                                       *
* Postconditions: None                                      *
*************************************************************/
void randomly_place_ships(char board[][10]);

//Shooting functions/main game body functions

/*************************************************************                   X
* Function: get_shot                                        *
* Date Created: 10/28/2016                                  *
* Date Last Modified: 10/28/2016                            *
* Description: Gets shot coordinates from the user          *
* Input parameters: Board array, height/width ptr           *
* Returns: None                                             *
* Preconditions: None                                       *
* Postconditions: None                                      *
*************************************************************/
void get_shot(int *height, int *width, char board[][10]);

/*************************************************************                   X
* Function: get_random_shot                                 *
* Date Created: 10/29/2016                                  *
* Date Last Modified: 10/29/2016                            *
* Description: Randomly generates a shot                    *
* Input parameters: Board array, height/width ptr           *
* Returns: None                                             *
* Preconditions: None                                       *
* Postconditions: None                                      *
*************************************************************/
void get_random_shot(int *h, int *w, char board[][10]);

/*************************************************************                   X
* Function: check_shot                                      *
* Date Created: 10/25/2016                                  *
* Date Last Modified: 10/25/2016                            *
* Description: Checks if a shot is a hit or a miss          *
* Input parameters: Coordinates of shot (height, width)     *
* Returns: 1 if hit, 0 if miss                              *
* Preconditions: None                                       *
* Postconditions: None                                      *
*************************************************************/
int check_shot(int height, int width, char board[][10]);

/*************************************************************                   X
* Function: update_board                                    *
* Date Created: 10/25/2016                                  *
* Date Last Modified: 10/25/2016                            *
* Description: Updates board after every shot (X for hit, M for miss)
* Input parameters: Char array board, shot coordinates       *
* Returns: None                                             *
* Preconditions: None                                       *
* Postconditions: None                                      *
*************************************************************/
void update_board(int height, int width, char board[][10]);

/*************************************************************
* Function: output_current_move                             *
* Date Created: 10/25/2016                                  *
* Date Last Modified: 10/25/2016                            *
* Description: Writes current move and result to log file   *
* Input parameters: Int height and width, char result, file outfile
* Returns: None                                             *
* Preconditions: None                                       *
* Postconditions: None                                      *
*************************************************************/
void output_current_move(FILE *outfile, int height, int width, char result);

/*************************************************************                   X
* Function: play_shot                                       *
* Date Created: 10/26/2016                                  *
* Date Last Modified: 10/26/2016                            *
* Description: Gets shot, checks if hit, updates board, outputs to file
* Input parameters: Char array board, width 10              *
* Returns: None                                             *
* Preconditions: check_shot and update_board must be declared
* Postconditions: None                                      *
*************************************************************/
void play_shot(char board[][10], int player_number);

/*************************************************************                   X
* Function: check_if_ship_sunk                              *
* Date Created: 10/25/2016                                  *
* Date Last Modified: 10/25/2016                            *
* Description: Checks if a ship is sunk                     *
* Input parameters: Char array board, width 10, char ship name
* Returns: 1 if sunk, 0 if not                              *
* Preconditions: None                                       *
* Postconditions: None                                      *
*************************************************************/
int check_if_ship_sunk(char board[][10], char ship_name);

/*************************************************************                   X
* Function: notify_player_ship_sunk                         *
* Date Created: 11/1/2016                                   *
* Date Last Modified: 11/1/2016                             *
* Description: Tells the player they sunk a ship            *
* Input parameters: Char board array && remaining_ships array
* Returns: None (tells the user they sunk a ship)           *
* Preconditions: None                                       *
* Postconditions: None                                      *
*************************************************************/
void notify_player_ship_sunk(char board[][10], char remaining_ships[5]);

/*************************************************************                   X
* Function: is_winner                                       *
* Date Created: 10/25/2016                                  *
* Date Last Modified: 10/25/2016                            *
* Description: Checks boards for winner                     *
* Input parameters: Char array board                        *
* Returns: 1 if P1 wins, 2 if P2 wins, 0 otherwise          *
* Preconditions: None                                       *
* Postconditions: None                                      *
*************************************************************/
int is_winner(char board[][10]);

//Stats functions

/*************************************************************
* Function: output_current_move                             *
* Date Created: 10/25/2016                                  *
* Date Last Modified: 10/25/2016                            *
* Description: Writes current move and result to log file   *
* Input parameters: Int height and width, char result, file outfile
* Returns: None                                             *
* Preconditions: None                                       *
* Postconditions: None                                      *
*************************************************************/
void output_current_move(FILE *outfile, int height, int width, char result);

/*************************************************************
* Function: update_stats                                    *
* Date Created: 11/1/2016                                   *
* Date Last Modified: 11/1/2016                             *
* Description: Updates game stats after shot                *
* Input parameters: Stats pointer, int hit (1 if hit, 0 if miss)
* Returns: None                                             *
* Preconditions: Typedef stats must be defined              *
* Postconditions: None                                      *
*************************************************************/
void update_stats(Stats *p_stats, int hit);

/*************************************************************
* Function: output_stats                                    *
* Date Created: 10/25/2016                                  *
* Date Last Modified: 10/25/2016                            *
* Description: Calculates and outputs stats to outfile      *
* Input parameters: Files outfile and infile                *
* Returns: None                                             *
* Preconditions: None                                       *
* Postconditions: None                                      *
*************************************************************/
void output_stats(FILE *infile, FILE *outfile);

#endif
