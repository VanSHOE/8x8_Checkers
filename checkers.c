
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rlutil.h"
#include "checkers.h"
#include <stdbool.h>
#include <assert.h>
int lim = 4;

long double bot_helperb(game_state g_o, int lim)
{
    if (!lim)
        return 0;

    long double *scores = (long double *)calloc(tp * 4, sizeof(long double));
    g_o.cur_turn = colorFlip(g_o.cur_turn);
    game_state g = g_o;
    if (g.cur_turn == BLACK)
    {
        for (int i = 0; i < tp; i++)
        {
            int pc_i = i;

            if (move_entries(&g, g.black[pc_i], g.black[pc_i].x + 1, g.black[pc_i].y + 1))
            {
                scores[4 * i] = 1;
                scores[4 * i] += 0.9 * bot_helperb(g, lim - 1);
                g = g_o;
            }

            else if (move_entries(&g, g.black[pc_i], g.black[pc_i].x + 2, g.black[pc_i].y + 2))
            {
                scores[4 * i] = 10;
                scores[4 * i] += 0.9 * bot_helperb(g, lim - 1);
                g = g_o;
            }
            if (move_entries(&g, g.black[pc_i], g.black[pc_i].x + 1, g.black[pc_i].y - 1))
            {
                scores[4 * i + 1] = (g.black[pc_i].is_king) ? 1 : 2;
                scores[4 * i + 1] += 0.9 * bot_helperb(g, lim - 1);
                g = g_o;
            }
            else if (move_entries(&g, g.black[pc_i], g.black[pc_i].x + 2, g.black[pc_i].y - 2))
            {
                scores[4 * i + 1] = 10;
                scores[4 * i + 1] += 0.9 * bot_helperb(g, lim - 1);
                g = g_o;
            }
            if (move_entries(&g, g.black[pc_i], g.black[pc_i].x - 1, g.black[pc_i].y - 1))
            {
                scores[4 * i + 2] = (g.black[pc_i].is_king) ? 1 : 2;
                scores[4 * i + 2] += 0.9 * bot_helperb(g, lim - 1);
                g = g_o;
            }
            else if (move_entries(&g, g.black[pc_i], g.black[pc_i].x - 2, g.black[pc_i].y - 2))
            {
                scores[4 * i + 2] = 10;
                scores[4 * i + 2] += 0.9 * bot_helperb(g, lim - 1);
                g = g_o;
            }
            if (move_entries(&g, g.black[pc_i], g.black[pc_i].x - 1, g.black[pc_i].y + 1))
            {
                scores[4 * i + 3] = 1;
                scores[4 * i + 3] += 0.9 * bot_helperb(g, lim - 1);
                g = g_o;
            }
            else if (move_entries(&g, g.black[pc_i], g.black[pc_i].x - 2, g.black[pc_i].y + 2))
            {
                scores[4 * i + 3] = 10;
                scores[4 * i + 3] += 0.9 * bot_helperb(g, lim - 1);
                g = g_o;
            }
        }
    }
    else
    {
        for (int i = 0; i < tp; i++)
        {
            int pc_i = i;

            if (move_entries(&g, g.white[pc_i], g.white[pc_i].x + 1, g.white[pc_i].y + 1))
            {
                scores[4 * i] = (g.white[pc_i].is_king) ? 1 : 2;
                scores[4 * i] += 0.9 * bot_helperb(g, lim - 1);
                g = g_o;
            }

            else if (move_entries(&g, g.white[pc_i], g.white[pc_i].x + 2, g.white[pc_i].y + 2))
            {
                scores[4 * i] = 10;
                scores[4 * i] += 0.9 * bot_helperb(g, lim - 1);
                g = g_o;
            }
            if (move_entries(&g, g.white[pc_i], g.white[pc_i].x + 1, g.white[pc_i].y - 1))
            {
                scores[4 * i + 1] = 1;
                scores[4 * i + 1] += 0.9 * bot_helperb(g, lim - 1);
                g = g_o;
            }
            else if (move_entries(&g, g.white[pc_i], g.white[pc_i].x + 2, g.white[pc_i].y - 2))
            {
                scores[4 * i + 1] = 10;
                scores[4 * i + 1] += 0.9 * bot_helperb(g, lim - 1);
                g = g_o;
            }
            if (move_entries(&g, g.white[pc_i], g.white[pc_i].x - 1, g.white[pc_i].y - 1))
            {
                scores[4 * i + 2] = 1;
                scores[4 * i + 2] += 0.9 * bot_helperb(g, lim - 1);
                g = g_o;
            }
            else if (move_entries(&g, g.white[pc_i], g.white[pc_i].x - 2, g.white[pc_i].y - 2))
            {
                scores[4 * i + 2] = 10;
                scores[4 * i + 2] += 0.9 * bot_helperb(g, lim - 1);
                g = g_o;
            }
            if (move_entries(&g, g.white[pc_i], g.white[pc_i].x - 1, g.white[pc_i].y + 1))
            {
                scores[4 * i + 3] = (g.white[pc_i].is_king) ? 1 : 2;
                scores[4 * i + 3] += 0.9 * bot_helperb(g, lim - 1);
                g = g_o;
            }
            else if (move_entries(&g, g.white[pc_i], g.white[pc_i].x - 2, g.white[pc_i].y + 2))
            {
                scores[4 * i + 3] = 10;
                scores[4 * i + 3] += 0.9 * bot_helperb(g, lim - 1);
                g = g_o;
            }
            scores[4 * i] = -scores[4 * i];
            scores[4 * i + 1] = -scores[4 * i + 1];
            scores[4 * i + 2] = -scores[4 * i + 2];
            scores[4 * i + 3] = -scores[4 * i + 3];
        }
    }
    long double sum = 0;
    for (int i = 0; i < 4 * tp; i++)
    {
        sum += scores[i];
    }
    free(scores);
    return sum;
}

void botb()
{

    long double *scores = (long double *)calloc(tp * 4, sizeof(long double));
    game_state g = c_state;
    for (int i = 0; i < tp; i++)
    {
        int pc_i = i;

        if (move_entries(&g, g.black[pc_i], g.black[pc_i].x + 1, g.black[pc_i].y + 1))
        {
            scores[4 * i] = 1;
            scores[4 * i] += 0.9 * bot_helperb(g, lim - 1);
            g = c_state;
        }

        else if (move_entries(&g, g.black[pc_i], g.black[pc_i].x + 2, g.black[pc_i].y + 2))
        {
            scores[4 * i] = 10;
            scores[4 * i] += 0.9 * bot_helperb(g, lim - 1);
            g = c_state;
        }
        if (move_entries(&g, g.black[pc_i], g.black[pc_i].x + 1, g.black[pc_i].y - 1))
        {
            scores[4 * i + 1] = 2;
            scores[4 * i + 1] += 0.9 * bot_helperb(g, lim - 1);
            g = c_state;
        }
        else if (move_entries(&g, g.black[pc_i], g.black[pc_i].x + 2, g.black[pc_i].y - 2))
        {
            scores[4 * i + 1] = 10;
            scores[4 * i + 1] += 0.9 * bot_helperb(g, lim - 1);
            g = c_state;
        }
        if (move_entries(&g, g.black[pc_i], g.black[pc_i].x - 1, g.black[pc_i].y - 1))
        {
            scores[4 * i + 2] = 2;
            scores[4 * i + 2] += 0.9 * bot_helperb(g, lim - 1);
            g = c_state;
        }
        else if (move_entries(&g, g.black[pc_i], g.black[pc_i].x - 2, g.black[pc_i].y - 2))
        {
            scores[4 * i + 2] = 10;
            scores[4 * i + 2] += 0.9 * bot_helperb(g, lim - 1);
            g = c_state;
        }
        if (move_entries(&g, g.black[pc_i], g.black[pc_i].x - 1, g.black[pc_i].y + 1))
        {
            scores[4 * i + 3] = 1;
            scores[4 * i + 3] += 0.9 * bot_helperb(g, lim - 1);
            g = c_state;
        }
        else if (move_entries(&g, g.black[pc_i], g.black[pc_i].x - 2, g.black[pc_i].y + 2))
        {
            scores[4 * i + 3] = 10;
            scores[4 * i + 3] += 0.9 * bot_helperb(g, lim - 1);
            g = c_state;
        }
    }
    int mi = 0;
    for (int i = 1; i < 4 * tp; i++)
    {
        if (scores[mi] < scores[i])
        {
            mi = i;
        }
    }

    printf("Moving %d", mi);
    int flag = 0;
    while (!flag)
    {
        int pc_i = mi / 4;
        switch (mi % 4)
        {
        case 0:
            if (!move_entries(&c_state, c_state.black[pc_i], c_state.black[pc_i].x + 1, c_state.black[pc_i].y + 1))
            {
                if (move_entries(&c_state, c_state.black[pc_i], c_state.black[pc_i].x + 2, c_state.black[pc_i].y + 2))
                    flag = 1;
            }
            else
                flag = 1;
            break;
        case 1:
            if (!move_entries(&c_state, c_state.black[pc_i], c_state.black[pc_i].x + 1, c_state.black[pc_i].y - 1))
            {
                if (move_entries(&c_state, c_state.black[pc_i], c_state.black[pc_i].x + 2, c_state.black[pc_i].y - 2))
                    flag = 1;
            }
            else
                flag = 1;
            break;
        case 2:
            if (!move_entries(&c_state, c_state.black[pc_i], c_state.black[pc_i].x - 1, c_state.black[pc_i].y - 1))
            {
                if (move_entries(&c_state, c_state.black[pc_i], c_state.black[pc_i].x - 2, c_state.black[pc_i].y - 2))
                    flag = 1;
            }
            else
                flag = 1;
            break;
        case 3:
            if (!move_entries(&c_state, c_state.black[pc_i], c_state.black[pc_i].x - 1, c_state.black[pc_i].y + 1))
            {
                if (move_entries(&c_state, c_state.black[pc_i], c_state.black[pc_i].x - 2, c_state.black[pc_i].y + 2))
                    flag = 1;
            }
            else
                flag = 1;
            break;
        }
        if (flag == 0)
        {
            scores[mi] = -9999999999999;
        }
        mi = 0;
        for (int i = 1; i < 48; i++)
        {
            if (scores[mi] < scores[i])
            {
                mi = i;
            }
        }
    }
    free(scores);
}
long double bot_helperw(game_state g_o, int lim)
{
    if (!lim)
        return 0;

    long double *scores = (long double *)calloc(tp * 4, sizeof(long double));
    g_o.cur_turn = colorFlip(g_o.cur_turn);
    game_state g = g_o;
    if (g.cur_turn == BLACK)
    {
        for (int i = 0; i < tp; i++)
        {
            int pc_i = i;

            if (move_entries(&g, g.black[pc_i], g.black[pc_i].x + 1, g.black[pc_i].y + 1))
            {
                scores[4 * i] = 1;
                scores[4 * i] += 0.9 * bot_helperw(g, lim - 1);
                g = g_o;
            }

            else if (move_entries(&g, g.black[pc_i], g.black[pc_i].x + 2, g.black[pc_i].y + 2))
            {
                scores[4 * i] = 10;
                scores[4 * i] += 0.9 * bot_helperw(g, lim - 1);
                g = g_o;
            }
            if (move_entries(&g, g.black[pc_i], g.black[pc_i].x + 1, g.black[pc_i].y - 1))
            {
                scores[4 * i + 1] = (g.black[pc_i].is_king) ? 1 : 2;
                scores[4 * i + 1] += 0.9 * bot_helperw(g, lim - 1);
                g = g_o;
            }
            else if (move_entries(&g, g.black[pc_i], g.black[pc_i].x + 2, g.black[pc_i].y - 2))
            {
                scores[4 * i + 1] = 10;
                scores[4 * i + 1] += 0.9 * bot_helperw(g, lim - 1);
                g = g_o;
            }
            if (move_entries(&g, g.black[pc_i], g.black[pc_i].x - 1, g.black[pc_i].y - 1))
            {
                scores[4 * i + 2] = (g.black[pc_i].is_king) ? 1 : 2;
                scores[4 * i + 2] += 0.9 * bot_helperw(g, lim - 1);
                g = g_o;
            }
            else if (move_entries(&g, g.black[pc_i], g.black[pc_i].x - 2, g.black[pc_i].y - 2))
            {
                scores[4 * i + 2] = 10;
                scores[4 * i + 2] += 0.9 * bot_helperw(g, lim - 1);
                g = g_o;
            }
            if (move_entries(&g, g.black[pc_i], g.black[pc_i].x - 1, g.black[pc_i].y + 1))
            {
                scores[4 * i + 3] = 1;
                scores[4 * i + 3] += 0.9 * bot_helperw(g, lim - 1);
                g = g_o;
            }
            else if (move_entries(&g, g.black[pc_i], g.black[pc_i].x - 2, g.black[pc_i].y + 2))
            {
                scores[4 * i + 3] = 10;
                scores[4 * i + 3] += 0.9 * bot_helperw(g, lim - 1);
                g = g_o;
            }
            scores[4 * i] = -scores[4 * i];
            scores[4 * i + 1] = -scores[4 * i + 1];
            scores[4 * i + 2] = -scores[4 * i + 2];
            scores[4 * i + 3] = -scores[4 * i + 3];
        }
    }
    else
    {
        for (int i = 0; i < tp; i++)
        {
            int pc_i = i;

            if (move_entries(&g, g.white[pc_i], g.white[pc_i].x + 1, g.white[pc_i].y + 1))
            {
                scores[4 * i] = (g.white[pc_i].is_king) ? 1 : 2;
                scores[4 * i] += 0.9 * bot_helperw(g, lim - 1);
                g = g_o;
            }

            else if (move_entries(&g, g.white[pc_i], g.white[pc_i].x + 2, g.white[pc_i].y + 2))
            {
                scores[4 * i] = 10;
                scores[4 * i] += 0.9 * bot_helperw(g, lim - 1);
                g = g_o;
            }
            if (move_entries(&g, g.white[pc_i], g.white[pc_i].x + 1, g.white[pc_i].y - 1))
            {
                scores[4 * i + 1] = 1;
                scores[4 * i + 1] += 0.9 * bot_helperw(g, lim - 1);
                g = g_o;
            }
            else if (move_entries(&g, g.white[pc_i], g.white[pc_i].x + 2, g.white[pc_i].y - 2))
            {
                scores[4 * i + 1] = 10;
                scores[4 * i + 1] += 0.9 * bot_helperw(g, lim - 1);
                g = g_o;
            }
            if (move_entries(&g, g.white[pc_i], g.white[pc_i].x - 1, g.white[pc_i].y - 1))
            {
                scores[4 * i + 2] = 1;
                scores[4 * i + 2] += 0.9 * bot_helperw(g, lim - 1);
                g = g_o;
            }
            else if (move_entries(&g, g.white[pc_i], g.white[pc_i].x - 2, g.white[pc_i].y - 2))
            {
                scores[4 * i + 2] = 10;
                scores[4 * i + 2] += 0.9 * bot_helperw(g, lim - 1);
                g = g_o;
            }
            if (move_entries(&g, g.white[pc_i], g.white[pc_i].x - 1, g.white[pc_i].y + 1))
            {
                scores[4 * i + 3] = (g.white[pc_i].is_king) ? 1 : 2;
                scores[4 * i + 3] += 0.9 * bot_helperw(g, lim - 1);
                g = g_o;
            }
            else if (move_entries(&g, g.white[pc_i], g.white[pc_i].x - 2, g.white[pc_i].y + 2))
            {
                scores[4 * i + 3] = 10;
                scores[4 * i + 3] += 0.9 * bot_helperw(g, lim - 1);
                g = g_o;
            }
        }
    }
    long double sum = 0;
    for (int i = 0; i < 4 * tp; i++)
    {
        sum += scores[i];
    }
    free(scores);
    return sum;
}

void botw()
{

    long double *scores = (long double *)calloc(tp * 4, sizeof(long double));
    game_state g = c_state;
    for (int i = 0; i < tp; i++)
    {
        int pc_i = i;

        if (move_entries(&g, g.white[pc_i], g.white[pc_i].x + 1, g.white[pc_i].y + 1))
        {
            scores[4 * i] = 1;
            scores[4 * i] += 0.9 * bot_helperw(g, lim - 1);
            g = c_state;
        }

        else if (move_entries(&g, g.white[pc_i], g.white[pc_i].x + 2, g.white[pc_i].y + 2))
        {
            scores[4 * i] = 10;
            scores[4 * i] += 0.9 * bot_helperw(g, lim - 1);
            g = c_state;
        }
        if (move_entries(&g, g.white[pc_i], g.white[pc_i].x + 1, g.white[pc_i].y - 1))
        {
            scores[4 * i + 1] = 2;
            scores[4 * i + 1] += 0.9 * bot_helperw(g, lim - 1);
            g = c_state;
        }
        else if (move_entries(&g, g.white[pc_i], g.white[pc_i].x + 2, g.white[pc_i].y - 2))
        {
            scores[4 * i + 1] = 10;
            scores[4 * i + 1] += 0.9 * bot_helperw(g, lim - 1);
            g = c_state;
        }
        if (move_entries(&g, g.white[pc_i], g.white[pc_i].x - 1, g.white[pc_i].y - 1))
        {
            scores[4 * i + 2] = 2;
            scores[4 * i + 2] += 0.9 * bot_helperw(g, lim - 1);
            g = c_state;
        }
        else if (move_entries(&g, g.white[pc_i], g.white[pc_i].x - 2, g.white[pc_i].y - 2))
        {
            scores[4 * i + 2] = 10;
            scores[4 * i + 2] += 0.9 * bot_helperw(g, lim - 1);
            g = c_state;
        }
        if (move_entries(&g, g.white[pc_i], g.white[pc_i].x - 1, g.white[pc_i].y + 1))
        {
            scores[4 * i + 3] = 1;
            scores[4 * i + 3] += 0.9 * bot_helperw(g, lim - 1);
            g = c_state;
        }
        else if (move_entries(&g, g.white[pc_i], g.white[pc_i].x - 2, g.white[pc_i].y + 2))
        {
            scores[4 * i + 3] = 10;
            scores[4 * i + 3] += 0.9 * bot_helperw(g, lim - 1);
            g = c_state;
        }
    }
    int mi = 0;
    for (int i = 1; i < 4 * tp; i++)
    {
        if (scores[mi] < scores[i])
        {
            mi = i;
        }
    }

    printf("Moving %d", mi);
    int flag = 0;
    while (!flag)
    {
        int pc_i = mi / 4;
        switch (mi % 4)
        {
        case 0:
            if (!move_entries(&c_state, c_state.white[pc_i], c_state.white[pc_i].x + 1, c_state.white[pc_i].y + 1))
            {
                if (move_entries(&c_state, c_state.white[pc_i], c_state.white[pc_i].x + 2, c_state.white[pc_i].y + 2))
                    flag = 1;
            }
            else
                flag = 1;
            break;
        case 1:
            if (!move_entries(&c_state, c_state.white[pc_i], c_state.white[pc_i].x + 1, c_state.white[pc_i].y - 1))
            {
                if (move_entries(&c_state, c_state.white[pc_i], c_state.white[pc_i].x + 2, c_state.white[pc_i].y - 2))
                    flag = 1;
            }
            else
                flag = 1;
            break;
        case 2:
            if (!move_entries(&c_state, c_state.white[pc_i], c_state.white[pc_i].x - 1, c_state.white[pc_i].y - 1))
            {
                if (move_entries(&c_state, c_state.white[pc_i], c_state.white[pc_i].x - 2, c_state.white[pc_i].y - 2))
                    flag = 1;
            }
            else
                flag = 1;
            break;
        case 3:
            if (!move_entries(&c_state, c_state.white[pc_i], c_state.white[pc_i].x - 1, c_state.white[pc_i].y + 1))
            {
                if (move_entries(&c_state, c_state.white[pc_i], c_state.white[pc_i].x - 2, c_state.white[pc_i].y + 2))
                    flag = 1;
            }
            else
                flag = 1;
            break;
        }
        if (flag == 0)
        {
            scores[mi] = -9999999999999;
        }
        mi = 0;
        for (int i = 1; i < 48; i++)
        {
            if (scores[mi] < scores[i])
            {
                mi = i;
            }
        }
    }
    free(scores);
}
game_state play_capture_move(game_state *g, pawn p, int direction)
{
    int aftermove_x, aftermove_y;
    if (direction == topLeft)
    {
        aftermove_x = p.x - 2;
        aftermove_y = p.y + 2;
    }
    else if (direction == topRight)
    {
        aftermove_x = p.x + 2;
        aftermove_y = p.x + 2;
    }
    else if (direction == bottomLeft)
    {
        aftermove_x = p.x - 2;
        aftermove_y = p.y - 2;
    }
    else
    {
        aftermove_x = p.x + 2;
        aftermove_y = p.y - 2;
    }

    pawn new;
    new.x = aftermove_x;
    new.y = aftermove_y;
    new.allegiance = p.allegiance;
    new.is_king = p.is_king;

    if (!isLegal(p, new, g))
    {
        printf("Invalid move!\n");
        return *g;
    }

    if (isOccupied(g, aftermove_x, aftermove_y))
    {
        printf("Position is already occupied!\n");
        return *g;
    }

    if (!is_present(g, p))
    {
        printf("Piece is Not present\n");
        return *g;
    }

    //checking if it becomes king due to move
    if (p.allegiance == WHITE && aftermove_y == sb - 1)
    {
        new.is_king = true;
    }
    if (p.allegiance == BLACK && aftermove_y == 0)
    {
        new.is_king = true;
    }

    if (p.allegiance == WHITE)
    {
        for (int i = 0; i < 12; i++)
        {
            if (g->white[i].x == p.x && g->white[i].y == p.y)
            {
                g->white[i].x = aftermove_x;
                g->black[i].y = aftermove_y;
                break;
            }
        }
    }
    else
    {
        for (int i = 0; i < 12; i++)
        {
            if (g->black[i].x == p.x && g->black[i].y == p.y)
            {
                g->black[i].x = aftermove_x;
                g->black[i].y = aftermove_y;
                break;
            }
        }
    }

    g->cur_turn = colorFlip(g->cur_turn);

    return *g;
}
game_state play_simple_move(game_state *g, pawn p, int direction)
{
    int aftermove_x, aftermove_y;
    if (direction == topLeft)
    {
        aftermove_x = p.x - 1;
        aftermove_y = p.y + 1;
    }
    else if (direction == topRight)
    {
        aftermove_x = p.x + 1;
        aftermove_y = p.x + 1;
    }
    else if (direction == bottomLeft)
    {
        aftermove_x = p.x - 1;
        aftermove_y = p.y - 1;
    }
    else
    {
        aftermove_x = p.x + 1;
        aftermove_y = p.y - 1;
    }

    pawn new;
    new.x = aftermove_x;
    new.y = aftermove_y;
    new.allegiance = p.allegiance;
    new.is_king = p.is_king;

    if (!isLegal(p, new, g))
    {
        printf("Invalid move!\n");
        return *g;
    }

    if (isOccupied(g, aftermove_x, aftermove_y))
    {
        printf("Position is already occupied!\n");
        return *g;
    }

    if (!is_present(g, p))
    {
        printf("Piece is Not present\n");
        return *g;
    }

    //checking if it becomes king due to move
    if (p.allegiance == WHITE && aftermove_y == sb - 1)
    {
        new.is_king = true;
    }
    if (p.allegiance == BLACK && aftermove_y == 0)
    {
        new.is_king = true;
    }

    if (p.allegiance == WHITE)
    {
        for (int i = 0; i < tp; i++)
        {
            if (g->white[i].x == p.x && g->white[i].y == p.y)
            {
                g->white[i].x = aftermove_x;
                g->black[i].y = aftermove_y;
                break;
            }
        }
    }
    else
    {
        for (int i = 0; i < tp; i++)
        {
            if (g->black[i].x == p.x && g->black[i].y == p.y)
            {
                g->black[i].x = aftermove_x;
                g->black[i].y = aftermove_y;
                break;
            }
        }
    }

    g->cur_turn = (g->cur_turn + 1) % 2;

    return *g;
}

void print_all_possible_next_move(node *current) // given a game state , what all possible can be achieved in next move
{
    // array will contain board condition possible after a piece whose turn it should be has been moved
    for (int i = 0; i < 12; i++) // selecting the piece
    {
        for (int j = 0; j < 4; j++) // selecting the dirn
        {
            if (current->array[i][j] != NULL) // checking if that piece is available or dirn is valid
            {
                print_board(&(current->array[i][j]->board)); // printing the board after that move has been performed
            }
        }
    }
}

void point_to_null(node *p) // take ptr to node and initialize each of its child to null
{
    //p->prev_board = NULL;           // why this , confused ???   me too , chill XD!!
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            p->array[i][j] = NULL;
        }
    }
}

void reached_how(node *final) // will tell how we reached a particular board position // every node contains address of its parent node
{
    node stack[10]; // assuming that value of board will be less than this
    int id = 0;
    stack[0] = *final;

    while ((*final).prev_board != NULL) // will keep moving backward untill we do not reach the parent board
    {
        id++;
        final = (*final).prev_board;
        stack[id] = *final;
    }

    for (int i = 0; i <= id; i++)
    {
        print_board(&(stack[i].board));
        printf("\n");
    }
}

void filling_node(node *current, game_state p);

void print_k_state(game_state p, int k)
{
    node *root;
    root = (node *)malloc(sizeof(node));
    root->board = p;
    root->depth = 0;
    root->next_board = NULL;
    root->prev_board = NULL;

    if (k == 0)
    {
        print_board(&p);
        return;
    }

    point_to_null(root);

    filling_node(root, p);

    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (root->array[i][j] != NULL) //  not equal to null means that a move is possible in this dirn
            {
                print_k_state(root->array[i][j]->board, k - 1);
            }
        }
    }
    printf("press 'e' to Resume\n");
    while (1)
    {
        char ch = getkey();
        if (ch == 'e')
        {
            cls();
            return;
        }
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
                            game_state board_next = play_simple_move(&p, p.black[i], topLeft); // fix the error
                            //allocating memory
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                            current->array[i][j]->depth = current->depth + 1; // have to conform  ************************
                            point_to_null(current->array[i][j]);
                        }
                        //else we will check if capturing another color piece is possible in that direction
                        else if (capturePossible(&p, p.black[i], topLeft))
                        {
                            game_state board_next = play_capture_move(&p, p.black[i], topLeft);
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                            current->array[i][j]->depth = current->depth + 1; // have to conform  ************************
                            point_to_null(current->array[i][j]);
                        }
                    }
                    else if (j == 1)
                    {
                        //checking if simple move is poosible in this direction
                        if (simple_Move_Possible(&p, p.black[i], topRight))
                        {
                            // finding the board after the move is made
                            game_state board_next = play_simple_move(&p, p.black[i], topRight); // fix the error
                            //allocating memory
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                            current->array[i][j]->depth = current->depth + 1; // have to conform  ************************
                            point_to_null(current->array[i][j]);
                        }
                        //else we will check if capturing another color piece is possible in that direction
                        else if (capturePossible(&p, p.black[i], topRight))
                        {
                            game_state board_next = play_capture_move(&p, p.black[i], topRight);
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                            current->array[i][j]->depth = current->depth + 1; // have to conform  ************************
                            point_to_null(current->array[i][j]);
                        }
                    }
                    else if (j == 2)
                    {
                        //checking if simple move is poosible in this direction
                        if (simple_Move_Possible(&p, p.black[i], bottomLeft))
                        {
                            // finding the board after the move is made
                            game_state board_next = play_simple_move(&p, p.black[i], bottomLeft); // fix the error
                            //allocating memory
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                            current->array[i][j]->depth = current->depth + 1; // have to conform  ************************
                            point_to_null(current->array[i][j]);
                        }
                        //else we will check if capturing another color piece is possible in that direction
                        else if (capturePossible(&p, p.black[i], bottomLeft))
                        {
                            game_state board_next = play_capture_move(&p, p.black[i], bottomLeft);
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                            current->array[i][j]->depth = current->depth + 1; // have to conform  ************************
                            point_to_null(current->array[i][j]);
                        }
                    }
                    else if (j == 3)
                    {
                        //checking if simple move is poosible in this direction
                        if (simple_Move_Possible(&p, p.black[i], bottomRight))
                        {
                            // finding the board after the move is made
                            game_state board_next = play_simple_move(&p, p.black[i], bottomRight); // fix the error
                            //allocating memory
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                            current->array[i][j]->depth = current->depth + 1; // have to conform  ************************
                            point_to_null(current->array[i][j]);
                        }
                        //else we will check if capturing another color piece is possible in that direction
                        else if (capturePossible(&p, p.black[i], bottomRight))
                        {
                            game_state board_next = play_capture_move(&p, p.black[i], bottomRight);
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                            current->array[i][j]->depth = current->depth + 1; // have to conform  ************************
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
                            game_state board_next = play_simple_move(&p, p.black[i], bottomLeft); // fix the error
                            //allocating memory
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                            current->array[i][j]->depth = current->depth + 1; // have to conform  ************************
                            point_to_null(current->array[i][j]);
                        }
                        //else we will check if capturing another color piece is possible in that direction
                        else if (capturePossible(&p, p.black[i], bottomLeft))
                        {
                            game_state board_next = play_capture_move(&p, p.black[i], bottomLeft);
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                            current->array[i][j]->depth = current->depth + 1; // have to conform  ************************
                            point_to_null(current->array[i][j]);
                        }
                    }
                    else if (j == 3)
                    {
                        //checking if simple move is poosible in this direction
                        if (simple_Move_Possible(&p, p.black[i], bottomRight))
                        {
                            // finding the board after the move is made
                            game_state board_next = play_simple_move(&p, p.black[i], bottomRight); // fix the error
                            //allocating memory
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                            current->array[i][j]->depth = current->depth + 1; // have to conform  ************************
                            point_to_null(current->array[i][j]);
                        }
                        //else we will check if capturing another color piece is possible in that direction
                        else if (capturePossible(&p, p.black[i], bottomRight))
                        {
                            game_state board_next = play_capture_move(&p, p.black[i], bottomRight);
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                            current->array[i][j]->depth = current->depth + 1; // have to conform  ************************
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
                            game_state board_next = play_simple_move(&p, p.white[i], topLeft); // fix the error
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
                            game_state board_next = play_capture_move(&p, p.white[i], topLeft);
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
                            game_state board_next = play_simple_move(&p, p.white[i], topRight); // fix the error
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
                            game_state board_next = play_capture_move(&p, p.white[i], topRight);
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
                            game_state board_next = play_simple_move(&p, p.white[i], bottomLeft); // fix the error
                            //allocating memory
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                            point_to_null(current->array[i][j]);
                        }
                        //else we will check if capturing another color piece is possible in that direction
                        else if (capturePossible(&p, p.white[i], bottomLeft))
                        {
                            game_state board_next = play_capture_move(&p, p.white[i], bottomLeft);
                            current->array[i][j] = (node *)malloc(sizeof(node));
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
                            game_state board_next = play_simple_move(&p, p.white[i], bottomRight); // fix the error
                            //allocating memory
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                            point_to_null(current->array[i][j]);
                        }
                        //else we will check if capturing another color piece is possible in that direction
                        else if (capturePossible(&p, p.white[i], bottomRight))
                        {
                            game_state board_next = play_capture_move(&p, p.white[i], bottomRight);
                            current->array[i][j] = (node *)malloc(sizeof(node));
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
                            game_state board_next = play_simple_move(&p, p.white[i], topLeft); // fix the error
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
                            game_state board_next = play_capture_move(&p, p.white[i], topLeft);
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
                            game_state board_next = play_simple_move(&p, p.white[i], topRight); // fix the error
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
                            game_state board_next = play_capture_move(&p, p.white[i], topRight);
                            current->array[i][j] = (node *)malloc(sizeof(node));
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

void multi_Capture_BLACK(game_state *g)
{
    int cnt = 0;
    pawn P;
    P.allegiance = BLACK;
    coords new;
    for (int i = 0; i < tp; ++i)
    {
        if (g->black[i].x != -1)
        {
            if (capturePossible(g, g->black[i], bottomRight))
            {
                P = g->black[i];
                new.x = g->black[i].x + 1;
                new.y = g->black[i].y - 1;
                cnt++;
            }
            if (capturePossible(g, g->black[i], bottomLeft))
            {
                P = g->black[i];
                new.x = g->black[i].x - 1;
                new.y = g->black[i].y - 1;
                cnt++;
            }
            if (g->black[i].is_king)
            {
                if (capturePossible(g, g->black[i], topRight))
                {
                    P = g->black[i];
                    new.x = g->black[i].x + 1;
                    new.y = g->black[i].y + 1;
                    cnt++;
                }
                if (capturePossible(g, g->black[i], topLeft))
                {
                    P = g->black[i];
                    new.x = g->black[i].x - 1;
                    new.y = g->black[i].y + 1;
                    cnt++;
                }
            }
            if (cnt > 1)
                break;
        }
    }
    if (cnt > 1 || cnt == 0)
        return;
    else
    {
        if (!move_entries(g, P, new.x, new.y))
            return;
    }
}

void multi_Capture_WHITE(game_state *g)
{
    int cnt = 0;
    pawn P;
    P.allegiance = WHITE;
    coords new;
    for (int i = 0; i < tp; ++i)
    {
        if (g->white[i].x != -1)
        {
            if (capturePossible(g, g->white[i], topRight))
            {
                P = g->white[i];
                new.x = g->white[i].x + 1;
                new.y = g->white[i].y + 1;
                cnt++;
            }
            if (capturePossible(g, g->white[i], topLeft))
            {
                P = g->white[i];
                new.x = g->white[i].x - 1;
                new.y = g->white[i].y + 1;
                cnt++;
            }
            if (g->white[i].is_king)
            {
                if (capturePossible(g, g->white[i], bottomRight))
                {
                    P = g->white[i];
                    new.x = g->white[i].x + 1;
                    new.y = g->white[i].y - 1;
                    cnt++;
                }
                if (capturePossible(g, g->white[i], bottomLeft))
                {
                    P = g->white[i];
                    new.x = g->white[i].x - 1;
                    new.y = g->white[i].y - 1;
                    cnt++;
                }
            }
            if (cnt > 1)
                break;
        }
    }
    if (cnt > 1 || cnt == 0)
        return;
    else
    {
        if (!move_entries(g, P, new.x, new.y))
            return;
    }
}

bool move_entries(game_state *g, pawn P, int horizontal, int vertical)
{
    if (!is_present(g, P))
    {
        //    printf("NOT PRESENT\n");
        return false;
    }
    pawn n;
    n.x = horizontal;
    n.y = vertical;
    if (!isLegal(P, n, g))
    {
        //   printf("NOT LEGAL\n");
        return false;
    }
    // printf("WORKING\n");
    if (P.allegiance == BLACK)
    { //printf("WORKINGb\n");
        for (int i = 0; i < tp; ++i)
        {
            if (P.x == g->black[i].x && P.y == g->black[i].y)
            {
                if (abs(P.x - horizontal) == 2 && abs(P.y - vertical) == 2)
                {
                    coords captured_piece = {0, 0};
                    captured_piece.x = (P.x < horizontal) ? (P.x + 1) : (P.x - 1);
                    captured_piece.y = (P.y < vertical) ? (P.y + 1) : (P.y - 1);
                    for (int i = 0; i < tp; ++i)
                    {
                        if (g->white[i].x == captured_piece.x && g->white[i].y == captured_piece.y)
                        {
                            g->white[i].x = -1;
                            g->white[i].y = -1;
                        }
                    }
                }
                g->black[i].x = horizontal;
                g->black[i].y = vertical;

                if (g->black[i].y == 0) // black piece reached to row 0
                    g->black[i].is_king = true;
                // multi_Capture_BLACK(g);
                break;
            }
        }
    }
    else if (P.allegiance == WHITE)
    {

        for (int i = 0; i < tp; ++i)
        {
            if (P.x == g->white[i].x && P.y == g->white[i].y)
            { //   printf("OLD:%d, %d ; New: %d , %d\n",g->white[i].x, g->white[i].y,horizontal,vertical);
                if (abs(P.x - horizontal) == 2 && abs(P.y - vertical) == 2)
                {
                    coords captured_piece = {0, 0};
                    captured_piece.x = (P.x < horizontal) ? (P.x + 1) : (P.x - 1);
                    captured_piece.y = (P.y < vertical) ? (P.y + 1) : (P.y - 1);
                    for (int i = 0; i < tp; ++i)
                    {
                        if (g->black[i].x == captured_piece.x && g->black[i].y == captured_piece.y)
                        {
                            g->black[i].x = -1;
                            g->black[i].y = -1;
                        }
                    }
                }
                g->white[i].x = horizontal;
                g->white[i].y = vertical;

                if (g->white[i].y == sb - 1) // white piece reached to row 7
                    g->white[i].is_king = true;
                // multi_Capture_WHITE(g);
                break;
            }
        }
    }
    return true;
}

void menu()
{
}

void print_board(game_state *P)
{
    int c_s = 4, r_s = 8;
    int b[sb][sb];
    for (int i = 0; i < sb; i++)
    {
        for (int j = 0; j < sb; j++)
        {
            b[i][j] = 0;
        }
    }
    resetColor();
    int yc1 = sb - 1 - P->hover[0].y;
    int xc1 = P->hover[0].x;
    int yc2 = sb - 1 - P->hover[1].y;
    int xc2 = P->hover[1].x;

    for (int i = 0; i < tp; i++)
    {
        if (P->black[i].y != -1)
        {
            if (P->black[i].is_king)
                b[sb - 1 - P->black[i].y][P->black[i].x] = 3;
            else
                b[sb - 1 - P->black[i].y][P->black[i].x] = 1;
        }
        if (P->white[i].y != -1)
        {
            if (P->white[i].is_king)
                b[sb - 1 - P->white[i].y][P->white[i].x] = 4;
            else
                b[sb - 1 - P->white[i].y][P->white[i].x] = 2;
        }
    }

    for (int i = 0; i < sb; i++)
    {
        for (int j = 0; j < sb; j++)
        {
            printf("%d ", b[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i <= (sb)*c_s; i++)
    {
        for (int j = 0; j <= (sb)*r_s; j++)
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
                    else if (b[i / c_s][j / r_s] == 3)
                    {
                        setColor(BLACK);
                        printf("W");
                    }
                    else if (b[i / c_s][j / r_s] == 2)
                    {
                        setColor(WHITE);
                        printf("@");
                    }
                    else if (b[i / c_s][j / r_s] == 4)
                    {
                        setColor(WHITE);
                        printf("W");
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
    if (c_state.cur_turn == BLACK)
    {
        printf("BLACK\n");
    }
    else
        printf("WHITE\n");

    printf("Press 'H' to see instructions , 'Q' to Quit game and 'N' to restart game\n");
}

bool isOccupied(game_state *g, int x, int y)
{
    for (int i = 0; i < tp; ++i)
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
        for (int i = 0; i < tp; ++i)
        {
            if (P.x == g->black[i].x && P.y == g->black[i].y)
                return true;
        }
    }
    else if (P.allegiance == WHITE)
    {
        for (int i = 0; i < tp; ++i)
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
        if (P.x + 1 > sb - 1 || P.y + 1 > sb - 1)
            return false;
        AfterMove_X = P.x + 1;
        AfterMove_Y = P.y + 1;
        break;
    case bottomRight:
        if (P.x + 1 > sb - 1 || P.y - 1 < 0)
            return false;
        AfterMove_X = P.x + 1;
        AfterMove_Y = P.y - 1;
        break;
    case topLeft:
        if (P.x - 1 < 0 || P.y + 1 > sb - 1)
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
    if (P.allegiance == BLACK && P.is_king == false)
    {
        if (direction == topRight || direction == topLeft)
            return false;
    }
    else if (P.allegiance == WHITE && P.is_king == false)
    {
        if (direction == bottomRight || direction == bottomLeft)
            return false;
    }
    pawn Enemy;
    int AfterCapture_X, AfterCapture_Y;
    switch (direction)
    {
    case topRight:
        if (P.x + 2 >= sb || P.y + 2 >= sb)
            return false;
        AfterCapture_X = P.x + 2;
        AfterCapture_Y = P.y + 2;
        Enemy.x = P.x + 1;
        Enemy.y = P.y + 1;
        Enemy.allegiance = colorFlip(P.allegiance);
        break;
    case bottomRight:
        if (P.x + 2 >= sb || P.y - 2 < 0)
            return false;
        AfterCapture_X = P.x + 2;
        AfterCapture_Y = P.y - 2;
        Enemy.x = P.x + 1;
        Enemy.y = P.y - 1;
        Enemy.allegiance = colorFlip(P.allegiance);
        break;
    case topLeft:
        if (P.x - 2 < 0 || P.y + 2 >= sb)
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
    if (p.x < 0 || p.y < 0 || p.x >= sb || p.y >= sb) // x and y between 0 and 7
        return false;
    if (new_pos.x < 0 || new_pos.y < 0 || new_pos.x >= sb || new_pos.y >= sb)
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

        if (p.allegiance == WHITE)
        {
            for (int i = 0; i < tp; ++i)
            {
                if (g->white[i].x != -1)
                {
                    if (capturePossible(g, g->white[i], topRight) ||
                        capturePossible(g, g->white[i], topLeft))
                        return false;
                    if (g->white[i].is_king &&
                        (capturePossible(g, g->white[i], bottomRight) ||
                         capturePossible(g, g->white[i], bottomLeft)))
                        return false;
                }
            }
        }
        else if (p.allegiance == BLACK)
        {
            for (int i = 0; i < tp; ++i)
            {
                if (g->black[i].x != -1)
                {
                    if (capturePossible(g, g->black[i], bottomRight) ||
                        capturePossible(g, g->black[i], bottomLeft))
                        return false;
                    if (g->black[i].is_king &&
                        (capturePossible(g, g->black[i], topRight) ||
                         capturePossible(g, g->black[i], topLeft)))
                        return false;
                }
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

void start(log *head)
{
    int cur_pc = 0;
    for (int i = 0; i < (sb - 2) / 2; i++)
    {
        for (int j = 0; j < sb; j++)
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
    for (int i = sb - 1; i >= sb - (sb - 2) / 2; i--)
    {
        for (int j = 0; j < sb; j++)
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
    cls();
    controller(head);
    // print_board(&c_state);
}

void restart(log *head)
{
    clear_stack(head);
    start(head);
}

void clear_stack(log *head)
{
    log *temp;
    while (head->next != NULL)
    {
        temp = head->next;
        if (head->next->next != NULL)
        {
            head->next = head->next->next;
            head->next->prev = head;
        }
        else
        {
            head->next = NULL;
        }
        free(temp);
    }
}

void result(game_state *P, log *head)
{
    int white_pieces_left = 0;
    int black_pieces_left = 0;

    for (int i = 0; i < tp; i++)
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
        printf("press 'R' to Review\n");
        char key = getkey();
        if (key == 'R')
            review(head);
        return;
    }
    else if (black_pieces_left == 0)
    {
        printf("White is the winner\n");
        printf("press 'R' to Review\n");
        char key = getkey();
        if (key == 'R')
            review(head);
        return;
    }
    else // in this case , no. of pieces left of both color will be non zero
    {
        bool white_draw_Check = true, black_draw_Check = true; // if both are true -> DRAW

        for (int i = 0; i < tp; ++i)
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
            return;
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

void draw(game_state *P, log *head) // just call this fxn and it will print who is the winner and the current board
{
    result(P, head);
    print_board(P);
}

void Quit(log *head)
{

    printf("Do you want to quit the game? [y/n]\n");
    while (1)
    {
        char ch = getkey();
        if (ch == 'y')
        {
            printf("Do you want to Review the game?[y/n]\n");
            while (1)
            {
                char key = getkey();
                if (key == 'y')
                {
                    review(head);
                }
                else if (key == 'n')
                {
                    clear_stack(head);
                    cls();
                    exit(0);
                }
            }
        }
        else if (ch == 'n')
        {
            cls();
            return;
        }
    }
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

void controller(log *head)
{
    push(head, &c_state);
    while (1)
    {
        pawn p;
        int c;
        if (c_state.cur_turn == BLACK)
        {
            //  char c = getkey();
            /*   if(c == 'u') 
            {
                c_state = undo(head);
                print_board(&c_state);
                continue;
            }*/
            if (bot_mode == BLACK)
            {
                //---------------------------------------------------------------BOT-Playing----------------------------------------------------------------
                int count_w = 0;
                for (int i = 0; i < tp; i++)
                {
                    if (capturePossible(&c_state, c_state.black[i], bottomLeft) || capturePossible(&c_state, c_state.black[i], bottomRight))
                    {
                        count_w = 1;
                        break;
                    }
                    else if (c_state.black[i].is_king == 1)
                    {
                        if (capturePossible(&c_state, c_state.black[i], topLeft) || capturePossible(&c_state, c_state.black[i], topRight))
                        {
                            count_w = 1;
                            break;
                        }
                    }
                }
                printf("Bot");
                botb();
                //    print_board(&c_state);
                int flag1 = 0;
                if (count_w == 1)
                {
                    for (int i = 0; i < tp; i++)
                    {
                        if (capturePossible(&c_state, c_state.black[i], bottomLeft) || capturePossible(&c_state, c_state.black[i], bottomRight))
                        {
                            flag1 = 1;
                            break;
                        }
                        else if (c_state.black[i].is_king == 1)
                        {
                            if (capturePossible(&c_state, c_state.black[i], topLeft) || capturePossible(&c_state, c_state.black[i], topRight))
                            {
                                flag1 = 1;
                                break;
                            }
                        }
                    }
                    count_w = 0;
                }
                if (flag1 == 1)
                {
                    flag1 = 0;
                    push(head, &c_state);
                    continue;
                }

                c_state.cur_turn = colorFlip(c_state.cur_turn);
                push(head, &c_state);
                //-----------------------------------------------------------------------------------------------------------------------------------------------
            }
            else
            {

                for (int i = tp - 1; i >= 0; --i)
                {
                    if (c_state.black[i].x != -1 && c_state.black[i].y != -1)
                    {
                        c = i;
                        break;
                    }
                }
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
                        x[cur] = (x[cur] + 1) % sb;
                    }
                    else if (ch == 's')
                    {
                        y[cur] = (y[cur] - 1) % sb;
                        if (y[cur] < 0)
                            y[cur] += sb;
                    }
                    else if (ch == 'w')
                    {
                        y[cur] = (y[cur] + 1) % sb;
                    }
                    else if (ch == 'a')
                    {
                        x[cur] = (x[cur] - 1) % sb;
                        if (x[cur] < 0)
                            x[cur] += sb;
                    }
                    else if (ch == 'r')
                    {
                        cls();
                    }
                    else if (ch == 'b')
                    {
                        cls();
                        while (1)
                        {
                            rule();
                            char key = getkey();
                            if (key == 'e')
                            {
                                cls();
                                break;
                            }
                        }
                    }
                    else if (ch == 'u')
                    {
                        c_state = undo(head);
                        if (bot_mode != -1)
                            c_state = undo(head);
                        break;
                    }
                    else if (ch == 'N')
                    {
                        restart(head);
                    }
                    else if (ch == 'H')
                    {
                        cls();
                        while (1)
                        {
                            instruction();
                            char key = getkey();
                            if (key == 'e')
                            {
                                cls();
                                break;
                            }
                        }
                    }
                    else if (ch == 'Q')
                    {
                        Quit(head);
                    }
                    else if (ch == 'R')
                    {
                        review(head);
                    }
                    else if (ch == 'k')
                    {
                        printf("Enter 'k' (# next state you want to print)\n");
                        int k;
                        scanf("%d", &k);
                        print_k_state(c_state, k);
                    }
                    else if (ch == KEY_SPACE)
                    {
                        if (cur == 0)
                        {
                            int flag = -1;
                            for (int i = 0; i < tp; ++i)
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
                            int count_w = 0;
                            if (capturePossible(&c_state, p, bottomLeft) || capturePossible(&c_state, p, bottomRight))
                            {
                                count_w = 1;
                            }
                            else if (p.is_king == 1)
                            {
                                if (capturePossible(&c_state, p, topLeft) || capturePossible(&c_state, p, topRight))
                                    count_w = 1;
                            }

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

                                int flag1 = 0;
                                if (count_w == 1)
                                {
                                    for (int i = 0; i < tp; i++)
                                    {
                                        if (capturePossible(&c_state, c_state.black[i], bottomLeft) || capturePossible(&c_state, c_state.black[i], bottomRight))
                                        {
                                            push(head, &c_state);
                                            flag1 = 1;
                                            break;
                                        }
                                        else if (c_state.black[i].is_king == 1)
                                        {
                                            if (capturePossible(&c_state, c_state.black[i], topLeft) || capturePossible(&c_state, c_state.black[i], topRight))
                                            {
                                                flag1 = 1;
                                                push(head, &c_state);
                                                break;
                                            }
                                        }
                                    }
                                    count_w = 0;
                                }
                                if (flag1 == 1)
                                {
                                    flag1 = 0;
                                    continue;
                                }

                                c_state.cur_turn = colorFlip(c_state.cur_turn);
                                push(head, &c_state);
                                break;
                            }
                        }
                    }
                }
            }
        }

        else
        {
            if (bot_mode == WHITE)
            {
                int count_w = 0;
                for (int i = 0; i < tp; i++)
                {
                    if (capturePossible(&c_state, c_state.white[i], topLeft) || capturePossible(&c_state, c_state.white[i], topRight))
                    {
                        count_w = 1;
                        break;
                    }
                    else if (c_state.white[i].is_king == 1)
                    {
                        if (capturePossible(&c_state, c_state.white[i], bottomLeft) || capturePossible(&c_state, c_state.white[i], bottomRight))
                        {
                            count_w = 1;
                            break;
                        }
                    }
                }
                printf("Bot");
                botw();
                //    print_board(&c_state);
                int flag1 = 0;
                if (count_w == 1)
                {
                    for (int i = 0; i < tp; i++)
                    {
                        if (capturePossible(&c_state, c_state.white[i], topLeft) || capturePossible(&c_state, c_state.white[i], topRight))
                        {
                            flag1 = 1;
                            break;
                        }
                        else if (c_state.white[i].is_king == 1)
                        {
                            if (capturePossible(&c_state, c_state.white[i], bottomLeft) || capturePossible(&c_state, c_state.white[i], bottomRight))
                            {
                                flag1 = 1;
                                break;
                            }
                        }
                    }
                    count_w = 0;
                }
                if (flag1 == 1)
                {
                    flag1 = 0;
                    push(head, &c_state);
                    continue;
                }

                c_state.cur_turn = colorFlip(c_state.cur_turn);
                push(head, &c_state);
            }
            else
            {
                for (int i = tp - 1; i >= 0; --i)
                {
                    if (c_state.white[i].x != -1 && c_state.white[i].y != -1)
                    {
                        c = i;
                        break;
                    }
                }
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
                        x[cur] = (x[cur] + 1) % sb;
                    }
                    else if (ch == 's')
                    {
                        y[cur] = (y[cur] - 1) % sb;
                        if (y[cur] < 0)
                            y[cur] += sb;
                    }
                    else if (ch == 'w')
                    {
                        y[cur] = (y[cur] + 1) % sb;
                    }
                    else if (ch == 'a')
                    {
                        x[cur] = (x[cur] - 1) % sb;
                        if (x[cur] < 0)
                            x[cur] += sb;
                    }
                    else if (ch == 'r')
                    {
                        cls();
                    }
                    else if (ch == 'b')
                    {
                        cls();
                        while (1)
                        {
                            rule();
                            char key = getkey();
                            if (key == 'e')
                            {
                                cls();
                                break;
                            }
                        }
                    }
                    else if (ch == 'u')
                    {
                        c_state = undo(head);
                        if (bot_mode != -1)
                            c_state = undo(head);
                        break;
                    }
                    else if (ch == 'N')
                    {
                        restart(head);
                    }
                    else if (ch == 'H')
                    {
                        cls();
                        while (1)
                        {
                            instruction();
                            char key = getkey();
                            if (key == 'e')
                            {
                                cls();
                                break;
                            }
                        }
                    }
                    else if (ch == 'Q')
                    {
                        Quit(head);
                    }
                    else if (ch == 'R')
                    {
                        review(head);
                    }
                    else if (ch == 'k')
                    {
                        printf("Enter 'k' (# next state you want to print)\n");
                        int k;
                        scanf("%d", &k);
                        print_k_state(c_state, k);
                    }
                    else if (ch == KEY_SPACE)
                    {
                        if (cur == 0)
                        {
                            int flag = -1;
                            for (int i = 0; i < tp; ++i)
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
                            int count_b = 0;
                            if (capturePossible(&c_state, p, topLeft) || capturePossible(&c_state, p, topRight))
                            {
                                count_b = 1;
                            }
                            else if (p.is_king == 1)
                            {
                                if (capturePossible(&c_state, p, bottomLeft) || capturePossible(&c_state, p, bottomRight))
                                    count_b = 1;
                            }

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
                                int flag2 = 0;
                                if (count_b == 1)
                                {
                                    for (int i = 0; i < tp; i++)
                                    {
                                        if (capturePossible(&c_state, c_state.white[i], topLeft) || capturePossible(&c_state, c_state.white[i], topRight))
                                        {
                                            flag2 = 1;
                                            push(head, &c_state);
                                            break;
                                        }
                                        else if (c_state.white[i].is_king == 1)
                                        {
                                            if (capturePossible(&c_state, c_state.white[i], bottomLeft) || capturePossible(&c_state, c_state.white[i], bottomRight))
                                            {
                                                flag2 = 1;
                                                push(head, &c_state);
                                                break;
                                            }
                                        }
                                    }
                                    count_b = 0;
                                }
                                if (flag2 == 1)
                                {
                                    flag2 = 0;
                                    continue;
                                }

                                c_state.cur_turn = colorFlip(c_state.cur_turn);
                                push(head, &c_state);
                                break;
                            }
                        }
                    }
                }
            }
        }
        result(&c_state, head);
    }
}

void instruction()
{
    cls();
    char A;
    FILE *fp;

    fp = fopen("instruction.txt", "r");
    while (feof(fp) != 1)
    {
        fscanf(fp, "%c", &A);
        printf("%c", A);
    }
    if (fp == NULL)
        printf("File doesnot exist\n");

    fclose(fp);
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
    cls();
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

log *CreateEmptyStackNode()
{
    log *S = (log *)malloc(sizeof(log));

    S->next = NULL;
    S->prev = NULL;

    return S;
}

void push(log *head, game_state *preState)
{
    log *S = CreateEmptyStackNode();
    S->g = *preState;
    if (head->next != NULL)
    {
        S->next = head->next;
        head->next = S;
        S->next->prev = S;
        S->prev = head;
    }
    else
    {
        //      assert(0); // should never happen now
        S->next = head->next;
        head->next = S;
        S->prev = head;
    }
}

game_state undo(log *head) //undo fxn go one steps back and deletes the current state
{

    if (head->next->next == NULL)
    {
        printf("Stack is Empty\n");
        return c_state;
    }
    log *t = head->next;
    log *temp = head->next->next;
    game_state s = temp->g;
    head->next = temp;
    temp->prev = head;

    free(t);
    return s;
}

void review(log *head)
{
    cls();
    log *temp;
    while (head->next != NULL)
    {
        temp = head->next;
        game_state s = temp->g;

        print_board(&(temp->g));
        head = head->next;
    }

    printf("press 'e' to resume the game or 'Q' to Quit the game\n");
    while (1)
    {
        char ch = getkey();

        if (ch == 'e')
        {
            cls();
            return;
        }
        if (ch == 'Q')
        {
            cls();
            exit(0);
        }
    }
}

void max_heapify(nodeb array[], int N, int i) //N is size of array, and afer i it follows max-heap property
{
    //sorted according to score.
    int left_child = 2 * i;
    int right_child = 2 * i + 1;
    int max = i;
    if (left_child < N && array[i].score < array[left_child].score)
        max = left_child;
    if (right_child < N && array[max].score < array[right_child].score)
        max = right_child;
    if (max != i)
    {
        nodeb temp = array[i]; //swaping nodes
        array[i] = array[max];
        array[max] = temp;
        max_heapify(array, N, max); //if swap than only calling the function, just saving iretration.
    }
}

void build_max_heap(nodeb array[], int N) //for bot
{
    for (int i = N / 2 - 1; i >= 0; --i)
        max_heapify(array, N, i);
}
void insert_element(nodeb array[], int *ptr_size, nodeb element)
{
    //insert element at correct place in max_heap, i.e assuming array is max_heap
    //also i assume array was init by malloc
    *ptr_size = *ptr_size + 1;
    array = (nodeb *)realloc(array, *ptr_size);
    assert(array != NULL);
    max_heapify(array, *ptr_size, *ptr_size - 1);
}

void delete_element(nodeb array[], int *ptr_size)
{
    //delete the max element in the heap
    array[0] = array[*ptr_size - 1];
    *ptr_size = *ptr_size - 1; //i.e size of array is now on
    max_heapify(array, *ptr_size, 0);
}
int main()
{
    //cls();
    if (sb % 2 != 0)
        exit(1);
    resetColor();
    log *head = CreateEmptyStackNode(); // start of linked list which is going to store table after every move

    char key;
    printf("Press 'e' to start and 't' to toss\n");

    while (1)
    {
        key = getkey();
        if (key == 't')
            toss();

        else if (key == 'e')
            start(head);
    }
    return 0;
}