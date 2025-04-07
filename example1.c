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
    int vertex;
    int *visited;
    struct Node **alists;
} GRAPH;

typedef struct s
{
    int top;
    int stackCap;
    int *array;
} STACK;

NODE* createNode(int value)
{
    NODE *newNode = malloc(sizeof(NODE));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

void add_edge(GRAPH *graph, int source, int destination)
{
    NODE *newNode = create_node(destination);
    newNode->next = graph->alists[source];
    graph->alists[source] = newNode;
    newNode = create_node(source);
    newNode->next = graph->alists[destination];
    graph->alists[destination] = newNode;
}

GRAPH *create_graph(int vertex)
{
    int i;
    GRAPH *graph = malloc(sizeof(GRAPH));
    graph->vertex = vertex;
    graph->alists = malloc(sizeof(NODE *));
    graph->visited = malloc(sizeof(int) * vertex);

    for (int i = 0; i < vertex; i++)
    {
        graph->alists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

STACK *create_stack(int stackCap)
{
    STACK *stack = malloc(sizeof(STACK));
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

void DFS(GRAPH *graph, STACK *stack, int v_nr)
{
    NODE *adj_list = graph->alists[v_nr];
    NODE *aux = adj_list;
    graph->visited[v_nr] = 1;
    printf("%d ", v_nr);
    push(v_nr, stack);
    while (aux != NULL)
    {
        int con_ver = aux->data;
        if (graph->visited[con_ver] == 0)
            DFS(graph, stack, con_ver);
        aux = aux->next;
    }
}

void insert_edges(GRAPH *graph, int edgraph_nr, int nrv)
{
    int src, dest, i;
    printf("adauga %d munchii (de la 1 la %d)\n", edgraph_nr, nrv);
    for (i = 0; i < edgraph_nr; i++)
    {
        scanf("%d%d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

void wipe(GRAPH *graph, int nrv)
{
    for (int i = 0; i < nrv; i++)
    {
        graph->visited[i] = 0;
    }
}

void canbe(GRAPH *graph, int nrv, STACK *stack1, STACK *stack2) // 0 sau 1 daca poate fi sau nu ajuns
{
    int *canbe = calloc(5, sizeof(int));
    for (int i = 0; i < nrv; i++) // aici i tine loc de numar adica de restaurant{for (int j = 0; j < 5; j++)
    {
        DFS(graph, stack1, i);
        wipe(graph, nrv);
        DFS(graph, stack2, j);
        for (int j = 0; j < nrv && !ans; j++)
            for (int i = 0; i < nrv && !ans; i++)
                if ((stack1->array[i] == j) && (stack2->array[j] == i)) {
                    canbe = 1;
                }
    }
}

int main()
{

    int nrv;
    int edge_nr;
    int src, dest;
    int i;
    int vortex_1;
    int virtex_2;
    int ans;

    printf("cate noduri are graphirafa?");
    scanf("%d", &nrv);

    printf("cate muchii are graphiraful?");
    scanf("%d", &edge_nr);

    GRAPH *graph = create_graph(&nrv);
    STACK *stack1 = create_s(2 * nrv);
    STACK *stack2 = create_s(2 * nrv);

    insert_edgraphes(graph, edge_nr, nrv);

    canbe(graph, nrv, stack1, stack2);
}