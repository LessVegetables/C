#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
    #define INPUT "/Users/danielgehrman/Documents/Programming/Uni/PPL/Prog2/input.txt"
    #define OUTPUT "/Users/danielgehrman/Documents/Programming/Uni/PPL/Prog2/output.txt"
#else 
    #define INPUT "input.txt"
    #define OUTPUT "output.txt"
#endif

#define MAX_NODES 200001
#define INF -1

typedef struct {
    int *neighbors;
    int neighbor_count;
} Node;

Node graph[MAX_NODES];
int distances[MAX_NODES];

void bfs(int start, int num_nodes)
{
    int queue[MAX_NODES];
    int front = 0, rear = 0;

    // Initialize distances
    for (int i = 0; i < num_nodes; i++)
    {
        distances[i] = INF;
    }
    distances[start] = 0;

    // Add starting node
    queue[rear++] = start;

    while (front < rear)
    {
        int current = queue[front++];
        
        // Process all neighbors
        for (int i = 0; i < graph[current].neighbor_count; i++)
        {
            int neighbor = graph[current].neighbors[i];

            if (distances[neighbor] == INF)
            {
                distances[neighbor] = distances[current] + 1;
                queue[rear++] = neighbor;
            }
        }
    }
}

void add_edge(int u, int v)
{
    graph[u].neighbors = (int*)realloc(graph[u].neighbors, (graph[u].neighbor_count + 1) * sizeof(int));

    graph[u].neighbors[graph[u].neighbor_count++] = v;
}

int main()
{
    int m, n, u, v;

    FILE *inp, *out;
    if ((inp = fopen(INPUT, "r")) == NULL)
    {
        fprintf(stderr, "Failed to open input file\n");
        return 1;
    }

    fscanf(inp, "%d%d", &m, &n);

    // Initialize the graph
    for (int i = 0; i < m; i++)
    {
        graph[i].neighbors = NULL;
        graph[i].neighbor_count = 0;
    }

    // Read edges
    for (int i = 0; i < n; i++)
    {
        fscanf(inp, "%d %d", &u, &v);
        add_edge(u - 1, v - 1);  // Directed edge from u to v
    }
    fclose(inp);

    bfs(0, m);

    // Output distances
    out = fopen(OUTPUT, "w");
    for (int i = 0; i < m; i++)
    {
        if (distances[i] == INF) fprintf(out, "-1\n");
        else fprintf(out, "%d\n", distances[i]);
    }
    fclose(out);

    // Free allocated memory
    for (int i = 0; i < MAX_NODES; i++)
    {
        free(graph[i].neighbors);
    }

    return 0;
}
