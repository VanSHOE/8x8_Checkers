#ifndef HEADER
#define HEADER
#include <stdbool.h>

#define ll long long

typedef struct board game_state; //game state
typedef struct pieces pawn;
typedef struct move move;
typedef struct undo_stack log;
typedef struct node node;
#define topRight 1
#define bottomRight 2
#define topLeft 3
#define bottomLeft 4
// WHITE = 15, BLACK = 0;
//At start of game white occupies row 0,1,2 and black occupies row 5,6,7.
int difficulty = 0;                       // 0 - hardest, 1 - medium , 2 - easy
#define sb 8                              //size of board
const int tp = (sb / 2) * ((sb - 2) / 2); // total pieces
#define colorFlip(i) (i ^ (1 << 0) ^ (1 << 1) ^ (1 << 2) ^ (1 << 3))
// if i is WHITE, converts it to black and vice-versa

int bot_mode = WHITE; // -1: 2 player mode ; 0: Black is bot ; 15: White is bot

typedef struct
{
    int score;
    int index;
} nodeb; //this struct is for bot heap implementation

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
    pawn white[(sb / 2) * ((sb - 2) / 2)]; // stores info about 12 white elements
    pawn black[(sb / 2) * ((sb - 2) / 2)]; // stores info about 12 black elements
    coords hover[2];
    int cur_turn; // Whose turn is it at this particular state // 0 is for black , 15 is for white
};

struct move // move will store new position of piece after a move is made
{
    pawn piece;
    int x_new;
    int y_new;
};

struct node
{
    node *array[(sb / 2) * ((sb - 2) / 2)][4]; // at each turn , at max all 12 pieces of that color can move in at max 4 dirn
    node *next_board;
    node *prev_board; // will store address of previous posn
    game_state board; // will store the current board
    int depth;        // will store the depth of each node from root node(depth ==0)
};

struct undo_stack // stores the data using doubly linked list
{
    game_state g;
    struct undo_stack *next;
    struct undo_stack *prev;
};

typedef struct he
{
    int index;
    ll d;
} he;


game_state c_state;

bool is_multi_capture_possible(game_state g); // to check if multiple captures are possible while calculating score by bot
void start(log *head);
void restart(log *head);
void Quit(log *head);
void menu(log *head);
void draw(game_state *g, log *head);
int toss(void);
void instruction();
void clear_stack(log *head); // used in restart function to empty the stack

//update board
// horizontal and vertical will tell in which direction we have to move the pawn p
bool move_entries(game_state *g, pawn p, int horizontal, int vertical); // Function to move one of the pawns
bool isOccupied(game_state *g, int x, int y);                           // checks if coordinates (x ,y) are occupied on board
bool is_present(game_state *g, pawn P);                                 // returns true if P is present on board
bool capturePossible(game_state *g, pawn P, int direction);
// checks if capture is possible from P in a direction
// direction can be one of the four: topLeft, bottomLeft, topRight and bottomRight
bool simple_Move_Possible(game_state *g, pawn P, int direction);

log *CreateEmptyStackNode();
void push(log *head, game_state *preState);
void print_board(game_state *P);
game_state undo(log *head);                        // undo the last move taken
void review(log *head);                            // prints all the boards in the game
void add_board(game_state p, log *head);           // after every move , add game state to it
void rule(void);                                   //just prints rule book
bool isLegal(pawn p, pawn new_pos, game_state *g); // returns true if a move from coordinates of p to coordinates of new_pos is "legal"
void result(game_state *P, log *head);             //tells the result of the game // will simply print a string

void print_all_possible_next_move(node *current); // given a game state , what all possible can be achieved in next move
void point_to_null(node *p); // take ptr to node and initialize each of its child to null
void reached_how(node *final); // will tell how we reached a particular board position // every node contains address of its parent node
void filling_node(node *current, game_state p, int k);
// takes a node , find which colors turn it is , and then fills the array accodingly if the move can be played by that color
void print_k_state(game_state p, int k);

void controller(log *head);

void siftup(int index);
void DownHeap(int index);
void insert(he elem);
he Extract_max();

long double bot_helperb(game_state g_o, int lim);
void botb()
long double bot_helperw(game_state g_o, int lim)
void botw()




#endif