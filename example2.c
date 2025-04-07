/*parcurgerge  graf cu DFS/BFS*/

// Imi cer scuze in avans

#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node* next;
} NODE;
typedef struct Graph
{
    int vertices;
    int* visited;
    struct Node** adjacencyLists;
} GRAPH;

/// utils
NODE* createNode(int value)
{
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}
GRAPH* createGraph(int vertices)
{
    int i;
    GRAPH* graph = (GRAPH*)malloc(sizeof(GRAPH));
    graph->vertices = vertices;
    graph->adjacencyLists = (NODE**)malloc(vertices * sizeof(NODE *));

    graph->visited = (int*)malloc(sizeof(int) * vertices);
    for (i = 0; i < vertices; i++)
    {
        graph->adjacencyLists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
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

void insertEdges(int numberOfVertices, int numberOfEdges, GRAPH* graph)
{
    int source, destination, i;
    printf("adauga %d muchii (de la 1 la %d)\n", numberOfEdges, numberOfVertices);
    for (i = 0; i < numberOfEdges; i++)
    {
        scanf("%d%d", &source, &destination);
        addEdge(graph, source, destination);
    }
}

/// bfs utils
int isEmpty(NODE* queue)
{
    return queue == NULL;
}

void enqueue(NODE** queue, int data)
{
    NODE* newNode = createNode(data);

    if (isEmpty(*queue))
        *queue = newNode;
    else
    {
        NODE* temp = *queue;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

int dequeue(NODE** queue)
{
    int data = (*queue)->data;
    NODE* temp = *queue;
    *queue = (*queue)->next;
    return data;
}

void printGraph(GRAPH* graph)
{
    int i;
    for (i = 0; i < graph->vertices; i += 1)
    {
        NODE* temp = graph->adjacencyLists[i];

        while (temp)
        {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

void printQueue(NODE* queue)
{
    while (queue != NULL)
    {
        printf("%d ", queue->data);
        queue = queue->next;
    }
}

void wipeVisitedList(GRAPH* graph, int numberOfVertices)
{
    for (int i = 0; i < numberOfVertices; i++)
    {
        graph->visited[i] = 0;
    }
}
// parcurgeri
void DFS(GRAPH* graph, int vertexNumber)
{
    NODE* adjacencyLists = graph->adjacencyLists[vertexNumber];
    NODE* temp = adjacencyLists;

    graph->visited[vertexNumber] = 1;
    printf("%d->", vertexNumber);

    while (temp != NULL)
    {
        int connectedVertex = temp->data;

        if (graph->visited[connectedVertex] == 0)
        {
            DFS(graph, connectedVertex);
        }
        temp = temp->next;
    }
}

void BFS(GRAPH* graph, int start)
{
    NODE* queue = NULL;

    graph->visited[start] = 1;
    enqueue(&queue, start);

    while (!isEmpty(queue))
    {
        int current = dequeue(&queue);
        printf("%d ", current);

        NODE* temp = graph->adjacencyLists[current];

        while (temp)
        {
            int adjacentVertex = temp->data;

            if (graph->visited[adjacentVertex] == 0)
            {
                graph->visited[adjacentVertex] = 1;
                enqueue(&queue, adjacentVertex);
            }
            temp = temp->next;
        }
    }
}

int main()
{

    int numberOfVertices;
    int numberOfEdges;
    int source, destination;
    int i;
    int startingVertex;
    int *adjacentMatrix;

    printf("cate noduri are graful?: ");
    scanf("%d", &numberOfVertices);
    
    printf("cate muchii are graful?: ");
    scanf("%d", &numberOfEdges);
    
    GRAPH* graph = createGraph(numberOfVertices);
    insertEdges(numberOfVertices, numberOfEdges, graph);

    printf("de unde plecam in DFS?: ");
    scanf("%d", &startingVertex); // =)))
    
    printf("parcurgere cu DFS:");
    DFS(graph, startingVertex);

    wipeVisitedList(graph, numberOfVertices);
    printf("\n");
    
    printf("de unde plecam in BFS?");
    scanf("%d", &startingVertex);
    
    printf("parcurgere cu BFS:");
    BFS(graph, startingVertex);
    
    return 0;
}
