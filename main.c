#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <time.h>
#include "rlutil.h"
#include "checkers.h"
#include <stdbool.h>

void print_all_possible_next_move(node *current) // given a game state , what all possible can be achieved in next move
{
    // array will contain board condition possible after a piece whose turn it should be has been moved
    for (int i = 0; i < 12; i++) // selecting the piece
    {
        for (int j = 0; j < 4; j++) // selecting the dirn
        {
            if (current->array[i][j] != NULL) // cheching if that piece is available or dirn is valid
            {
                print_board(&(current->array[i][j]->board)); // printing the board after that move has been performed
            }
        }
    }
}

void point_to_null(node *p) // take ptr to node and initialize each of its child to null
{
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 4; j++)
            p->array[i][j] = NULL;
    }
}

// #define topRight 1
// #define bottomRight 2
// #define topLeft 3
// #define bottomLeft 4

void filling_node(node *current, game_state p) // takes a node , find which colors turn it is , and then fills the array accodingly if the move can be played by that color
{
    if (p.cur_turn == 0) // means black pieces will have to move
    {
        for (int i = 0; i < 12; i++) // selecting which black piece
        {
            //if that piece is not available then continue
            if (!is_present(&p, p.black[i]))
                continue;

            // taking j  0 -> top left/ 1 -> top right / 2 -> left bottom / 3 -> right bottom
            for (int j = 0; j < 4; j++) // selecting if that piece can move in that dirn or not
            {
                // first checking if this piece is king or not
                if (p.black[i].is_king == true) // have to check all 4 directions
                {
                    if (j == 0)
                    {
                        //checking if simple move is poosible in this direction
                        if (simple_Move_Possible(&p, p.black[i], topLeft))
                        {
                            // finding the board after the move is made
                            game_state board_next = play_simple_move(p, p.black[i], topLeft); // fix the error

                            //allocating memory
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                            point_to_null(current->array[i][j]);
                        }
                        //else we will check if capturing another color piece is possible in that direction
                        else if (capturePossible(&p, p.black[i], topLeft))
                        {
                            game_state board_next = play_capture_move(p, p.black[i], topLeft);

                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                            point_to_null(current->array[i][j]);
                        }
                    }

                    else if (j == 1)
                    {
                        //checking if simple move is poosible in this direction
                        if (simple_Move_Possible(&p, p.black[i], topRight))
                        {
                            // finding the board after the move is made
                            game_state board_next = play_simple_move(p, p.black[i], topRight); // fix the error

                            //allocating memory
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                            point_to_null(current->array[i][j]);
                        }
                        //else we will check if capturing another color piece is possible in that direction
                        else if (capturePossible(&p, p.black[i], topRight))
                        {
                            game_state board_next = play_capture_move(p, p.black[i], topRight);

                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                            point_to_null(current->array[i][j]);
                        }
                    }

                    else if (j == 2)
                    {
                        //checking if simple move is poosible in this direction
                        if (simple_Move_Possible(&p, p.black[i], bottomLeft))
                        {
                            // finding the board after the move is made
                             game_state board_next =  play_simple_move(p , p.black[i] , bottomLeft);  // fix the error
                             
                             //allocating memory 
                             current->array[i][j] = (node*)malloc(sizeof(node));
                             current->array[i][j]->next_board = NULL;
                             current->array[i][j]->prev_board = current;
                             current->array[i][j]->board = board_next;
                             point_to_null(current->array[i][j]);

                        }
                        //else we will check if capturing another color piece is possible in that direction
                        else if (capturePossible(&p , p.black[i] , bottomLeft))
                        {
                             game_state board_next =  play_capture_move(p , p.black[i] , bottomLeft);

                             current->array[i][j] = (node*)malloc(sizeof(node));
                             current->array[i][j]->next_board = NULL;
                             current->array[i][j]->prev_board = current;
                             current->array[i][j]->board = board_next;
                             point_to_null(current->array[i][j]);
                        }
                    }

                    else if (j == 3)
                    {
                        //checking if simple move is poosible in this direction
                        if (simple_Move_Possible(&p, p.black[i], bottomRight))
                        {
                            // finding the board after the move is made
                             game_state board_next =  play_simple_move(p , p.black[i] , bottomRight);  // fix the error
                             
                             //allocating memory 
                             current->array[i][j] = (node*)malloc(sizeof(node));
                             current->array[i][j]->next_board = NULL;
                             current->array[i][j]->prev_board = current;
                             current->array[i][j]->board = board_next;
                             point_to_null(current->array[i][j]);

                        }
                        //else we will check if capturing another color piece is possible in that direction
                        else if (capturePossible(&p , p.black[i] , bottomRight))
                        {
                             game_state board_next =  play_capture_move(p , p.black[i] , bottomRight);

                             current->array[i][j] = (node*)malloc(sizeof(node));
                             current->array[i][j]->next_board = NULL;
                             current->array[i][j]->prev_board = current;
                             current->array[i][j]->board = board_next;
                             point_to_null(current->array[i][j]);
                        }
                    }
                }

                else // have to check only bottomLeft and bottomRight only
                {
                    if (j == 2)
                    {
                        //checking if simple move is poosible in this direction
                        if (simple_Move_Possible(&p, p.black[i], bottomLeft))
                        {
                            // finding the board after the move is made
                             game_state board_next =  play_simple_move(p , p.black[i] , bottomLeft);  // fix the error
                             
                             //allocating memory 
                             current->array[i][j] = (node*)malloc(sizeof(node));
                             current->array[i][j]->next_board = NULL;
                             current->array[i][j]->prev_board = current;
                             current->array[i][j]->board = board_next;
                             point_to_null(current->array[i][j]);

                        }
                        //else we will check if capturing another color piece is possible in that direction
                        else if (capturePossible(&p , p.black[i] , bottomLeft))
                        {
                             game_state board_next =  play_capture_move(p , p.black[i] , bottomLeft);

                             current->array[i][j] = (node*)malloc(sizeof(node));
                             current->array[i][j]->next_board = NULL;
                             current->array[i][j]->prev_board = current;
                             current->array[i][j]->board = board_next;
                             point_to_null(current->array[i][j]);
                        }
                    }
                    else if (j == 3)
                    {
                       //checking if simple move is poosible in this direction
                        if (simple_Move_Possible(&p, p.black[i], bottomRight))
                        {
                            // finding the board after the move is made
                             game_state board_next =  play_simple_move(p , p.black[i] ,bottomRight);  // fix the error
                             
                             //allocating memory 
                             current->array[i][j] = (node*)malloc(sizeof(node));
                             current->array[i][j]->next_board = NULL;
                             current->array[i][j]->prev_board = current;
                             current->array[i][j]->board = board_next;
                             point_to_null(current->array[i][j]);

                        }
                        //else we will check if capturing another color piece is possible in that direction
                        else if (capturePossible(&p , p.black[i] , bottomRight))
                        {
                             game_state board_next =  play_capture_move(p , p.black[i] , bottomRight);

                             current->array[i][j] = (node*)malloc(sizeof(node));
                             current->array[i][j]->next_board = NULL;
                             current->array[i][j]->prev_board = current;
                             current->array[i][j]->board = board_next;
                             point_to_null(current->array[i][j]);
                        } 
                    }
                }
            }
        }
    }
    else // means white pieces have to move
    {
        for (int i = 0; i < 12; i++) // selecting which black piece
        {
            //if that piece is not available then continue
            if (!is_present(&p, p.white[i]))
                continue;

            // taking j  0 -> top left/ 1 -> top right / 2 -> left bottom / 3 -> right bottom
            for (int j = 0; j < 4; j++) // selecting if that piece can move in that dirn or not
            {
                // first checking if this piece is king or not
                if (p.white[i].is_king == true) // have to check all 4 directions
                {
                    if (j == 0)
                    {
                        //checking if simple move is poosible in this direction
                        if (simple_Move_Possible(&p, p.white[i], topLeft))
                        {
                            // finding the board after the move is made
                            game_state board_next = play_simple_move(p, p.white[i], topLeft); // fix the error

                            //allocating memory
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                            point_to_null(current->array[i][j]);
                        }
                        //else we will check if capturing another color piece is possible in that direction
                        else if (capturePossible(&p, p.white[i], topLeft))
                        {
                            game_state board_next = play_capture_move(p, p.white[i], topLeft);

                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                            point_to_null(current->array[i][j]);
                        }
                    }

                    else if (j == 1)
                    {
                        //checking if simple move is poosible in this direction
                        if (simple_Move_Possible(&p, p.white[i], topRight))
                        {
                            // finding the board after the move is made
                            game_state board_next = play_simple_move(p, p.white[i], topRight); // fix the error

                            //allocating memory
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                            point_to_null(current->array[i][j]);
                        }
                        //else we will check if capturing another color piece is possible in that direction
                        else if (capturePossible(&p, p.white[i], topRight))
                        {
                            game_state board_next = play_capture_move(p, p.white[i], topRight);

                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                            point_to_null(current->array[i][j]);
                        }
                    }

                    else if (j == 2)
                    {
                        //checking if simple move is poosible in this direction
                        if (simple_Move_Possible(&p, p.white[i], bottomLeft))
                        {
                            // finding the board after the move is made
                             game_state board_next =  play_simple_move(p , p.white[i] , bottomLeft);  // fix the error
                             
                             //allocating memory 
                             current->array[i][j] = (node*)malloc(sizeof(node));
                             current->array[i][j]->next_board = NULL;
                             current->array[i][j]->prev_board = current;
                             current->array[i][j]->board = board_next;
                             point_to_null(current->array[i][j]);

                        }
                        //else we will check if capturing another color piece is possible in that direction
                        else if (capturePossible(&p , p.white[i] , bottomLeft))
                        {
                             game_state board_next =  play_capture_move(p , p.white[i] , bottomLeft);

                             current->array[i][j] = (node*)malloc(sizeof(node));
                             current->array[i][j]->next_board = NULL;
                             current->array[i][j]->prev_board = current;
                             current->array[i][j]->board = board_next;
                             point_to_null(current->array[i][j]);
                        }
                    }

                    else if (j == 3)
                    {
                        //checking if simple move is poosible in this direction
                        if (simple_Move_Possible(&p, p.white[i], bottomRight))
                        {
                            // finding the board after the move is made
                             game_state board_next =  play_simple_move(p , p.white[i] , bottomRight);  // fix the error
                             
                             //allocating memory 
                             current->array[i][j] = (node*)malloc(sizeof(node));
                             current->array[i][j]->next_board = NULL;
                             current->array[i][j]->prev_board = current;
                             current->array[i][j]->board = board_next;
                             point_to_null(current->array[i][j]);

                        }
                        //else we will check if capturing another color piece is possible in that direction
                        else if (capturePossible(&p , p.white[i] , bottomRight))
                        {
                             game_state board_next =  play_capture_move(p , p.white[i] , bottomRight);

                             current->array[i][j] = (node*)malloc(sizeof(node));
                             current->array[i][j]->next_board = NULL;
                             current->array[i][j]->prev_board = current;
                             current->array[i][j]->board = board_next;
                             point_to_null(current->array[i][j]);
                        }
                    }
                }

                else // have to check only topRight and topLeft only
                {
                    if (j == 0)
                    {
                        //checking if simple move is poosible in this direction
                        if (simple_Move_Possible(&p, p.white[i], topLeft))
                        {
                            // finding the board after the move is made
                             game_state board_next =  play_simple_move(p , p.white[i] , topLeft);  // fix the error
                             
                             //allocating memory 
                             current->array[i][j] = (node*)malloc(sizeof(node));
                             current->array[i][j]->next_board = NULL;
                             current->array[i][j]->prev_board = current;
                             current->array[i][j]->board = board_next;
                             point_to_null(current->array[i][j]);

                        }
                        //else we will check if capturing another color piece is possible in that direction
                        else if (capturePossible(&p , p.white[i] , topLeft))
                        {
                             game_state board_next =  play_capture_move(p , p.white[i] , topLeft);

                             current->array[i][j] = (node*)malloc(sizeof(node));
                             current->array[i][j]->next_board = NULL;
                             current->array[i][j]->prev_board = current;
                             current->array[i][j]->board = board_next;
                             point_to_null(current->array[i][j]);
                        }
                    }
                    else if (j == 1)
                    {
                       //checking if simple move is poosible in this direction
                        if (simple_Move_Possible(&p, p.white[i], topRight))
                        {
                            // finding the board after the move is made
                             game_state board_next =  play_simple_move(p , p.white[i] ,topRight);  // fix the error
                             
                             //allocating memory 
                             current->array[i][j] = (node*)malloc(sizeof(node));
                             current->array[i][j]->next_board = NULL;
                             current->array[i][j]->prev_board = current;
                             current->array[i][j]->board = board_next;
                             point_to_null(current->array[i][j]);

                        }
                        //else we will check if capturing another color piece is possible in that direction
                        else if (capturePossible(&p , p.white[i] , topRight))
                        {
                             game_state board_next =  play_capture_move(p , p.white[i] , topRight);

                             current->array[i][j] = (node*)malloc(sizeof(node));
                             current->array[i][j]->next_board = NULL;
                             current->array[i][j]->prev_board = current;
                             current->array[i][j]->board = board_next;
                             point_to_null(current->array[i][j]);
                        } 
                    }
                }
            }
        }
    }
}



bool move_entries(game_state *g, pawn P, int horizontal, int vertical)
{
    if (!is_present(g, P))
    {
        printf("NOT PRESENT\n");
        return false;
    }
    pawn n;
    n.x = horizontal;
    n.y = vertical;
    if (!isLegal(P, n, g))
    {
        printf("NOT LEGAL\n");
        return false;
    }
    // printf("WORKING\n");
    if (P.allegiance == BLACK)
    { //printf("WORKINGb\n");
        for (int i = 0; i < 12; ++i)
        {
            if (P.x == g->black[i].x && P.y == g->black[i].y)
            {
                g->black[i].x = horizontal;
                g->black[i].y = vertical;

                if (g->black[i].y == 0) // black piece reached to row 0
                    g->black[i].is_king = 1;
            }
        }
    }
    else if (P.allegiance == WHITE)
    {

        for (int i = 0; i < 12; ++i)
        {
            if (P.x == g->white[i].x && P.y == g->white[i].y)
            { //   printf("OLD:%d, %d ; New: %d , %d\n",g->white[i].x, g->white[i].y,horizontal,vertical);
                g->white[i].x = horizontal;
                g->white[i].y = vertical;

                if (g->white[i].y == 7) // white piece reached to row 7
                    g->white[i].is_king = 1;
            }
        }
    }
    return true;
}

void print_board(game_state *P)
{
    int c_s = 4, r_s = 8;
    int b[8][8] = {0};
    resetColor();
    int yc1 = 7 - P->hover[0].y;
    int xc1 = P->hover[0].x;
    int yc2 = 7 - P->hover[1].y;
    int xc2 = P->hover[1].x;
    for (int i = 0; i < 12; i++)
    {
        b[7 - P->black[i].y][P->black[i].x] = 1;
        b[7 - P->white[i].y][P->white[i].x] = 2;
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            printf("%d ", b[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i <= 8 * c_s; i++)
    {
        for (int j = 0; j <= 8 * r_s; j++)
        {
            setBackgroundColor(BLACK);
            if (i % (c_s) == 0 && j % (r_s) == 0)
            {
                printf("+");
            }
            else if (i % (c_s) == 0)
                printf("-");
            else if (j % (r_s) == 0)
            {
                printf("|");
            }
            else
            {
                if ((i / c_s) == yc1 && j / r_s == xc1)
                {
                    setBackgroundColor(RED);
                }
                else if ((i / c_s) == yc2 && j / r_s == xc2)
                {
                    setBackgroundColor(RED);
                }

                else if (((i / c_s) + (j / r_s)) % 2 == 0)
                {
                    setBackgroundColor(7);
                }
                else
                    setBackgroundColor(2);
                if ((i % c_s == c_s / 2) && (j % r_s == r_s / 2))
                {

                    if (b[i / c_s][j / r_s] == 1)
                    {
                        setColor(BLACK);
                        printf("@");
                    }
                    else if (b[i / c_s][j / r_s] == 2)
                    {
                        setColor(WHITE);
                        printf("@");
                    }
                    else
                        printf(" ");
                    resetColor();
                }
                else
                    printf(" ");
                resetColor();
            }
        }
        resetColor();
        printf("\n");
    }
}

bool isOccupied(game_state *g, int x, int y)
{
    for (int i = 0; i < 12; ++i)
    {
        if ((x == g->white[i].x && y == g->white[i].y) || (x == g->black[i].x && y == g->black[i].y))
        {
            return true;
        }
    }
    return false;
}

bool is_present(game_state *g, pawn P)
{
    if (P.allegiance == BLACK)
    {
        for (int i = 0; i < 12; ++i)
        {
            if (P.x == g->black[i].x && P.y == g->black[i].y)
                return true;
        }
    }
    else if (P.allegiance == WHITE)
    {
        for (int i = 0; i < 12; ++i)
        {
            if (P.x == g->white[i].x && P.y == g->white[i].y)
                return true;
        }
    }
    return false;
}

// topRight       1
// bottomRight    2
// topLeft        3
// bottomLeft     4

bool simple_Move_Possible(game_state *g, pawn P, int direction)
{
    int AfterMove_X, AfterMove_Y;
    switch (direction)
    {
    case topRight:
        if (P.x + 1 > 7 || P.y + 1 > 7)
            return false;
        AfterMove_X = P.x + 1;
        AfterMove_Y = P.y + 1;
        break;
    case bottomRight:
        if (P.x + 1 > 7 || P.y - 1 < 0)
            return false;
        AfterMove_X = P.x + 1;
        AfterMove_Y = P.y - 1;
        break;
    case topLeft:
        if (P.x - 1 < 0 || P.y + 1 > 7)
            return false;
        AfterMove_X = P.x - 1;
        AfterMove_Y = P.y + 1;
        break;
    case bottomLeft:
        if (P.x - 1 < 0 || P.y - 1 < 0)
            return false;
        AfterMove_X = P.x - 1;
        AfterMove_Y = P.y - 1;
        break;
    }
    if (!isOccupied(g, AfterMove_X, AfterMove_Y))
        return true;
    else
        return false;
}

bool capturePossible(game_state *g, pawn P, int direction)
{
    pawn Enemy;
    int AfterCapture_X, AfterCapture_Y;
    switch (direction)
    {
    case topRight:
        if (P.x + 2 > 7 || P.y + 2 > 7)
            return false;
        AfterCapture_X = P.x + 2;
        AfterCapture_Y = P.y + 2;
        Enemy.x = P.x + 1;
        Enemy.y = P.y + 1;
        Enemy.allegiance = colorFlip(P.allegiance);
        break;
    case bottomRight:
        if (P.x + 2 > 7 || P.y - 2 < 0)
            return false;
        AfterCapture_X = P.x + 2;
        AfterCapture_Y = P.y - 2;
        Enemy.x = P.x + 1;
        Enemy.y = P.y - 1;
        Enemy.allegiance = colorFlip(P.allegiance);
        break;
    case topLeft:
        if (P.x - 2 < 0 || P.y + 2 > 7)
            return false;
        AfterCapture_X = P.x - 2;
        AfterCapture_Y = P.y + 2;
        Enemy.x = P.x - 1;
        Enemy.y = P.y + 1;
        Enemy.allegiance = colorFlip(P.allegiance);
        break;
    case bottomLeft:
        if (P.x - 2 < 0 || P.y - 2 < 0)
            return false;
        AfterCapture_X = P.x - 2;
        AfterCapture_Y = P.y - 2;
        Enemy.x = P.x - 1;
        Enemy.y = P.y - 1;
        Enemy.allegiance = colorFlip(P.allegiance);
        break;
    }

    // AfterCapture position is not occupied and
    // Enemy piece is present on the diagonal between P and AfterCapture
    if (!isOccupied(g, AfterCapture_X, AfterCapture_Y) && is_present(g, Enemy))
        return true;
    else
        return false;
}

bool isLegal(pawn p, pawn new_pos, game_state *g)
{
    if (p.x < 0 || p.y < 0 || p.x > 7 || p.y > 7) // x and y between 0 and 7
        return false;
    if (new_pos.x < 0 || new_pos.y < 0 || new_pos.x > 7 || new_pos.y > 7)
        return false;

    if (!p.is_king) // if not a king
    {
        // if white, check if moves UP on board
        if (p.allegiance == WHITE && !(new_pos.y > p.y))
            return false;
        // if black, check if moves DOWN on board
        if (p.allegiance == BLACK && !(new_pos.y < p.y))
            return false;
    }

    int x_diff = abs(p.x - new_pos.x);
    int y_diff = abs(p.y - new_pos.y);

    if (x_diff < 1 || y_diff < 1 || x_diff > 2 || y_diff > 2) // invalid move
        return false;

    if (x_diff != y_diff)
        return false;
    if (!isOccupied(g, p.x, p.y)) // check if p is present in board
    {
        return false;
    }

    if (isOccupied(g, new_pos.x, new_pos.y)) // check if the new_pos coordinates are empty
    {
        return false;
    }

    if (x_diff == 1 && y_diff == 1)
    {
        // move is value only if any capture is not possible
        if (p.is_king)
        {
            if (!(new_pos.x > p.x && new_pos.y > p.y) &&
                capturePossible(g, p, topRight))
                return false;
            if (!(new_pos.x > p.x && new_pos.y < p.y) &&
                capturePossible(g, p, bottomRight))
                return false;
            if (!(new_pos.x < p.x && new_pos.y > p.y) &&
                capturePossible(g, p, topLeft))
                return false;
            if (!(new_pos.x < p.x && new_pos.y < p.y) &&
                capturePossible(g, p, bottomLeft))
                return false;
        }
        else
        {
            if (p.allegiance == WHITE)
            {
                if (new_pos.x < p.x && capturePossible(g, p, topRight))
                    return false;
                if (new_pos.x > p.x && capturePossible(g, p, topLeft))
                    return false;
            }
            else if (p.allegiance == BLACK)
            {
                if (new_pos.x < p.x && capturePossible(g, p, bottomRight))
                    return false;
                if (new_pos.x > p.x && capturePossible(g, p, bottomLeft))
                    return false;
            }
        }

        return true;
    }

    if (x_diff == 2 && y_diff == 2)
    {
        if (p.is_king)
        {
            // if destination is topRight jump, check if capturePossible
            if (new_pos.x > p.x && new_pos.y > p.y &&
                capturePossible(g, p, topRight))
                return true;

            // if destination is bottomRight jump, check if capturePossible
            if (new_pos.x > p.x && new_pos.y < p.y &&
                capturePossible(g, p, bottomRight))
                return true;

            // if destination is topLeft jump, check if capturePossible
            if (new_pos.x < p.x && new_pos.y > p.y &&
                capturePossible(g, p, topLeft))
                return true;

            // if destination is topRight jump, check if capturePossible
            if (new_pos.x < p.x && new_pos.y < p.y &&
                capturePossible(g, p, bottomLeft))
                return true;
        }
        else
        {
            if (p.allegiance == WHITE)
            {
                if (new_pos.x > p.x && capturePossible(g, p, topRight))
                    return true;
                if (new_pos.x < p.x && capturePossible(g, p, topLeft))
                    return true;
            }
            else if (p.allegiance == BLACK)
            {
                if (new_pos.x > p.x && capturePossible(g, p, bottomRight))
                    return true;
                if (new_pos.x < p.x && capturePossible(g, p, bottomLeft))
                    return true;
            }
        }

        return false;
    }

    return false;
}

void start()
{
    int cur_pc = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if ((i + j) % 2 == 0)
            {
                c_state.white[cur_pc].allegiance = WHITE;
                c_state.white[cur_pc].is_king = 0;
                c_state.white[cur_pc].x = j;
                c_state.white[cur_pc++].y = i;
            }
        }
    }
    cur_pc = 0;
    for (int i = 7; i >= 5; i--)
    {
        for (int j = 0; j < 8; j++)
        {
            if ((i + j) % 2 == 0)
            {
                c_state.black[cur_pc].allegiance = BLACK;
                c_state.black[cur_pc].is_king = 0;
                c_state.black[cur_pc].x = j;
                c_state.black[cur_pc++].y = i;
            }
        }
    }
    c_state.cur_turn = BLACK;
    controller();
    //    print_board(&c_state);
}

void undo(log *head) //undo fxn go one steps back and deletes the current state
{
    if (head->next->next == NULL) // no move has been made , so returns the initial board
    {
        printf("Atleast one move has to be made to use undo fxn\n");
        print_board(&(head->next->g));
        return;
    }
    // atleast one move has been taken // delete the log of current state
    log *temp = head->next;
    head->next = head->next->next;
    head->next->prev = head;
    free(temp);
    print_board(&(head->next->g));
    return;
}

void review(log *head)
{
    log *last = head->prev;
    log *temp = head->prev;

    while (temp->prev != last)
    {
        print_board(&(temp->g));
        temp = temp->prev;
    }
}

void result(game_state *P)
{
    int white_pieces_left = 0;
    int black_pieces_left = 0;

    for (int i = 0; i < 12; i++)
    {
        if (P->white[i].x != -1) // for piece that has got out , its x and y position will be -1
        {
            white_pieces_left++;
        }
        if (P->black[i].x != -1)
        {
            black_pieces_left++;
        }
    }

    if (white_pieces_left == 0)
    {
        printf("Black is the winner\n");
        return;
    }
    else if (black_pieces_left == 0)
    {
        printf("White is the winner\n");
        return;
    }
    else // in this case , no. of pieces left of both color will be non zero
    {
        bool white_draw_Check = true, black_draw_Check = true; // if both are true -> DRAW

        for (int i = 0; i < 12; ++i)
        {
            if (P->black[i].x != -1)
            {
                if (simple_Move_Possible(P, P->black[i], bottomRight) ||
                    simple_Move_Possible(P, P->black[i], bottomLeft) ||
                    capturePossible(P, P->black[i], bottomRight) ||
                    capturePossible(P, P->black[i], bottomLeft))
                {
                    black_draw_Check = false;
                    if (!white_draw_Check && !black_draw_Check)
                        break;
                }
                else if (P->black[i].is_king)
                {
                    if (simple_Move_Possible(P, P->black[i], topRight) ||
                        simple_Move_Possible(P, P->black[i], topLeft) ||
                        capturePossible(P, P->black[i], topRight) ||
                        capturePossible(P, P->black[i], topLeft))
                    {
                        black_draw_Check = false;
                        if (!white_draw_Check && !black_draw_Check)
                            break;
                    }
                }
            }

            if (P->white[i].x != -1)
            {
                if (simple_Move_Possible(P, P->white[i], topRight) ||
                    simple_Move_Possible(P, P->white[i], topLeft) ||
                    capturePossible(P, P->white[i], topRight) ||
                    capturePossible(P, P->white[i], topLeft))
                {
                    white_draw_Check = false;
                    if (!white_draw_Check && !black_draw_Check)
                        break;
                }
                else if (P->white[i].is_king)
                {
                    if (simple_Move_Possible(P, P->white[i], bottomRight) ||
                        simple_Move_Possible(P, P->white[i], bottomLeft) ||
                        capturePossible(P, P->white[i], bottomRight) ||
                        capturePossible(P, P->white[i], bottomLeft))
                    {
                        white_draw_Check = false;
                        if (!white_draw_Check && !black_draw_Check)
                            break;
                    }
                }
            }
        }

        if (!white_draw_Check && !black_draw_Check)
        {
            // no draw.. game continues
        }

        if (white_draw_Check && black_draw_Check)
        {
            printf("Match has been drawed\n");
        }
        else
        {
            if (!white_draw_Check && black_draw_Check)
            {
                printf("White is the winner\n");
            }

            if (white_draw_Check && !black_draw_Check)
            {
                printf("Black is the winner\n");
            }
        }

        return;
    }
}

void draw(game_state *P) // just call this fxn and it will print who is the winner and the current board
{
    result(P);
    print_board(P);
}

void add_board(game_state p, log *head) // after every move , add game state to it
{
    log *temp = (log *)malloc(sizeof(log));
    temp->g = p;
    temp->next = head->next;

    if (head->next != NULL)
        head->next->prev = temp;

    head->next = temp;
    temp->prev = head;
    if (temp->next == NULL)
        head->prev = temp;
}

void controller()
{
    pawn p;
    if (c_state.cur_turn == BLACK)
    {
        int c = 10;
        int x[2];
        int y[2];
        x[0] = c_state.black[c].x;
        y[0] = c_state.black[c].y;
        x[1] = y[1] = -1;
        int cur = 0;

        while (1)
        {
            c_state.hover[0].x = x[0];
            c_state.hover[0].y = y[0];
            c_state.hover[1].x = x[1];
            c_state.hover[1].y = y[1];

            //    cls();
            locate(1, 1);
            hidecursor();
            print_board(&c_state);
            char ch = getkey();
            if (ch == 'd')
            {
                x[cur] = (x[cur] + 1) % 8;
            }
            else if (ch == 's')
            {
                y[cur] = (y[cur] - 1) % 8;
                if (y[cur] < 0)
                    y[cur] += 8;
            }
            else if (ch == 'w')
            {
                y[cur] = (y[cur] + 1) % 8;
            }
            else if (ch == 'a')
            {
                x[cur] = (x[cur] - 1) % 8;
                if (x[cur] < 0)
                    x[cur] += 8;
            }
            else if (ch == 'r')
            {
                cls();
            }
            else if (ch == KEY_SPACE)
            {
                if (cur == 0)
                {
                    int flag = -1;
                    for (int i = 0; i < 12; ++i)
                    {
                        if (x[0] == c_state.black[i].x && y[0] == c_state.black[i].y)
                        {
                            flag = i;
                            x[1] = x[0];
                            y[1] = y[0];
                            p = c_state.black[i];
                            break;
                        }
                    }
                    if (flag == -1)
                        continue;
                    cur++;
                }
                else
                {
                    if (x[1] == x[0] && y[0] == y[1])
                    {
                        cur--;
                        x[1] = -1;
                        y[1] = -1;
                        continue;
                    }

                    pawn n;
                    n.x = x[1];
                    n.y = y[1];
                    if (!move_entries(&c_state, p, x[1], y[1]))
                    {
                        continue;
                    }
                    else
                    {
                        cur--;
                        x[0] = x[1];
                        y[0] = y[1];
                        x[1] = -1;
                        y[1] = -1;
                        c_state.cur_turn = WHITE;
                        break;
                    }
                }
            }
        }
    }
    else
    {
        int c = 10;
        int x[2];
        int y[2];
        x[0] = c_state.white[c].x;
        y[0] = c_state.white[c].y;
        x[1] = y[1] = -1;
        int cur = 0;
        while (1)
        {
            c_state.hover[0].x = x[0];
            c_state.hover[0].y = y[0];
            c_state.hover[1].x = x[1];
            c_state.hover[1].y = y[1];

            //    cls();
            locate(1, 1);
            hidecursor();
            print_board(&c_state);
            char ch = getkey();
            if (ch == 'd')
            {
                x[cur] = (x[cur] + 1) % 8;
            }
            else if (ch == 's')
            {
                y[cur] = (y[cur] - 1) % 8;
                if (y[cur] < 0)
                    y[cur] += 8;
            }
            else if (ch == 'w')
            {
                y[cur] = (y[cur] + 1) % 8;
            }
            else if (ch == 'a')
            {
                x[cur] = (x[cur] - 1) % 8;
                if (x[cur] < 0)
                    x[cur] += 8;
            }
            else if (ch == 'r')
            {
                cls();
            }
            else if (ch == KEY_SPACE)
            {
                if (cur == 0)
                {
                    int flag = -1;
                    for (int i = 0; i < 12; ++i)
                    {
                        if (x[0] == c_state.white[i].x && y[0] == c_state.white[i].y)
                        {
                            flag = i;
                            x[1] = x[0];
                            y[1] = y[0];
                            p = c_state.white[i];
                            break;
                        }
                    }
                    if (flag == -1)
                        continue;
                    cur++;
                }
                else
                {
                    if (x[1] == x[0] && y[0] == y[1])
                    {
                        cur--;
                        x[1] = -1;
                        y[1] = -1;
                        continue;
                    }

                    pawn n;
                    n.x = x[1];
                    n.y = y[1];
                    if (!move_entries(&c_state, p, x[1], y[1]))
                    {
                        continue;
                    }
                    else
                    {
                        cur--;
                        x[0] = x[1];
                        y[0] = y[1];
                        x[1] = -1;
                        y[1] = -1;
                        c_state.cur_turn = BLACK;
                        break;
                    }
                }
            }
        }
    }
    controller();
}

void toss(void)
{
    srand(time(0));
    int Toss;
    for (int i = 0; i < 100; i++)
    {
        Toss = rand() % 2;
        if (Toss == 1)
            printf("HEAD\n");
        else
            printf("TAIL\n");

        msleep(i);
        cls();
    }
    if (Toss == 1)
        printf("HEAD\n");
    else
        printf("TAIL\n");
}

void rule(void)
{
    char A;
    FILE *fp;

    fp = fopen("Rule_book.txt", "r");
    while (feof(fp) != 1)
    {
        fscanf(fp, "%c", &A);
        printf("%c", A);
    }
    if (fp == NULL)
        printf("File doesnot exist\n");

    fclose(fp);
}

int main()
{
    //cls();
    resetColor();
    log head; // start of linked list which is going to store table after every move
    head.next = NULL;
    head.prev = NULL;

    // print_board(s);

    //  while(1)
    // start();
    //   move_entries(&c_state,c_state.black[8],2,4);
    toss();
    return 0;
}