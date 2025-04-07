/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graphraf*/

#include <stdlib.h>
#include <stdio.h>

typedef struct Node 
{
    int data;
    struct Node* next;
} NODE;
/// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
/// ex: 1 - restaurantul 1 si tot asa

typedef struct graph
{
    int vertex;
    int* visited;
    struct Node** adjacencyLists;
} GRAPH;

typedef struct stack
{
    int top;
    int stackCap;
    int* array;
} STACK;

NODE* createNode(int value)
{
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

void addEdge(GRAPH *graph, int source, int destination)
{
    NODE* newNode = createNode(destination);
    newNode->next = graph->adjacencyLists[source];
    graph->adjacencyLists[source] = newNode;
    newNode = createNode(source);
    newNode->next = graph->adjacencyLists[destination];
    graph->adjacencyLists[destination] = newNode;
}

GRAPH* createGraph(int vertex)
{
    int i;
    GRAPH* graph = malloc(sizeof(GRAPH));
    graph->vertex = vertex;
    graph->adjacencyLists = (NODE**)malloc(vertex * sizeof(NODE*));
    graph->visited = (int*)malloc(sizeof(int) * vertex);

    for (i = 0; i < vertex; i++)
    {
        graph->adjacencyLists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

STACK* createStack(int stackCap)
{
    STACK* stack = malloc(sizeof(STACK));
    stack->array = malloc(stackCap * sizeof(int));
    stack->top = -1;
    stack->stackCap = stackCap;

    return stack;
}

void push(int value, STACK *stack)
{
    stack->top = stack->top + 1;
    stack->array[stack->top] = value;
}

void DFS(GRAPH *graph, STACK *stack, int numberOfVertices)
{
    NODE* adj_list = graph->adjacencyLists[numberOfVertices];
    NODE* temp = adj_list;
    graph->visited[numberOfVertices] = 1;
    printf("%d ", numberOfVertices);
    push(numberOfVertices, stack);
    while (temp != NULL)
    {
        int connectedVertex = temp->data;
        if (graph->visited[connectedVertex] == 0)
            DFS(graph, stack, connectedVertex);
        temp = temp->next;
    }
}

void insertEdges(GRAPH* graph, int edgraph_nr, int numberOfVertices)
{
    int source, destination, i;
    printf("adauga %d munchii (de la 1 la %d)\n", edgraph_nr, numberOfVertices);
    for (i = 0; i < edgraph_nr; i++)
    {
        scanf("%d%d", &source, &destination);
        insertEdges(graph, source, destination);
    }
}

void wipe(GRAPH* graph, int numberOfVertices)
{
    for (int i = 0; i < numberOfVertices; i++)
    {
        graph->visited[i] = 0;
    }
}

void canbe(GRAPH* graph, int numberOfVertices, STACK* stack1, STACK* stack2) // 0 sau 1 daca poate fi sau nu ajuns
{
    int* canbe = calloc(5, sizeof(int));
    for (int i = 0; i < numberOfVertices; i++) { // aici i tine loc de numar adica de restaurant{for (int j = 0; j < 5; j++)
        for(int j = 0; j < 5; j++) {
            DFS(graph, stack1, i);
            wipe(graph, numberOfVertices);
            DFS(graph, stack2, j);
            for (int j = 0; j < numberOfVertices; j++) {
                for (int i = 0; i < numberOfVertices; i++) {
                    if ((stack1->array[i] == j) && (stack2->array[j] == i)) {
                        canbe[j] = 1;
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

    insertEdges(graph, numberOfEdges, numberOfVertices);

    canbe(graph, numberOfVertices, stack1, stack2);
}