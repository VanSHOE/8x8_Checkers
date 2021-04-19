#ifndef HEADER
#define HEADER
#include <stdbool.h>

typedef struct board game_state; //game state
typedef struct pieces pawn;

struct pieces
{
    int x;
    int y;
    int allegiance; // Whose team is it on?
    bool is_king;   // Is it king yet?
};

struct board
{
    pawn white[12];
    pawn black[12];
    int cur_turn; // Whose turn is it at this particular state
};

//make bot
void init_game_2players(); //starts the game with 2 players mode
void init_game_bot();      //starts the game with bot

void start();
void resign(game_state g);
void draw(game_state g);
void toss();

//update board
game_state move_entries(pawn p); // Function to move one of the pawns
/*
in this function i am writing here but after .c is made paste it there,
we have to update board which involves lots of subfunctions like checking if move is legal or not
also we have to update the position. and additional features if one can add (using \b) sounds to show moves
*/
void print_board(game_state P);
game_state undo(pawn p);
void rule();                        //just prints rule book
bool islegal(pawn p, pawn new_pos); // Need a 'from' and a 'to'
void result(game_state P);          //tells the result of the game

//interface
/*
we have to make elegant impresion and to fully appriciate the function print board, we have to create 
a game like interface for board. apart from that we also want function to show legal moves
i cant think of functions data types so plz excuse me.....
*/

//analysis
void review();                              //slideshow of board , added:- we will be using a global stack , no need to pass anything in review, undo etc
void show_all_possible_moves(game_state P); //print all possible moves in simple algebraic manner
void best_move(game_state P);               //tells best move we can go upto depth of 2/3 or as we discussed as far as 10
//void evaluation_bar(game_state P); //its hard to do so..but ok i wrote it , not required , these parameters are best kept out of the view of the player , they will be used just for the bot

/*
NOTES- 
after a move is played by running a command, we will print board interface and subseq. after user types next move 
command we will clear screen and prints the board.
similarly when user prints undo, we print prev board configurations.
*/

#endif
