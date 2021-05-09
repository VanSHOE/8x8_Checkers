
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rlutil.h"
#include "checkers.h"
#include <stdbool.h>
#include <assert.h>
int lim = 4;

he heap[10000007];
ll size = 0;

void siftup(int index)
{
    if (index == 0)
        return;
    if (heap[(index - 1) / 2].d < heap[index].d)
    {
        he temp = heap[index];
        heap[index] = heap[(index - 1) / 2];
        heap[(index - 1) / 2] = temp;
        siftup((index - 1) / 2);
    }
}

void DownHeap(int index)
{
    int w1 = 2 * index + 1;
    if (w1 >= size)
        return;

    if (w1 + 1 < size)
        if (heap[w1].d < heap[w1 + 1].d)
            w1++;

    if (heap[index].d >= heap[w1].d)
        return;
    he temp = heap[w1];
    heap[w1] = heap[index];
    heap[index] = temp;
    DownHeap(w1);
}

void insert(he elem)
{
    heap[size++] = elem;
    siftup(size - 1);
}

he Extract_max()
{
    if (size <= 0)
    {

        he temp;
        temp.index = -1;
        temp.d = -1;
        return temp;
    }

    he ans = heap[0];
    heap[0] = heap[--size];
    DownHeap(0);
    return ans;
}

bool is_multi_capture_possible(game_state g)
{
    if (g.cur_turn == BLACK)
    {
        for (int i = 0; i < tp; i++)
        {
            if (capturePossible(&g, g.black[i], bottomLeft) || capturePossible(&g, g.black[i], bottomRight))
            {
                return true;
            }
            else if (g.black[i].is_king == 1)
            {
                if (capturePossible(&g, g.black[i], topLeft) || capturePossible(&g, g.black[i], topRight))
                {
                    return true;
                }
            }
        }
    }

    else
    {
        for (int i = 0; i < tp; i++)
        {
            if (capturePossible(&g, g.white[i], topLeft) || capturePossible(&g, g.white[i], topRight))
            {
                return true;
            }
            else if (g.white[i].is_king == 1)
            {
                if (capturePossible(&g, g.white[i], bottomLeft) || capturePossible(&g, g.white[i], bottomRight))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

long double bot_helperb(game_state g_o, int lim)
{
    if (!lim)
        return 0;

    long double *scores = (long double *)calloc(tp * 4, sizeof(long double)); // This array is tasked with storing the scores of all possible moves in the current state
    g_o.cur_turn = colorFlip(g_o.cur_turn);                                   // Flip the turn from the last turn to calculate scores of the correct side, WHITE or BLACK
    game_state g = g_o;
    /*
        The 8 if statements in each of the main if blocks are simply calling move entries with all possible moves on all the pieces of the current player on the current game state g which modifies
        which again recursively calls this function for a total of lim times

        For a non king piece, moving towards the enemy's side grants the bot 2 points, while moving backwards grant only a single point
        Capturing grants 10 points

        Now, when the bot is thinking, the bot also calculates the moves of the opponent and calculates its points in the exact same way, the only difference being, it subtracts its scores from its own scores
        As an example, let's say you move a piece, which allowed opponent to capture some piece, then that move will get a -10 penalty on its score
        the 0.9 in second line of each if block simply ensures that priority of the current scores are more than priority of the scores further down the line
    */
    if (g.cur_turn == BLACK)
    {
        for (int i = 0; i < tp; i++)
        {
            int pc_i = i;
            // Top-Right
            if (move_entries(&g, g.black[pc_i], g.black[pc_i].x + 1, g.black[pc_i].y + 1))
            {
                scores[4 * i] = 1;
                scores[4 * i] += 0.9 * bot_helperb(g, lim - 1);
                g = g_o;
            }
            else if (move_entries(&g, g.black[pc_i], g.black[pc_i].x + 2, g.black[pc_i].y + 2))
            {
                // Now here and in statements below, a capture happened, according to our rules, if any of our piece can make a capture again, another turn is granted, so we check if there is any other capture available
                if (is_multi_capture_possible(g))
                    g.cur_turn = colorFlip(g.cur_turn); // If yes the line nullifies the turn flip by flipping the turn beforehand

                scores[4 * i] = 10;
                scores[4 * i] += 0.9 * bot_helperb(g, lim - 1);
                g = g_o;
            }
            // Bottom-Right
            if (move_entries(&g, g.black[pc_i], g.black[pc_i].x + 1, g.black[pc_i].y - 1))
            {
                scores[4 * i + 1] = (g.black[pc_i].is_king) ? 1 : 2; // Now if a piece IS a king, moving in any directions grants the same score
                scores[4 * i + 1] += 0.9 * bot_helperb(g, lim - 1);
                g = g_o;
            }
            else if (move_entries(&g, g.black[pc_i], g.black[pc_i].x + 2, g.black[pc_i].y - 2))
            {
                if (is_multi_capture_possible(g))
                    g.cur_turn = colorFlip(g.cur_turn);

                scores[4 * i + 1] = 10;
                scores[4 * i + 1] += 0.9 * bot_helperb(g, lim - 1);
                g = g_o;
            }
            // Bottom-Left
            if (move_entries(&g, g.black[pc_i], g.black[pc_i].x - 1, g.black[pc_i].y - 1))
            {
                scores[4 * i + 2] = (g.black[pc_i].is_king) ? 1 : 2;
                scores[4 * i + 2] += 0.9 * bot_helperb(g, lim - 1);
                g = g_o;
            }
            else if (move_entries(&g, g.black[pc_i], g.black[pc_i].x - 2, g.black[pc_i].y - 2))
            {
                if (is_multi_capture_possible(g))
                    g.cur_turn = colorFlip(g.cur_turn);

                scores[4 * i + 2] = 10;
                scores[4 * i + 2] += 0.9 * bot_helperb(g, lim - 1);
                g = g_o;
            }
            //Top-Left
            if (move_entries(&g, g.black[pc_i], g.black[pc_i].x - 1, g.black[pc_i].y + 1))
            {
                scores[4 * i + 3] = 1;
                scores[4 * i + 3] += 0.9 * bot_helperb(g, lim - 1);
                g = g_o;
            }
            else if (move_entries(&g, g.black[pc_i], g.black[pc_i].x - 2, g.black[pc_i].y + 2))
            {
                if (is_multi_capture_possible(g))
                    g.cur_turn = colorFlip(g.cur_turn);

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

            //Top right
            if (move_entries(&g, g.white[pc_i], g.white[pc_i].x + 1, g.white[pc_i].y + 1))
            {
                scores[4 * i] = (g.white[pc_i].is_king) ? 1 : 2;
                scores[4 * i] += 0.9 * bot_helperb(g, lim - 1);
                g = g_o;
            }
            else if (move_entries(&g, g.white[pc_i], g.white[pc_i].x + 2, g.white[pc_i].y + 2))
            {
                if (is_multi_capture_possible(g))
                    g.cur_turn = colorFlip(g.cur_turn);

                scores[4 * i] = 10;
                scores[4 * i] += 0.9 * bot_helperb(g, lim - 1);
                g = g_o;
            }
            //Bottom right
            if (move_entries(&g, g.white[pc_i], g.white[pc_i].x + 1, g.white[pc_i].y - 1))
            {
                scores[4 * i + 1] = 1;
                scores[4 * i + 1] += 0.9 * bot_helperb(g, lim - 1);
                g = g_o;
            }
            else if (move_entries(&g, g.white[pc_i], g.white[pc_i].x + 2, g.white[pc_i].y - 2))
            {
                if (is_multi_capture_possible(g))
                    g.cur_turn = colorFlip(g.cur_turn);

                scores[4 * i + 1] = 10;
                scores[4 * i + 1] += 0.9 * bot_helperb(g, lim - 1);
                g = g_o;
            }
            //Bottom left
            if (move_entries(&g, g.white[pc_i], g.white[pc_i].x - 1, g.white[pc_i].y - 1))
            {
                scores[4 * i + 2] = 1;
                scores[4 * i + 2] += 0.9 * bot_helperb(g, lim - 1);
                g = g_o;
            }
            else if (move_entries(&g, g.white[pc_i], g.white[pc_i].x - 2, g.white[pc_i].y - 2))
            {
                if (is_multi_capture_possible(g))
                    g.cur_turn = colorFlip(g.cur_turn);

                scores[4 * i + 2] = 10;
                scores[4 * i + 2] += 0.9 * bot_helperb(g, lim - 1);
                g = g_o;
            }
            //Top left
            if (move_entries(&g, g.white[pc_i], g.white[pc_i].x - 1, g.white[pc_i].y + 1))
            {
                scores[4 * i + 3] = (g.white[pc_i].is_king) ? 1 : 2;
                scores[4 * i + 3] += 0.9 * bot_helperb(g, lim - 1);
                g = g_o;
            }
            else if (move_entries(&g, g.white[pc_i], g.white[pc_i].x - 2, g.white[pc_i].y + 2))
            {
                if (is_multi_capture_possible(g))
                    g.cur_turn = colorFlip(g.cur_turn);

                scores[4 * i + 3] = 10;
                scores[4 * i + 3] += 0.9 * bot_helperb(g, lim - 1);
                g = g_o;
            }
            // This is where the inversion happens, we are in black bot function, so for that bot, scores of white must be inverted
            scores[4 * i] = -scores[4 * i];
            scores[4 * i + 1] = -scores[4 * i + 1];
            scores[4 * i + 2] = -scores[4 * i + 2];
            scores[4 * i + 3] = -scores[4 * i + 3];
        }
    }
    long double sum = 0;
    // Add up scores all of the moves that happened due to this move to this move's score
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
    /*
        The 8 if statements in each of the main if blocks are simply calling move entries with all possible moves on all the pieces of the current player on the current game state g which modifies
        which again recursively calls this function for a total of lim times

        For a non king piece, moving towards the enemy's side grants the bot 2 points, while moving backwards grant only a single point
        Capturing grants 10 points

        Now, when the bot is thinking, the bot also calculates the moves of the opponent and calculates its points in the exact same way, the only difference being, it subtracts its scores from its own scores
        As an example, let's say you move a piece, which allowed opponent to capture some piece, then that move will get a -10 penalty on its score
        the 0.9 in second line of each if block simply ensures that priority of the current scores are more than priority of the scores further down the line

        And incase of a capture, we check whether another capture is possible, if another turn is granted and we flip the turn to nullify the flip that happens in the recursive call
    */
    for (int i = 0; i < tp; i++)
    {
        int pc_i = i;

        //Top right
        if (move_entries(&g, g.black[pc_i], g.black[pc_i].x + 1, g.black[pc_i].y + 1))
        {
            scores[4 * i] = 1;
            scores[4 * i] += 0.9 * bot_helperb(g, lim - 1);
            g = c_state;
        }
        else if (move_entries(&g, g.black[pc_i], g.black[pc_i].x + 2, g.black[pc_i].y + 2))
        {
            if (is_multi_capture_possible(g))
                g.cur_turn = colorFlip(g.cur_turn);

            scores[4 * i] = 10;
            scores[4 * i] += 0.9 * bot_helperb(g, lim - 1);
            g = c_state;
        }
        //Bottom right
        if (move_entries(&g, g.black[pc_i], g.black[pc_i].x + 1, g.black[pc_i].y - 1))
        {
            scores[4 * i + 1] = (g.black[pc_i].is_king) ? 1 : 2; // Now if a piece IS a king, moving in any directions grants the same score
            scores[4 * i + 1] += 0.9 * bot_helperb(g, lim - 1);
            g = c_state;
        }
        else if (move_entries(&g, g.black[pc_i], g.black[pc_i].x + 2, g.black[pc_i].y - 2))
        {
            if (is_multi_capture_possible(g))
                g.cur_turn = colorFlip(g.cur_turn);

            scores[4 * i + 1] = 10;
            scores[4 * i + 1] += 0.9 * bot_helperb(g, lim - 1);
            g = c_state;
        }
        //Bottom left
        if (move_entries(&g, g.black[pc_i], g.black[pc_i].x - 1, g.black[pc_i].y - 1))
        {
            scores[4 * i + 2] = (g.black[pc_i].is_king) ? 1 : 2;
            scores[4 * i + 2] += 0.9 * bot_helperb(g, lim - 1);
            g = c_state;
        }
        else if (move_entries(&g, g.black[pc_i], g.black[pc_i].x - 2, g.black[pc_i].y - 2))
        {
            if (is_multi_capture_possible(g))
                g.cur_turn = colorFlip(g.cur_turn);

            scores[4 * i + 2] = 10;
            scores[4 * i + 2] += 0.9 * bot_helperb(g, lim - 1);
            g = c_state;
        }
        //Top left
        if (move_entries(&g, g.black[pc_i], g.black[pc_i].x - 1, g.black[pc_i].y + 1))
        {
            scores[4 * i + 3] = 1;
            scores[4 * i + 3] += 0.9 * bot_helperb(g, lim - 1);
            g = c_state;
        }
        else if (move_entries(&g, g.black[pc_i], g.black[pc_i].x - 2, g.black[pc_i].y + 2))
        {
            if (is_multi_capture_possible(g))
                g.cur_turn = colorFlip(g.cur_turn);

            scores[4 * i + 3] = 10;
            scores[4 * i + 3] += 0.9 * bot_helperb(g, lim - 1);
            g = c_state;
        }
    }
    int mi = 0;
    // Once the scores are calculated, we go through all moves and insert the valid ones into the heap
    for (int i = 0; i < 4 * tp; i++)
    {
        he q;
        int pc_i = i / 4;
        q.index = i;
        q.d = scores[i];
        pawn n;
        int flag = 0; // flag is set to 1 as soon as any valid move is detected
        switch (i % 4)
        {
        case 0:
            n.x = c_state.black[pc_i].x + 1;
            n.y = c_state.black[pc_i].y + 1;
            if (!isLegal(c_state.black[pc_i], n, &c_state))
            {
                n.x = c_state.black[pc_i].x + 2;
                n.y = c_state.black[pc_i].y + 2;
                if (isLegal(c_state.black[pc_i], n, &c_state))
                    flag = 1;
            }
            else
                flag = 1;
            break;
        case 1:
            n.x = c_state.black[pc_i].x + 1;
            n.y = c_state.black[pc_i].y - 1;
            if (!isLegal(c_state.black[pc_i], n, &c_state))
            {
                n.x = c_state.black[pc_i].x + 2;
                n.y = c_state.black[pc_i].y - 2;
                if (isLegal(c_state.black[pc_i], n, &c_state))
                    flag = 1;
            }
            else
                flag = 1;
            break;
        case 2:
            n.x = c_state.black[pc_i].x - 1;
            n.y = c_state.black[pc_i].y - 1;
            if (!isLegal(c_state.black[pc_i], n, &c_state))
            {
                n.x = c_state.black[pc_i].x - 2;
                n.y = c_state.black[pc_i].y - 2;
                if (isLegal(c_state.black[pc_i], n, &c_state))
                    flag = 1;
            }
            else
                flag = 1;
            break;
        case 3:
            n.x = c_state.black[pc_i].x - 1;
            n.y = c_state.black[pc_i].y + 1;
            if (!isLegal(c_state.black[pc_i], n, &c_state))
            {
                n.x = c_state.black[pc_i].x - 2;
                n.y = c_state.black[pc_i].y + 2;
                if (isLegal(c_state.black[pc_i], n, &c_state))
                    flag = 1;
            }
            else
                flag = 1;
            break;
        }
        if (flag)
            insert(q);
    }

    // Added to ensure some sort of randomness to the bot, the bot doesn't always pick the move it thinks is best but rather based on the difficulty
    // Has a probability distribution using which it will either pick the first best move, second best move or the third best move
    int prob = rand() % 100 + 1;
    int k;
    if (difficulty == 0)
    {
        if (prob <= 95)
        {
            k = 0;
        }
        else
            k = 1;
    }
    else if (difficulty == 1)
    {
        if (prob <= 80)
        {
            k = 0;
        }
        else if (prob <= 98)
        {
            k = 1;
        }
        else
            k = 2;
    }
    else
    {
        if (prob <= 70)
        {
            k = 0;
        }
        else if (prob <= 95)
        {
            k = 1;
        }
        else
            k = 2;
    }
    if (k >= size)
    {
        k = size - 1;
    }
    // remove the k best moves
    while (k--)
        Extract_max();

    he temp = Extract_max();
    if (temp.index == -1) // bot is out of move , call result fxn
    {
        size = 0;
        printf("Press R to review and Q to quit\n");
        return;
    }
    mi = temp.index;
    int pc_i = mi / 4;
    //   printf("Moving %d", mi);
    // Simply attempt that move, the way we store our moves, mi / 4 stores index of the piece and mi % 4 gives information about what move to play
    switch (mi % 4)
    {
    case 0:
        if (!move_entries(&c_state, c_state.black[pc_i], c_state.black[pc_i].x + 1, c_state.black[pc_i].y + 1))
        {
            move_entries(&c_state, c_state.black[pc_i], c_state.black[pc_i].x + 2, c_state.black[pc_i].y + 2);
        }
        break;
    case 1:
        if (!move_entries(&c_state, c_state.black[pc_i], c_state.black[pc_i].x + 1, c_state.black[pc_i].y - 1))
        {
            move_entries(&c_state, c_state.black[pc_i], c_state.black[pc_i].x + 2, c_state.black[pc_i].y - 2);
        };
        break;
    case 2:
        if (!move_entries(&c_state, c_state.black[pc_i], c_state.black[pc_i].x - 1, c_state.black[pc_i].y - 1))
        {
            move_entries(&c_state, c_state.black[pc_i], c_state.black[pc_i].x - 2, c_state.black[pc_i].y - 2);
        }

        break;
    case 3:
        if (!move_entries(&c_state, c_state.black[pc_i], c_state.black[pc_i].x - 1, c_state.black[pc_i].y + 1))
        {
            move_entries(&c_state, c_state.black[pc_i], c_state.black[pc_i].x - 2, c_state.black[pc_i].y + 2);
        }
        break;
    }
    // reset the heap for next use
    size = 0;
    free(scores);
}

long double bot_helperw(game_state g_o, int lim)
{
    if (!lim)
        return 0;

    long double *scores = (long double *)calloc(tp * 4, sizeof(long double));
    g_o.cur_turn = colorFlip(g_o.cur_turn);
    game_state g = g_o;
    /*
        The 8 if statements in each of the main if blocks are simply calling move entries with all possible moves on all the pieces of the current player on the current game state g which modifies
        which again recursively calls this function for a total of lim times

        For a non king piece, moving towards the enemy's side grants the bot 2 points, while moving backwards grant only a single point
        Capturing grants 10 points

        Now, when the bot is thinking, the bot also calculates the moves of the opponent and calculates its points in the exact same way, the only difference being, it subtracts its scores from its own scores
        As an example, let's say you move a piece, which allowed opponent to capture some piece, then that move will get a -10 penalty on its score
        the 0.9 in second line of each if block simply ensures that priority of the current scores are more than priority of the scores further down the line
    */
    if (g.cur_turn == BLACK)
    {
        for (int i = 0; i < tp; i++)
        {
            int pc_i = i;

            //Top right
            if (move_entries(&g, g.black[pc_i], g.black[pc_i].x + 1, g.black[pc_i].y + 1))
            {
                scores[4 * i] = 1;
                scores[4 * i] += 0.9 * bot_helperw(g, lim - 1);
                g = g_o;
            }
            else if (move_entries(&g, g.black[pc_i], g.black[pc_i].x + 2, g.black[pc_i].y + 2))
            {
                if (is_multi_capture_possible(g))
                    g.cur_turn = colorFlip(g.cur_turn);

                scores[4 * i] = 10;
                scores[4 * i] += 0.9 * bot_helperw(g, lim - 1);
                g = g_o;
            }
            //Bottom right
            if (move_entries(&g, g.black[pc_i], g.black[pc_i].x + 1, g.black[pc_i].y - 1))
            {
                scores[4 * i + 1] = (g.black[pc_i].is_king) ? 1 : 2;
                scores[4 * i + 1] += 0.9 * bot_helperw(g, lim - 1);
                g = g_o;
            }
            else if (move_entries(&g, g.black[pc_i], g.black[pc_i].x + 2, g.black[pc_i].y - 2))
            {
                if (is_multi_capture_possible(g))
                    g.cur_turn = colorFlip(g.cur_turn);

                scores[4 * i + 1] = 10;
                scores[4 * i + 1] += 0.9 * bot_helperw(g, lim - 1);
                g = g_o;
            }
            //Bottom left
            if (move_entries(&g, g.black[pc_i], g.black[pc_i].x - 1, g.black[pc_i].y - 1))
            {
                scores[4 * i + 2] = (g.black[pc_i].is_king) ? 1 : 2;
                scores[4 * i + 2] += 0.9 * bot_helperw(g, lim - 1);
                g = g_o;
            }
            else if (move_entries(&g, g.black[pc_i], g.black[pc_i].x - 2, g.black[pc_i].y - 2))
            {
                if (is_multi_capture_possible(g))
                    g.cur_turn = colorFlip(g.cur_turn);

                scores[4 * i + 2] = 10;
                scores[4 * i + 2] += 0.9 * bot_helperw(g, lim - 1);
                g = g_o;
            }
            //Top left
            if (move_entries(&g, g.black[pc_i], g.black[pc_i].x - 1, g.black[pc_i].y + 1))
            {
                scores[4 * i + 3] = 1;
                scores[4 * i + 3] += 0.9 * bot_helperw(g, lim - 1);
                g = g_o;
            }
            else if (move_entries(&g, g.black[pc_i], g.black[pc_i].x - 2, g.black[pc_i].y + 2))
            {
                if (is_multi_capture_possible(g))
                    g.cur_turn = colorFlip(g.cur_turn);

                scores[4 * i + 3] = 10;
                scores[4 * i + 3] += 0.9 * bot_helperw(g, lim - 1);
                g = g_o;
            }
            // This is where the inversion happens, we are in white bot function, so for that bot, scores of White must be inverted
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

            //Top right
            if (move_entries(&g, g.white[pc_i], g.white[pc_i].x + 1, g.white[pc_i].y + 1))
            {
                scores[4 * i] = (g.white[pc_i].is_king) ? 1 : 2;
                scores[4 * i] += 0.9 * bot_helperw(g, lim - 1);
                g = g_o;
            }
            else if (move_entries(&g, g.white[pc_i], g.white[pc_i].x + 2, g.white[pc_i].y + 2))
            {
                if (is_multi_capture_possible(g))
                    g.cur_turn = colorFlip(g.cur_turn);

                scores[4 * i] = 10;
                scores[4 * i] += 0.9 * bot_helperw(g, lim - 1);
                g = g_o;
            }
            //Bottom right
            if (move_entries(&g, g.white[pc_i], g.white[pc_i].x + 1, g.white[pc_i].y - 1))
            {
                scores[4 * i + 1] = 1;
                scores[4 * i + 1] += 0.9 * bot_helperw(g, lim - 1);
                g = g_o;
            }
            else if (move_entries(&g, g.white[pc_i], g.white[pc_i].x + 2, g.white[pc_i].y - 2))
            {
                if (is_multi_capture_possible(g))
                    g.cur_turn = colorFlip(g.cur_turn);

                scores[4 * i + 1] = 10;
                scores[4 * i + 1] += 0.9 * bot_helperw(g, lim - 1);
                g = g_o;
            }
            //Bottom left
            if (move_entries(&g, g.white[pc_i], g.white[pc_i].x - 1, g.white[pc_i].y - 1))
            {
                scores[4 * i + 2] = 1;
                scores[4 * i + 2] += 0.9 * bot_helperw(g, lim - 1);
                g = g_o;
            }
            else if (move_entries(&g, g.white[pc_i], g.white[pc_i].x - 2, g.white[pc_i].y - 2))
            {
                if (is_multi_capture_possible(g))
                    g.cur_turn = colorFlip(g.cur_turn);

                scores[4 * i + 2] = 10;
                scores[4 * i + 2] += 0.9 * bot_helperw(g, lim - 1);
                g = g_o;
            }
            //Top left
            if (move_entries(&g, g.white[pc_i], g.white[pc_i].x - 1, g.white[pc_i].y + 1))
            {
                scores[4 * i + 3] = (g.white[pc_i].is_king) ? 1 : 2;
                scores[4 * i + 3] += 0.9 * bot_helperw(g, lim - 1);
                g = g_o;
            }
            else if (move_entries(&g, g.white[pc_i], g.white[pc_i].x - 2, g.white[pc_i].y + 2))
            {
                if (is_multi_capture_possible(g))
                    g.cur_turn = colorFlip(g.cur_turn);

                scores[4 * i + 3] = 10;
                scores[4 * i + 3] += 0.9 * bot_helperw(g, lim - 1);
                g = g_o;
            }
        }
    }
    long double sum = 0;
    // Add up scores all of the moves that happened due to this move to this move's score
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
    /*
        The 8 if statements in each of the main if blocks are simply calling move entries with all possible moves on all the pieces of the current player on the current game state g which modifies
        which again recursively calls this function for a total of lim times

        For a non king piece, moving towards the enemy's side grants the bot 2 points, while moving backwards grant only a single point
        Capturing grants 10 points

        Now, when the bot is thinking, the bot also calculates the moves of the opponent and calculates its points in the exact same way, the only difference being, it subtracts its scores from its own scores
        As an example, let's say you move a piece, which allowed opponent to capture some piece, then that move will get a -10 penalty on its score
        the 0.9 in second line of each if block simply ensures that priority of the current scores are more than priority of the scores further down the line

        And incase of a capture, we check whether another capture is possible, if another turn is granted and we flip the turn to nullify the flip that happens in the recursive call
    */
    for (int i = 0; i < tp; i++)
    {
        int pc_i = i;

        //Top right
        if (move_entries(&g, g.white[pc_i], g.white[pc_i].x + 1, g.white[pc_i].y + 1))
        {
            scores[4 * i] = (g.white[pc_i].is_king) ? 1 : 2;
            scores[4 * i] += 0.9 * bot_helperw(g, lim - 1);
            g = c_state;
        }
        else if (move_entries(&g, g.white[pc_i], g.white[pc_i].x + 2, g.white[pc_i].y + 2))
        {
            if (is_multi_capture_possible(g))
                g.cur_turn = colorFlip(g.cur_turn);

            scores[4 * i] = 10;
            scores[4 * i] += 0.9 * bot_helperw(g, lim - 1);
            g = c_state;
        }
        //Bottom right
        if (move_entries(&g, g.white[pc_i], g.white[pc_i].x + 1, g.white[pc_i].y - 1))
        {
            scores[4 * i + 1] = 1;
            scores[4 * i + 1] += 0.9 * bot_helperw(g, lim - 1);
            g = c_state;
        }
        else if (move_entries(&g, g.white[pc_i], g.white[pc_i].x + 2, g.white[pc_i].y - 2))
        {
            if (is_multi_capture_possible(g))
                g.cur_turn = colorFlip(g.cur_turn);

            scores[4 * i + 1] = 10;
            scores[4 * i + 1] += 0.9 * bot_helperw(g, lim - 1);
            g = c_state;
        }
        //Bottom left
        if (move_entries(&g, g.white[pc_i], g.white[pc_i].x - 1, g.white[pc_i].y - 1))
        {
            scores[4 * i + 2] = 1;
            scores[4 * i + 2] += 0.9 * bot_helperw(g, lim - 1);
            g = c_state;
        }
        else if (move_entries(&g, g.white[pc_i], g.white[pc_i].x - 2, g.white[pc_i].y - 2))
        {
            if (is_multi_capture_possible(g))
                g.cur_turn = colorFlip(g.cur_turn);

            scores[4 * i + 2] = 10;
            scores[4 * i + 2] += 0.9 * bot_helperw(g, lim - 1);
            g = c_state;
        }
        //Top left
        if (move_entries(&g, g.white[pc_i], g.white[pc_i].x - 1, g.white[pc_i].y + 1))
        {
            scores[4 * i + 3] = (g.white[pc_i].is_king) ? 1 : 2;
            scores[4 * i + 3] += 0.9 * bot_helperw(g, lim - 1);
            g = c_state;
        }
        else if (move_entries(&g, g.white[pc_i], g.white[pc_i].x - 2, g.white[pc_i].y + 2))
        {
            if (is_multi_capture_possible(g))
                g.cur_turn = colorFlip(g.cur_turn);

            scores[4 * i + 3] = 10;
            scores[4 * i + 3] += 0.9 * bot_helperw(g, lim - 1);
            g = c_state;
        }
    }
    int mi = 0;
    // Once the scores are calculated, we go through all moves and insert the valid ones into the heap
    for (int i = 0; i < 4 * tp; i++)
    {
        he q;
        int pc_i = i / 4;
        q.index = i;
        q.d = scores[i];
        pawn n;
        int flag = 0; // flag is set to 1 as soon as any valid move is detected
        switch (i % 4)
        {
        case 0:
            n.x = c_state.white[pc_i].x + 1;
            n.y = c_state.white[pc_i].y + 1;
            if (!isLegal(c_state.white[pc_i], n, &c_state))
            {
                n.x = c_state.white[pc_i].x + 2;
                n.y = c_state.white[pc_i].y + 2;
                if (isLegal(c_state.white[pc_i], n, &c_state))
                    flag = 1;
            }
            else
                flag = 1;
            break;
        case 1:
            n.x = c_state.white[pc_i].x + 1;
            n.y = c_state.white[pc_i].y - 1;
            if (!isLegal(c_state.white[pc_i], n, &c_state))
            {
                n.x = c_state.white[pc_i].x + 2;
                n.y = c_state.white[pc_i].y - 2;
                if (isLegal(c_state.white[pc_i], n, &c_state))
                    flag = 1;
            }
            else
                flag = 1;
            break;
        case 2:
            n.x = c_state.white[pc_i].x - 1;
            n.y = c_state.white[pc_i].y - 1;
            if (!isLegal(c_state.white[pc_i], n, &c_state))
            {
                n.x = c_state.white[pc_i].x - 2;
                n.y = c_state.white[pc_i].y - 2;
                if (isLegal(c_state.white[pc_i], n, &c_state))
                    flag = 1;
            }
            else
                flag = 1;
            break;
        case 3:
            n.x = c_state.white[pc_i].x - 1;
            n.y = c_state.white[pc_i].y + 1;
            if (!isLegal(c_state.white[pc_i], n, &c_state))
            {
                n.x = c_state.white[pc_i].x - 2;
                n.y = c_state.white[pc_i].y + 2;
                if (isLegal(c_state.white[pc_i], n, &c_state))
                    flag = 1;
            }
            else
                flag = 1;
            break;
        }
        if (flag)
            insert(q);
    }
    int k;
    // Added to ensure some sort of randomness to the bot, the bot doesn't always pick the move it thinks is best but rather based on the difficulty
    // Has a probability distribution using which it will either pick the first best move, second best move or the third best move
    int prob = rand() % 100 + 1;
    if (difficulty == 0)
    {
        if (prob <= 95)
        {
            k = 0;
        }
        else
            k = 1;
    }
    else if (difficulty == 1)
    {
        if (prob <= 80)
        {
            k = 0;
        }
        else if (prob <= 98)
        {
            k = 1;
        }
        else
            k = 2;
    }
    else
    {
        if (prob <= 70)
        {
            k = 0;
        }
        else if (prob <= 95)
        {
            k = 1;
        }
        else
            k = 2;
    }
    if (k >= size)
    {
        k = size - 1;
    }
    // remove the k best moves
    while (k--)
        Extract_max();
    he temp = Extract_max();
    if (temp.index == -1) // bot is out of move , call result fxn
    {
        size = 0;
        printf("Press R to review and Q to quit\n");
        return;
    }
    mi = temp.index;
    //   printf("Moving %d", mi);
    int pc_i = mi / 4;
    // Simply attempt that move, the way we store our moves, mi / 4 stores index of the piece and mi % 4 gives information about what move to play
    switch (mi % 4)
    {
    case 0:
        if (!move_entries(&c_state, c_state.white[pc_i], c_state.white[pc_i].x + 1, c_state.white[pc_i].y + 1))
        {
            move_entries(&c_state, c_state.white[pc_i], c_state.white[pc_i].x + 2, c_state.white[pc_i].y + 2);
        }
        break;
    case 1:
        if (!move_entries(&c_state, c_state.white[pc_i], c_state.white[pc_i].x + 1, c_state.white[pc_i].y - 1))
        {
            move_entries(&c_state, c_state.white[pc_i], c_state.white[pc_i].x + 2, c_state.white[pc_i].y - 2);
        };
        break;
    case 2:
        if (!move_entries(&c_state, c_state.white[pc_i], c_state.white[pc_i].x - 1, c_state.white[pc_i].y - 1))
        {
            move_entries(&c_state, c_state.white[pc_i], c_state.white[pc_i].x - 2, c_state.white[pc_i].y - 2);
        }

        break;
    case 3:
        if (!move_entries(&c_state, c_state.white[pc_i], c_state.white[pc_i].x - 1, c_state.white[pc_i].y + 1))
        {
            move_entries(&c_state, c_state.white[pc_i], c_state.white[pc_i].x - 2, c_state.white[pc_i].y + 2);
        }
        break;
    }
    // reset the heap for next use
    free(scores);
    size = 0;
}

void print_all_possible_next_move(node *current) // given a game state , what all possible can be achieved in next move
{
    // array will contain board condition possible after a piece whose turn it should be has been moved
    for (int i = 0; i < tp; i++) // selecting the piece
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
    for (int i = 0; i < tp; i++)
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

void print_k_state(game_state p, int k)
{

    if (k == 0)
    {
        print_board(&p);
        return;
    }

    node *root;
    root = (node *)malloc(sizeof(node));
    root->board = p;
    root->depth = 0;
    root->next_board = NULL;
    root->prev_board = NULL;

    point_to_null(root);

    filling_node(root, p, k - 1);
}
// #define topRight 1
// #define bottomRight 2
// #define topLeft 3
// #define bottomLeft 4

void filling_node(node *current, game_state p, int k) // takes a node , find which colors turn it is , and then fills the array accodingly if the move can be played by that color
{
    if (p.cur_turn == 0) // means black pieces will have to move
    {
        for (int i = 0; i < tp; i++) // selecting which black piece
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
                            game_state board_next = p;
                            bool tmp = move_entries(&board_next, p.black[i], p.black[i].x - 1, p.black[i].y + 1);

                            if (tmp == false)
                                continue;

                            board_next.cur_turn = colorFlip(board_next.cur_turn);

                            //allocating memory
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            //current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                            //current->array[i][j]->depth = current->depth + 1; // have to conform  ************************
                        }
                        //else we will check if capturing another color piece is possible in that direction
                        else if (capturePossible(&p, p.black[i], topLeft))
                        {
                            game_state board_next = p;
                            bool tmp = move_entries(&board_next, p.black[i], p.black[i].x - 2, p.black[i].y + 2);
                            if (tmp == false)
                                continue;
                            board_next.cur_turn = colorFlip(board_next.cur_turn);
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                            current->array[i][j]->depth = current->depth + 1; // have to conform  ************************
                        }
                    }
                    else if (j == 1)
                    {
                        //checking if simple move is poosible in this direction
                        if (simple_Move_Possible(&p, p.black[i], topRight))
                        {
                            // finding the board after the move is made
                            game_state board_next = p;
                            bool tmp = move_entries(&board_next, p.black[i], p.black[i].x + 1, p.black[i].y + 1);
                            if (tmp == false)
                                continue;
                            board_next.cur_turn = colorFlip(board_next.cur_turn);
                            //allocating memory
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                            current->array[i][j]->depth = current->depth + 1; // have to conform  ************************
                        }
                        //else we will check if capturing another color piece is possible in that direction
                        else if (capturePossible(&p, p.black[i], topRight))
                        {
                            game_state board_next = p;
                            bool tmp = move_entries(&board_next, p.black[i], p.black[i].x + 2, p.black[i].y + 2);
                            if (tmp == false)
                                continue;
                            board_next.cur_turn = colorFlip(board_next.cur_turn);
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                            current->array[i][j]->depth = current->depth + 1; // have to conform  ************************
                        }
                    }
                    else if (j == 2)
                    {
                        //checking if simple move is poosible in this direction
                        if (simple_Move_Possible(&p, p.black[i], bottomLeft))
                        {
                            // finding the board after the move is made
                            game_state board_next = p;
                            bool tmp = move_entries(&board_next, p.black[i], p.black[i].x - 1, p.black[i].y - 1);
                            if (tmp == false)
                                continue;
                            board_next.cur_turn = colorFlip(board_next.cur_turn);
                            //allocating memory
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                            current->array[i][j]->depth = current->depth + 1; // have to conform  ************************
                        }
                        //else we will check if capturing another color piece is possible in that direction
                        else if (capturePossible(&p, p.black[i], bottomLeft))
                        {
                            game_state board_next = p;
                            bool tmp = move_entries(&board_next, p.black[i], p.black[i].x - 2, p.black[i].y - 2);
                            if (tmp == false)
                                continue;
                            board_next.cur_turn = colorFlip(board_next.cur_turn);
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                            current->array[i][j]->depth = current->depth + 1; // have to conform  ************************
                        }
                    }
                    else if (j == 3)
                    {
                        //checking if simple move is poosible in this direction
                        if (simple_Move_Possible(&p, p.black[i], bottomRight))
                        {
                            // finding the board after the move is made
                            game_state board_next = p;
                            bool tmp = move_entries(&board_next, p.black[i], p.black[i].x + 1, p.black[i].y - 1);
                            if (tmp == false)
                                continue;
                            board_next.cur_turn = colorFlip(board_next.cur_turn);
                            //allocating memory
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                            current->array[i][j]->depth = current->depth + 1; // have to conform  ************************
                        }
                        //else we will check if capturing another color piece is possible in that direction
                        else if (capturePossible(&p, p.black[i], bottomRight))
                        {
                            game_state board_next = p;
                            bool tmp = move_entries(&board_next, p.black[i], p.black[i].x + 2, p.black[i].y - 2);
                            if (tmp == false)
                                continue;
                            board_next.cur_turn = colorFlip(board_next.cur_turn);
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                            current->array[i][j]->depth = current->depth + 1; // have to conform  ************************
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
                            game_state board_next = p;
                            bool tmp = move_entries(&board_next, p.black[i], p.black[i].x - 1, p.black[i].y - 1);
                            if (tmp == false)
                                continue;
                            board_next.cur_turn = colorFlip(board_next.cur_turn);
                            //allocating memory
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                            current->array[i][j]->depth = current->depth + 1; // have to conform  ************************
                        }
                        //else we will check if capturing another color piece is possible in that direction
                        else if (capturePossible(&p, p.black[i], bottomLeft))
                        {
                            game_state board_next = p;
                            bool tmp = move_entries(&board_next, p.black[i], p.black[i].x - 2, p.black[i].y - 2);
                            if (tmp == false)
                                continue;
                            board_next.cur_turn = colorFlip(board_next.cur_turn);
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                            current->array[i][j]->depth = current->depth + 1; // have to conform  ************************
                        }
                    }
                    else if (j == 3)
                    {
                        //checking if simple move is poosible in this direction
                        if (simple_Move_Possible(&p, p.black[i], bottomRight))
                        {
                            // finding the board after the move is made
                            game_state board_next = p;
                            bool tmp = move_entries(&board_next, p.black[i], p.black[i].x + 1, p.black[i].y - 1);
                            if (tmp == false)
                                continue;
                            board_next.cur_turn = colorFlip(board_next.cur_turn);
                            //allocating memory
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                            current->array[i][j]->depth = current->depth + 1; // have to conform  ************************
                        }
                        //else we will check if capturing another color piece is possible in that direction
                        else if (capturePossible(&p, p.black[i], bottomRight))
                        {
                            game_state board_next = p;
                            bool tmp = move_entries(&board_next, p.black[i], p.black[i].x + 2, p.black[i].y - 2);
                            if (tmp == false)
                                continue;
                            board_next.cur_turn = colorFlip(board_next.cur_turn);
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                            current->array[i][j]->depth = current->depth + 1; // have to conform  ************************
                        }
                    }
                }

                if (current->array[i][j] != NULL)
                {
                    // printf("%d %d %d\n", i, j, current->array[i][j]->board.cur_turn);
                    print_k_state(current->array[i][j]->board, k);
                }
            }
        }
    }
    else // means white pieces have to move
    {
        for (int i = 0; i < tp; i++) // selecting which black piece
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
                            game_state board_next = p;
                            bool tmp = move_entries(&board_next, p.white[i], p.white[i].x - 1, p.white[i].y + 1);
                            if (tmp == false)
                                continue;
                            board_next.cur_turn = colorFlip(board_next.cur_turn);
                            //allocating memory
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                        }
                        //else we will check if capturing another color piece is possible in that direction
                        else if (capturePossible(&p, p.white[i], topLeft))
                        {
                            game_state board_next = p;
                            bool tmp = move_entries(&board_next, p.white[i], p.white[i].x - 2, p.white[i].y + 2);
                            if (tmp == false)
                                continue;
                            board_next.cur_turn = colorFlip(board_next.cur_turn);
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                        }
                    }
                    else if (j == 1)
                    {
                        //checking if simple move is poosible in this direction
                        if (simple_Move_Possible(&p, p.white[i], topRight))
                        {
                            // finding the board after the move is made
                            game_state board_next = p;
                            bool tmp = move_entries(&board_next, p.white[i], p.white[i].x + 1, p.white[i].y + 1);
                            if (tmp == false)
                                continue;
                            board_next.cur_turn = colorFlip(board_next.cur_turn);
                            //allocating memory
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                        }
                        //else we will check if capturing another color piece is possible in that direction
                        else if (capturePossible(&p, p.white[i], topRight))
                        {
                            game_state board_next = p;
                            bool tmp = move_entries(&board_next, p.white[i], p.white[i].x + 2, p.white[i].y + 2);
                            if (tmp == false)
                                continue;
                            board_next.cur_turn = colorFlip(board_next.cur_turn);
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                        }
                    }
                    else if (j == 2)
                    {
                        //checking if simple move is poosible in this direction
                        if (simple_Move_Possible(&p, p.white[i], bottomLeft))
                        {
                            // finding the board after the move is made
                            game_state board_next = p;
                            bool tmp = move_entries(&board_next, p.white[i], p.white[i].x - 1, p.white[i].y - 1);
                            if (tmp == false)
                                continue;
                            board_next.cur_turn = colorFlip(board_next.cur_turn);
                            //allocating memory
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                        }
                        //else we will check if capturing another color piece is possible in that direction
                        else if (capturePossible(&p, p.white[i], bottomLeft))
                        {
                            game_state board_next = p;
                            bool tmp = move_entries(&board_next, p.white[i], p.white[i].x - 2, p.white[i].y - 2);
                            if (tmp == false)
                                continue;
                            board_next.cur_turn = colorFlip(board_next.cur_turn);
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                        }
                    }
                    else if (j == 3)
                    {
                        //checking if simple move is poosible in this direction
                        if (simple_Move_Possible(&p, p.white[i], bottomRight))
                        {
                            // finding the board after the move is made
                            game_state board_next = p;
                            bool tmp = move_entries(&board_next, p.white[i], p.white[i].x + 1, p.white[i].y - 1);
                            if (tmp == false)
                                continue;
                            board_next.cur_turn = colorFlip(board_next.cur_turn);
                            //allocating memory
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                        }
                        //else we will check if capturing another color piece is possible in that direction
                        else if (capturePossible(&p, p.white[i], bottomRight))
                        {
                            game_state board_next = p;
                            bool tmp = move_entries(&board_next, p.white[i], p.white[i].x + 2, p.white[i].y - 2);
                            if (tmp == false)
                                continue;
                            board_next.cur_turn = colorFlip(board_next.cur_turn);
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
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
                            game_state board_next = p;
                            bool tmp = move_entries(&board_next, p.white[i], p.white[i].x - 1, p.white[i].y + 1);
                            if (tmp == false)
                                continue;
                            board_next.cur_turn = colorFlip(board_next.cur_turn);
                            //allocating memory
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                        }
                        //else we will check if capturing another color piece is possible in that direction
                        else if (capturePossible(&p, p.white[i], topLeft))
                        {
                            game_state board_next = p;
                            bool tmp = move_entries(&board_next, p.white[i], p.white[i].x - 2, p.white[i].y + 2);
                            if (tmp == false)
                                continue;
                            board_next.cur_turn = colorFlip(board_next.cur_turn);
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                        }
                    }
                    else if (j == 1)
                    {
                        //checking if simple move is poosible in this direction
                        if (simple_Move_Possible(&p, p.white[i], topRight))
                        {
                            // finding the board after the move is made
                            game_state board_next = p;
                            bool tmp = move_entries(&board_next, p.white[i], p.white[i].x + 1, p.white[i].y + 1);
                            if (tmp == false)
                                continue;
                            board_next.cur_turn = colorFlip(board_next.cur_turn);
                            //allocating memory
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                        }
                        //else we will check if capturing another color piece is possible in that direction
                        else if (capturePossible(&p, p.white[i], topRight))
                        {
                            game_state board_next = p;
                            bool tmp = move_entries(&board_next, p.white[i], p.white[i].x + 2, p.white[i].y + 2);
                            if (tmp == false)
                                continue;
                            board_next.cur_turn = colorFlip(board_next.cur_turn);
                            current->array[i][j] = (node *)malloc(sizeof(node));
                            current->array[i][j]->next_board = NULL;
                            current->array[i][j]->prev_board = current;
                            current->array[i][j]->board = board_next;
                        }
                    }
                }

                if (current->array[i][j] != NULL)
                    print_k_state(current->array[i][j]->board, k);
            }
        }
    }
}

bool move_entries(game_state *g, pawn P, int horizontal, int vertical)
{
    if (!is_present(g, P)) // First check if the current player even has a piece from where they wish to move it
    {
        return false;
    }
    pawn n;
    n.x = horizontal;
    n.y = vertical;
    if (!isLegal(P, n, g)) // If the piece is present, we check whether the move they made abides by the rules of checkers and we delegate that work to the isLegal function
    {
        return false;
    }
    // Green light has been given and now move_entries performs its task
    if (P.allegiance == BLACK)
    {
        for (int i = 0; i < tp; ++i)
        {
            if (P.x == g->black[i].x && P.y == g->black[i].y)
            {
                if (abs(P.x - horizontal) == 2 && abs(P.y - vertical) == 2) // Is this a capture move? if yes, we are also tasked with eliminating the capture piece be setting its coords to -1,-1
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

                if (g->black[i].y == 0) // Black piece reached to row 0 and hence now will be coronated to a king
                    g->black[i].is_king = true;
                break;
            }
        }
    }
    else if (P.allegiance == WHITE)
    {

        for (int i = 0; i < tp; ++i)
        {
            if (P.x == g->white[i].x && P.y == g->white[i].y)
            {
                if (abs(P.x - horizontal) == 2 && abs(P.y - vertical) == 2) // Is this a capture move? if yes, we are also tasked with eliminating the capture piece be setting its coords to -1,-1
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

                if (g->white[i].y == sb - 1) // White piece reached the end, and hence will now be coronated to a king
                    g->white[i].is_king = true;

                break;
            }
        }
    }
    return true;
}
// A simple menu function which displays the initial menu screen
void menu(log *head)
{
    int option = 0;
    cls();
    while (1)
    {
        locate(1, 1);
        hidecursor();
        // These 4 if statements check options to display which option is selected
        if (option == 0)
            printf("> Play Singleplayer\n");
        else
            printf("  Play Singleplayer\n");
        if (option == 1)
            printf("> Play Multiplayer\n");
        else
            printf("  Play Multiplayer\n");
        if (option == 2)
            printf("> Difficulty: %d\n", difficulty);
        else
            printf("  Difficulty: %d\n", difficulty);
        if (option == 3)
            printf("> Quit\n");
        else
            printf("  Quit\n");

        char key = getkey();
        // we further check for keys such as w and s to navigate between options
        if (key == 'w')
        {
            option = (option - 1) % 4;
            if (option < 0)
                option += 4;
        }
        else if (key == 's')
        {
            option = (option + 1) % 4;
        }
        else if (key == KEY_SPACE) // For selection based options such as Play Singleplay, Play multiplayer and Quit
        {
            if (option == 0)
            {
                int a = toss();
                if (a == 0)
                {
                    bot_mode = WHITE;
                }
                else
                    bot_mode = BLACK;
                start(head);
            }
            else if (option == 1)
            {
                bot_mode = -1;
                start(head);
            }
            else if (option == 3)
            {
                cls();
                exit(0);
            }
        }
        else if ((key == 'd' || key == 'a') && option == 2) // Used for changing difficulty of the bot using a and d
        {
            if (key == 'a')
            {
                difficulty--;
                if (difficulty < 0)
                    difficulty = 0;
            }
            else
            {
                difficulty++;
                if (difficulty > 2)
                {
                    difficulty = 2;
                }
            }
        }
    }
}
// The function that is called to print the board and any additional information required
void print_board(game_state *P)
{
    int c_s = 4, r_s = 8; // spacing of the squares, the reason r_s is higher because 1 character space in a row is not equal to the length between each line
    int b[sb][sb];
    for (int i = 0; i < sb; i++)
    {
        for (int j = 0; j < sb; j++)
        {
            b[i][j] = 0;
        }
    }
    resetColor();

    // These store the coordinates of the red square boxes used to select the pieces we want to move
    int yc1 = sb - 1 - P->hover[0].y;
    int xc1 = P->hover[0].x;
    int yc2 = sb - 1 - P->hover[1].y;
    int xc2 = P->hover[1].x;
    // Making a temporary 2d grid for easier printing, Black Non king - 1, Black king - 3, White Non king - 2, White king - 4, rest all 0
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

    // for (int i = 0; i < sb; i++)
    // {
    //     // for (int j = 0; j < sb; j++)
    //     // {
    //     //     printf("%d ", b[i][j]);
    //     // }
    //     printf("\n");
    // }

    printf("Turn: ");
    if (c_state.cur_turn == BLACK)
    {
        printf("BLACK\n");
    }
    else
    {
        printf("WHITE\n");
    }
    printf("\n");

    // This is the main for loop dedicated to printing the board, simply using some modular formulas to print the correct symbols
    for (int i = 0; i <= (sb)*c_s; i++)
    {
        for (int j = 0; j <= (sb)*r_s; j++)
        {
            setBackgroundColor(BLACK);
            if (i % (c_s) == 0 && j % (r_s) == 0) // Junction of rows and columns
            {
                printf("+");
            }
            else if (i % (c_s) == 0) // Printing the horizontal separators
                printf("-");
            else if (j % (r_s) == 0) // Printing vertical separators
            {
                printf("|");
            }
            else
            {
                if ((i / c_s) == yc1 && j / r_s == xc1) // We are in the square which is highlighted
                {
                    setBackgroundColor(RED);
                }
                else if ((i / c_s) == yc2 && j / r_s == xc2) // Another highlighted square (if only one of them is highlighted, then second square is set to (-1, -1))
                {
                    setBackgroundColor(RED);
                }

                else if (((i / c_s) + (j / r_s)) % 2 == 0) // Switching between white and green board squares
                {
                    setBackgroundColor(7);
                }
                else
                    setBackgroundColor(2);
                if ((i % c_s == c_s / 2) && (j % r_s == r_s / 2)) // At a center of the board cell
                {
                    // Now this is where our 2d grid helps us, we simply check what piece belongs here by comparing with the grid
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

    printf("\nPress 'H' to see instructions, 'Q' to Quit game and 'N' to restart game\n");
}

bool isOccupied(game_state *g, int x, int y)
{
    for (int i = 0; i < tp; ++i)
    {
        // if x and y are equal to any coordinates of a pawn, that coordinate is occupied.
        if ((x == g->white[i].x && y == g->white[i].y) || (x == g->black[i].x && y == g->black[i].y))
        {
            return true;
        }
    }
    return false;
}

bool is_present(game_state *g, pawn P)
{
    if (P.x != -1 && P.y != -1)
    {
        //If the coordinates of P are equal to the coordinates of any pawn, it is present.
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
    }
    return false;
}

// topRight       1
// bottomRight    2
// topLeft        3
// bottomLeft     4

bool simple_Move_Possible(game_state *g, pawn P, int direction)
{
    if (P.x == -1 && P.y == -1)
        return false;
    int AfterMove_X, AfterMove_Y;
    switch (direction)
    {
    case topRight:
        if (P.x + 1 > sb - 1 || P.y + 1 > sb - 1) // if coordinates are out of bounds, return false
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
    if (!isOccupied(g, AfterMove_X, AfterMove_Y)) // The final position should be free and not occupied by any other piece.
        return true;
    else
        return false;
}

bool capturePossible(game_state *g, pawn P, int direction)
{
    if (P.x == -1 && P.y == -1)
        return false;
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
        Enemy.allegiance = colorFlip(P.allegiance); // Enemy pawn's color is different than P.
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
    if (!isOccupied(g, p.x, p.y)) // check if the coordinates of p are occupied by p itself
    {
        return false;
    }

    if (isOccupied(g, new_pos.x, new_pos.y)) // check if the new_pos coordinates are empty
    {
        return false;
    }

    if (x_diff == 1 && y_diff == 1)
    {
        /*
        For a simple move i.e |p.x - new_pos.x| = 1 and |p.y - new_pos.y| = 1, also check if a capture move is possible for any piece
        because according to rules, jumping is mandatory even if doing so is disadvantageous for the jumping player.
        */
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
        bool white_draw_Check = true, black_draw_Check = true;

        // if both are true -> DRAW.
        // if both are false -> game continues.
        // if any one of the two is false, that color is the WINNER.

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
                    return;
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
// The controller function, tasked with running the entire game by reading input, and calling functions as required
void controller(log *head)
{
    push(head, &c_state);
    while (1)
    {
        pawn p;
        int c;
        if (c_state.cur_turn == BLACK) // First checks whose turn it is
        {
            //  char c = getkey();
            /*   if(c == 'u') 
            {
                c_state = undo(head);
                print_board(&c_state);
                continue;
            }*/
            if (bot_mode == BLACK) // If bot's allegiance is BLACK, then the control is given to the bot not the player
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
                //     printf("Bot");
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
            else // It is the player's turn
            {
                // Choose some valid piece on which to start the first red square on
                for (int i = tp - 1; i >= 0; --i)
                {
                    if (c_state.black[i].x != -1 && c_state.black[i].y != -1)
                    {
                        c = i;
                        break;
                    }
                }
                int x[2];
                int y[2]; // These both store x and y coords of the 2 squares
                x[0] = c_state.black[c].x;
                y[0] = c_state.black[c].y;
                x[1] = y[1] = -1; // Second square doesnt exist yet
                int cur = 0;

                while (1)
                {
                    // Sets the hover values as required by the print_board
                    c_state.hover[0].x = x[0];
                    c_state.hover[0].y = y[0];
                    c_state.hover[1].x = x[1];
                    c_state.hover[1].y = y[1];

                    //    cls();
                    locate(1, 1);
                    hidecursor();
                    print_board(&c_state);
                    char ch = getkey();
                    // cur is initially 0 , that means we are controlling the first square with wasd, the rest of these keys are documented in our instructions
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
                    else if (ch == 'm')
                    {
                        char a;
                        printf("Do you want to draw the game ? [y/N] ");
                        a = getkey();
                        if (a == 'y' || a == 'Y')
                        {
                            printf("Match has been drawed\n");
                            printf("Do you want to Review the game? [y/N]\n");
                            while (1)
                            {
                                char key = getkey();
                                if (key == 'y' || key == 'Y')
                                {
                                    review(head);
                                    break;
                                }
                                else if (key == 'n' || key == 'N')
                                {
                                    clear_stack(head);
                                    cls();
                                    exit(0);
                                }
                            }
                        }
                    }
                    else if (ch == 'k')
                    {
                        int x;
                        printf("Enter the value of k: ");
                        scanf("%d", &x);
                        print_k_state(c_state, x);

                        printf("press 'e' to Resume\n");
                        while (1)
                        {
                            char ch = getkey();
                            if (ch == 'e')
                            {
                                cls();
                                break;
                            }
                        }
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
                            while (c_state.cur_turn == bot_mode)
                            {
                                if (head->next->next == NULL)
                                    break;
                                c_state = undo(head);
                            }
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
                    else if (ch == KEY_SPACE) // A selection is being made
                    {
                        if (cur == 0) // It was the first square, that means we are just trying to select a piece to move it
                        {
                            int flag = -1;
                            // Confirm that piece exists, if yes we increment cur to now control the second square which will be used to select where to move
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
                                continue; // if the piece doesnt exist, just reset back to taking input again
                            cur++;
                        }
                        else // If cur is 1
                        {
                            if (x[1] == x[0] && y[0] == y[1]) // We wish to de select our previous selection
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

                            if (!move_entries(&c_state, p, x[1], y[1])) // If move did not succeed, simply reset
                            {
                                continue;
                            }
                            else // otherwise reset all the red squares, and push the current state to the stack
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

        else // White's Turn
        {
            if (bot_mode == WHITE) // If bot's allegiance is WHITE, then the control is given to the bot not the player
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
                //  printf("Bot");
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
            else // It is the player's turn
            {
                // Choose some valid piece on which to start the first red square on
                for (int i = tp - 1; i >= 0; --i)
                {
                    if (c_state.white[i].x != -1 && c_state.white[i].y != -1)
                    {
                        c = i;
                        break;
                    }
                }
                int x[2];
                int y[2]; // These both store x and y coords of the 2 squares
                x[0] = c_state.white[c].x;
                y[0] = c_state.white[c].y;
                x[1] = y[1] = -1; // Second square doesnt exist yet
                int cur = 0;
                while (1)
                {
                    // Sets the hover values as required by the print_board
                    c_state.hover[0].x = x[0];
                    c_state.hover[0].y = y[0];
                    c_state.hover[1].x = x[1];
                    c_state.hover[1].y = y[1];

                    //    cls();
                    locate(1, 1);
                    hidecursor();
                    print_board(&c_state);
                    char ch = getkey();
                    // cur is initially 0 , that means we are controlling the first square with wasd, the rest of these keys are documented in our instructions
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
                    else if (ch == 'm')
                    {
                        char a;
                        printf("Do you want to draw the game ? [y/N] ");
                        a = getkey();
                        if (a == 'y' || a == 'Y')
                        {
                            printf("Match has been drawed\n");
                            printf("Do you want to Review the game? [y/N]\n");
                            while (1)
                            {
                                char key = getkey();
                                if (key == 'y' || key == 'Y')
                                {
                                    review(head);
                                }
                                else if (key == 'n' || key == 'N')
                                {
                                    clear_stack(head);
                                    cls();
                                    exit(0);
                                }
                            }
                        }
                    }
                    else if (ch == 'k')
                    {
                        int x;
                        printf("Enter the value of k: ");
                        scanf("%d", &x);
                        print_k_state(c_state, x);

                        printf("press 'e' to Resume\n");
                        while (1)
                        {
                            char ch = getkey();
                            if (ch == 'e')
                            {
                                cls();
                                break;
                            }
                        }
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
                            while (c_state.cur_turn == bot_mode)
                            {
                                if (head->next->next == NULL)
                                    break;
                                c_state = undo(head);
                            }
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
                    else if (ch == KEY_SPACE) // A selection is being made
                    {
                        if (cur == 0) // It was the first square, that means we are just trying to select a piece to move it
                        {
                            int flag = -1;
                            // Confirm that piece exists, if yes we increment cur to now control the second square which will be used to select where to move
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
                                continue; // if the piece doesnt exist, just reset back to taking input again
                            cur++;
                        }
                        else // If cur is 1
                        {
                            if (x[1] == x[0] && y[0] == y[1]) // We wish to de select our previous selection
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

                            if (!move_entries(&c_state, p, x[1], y[1])) // If move did not succeed, simply reset
                            {
                                continue;
                            }
                            else // otherwise reset all the red squares, and push the current state to the stack
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
    while (!feof(fp) && !ferror(fp))
    {
        fscanf(fp, "%c", &A);
        printf("%c", A);
    }
    if (fp == NULL)
        printf("File doesnot exist\n");

    fclose(fp);
}

int toss(void)
{
    cls();
    int Toss;
    int arr[50];
    Toss = rand() % 2;
    for (int i = 49; i >= 0; i--)
    {
        arr[i] = Toss;
        Toss = (Toss + 1) % 2;
    }
    for (int i = 0; i < 50; i++)
    {
        if (arr[i] == 1)
            printf("Your Allegiance: WHITE\n");
        else
            printf("Your Allegiance: BLACK\n");

        msleep(3 * i);
        locate(1, 1);
        hidecursor();
    }
    if (arr[49] == 1)
        printf("Your Allegiance: WHITE\n");
    else
        printf("Your Allegiance: BLACK\n");

    msleep(2000);
    cls();
    return arr[49];
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
    int c = 0;
    while (head->next != NULL)
    {
        if (c > 10)
        {
            printf("Press 'spacebar' to print next 10 boards and 'e' to resume game \n");
            while (1)
            {
                char ch = getkey();
                if(ch == KEY_SPACE)
                {
                    msleep(500);
                    c = 0;
                    break;
                }
                if(ch == 'e')
                {
                    cls();
                    return;
                }
                
            }
        }
        temp = head->next;
        game_state s = temp->g;
        c++;
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

int main()
{
    cls();
    srand(time(0));
    if (sb % 2 != 0)
        exit(1);
    resetColor();
    log *head = CreateEmptyStackNode(); // start of linked list which is going to store table after every move
    int i = rand() % 50;
    ;
    while (i--)
    {
        rand();
    }
    //  char key;
    //   printf("Press 'e' to start and 't' to toss\n");
    menu(head);

    while (1)
    {
        char key = getkey();
        if (key == 't')
            toss();

        else if (key == 'e')
            start(head);
    }
    return 0;
}