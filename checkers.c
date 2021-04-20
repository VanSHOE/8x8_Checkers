#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include "rlutil.h"
#include "checkers.h"

void print_board(game_state *P)
{
    int c_s = 4, r_s = 8;
    int b[8][8] = {0};
    setColor(WHITE);
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
                if (((i / c_s) + (j / r_s)) % 2 == 0)
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
                    setColor(WHITE);
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
            if (!(new_pos.x > p.x && new_pos.y > p.y) && capturePossible(g, p, topRight))
                return false;
            if (!(new_pos.x > p.x && new_pos.y < p.y) && capturePossible(g, p, bottomRight))
                return false;
            if (!(new_pos.x < p.x && new_pos.y > p.y) && capturePossible(g, p, topLeft))
                return false;
            if (!(new_pos.x < p.x && new_pos.y < p.y) && capturePossible(g, p, bottomLeft))
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
            if (new_pos.x > p.x && new_pos.y > p.y && capturePossible(g, p, topRight))
                return true;

            // if destination is bottomRight jump, check if capturePossible
            if (new_pos.x > p.x && new_pos.y < p.y && capturePossible(g, p, bottomRight))
                return true;

            // if destination is topLeft jump, check if capturePossible
            if (new_pos.x < p.x && new_pos.y > p.y && capturePossible(g, p, topLeft))
                return true;

            // if destination is topRight jump, check if capturePossible
            if (new_pos.x < p.x && new_pos.y < p.y && capturePossible(g, p, bottomLeft))
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
    print_board(&c_state);
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

void result(game_state P)
{
    int white_pieces_left =0;
    int black_pieces_left =0;

    for(int i=0;i<12;i++)
    {
        if(P.white[i].x != -1) // for piece that has got out , its x and y position will be -1
        white_pieces_left++;
        if(P.black[i].x != -1)
        black_pieces_left++;
    }

    if(white_pieces_left == 0)
    {
        printf("Black is the winner\n");
        return ;
    }
    else if(black_pieces_left == 0)
    {
        printf("White is the winner\n");
        return;
    }
    else // in this case , no. of pieces left of both color will be non zero
    {
        printf("Match has been drawed\n");
        return;
    }
}

void draw(game_state P) // just call this fxn and it will print who is the winner and the current board
{
    result(P);
    print_board(&P);
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

int main()
{
    log head; // start of linked list which is going to store table after every move
    head.next = NULL;
    head.prev = NULL;

    // print_board(s);

    //  while(1)
    start();
    return 0;
}