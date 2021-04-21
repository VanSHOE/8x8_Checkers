#ifndef HEADER
#define HEADER
#include <stdbool.h>

typedef struct board game_state; //game state
typedef struct pieces pawn;
typedef struct move move;
typedef struct undo_stack log;

#define topRight 1
#define bottomRight 2
#define topLeft 3
#define bottomLeft 4
//const int WHITE = 15, BLACK = 0;

#define colorFlip(i) (i ^ (1 << 0) ^ (1 << 1) ^ (1 << 2) ^ (1 << 3))
// if i is WHITE, converts it to black and vice-versa

game_state c_state;

struct pieces
{
    int x;
    int y;
    int allegiance; // Whose team is it on?
    bool is_king;   // Is it king yet?
};
typedef struct coords
{
    int x;
    int y;
} coords;
struct board
{
    pawn white[12]; // stores info about 12 white elements
    pawn black[12]; // stores info about 12 black elements
    coords hover[2];
    int cur_turn;   // Whose turn is it at this particular state
};

struct move // move will store new posn of piece after a move is made // to be returned from best_move
{
    pawn piece;
    int x_new;
    int y_new;
};
struct undo_stack // stores the data using doubly linked list
{
    game_state g;
    struct undo_stack *next;
    struct undo_stack *prev;
};

//make bot
void init_game_2players(void); //starts the game with 2 players mode
void init_game_bot(void);      //starts the game with bot

void start(void);
void resign(game_state *g);
void draw(game_state *g);
void toss(void);

//update board
// horz and vert will tell in which direction we have to move the pawn p
bool move_entries(game_state *g, pawn p, int horizontal, int vertical); // Function to move one of the pawns
/*
in this function i am writing here but after .c is made paste it there,
we have to update board which involves lots of subfunctions like checking if move is legal or not
also we have to update the position. and additional features if one can add (using \b) sounds to show moves
*/

bool isOccupied(game_state *g, int x, int y); // checks if coordinates (x ,y) are occupied on board
bool is_present(game_state *g, pawn P);       // returns true if P is present on board
bool capturePossible(game_state *g, pawn P, int direction);
// checks if capture is possible from P in a direction
// direction can be one of the four: topLeft, bottomLeft, topRight and bottomRight
bool simple_Move_Possible(game_state *g, pawn P, int direction);

void print_board(game_state *P);
void undo(log *head);                              // undo the last move taken
void review(log *head);                            // print boards in order from 1 to last
void add_board(game_state p, log *head);           // after every move , add game state to it
void rule(void);                                   //just prints rule book
bool isLegal(pawn p, pawn new_pos, game_state *g); // Need a 'from' and a 'to'// will return the id. of rule which is voilated
void result(game_state *P);                        //tells the result of the game // will simply print a string

//interface
/* 
we have to make elegant impresion and to fully appriciate the function print board, we have to create 
a game like interface for board. apart from that we also want function to show legal moves
i cant think of functions data types so plz excuse me.....
*/

//analysis
void review();                              //slideshow of board , added:- we will be using a global stack , no need to pass anything in review, undo etc
void show_all_possible_moves(game_state P); //print all possible moves in simple algebraic manner
move best_move(game_state P);               //tells best move we can go upto depth of 2/3 or as we discussed as far as 10
//void evaluation_bar(game_state P); //its hard to do so..but ok i wrote it , not required , these parameters are best kept out of the view of the player , they will be used just for the bot
void controller();
/*
NOTES- 
after a move is played by running a command, we will print board interface and subseq. after user types next move 
command we will clear screen and prints the board.
similarly when user prints undo, we print prev board configurations.
*/

#endif
