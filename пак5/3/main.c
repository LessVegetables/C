#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __APPLE__
    #define INPUT "/Users/danielgehrman/Documents/Programming/Uni/PPL/Prog2/input.txt"
    #define OUTPUT "/Users/danielgehrman/Documents/Programming/Uni/PPL/Prog2/output.txt"
    // #define MYMAC
    // #define PRINT
#else 
    #define INPUT "input.txt"
    #define OUTPUT "output.txt"
#endif

typedef struct
{
    int x;
    int y;
} Cell;

typedef struct QueueNode
{
    Cell data;
    struct QueueNode* next;
} QueueNode;

typedef struct
{
    QueueNode* front;
    QueueNode* rear;
    int size;
} Queue;

Queue* createQueue()
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    queue->size = 0;
    return queue;
}

void enqueue(Queue* queue, Cell data)
{
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->data = data;
    newNode->next = NULL;
    if (queue->rear == NULL)
    {
        queue->front = newNode;
        queue->rear = newNode;
    }
    else
    {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    queue->size++;
}

Cell dequeue(Queue* queue)
{
    QueueNode* temp = queue->front;
    Cell data = temp->data;
    queue->front = queue->front->next;
    if (queue->front == NULL)
    {
        queue->rear = NULL;
    }
    free(temp);
    queue->size--;
    return data;
}

int isEmpty(Queue* queue)
{
    return queue->size == 0;
}

void freeQueue(Queue* queue)
{
    while (!isEmpty(queue))
    {
        dequeue(queue);
    }
    free(queue);
}

int shortestPath(int lab[102][102], int M, int N)
{    
    // Finding S and F coordinates
    Cell start = {-1, -1}, finish = {-1, -1};
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (lab[i][j] == 'S')
            {
                start.x = i;
                start.y = j;
                lab[i][j] = 1;  // Start point set to '1'
            }
            else if (lab[i][j] == 'F')
            {
                finish.x = i;
                finish.y = j;
            }
            else if (lab[i][j] == '.')
            {
                lab[i][j] = 0;  // Mark unvisited cells as 0
            }
        }
    }

    #ifdef MYMAC
    for (int visY = 0; visY < M; visY++)
    {
        for (int visX = 0; visX < N; visX++)
        {
            printf("%d", lab[visY][visX]);
        }
        printf("\n");
    }
    printf("\n");
    #endif

    if (start.x == -1 || finish.x == -1)
    {
        return -1; // Either start or finish not found
    }

    Queue* q = createQueue();
    enqueue(q, start);

    while (!isEmpty(q))
    {
        Cell current = dequeue(q);

        #ifdef PRINT
            for (int visY = 0; visY < M; visY++)
            {
                for (int visX = 0; visX < N; visX++)
                {
                    printf("%c\t", lab[visY][visX]);
                }
                printf("\n");
            }
            printf("\n");
        #endif

        // Check if finish cell is reached
        if (current.x == finish.x && current.y == finish.y)
        {
            #ifdef MYMAC
            for (int visY = 0; visY < M; visY++)
            {
                for (int visX = 0; visX < N; visX++)
                {
                    printf("%d\t", lab[visY][visX]);
                }
                printf("\n");
            }
            #endif
            freeQueue(q);
            return (int)(lab[current.x][current.y]) - 1;
        }

        // Check left cell
        if (current.x - 1 >= 0 &&
            (lab[current.x - 1][current.y] == 0 ||
             lab[current.x - 1][current.y] == 'F'))
        {
            Cell next = {current.x - 1, current.y};
            enqueue(q, next);  
            lab[current.x - 1][current.y] = lab[current.x][current.y] + 1;
        }

        // Check right cell
        if (current.x + 1 < M &&
            (lab[current.x + 1][current.y] == 0 ||
             lab[current.x + 1][current.y] == 'F'))
        {
            Cell next = {current.x + 1, current.y};
            enqueue(q, next);
            lab[current.x + 1][current.y] = lab[current.x][current.y] + 1;
        }

        // Check up cell
        if (current.y - 1 >= 0 &&
            (lab[current.x][current.y - 1] == 0 ||
             lab[current.x][current.y - 1] == 'F'))
        {
            Cell next = {current.x, current.y - 1};
            enqueue(q, next);
            lab[current.x][current.y - 1] = lab[current.x][current.y] + 1;
        }

        // Check down cell
        if (current.y + 1 < N &&
            (lab[current.x][current.y + 1] == 0 ||
             lab[current.x][current.y + 1] == 'F'))
        {
            Cell next = {current.x, current.y + 1};
            enqueue(q, next);
            lab[current.x][current.y + 1] = lab[current.x][current.y] + 1;
        }
    }

    // If finish cell is not found, return -1
    freeQueue(q);
    return -1;
}

int main()
{
    int M, N;
    int lab[102][102];

    FILE *inp, *out;
    if ((inp = fopen(INPUT, "r")) == NULL)
    {
        fprintf(stderr, "Failed to open input file\n");
        return 1;
    }

    fscanf(inp, "%d %d", &M, &N);
    fgetc(inp);

    char buff[101];
    for (int i = 0; i < M; i++)
    {
        fgets(buff, N + 1, inp);
        for (int j = 0; j < N; j++)
        {
            lab[i][j] = (int)(buff[j]);
        }
        fgetc(inp);
    }

    // printf("M: %d, N: %d\n", M, N);

    fclose(inp);

    int result = shortestPath(lab, M, N);

    out = fopen(OUTPUT, "w");
    if (out == NULL)
    {
        fprintf(stderr, "Failed to open output file\n");
        return 1;
    }

    fprintf(out, "%d\n", result);
    fclose(out);

    return 0;
}