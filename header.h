#ifndef HEADER
#define HEADER

typedef struct board position; //game state
typedef struct pieces pawn;

struct pieces {
    int x; 
    int y;
} ;

struct board {
    struct pieces white[12];
    struct pieces black[12];
} ;


//make bot
position init_game_2players(); //starts the game with 2 players mode
position init_game_bot(); //starts the game with bot

//start,restart,resign,draw,side switch, toss functions
/*
i dont know what to put here so plz see......
*/

//update board
position move_enteries(pawn p); //user will attempt p[i]...that is user will tell which pawn
/*
in this function i am writting here but after .c is made paste it there,
we have to update board which involves lots of subfunctions like checking if move is legal or not
also we have to update the position. and additional features if one can add (using \b) sounds to show moves
*/
void print_board(position P);
position undo(pawn p);
void rule(); //just prints rule book
void why_move_is_illegal(pawn p); 
void result(position P); //tells the result of the game

//interface 
/*
we have to make elegant impresion and to fully appriciate the function print board, we have to create 
a game like interface for board. apart from that we also want function to show legal moves
i cant think of functions data types so plz excuse me.....
*/

//analysis
position review(position P[]); //slideshow of board
void show_all_possible_moves(position P); //print all possible moves in simple algebraic manner
void best_move(position P); //tells best move we can go upto depth of 2/3 or as we discussed as far as 10
void evaluation_bar(position P); //its hard to do so..but ok i wrote it
/*
using last 2 function we can make solid bot who plays logically instead of random moves...
*/


/*
NOTES- 
after a move is played by running a command, we will print board interface and subseq. after user types next move 
command we will clear screen and prints the board.
similarly when user prints undo, we print prev board configurations.
*/

//this is prototype, plz correct where its wrong. 

#endif