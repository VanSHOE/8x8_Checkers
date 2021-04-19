#include <stdio.h>
#include <wchar.h>
#include "rlutil.h"
#include "checkers.h"

void print_board(game_state P)
{
    int c_s = 4;
    int b[8][8];
    setColor(WHITE);
  
    for (int i = 0; i <= 8 * c_s; i++)
    {
        for (int j = 0; j <= 8 * c_s; j++)
        {
           
            setBackgroundColor(BLACK);
            if (i % (c_s) == 0 && j % (c_s) == 0)
            {
                printf("+");
            }
            else if (i % (c_s) == 0)
                printf("-");
            else if (j % (c_s) == 0)
            {
                printf("|");
            }
            else
            {
                if (((i / c_s) + (j / c_s)) % 2)
                {
                    setBackgroundColor(BROWN);
                }
                else setBackgroundColor(GREY);
                if (i % (c_s) == j % (c_s) && j % (c_s) == c_s / 2)
                {
                    setColor(BLACK);
                    printf("@");
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

bool isOccupied(game_state *g, pawn P)
{
    for (int i = 0; i < 12; ++i)
    {
        if ((P.x == g->white[i].x && P.y == g->white[i].y) || (P.x == g->black[i].x && P.y == g->black[i].y))
        {
            return true;
        }
    }
    return false;
}

bool find_with_team(game_state *g, pawn P)
{
    if (P.allegiance == 1)
    {
        for (int i = 0; i < 12; ++i)
        {
            if (P.x == g->black[i].x && P.y == g->black[i].y)
                return true;
        }
    }
    else
    {
        for (int i = 0; i < 12; ++i)
        {
            if (P.x == g->white[i].x && P.y == g->white[i].y)
                return true;
        }
    }
    return false;
}

bool capturePossible(game_state *g, pawn tmp, int addToX, int addToY)
{
    if (!isOccupied(&g, tmp))
    {
        tmp.x += addToX;
        tmp.y += addToY;
        tmp.allegiance = (tmp.allegiance + 1) % 2;
        if (find_with_team(&g, tmp))
        {
            return true;
        }
    }
}

bool isLegal(pawn p, pawn new_pos, game_state *g)
{
    if (p.x < 0 || p.y < 0 || p.x > 7 || p.y > 7) // if p.x and p.y >= 0 && <= 7
        return false;
    if (new_pos.x < 0 || new_pos.y < 0 || new_pos.x > 7 || new_pos.y > 7)
        return false;

    int x_diff = abs(p.x - new_pos.x);
    int y_diff = abs(p.y - new_pos.y);

    if (!p.is_king && new_pos.y <= p.y) // not a king.. check if new.y > old.y
        return false;

    if (x_diff < 1 || y_diff < 1 || x_diff > 2 || y_diff > 2)
        return false;

    if (!isOccupied(&g, p)) // check if p is present in board
    {
        return false;
    }

    if (isOccupied(&g, new_pos)) // check if the new_pos coordinates are empty
    {
        return false;
    }

    if (x_diff == 1 && y_diff == 1)
    {
        if (p.is_king)
        {
            if (p.x - 2 >= 0 && p.y - 2 >= 0)
            {
                pawn tmp = {p.x - 2, p.y - 2, p.allegiance};
                if (capturePossible (&g, tmp, 1, 1))
                {
                    return false;
                }
            }
        }
        else
        {
            if (new_pos.x > p.x)
            {
                if (p.x - 2 >= 0 && p.y + 2 <= 7)
                {
                    pawn tmp = {p.x - 2, p.y + 2, p.allegiance};
                    if (capturePossible(&g, tmp, 1, -1))
                    {
                        return false;
                    }
                }
                return true;
            }
            else
            {
                if (p.x + 2 <= 7 && p.y + 2 <= 7)
                {
                    pawn tmp = {p.x + 2, p.y + 2};
                    if (!isOccupied(&g, tmp))
                    {
                        tmp.x = p.x + 1;
                        tmp.y = p.y + 1;
                        tmp.allegiance = (p.allegiance + 1) % 2;
                        if (find_with_team(&g, tmp))
                        {
                            return false;
                        }
                    }
                }
                return true;
            }
        }
    }

    if (x_diff == 2 && y_diff == 2)
    {
    }

    return true;
}

int main()
{
    game_state s;
    print_board(s);
    return 0;
}