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
    if(newNode == NULL) {
        fprintf(stderr, "Eroare alocare!\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

GRAPH *createGraph(int numberOfVertices)
{
    int i;
    GRAPH *graph = (GRAPH *)malloc(sizeof(GRAPH));
    if (graph == NULL) {
        fprintf(stderr, "Eroare alocare!\n");
        exit(1);
    }
    graph->vertices = numberOfVertices;
    graph->adjacencyLists = (NODE **)malloc((numberOfVertices + 1) * sizeof(NODE *));
    graph->visited = (int *)malloc((numberOfVertices + 1) * sizeof(int));

    for (i = 1; i <= numberOfVertices; i++)
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

void insertEdges(GRAPH *graph, int numberOfEdges)
{
    int source, destination, i;
    printf("adauga %d munchii (de la 1 la %d)\n", numberOfEdges, graph->vertices);
    for (i = 0; i < numberOfEdges; i++)
    {
        scanf("%d%d", &source, &destination);
        addEdge(graph, source, destination);
    }
}

void wipe(GRAPH *graph)
{
    for (int i = 1; i <= graph->vertices; i++)
    {
        graph->visited[i] = 0;
    }
}

void subsequentDFS(GRAPH* graph, STACK* stack1, STACK* stack2) {
    int* ans = calloc(graph->vertices, sizeof(int));
    if (ans == NULL) {
        fprintf(stderr, "Eroare alocare!\n");
        exit(1);
    }
    for (int i = 1; i <= graph->vertices; i++) {
        for (int j = 1; j <= graph->vertices; j++) {
            stack1->top = 0;
            DFS(graph, stack1, i);

            wipe(graph);

            stack2->top = 0;
            DFS(graph, stack2, j);

            for (int j = 1; j <= graph->vertices; j++) {
                for (int i = 1; i <= graph->vertices; i++) {
                    if ((stack1->array[i - 1] == j) && (stack2->array[j - 1] == i)) {
                        ans[i] = 1;
                    }
                }
            }
        }
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

    GRAPH* graph = createGraph(numberOfVertices);
    STACK* stack1 = createStack(2 * numberOfVertices);
    STACK* stack2 = createStack(2 * numberOfVertices);

    insertEdges(graph, numberOfEdges);

    subsequentDFS(graph, stack1, stack2);

    printf("Compileaza dar nu sunt sigur ce trebuie sa faca\n");

    return 0;
}