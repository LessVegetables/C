#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
    #define INPUT "/Users/danielgehrman/Documents/Programming/Uni/PPL/Prog2/input.txt"
    #define OUTPUT "/Users/danielgehrman/Documents/Programming/Uni/PPL/Prog2/output.txt"
#else 
    #define INPUT "input.txt"
    #define OUTPUT "output.txt"
#endif

# pragma comment(linker, "/STACK:50000000")

/*
INPUT:
9
*** *****
*       *
* ** *  *
* * * * *
* * *** *
* * * * *
* ***** *
*       *
*********

OUTPUT: 
2
*/

int gridSize;
char arr[1001][1001];

void dfs(int i, int j)
{
    arr[i][j] = '*';

    // Move left
    if (j - 1 >= 0 && arr[i][j - 1] != '*')       dfs(i, j - 1);

    // Move right
    if (j + 1 < gridSize && arr[i][j + 1] != '*') dfs(i, j + 1);

    // Move up
    if (i - 1 >= 0 && arr[i - 1][j] != '*')       dfs(i - 1, j);

    // Move down
    if (i + 1 < gridSize && arr[i + 1][j] != '*') dfs(i + 1, j);
}

int main()
{
    FILE *inp, *out;
    if ((inp = fopen(INPUT, "r")) == NULL)
    {
        fprintf(stderr, "Failed to open input file\n");
        return 1;
    }

    fscanf(inp, "%d", &gridSize);
    fgetc(inp);  // consume the newline character after the gridSize

    // Allocate memory for the grid
    // arr = (char*)malloc(gridSize * gridSize * sizeof(char));

    // Read the grid
    for (int i = 0; i < gridSize; i++)
    {
        fgets(arr[i], gridSize + 1, inp);
        fgetc(inp);
    }

    fclose(inp);


    out = fopen(OUTPUT, "w");
    // for (int i = 0; i < gridSize; i ++)
    // {
    //     for (int j = 0; j < gridSize; j++)
    //     {
    //         fprintf(out, "%c", arr[i][j]);
    //     }
    //     fprintf(out, "\n");
    // }

    int hiddenAreas = -1;

    // Traverse the grid to find hidden areas
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            if (arr[i][j] != '*')
            {
                dfs(i, j);
                hiddenAreas++;
            }
        }
    }

    fprintf(out, "%d", hiddenAreas);

    fclose(out);
    // free(arr);
    return 0;
}