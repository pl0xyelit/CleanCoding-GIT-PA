/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graphraf*/

#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
} NODE;
/// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
/// ex: 1 - restaurantul 1 si tot asa

typedef struct graph
{
    int vertices;
    int *visited;
    struct Node **adjacencyLists;
} GRAPH;

typedef struct stack
{
    int top;
    int stackCap;
    int *array;
} STACK;

NODE *createNode(int value)
{
    NODE *newNode = (NODE *)malloc(sizeof(NODE));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

GRAPH *createGraph(int numberOfVertices)
{
    int i;
    GRAPH *graph = (GRAPH *)malloc(sizeof(GRAPH));
    graph->vertices = numberOfVertices;
    graph->adjacencyLists = (NODE **)malloc(numberOfVertices * sizeof(NODE *));
    graph->visited = (int *)malloc(numberOfVertices * sizeof(int));

    for (i = 0; i < numberOfVertices; i++)
    {
        graph->adjacencyLists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

STACK *createStack(int stackCap)
{
    STACK *stack = (STACK *)malloc(sizeof(STACK));
    stack->array = (int *)malloc(stackCap * sizeof(int));
    stack->top = -1;
    stack->stackCap = stackCap;

    return stack;
}

void push(int value, STACK *stack)
{
    stack->top = stack->top + 1;
    stack->array[stack->top] = value;
}

void DFS(GRAPH *graph, STACK *stack, int vertexNumber)
{
    NODE *adjacencyList = graph->adjacencyLists[vertexNumber];
    NODE *temp = adjacencyList;
    graph->visited[vertexNumber] = 1;
    // printf("%d ", vertexNumber + 1);
    push(vertexNumber, stack);
    while (temp != NULL)
    {
        int connectedVertex = temp->data;
        if (graph->visited[connectedVertex] == 0)
            DFS(graph, stack, connectedVertex);
        temp = temp->next;
    }
}

void addEdge(GRAPH *graph, int source, int destination)
{
    NODE *newNode = createNode(destination);

    newNode->next = graph->adjacencyLists[source];
    graph->adjacencyLists[source] = newNode;

    newNode = createNode(source);

    newNode->next = graph->adjacencyLists[destination];
    graph->adjacencyLists[destination] = newNode;
}

void insertEdges(GRAPH *graph, int numberOfEdges, int numberOfVertices)
{
    int source, destination, i;
    printf("adauga %d munchii (de la 1 la %d)\n", numberOfEdges, numberOfVertices);
    for (i = 0; i < numberOfEdges; i++)
    {
        scanf("%d%d", &source, &destination);
        addEdge(graph, source - 1, destination - 1);
    }
}

void wipe(GRAPH *graph, int numberOfVertices)
{
    for (int i = 0; i < numberOfVertices; i++)
    {
        graph->visited[i] = 0;
    }
}

void canbe(GRAPH *graph, int numberOfVertices, STACK *stack1, STACK *stack2) // 0 sau 1 daca poate fi sau nu ajuns
{
    // int* canbe = calloc(5, sizeof(int));
    int ans = 0;
    for (int j = 0; j < numberOfVertices && !ans; j++)
    {
        DFS(graph, stack1, j);
        wipe(graph, numberOfVertices);
        for (int i = 0; i < numberOfVertices && !ans; i++)
        {
            DFS(graph, stack2, i);
            if ((stack1->array[i] == j) && (stack2->array[j] == i))
            {
                ans = 1;
                break;
            }
        }
    }
    if (ans)
    {
        printf("Graful poate fi ajuns de la restaurantul %d si invers.\n", stack1->array[0] + 1);
    }
    else
    {
        printf("Graful NU poate fi ajuns de la niciun restaurant.\n");
    }
}

int main()
{

    int numberOfVertices;
    int numberOfEdges;

    printf("cate noduri are graful? ");
    scanf("%d", &numberOfVertices);

    printf("cate muchii are graful? ");
    scanf("%d", &numberOfEdges);

    GRAPH *graph = createGraph(numberOfVertices);
    STACK *stack1 = createStack(2 * numberOfVertices);
    STACK *stack2 = createStack(2 * numberOfVertices);

    insertEdges(graph, numberOfEdges, numberOfVertices);

    canbe(graph, numberOfVertices, stack1, stack2);
}