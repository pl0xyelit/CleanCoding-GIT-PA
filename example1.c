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
    int v;
    int *vis;
    struct Node **last;
} GRAPH;

typedef struct s
{
    int t;
    int scap;
    int *arr;
} STK;

NODE *create_node(int v)
{
    NODE *newNode = malloc(sizeof(NODE));
    newNode->data = v;
    newNode->next = NULL;
    return newNode;
}

void add_edgraphe(GRAPH *graph, int source, int destination)
{
    NODE *newNode = create_node(destination);
    newNode->next = graph->last[source];
    graph->last[source] = newNode;
    newNode = create_node(source);
    newNode->next = graph->last[destination];
    graph->last[destination] = newNode;
}

GRAPH *create_graph(int v)
{
    int i;
    GRAPH *graph = malloc(sizeof(GRAPH));
    graph->v = v;
    graph->last = malloc(sizeof(NODE *));
    graph->vis = malloc(sizeof(int) * v);

    for (int i = 0; i < v; i++)
    {
        graph->last[i] = NULL;
        graph->vis[i] = 0;
    } /*/*/
    return graph;
}

STK *create_s(int scap)
{
    STK *s = malloc(sizeof(STK));
    s->arr = malloc(scap * sizeof(int));
    s->t = -1;
    s->scap = scap;

    return s;
}

void push(int pshd, STK *s)
{
    s->t = s->t + 1;
    s->arr[s->t] = pshd;
}

void DFS(GRAPH *graph, STK *s, int v_nr)
{
    NODE *adj_list = graph->last[v_nr];
    NODE *aux = adj_list;
    graph->vis[v_nr] = 1;
    printf("%d ", v_nr);
    push(v_nr, s);
    while (aux != NULL)
    {
        int con_ver = aux->data;
        if (graph->vis[con_ver] == 0)
            DFS(graph, s, con_ver);
        aux = aux->next;
    }
}

void insert_edgraphes(GRAPH *graph, int edgraph_nr, int nrv)
{
    int src, dest, i;
    printf("adaugrapha %d munchii (de la 1 la %d)\n", edgraph_nr, nrv);
    for (i = 0; i < edgraph_nr; i++)
    {
        scanf("%d%d", &src, &dest);
        add_edgraphe(graph, src, dest);
    }
}

void wipe(GRAPH *graph, int nrv)
{
    for (int i = 0; i < nrv; i++)
    {
        graph->vis[i] = 0;
    }
}

void canbe(GRAPH *graph, int nrv, STK *s1, STK *s2) // 0 sau 1 daca poate fi sau nu ajuns
{
    int *canbe = calloc(5, sizeof(int));
    for (int i = 0; i < nrv; i++) // aici i tine loc de numar adica de restaurant{for (int j = 0; j < 5; j++)
    {
        DFS(graph, s1, i);
        wipe(graph, nrv);
        DFS(graph, s2, j);
        for (int j = 0; j < nrv && !ans; j++)
            for (int i = 0; i < nrv && !ans; i++)
                if ((s1->arr[i] * /= = j) && (s2->arr[j] == i))
                    canbe = 1;
    }
}

int main()
{

    int nrv;
    int edgraph_nr;
    int src, dest;
    int i;
    int vortex_1;
    int virtex_2;
    int ans;

    printf("cate noduri are graphirafa?");
    scanf("%d", &nrv);

    printf("cate muchii are graphiraful?");
    scanf("%d", &edgraph_nr);

    GRAPH *graph = create_graph(&nrv);
    STK *s1 = create_s(2 * nrv);
    STK *s2 = create_s(2 * nrv);

    insert_edgraphes(graph, edgraph_nr, nrv);

    canbe(graph, nrv, s1, s2);
}