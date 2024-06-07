#include <stdio.h>
#include <stdbool.h>

#ifdef __APPLE__
    #define INPUT "/Users/danielgehrman/Documents/Programming/Uni/PPL/Prog2/input.txt"
    #define OUTPUT "/Users/danielgehrman/Documents/Programming/Uni/PPL/Prog2/output.txt"
#else 
    #define INPUT "input.txt"
    #define OUTPUT "output.txt"
#endif

#define MAX 13

int M, N;
char board[MAX][MAX];
char solution[MAX][MAX];
bool col_occupied[MAX];
bool diag1_occupied[2 * MAX - 1];
bool diag2_occupied[2 * MAX - 1];

bool is_safe(int row, int col)
{
    return !col_occupied[col] && 
           !diag1_occupied[row - col + N - 1] &&
           !diag2_occupied[row + col];
}

bool place_queens(int row)
{
    if (row == M) return true;

    for (int col = 0; col < N; col++)
    {
        if (board[row][col] == '?' && is_safe(row, col))
        {
            solution[row][col] = 'X';
            col_occupied[col] = true;
            diag1_occupied[row - col + N - 1] = true;
            diag2_occupied[row + col] = true;

            if (place_queens(row + 1)) return true;

            solution[row][col] = '.';
            col_occupied[col] = false;
            diag1_occupied[row - col + N - 1] = false;
            diag2_occupied[row + col] = false;
        }
    }

    return false;
}

int main()
{
    FILE *inp, *out;
    if ((inp = fopen(INPUT, "r")) == NULL)
    {
        printf("Failed to open file\n");
        return 1;
    }
    out = fopen(OUTPUT, "w");

    fscanf(inp, "%d %d", &M, &N);
    for (int i = 0; i < M; i++)
    {
        fscanf(inp, "%s", board[i]);
    }

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            solution[i][j] = board[i][j] == '?' ? '.' : board[i][j];
        }
    }
    
    if (place_queens(0))
    {
        fprintf(out, "YES\n");
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                fprintf(out, "%c", solution[i][j]);
            }
            fprintf(out, "\n");
        }
    }
    else fprintf(out, "NO\n");

    fclose(inp);
    fclose(out);
    return 0;
}
