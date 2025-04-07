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
    int vertices;
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

GRAPH* createGraph(int numberOfVertices)
{
    int i;
    GRAPH* graph = (GRAPH*)malloc(sizeof(GRAPH));
    graph->vertices = numberOfVertices;
    graph->adjacencyLists = (NODE**)malloc(numberOfVertices * sizeof(NODE*));
    graph->visited = (int*)malloc(numberOfVertices * sizeof(int));

    for (i = 0; i < numberOfVertices; i++)
    {
        graph->adjacencyLists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

STACK* createStack(int stackCap)
{
    STACK* stack = (STACK*)malloc(sizeof(STACK));
    stack->array = (STACK*)malloc(stackCap * sizeof(int));
    stack->top = -1;
    stack->stackCap = stackCap;
    
    return stack;
}

void push(int value, STACK *stack)
{
    stack->top = stack->top + 1;
    stack->array[stack->top] = value;
}

void DFS(GRAPH* graph, STACK* stack, int vertexNumber)
{
    NODE* adjacencyList = graph->adjacencyLists[vertexNumber];
    NODE* temp = adjacencyList;
    graph->visited[vertexNumber] = 1;
    printf("%d ", vertexNumber);
    push(vertexNumber, stack);
    while (temp != NULL)
    {
        int connectedVertex = temp->data;
        if (graph->visited[connectedVertex] == 0)
            DFS(graph, stack, connectedVertex);
        temp = temp->next;
    }
}

void addEdge(GRAPH* graph, int source, int destination)
{
    NODE* newNode = createNode(destination);

    newNode->next = graph->adjacencyLists[source];
    graph->adjacencyLists[source] = newNode;

    newNode = createNode(source);

    newNode->next = graph->adjacencyLists[destination];
    graph->adjacencyLists[destination] = newNode;
}

void insertEdges(GRAPH* graph, int edgraph_nr, int numberOfVertices)
{
    int source, destination, i;
    printf("adauga %d munchii (de la 1 la %d)\n", edgraph_nr, numberOfVertices);
    for (i = 0; i < edgraph_nr; i++)
    {
        scanf("%d%d", &source, &destination);
        addEdge(graph, source - 1, destination - 1);
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