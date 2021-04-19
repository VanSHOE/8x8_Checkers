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
bool islegal(pawn p, pawn new_pos)
{
}

int main()
{
    game_state s;
    print_board(s);
    return 0;
}