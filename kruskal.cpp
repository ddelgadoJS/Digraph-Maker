#include "kruskal.h"
#include "ui_kruskal.h"

#include "manualgraphscreen.h"
#include "testfilegraph.h"

int nums[1000];
int counter = 0;







///////////

#include <iostream>
#define SIZE 10

using namespace std;

/*
 * Prim's Algorithm
 * using a Min Heap
 *
 * Authored by,
 * Vamsi Sangam.
 *
 */

struct node2 {
    int val;
    int weight;
    struct node2 * next;
};

struct edge2 {
    int weight;
    int u, v;   // edge from u ---> v
};

// Adds an edge to an Adjacency List element
struct node2 * addEdge2(struct node2 * head, int num, int weight)
{
    struct node2 * p = (struct node2 *) malloc(sizeof(struct node2));

    p->val = num;
    p->next = head;
    p->weight = weight;
    head = p;

    return p;
}

// Enqueues an entry into the Priority Queue
void Enqueue2(struct edge2 heap[], int size, struct edge2 value)
{
    heap[size] = value;

    int i = size;
    struct edge2 temp;

    while (i >= 1) {
        if (heap[i / 2].weight > heap[i].weight) {
            temp = heap[i / 2];
            heap[i / 2] = heap[i];
            heap[i] = temp;

            i = i / 2;
        } else {
            break;
        }
    }
}

void Heapify2(struct edge2 heap[], int size, int index)
{
    int i = index;
    struct edge2 temp;

    while ((2 * i) < size) {
        if ((2 * i) + 1 >= size) {
            if (heap[i].weight > heap[2 * i].weight) {
                temp = heap[i];
                heap[i] = heap[2 * i];
                heap[2 * i] = temp;

                break;
            }
        }

        if (heap[i].weight > heap[2 * i].weight || heap[i].weight > heap[2 * i + 1].weight) {
            if (heap[2 * i].weight <= heap[(2 * i) + 1].weight) {
                temp = heap[2 * i];
                heap[2 * i] = heap[i];
                heap[i] = temp;

                i = 2 * i;
            } else if (heap[2 * i].weight > heap[(2 * i) + 1].weight) {
                temp = heap[(2 * i) + 1];
                heap[(2 * i) + 1] = heap[i];
                heap[i] = temp;

                i = (2 * i) + 1;
            }
        } else {
            break;
        }
    }
}

// Deletes and entry in the Priority Queue
void DeleteNode2(struct edge2 heap[], int size, int index)
{
    struct edge2 temp = heap[index];

    heap[index] = heap[size - 1];
    heap[size - 1] = temp;

    int i = index;
    --size;

    Heapify2(heap, size, i);
}

// Returns the element with
// Minimum Priority and deletes it
struct edge2 ExtractMin2(struct edge2 heap[], int size)
{
    struct edge2 min = heap[0];

    DeleteNode2(heap, size, 0);

    return min;
}

// Prim's Algorithm function
void Prim3(struct node2 * adjacencylist[], int vertices, int edges, int startVertex, struct node2 * MST[])
{
    int current = startVertex, newVertex;
    bool visited[vertices + 1];
    struct node2 * temp;
    struct edge2 var;
    struct edge2 PriorityQueue[2 * edges];
    int QueueSize = 0;

    int i;

    cout << "VERTICES " << vertices << endl;
    cout << "EDGES " << edges << endl;

    for (i = 0; i <= vertices; ++i) {        // Initializing
        visited[i] = false;
    }

    i = 0;

    while (i < vertices) {
        if (!visited[current]) {            // If current node is not visited
            visited[current] = true;        // Mark it visited
            temp = adjacencylist[current];

            while (temp != NULL) {
                var.u = current;
                var.v = temp->val;
                var.weight = temp->weight;

                if (!visited[var.v]) {
                    // If the edge leads to an un-visited
                    // vertex only then enqueue it
                    Enqueue2(PriorityQueue, QueueSize, var);
                    ++QueueSize;
                }

                temp = temp->next;
            }

            var = ExtractMin2(PriorityQueue, QueueSize);     // The greedy choice
            --QueueSize;

            newVertex = var.v;
            current = var.u;

            if (!visited[newVertex]) {
                // If it leads to an un-visited vertex, add it to MST
                MST[current] = addEdge2(MST[current], newVertex, var.weight);
                MST[newVertex] = addEdge2(MST[newVertex], current, var.weight);
            }

            current = newVertex;
            ++i;
        } else {

            var = ExtractMin2(PriorityQueue, QueueSize);
            --QueueSize;

            newVertex = var.v;
            current = var.u;

            if (!visited[newVertex]) {
                MST[current] = addEdge2(MST[current], newVertex, var.weight);
                MST[newVertex] = addEdge2(MST[newVertex], current, var.weight);
            }

            current = newVertex;
        }
    }
}




//////////

// C++ program for Kruskal's algorithm to find Minimum Spanning Tree
// of a given connected, undirected and weighted graph
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// a structure to represent a weighted edge in graph
struct Edge
{
    int src, dest, weight;
};

// a structure to represent a connected, undirected and weighted graph
struct Graph
{
    // V-> Number of vertices, E-> Number of edges
    int V, E;

    // graph is represented as an array of edges. Since the graph is
    // undirected, the edge from src to dest is also edge from dest
    // to src. Both are counted as 1 edge here.
    struct Edge* edge;
};

// Creates a graph with V vertices and E edges
struct Graph* createGraph(int V, int E)
{
    struct Graph* graph = (struct Graph*) malloc( sizeof(struct Graph) );
    graph->V = V;
    graph->E = E;

    graph->edge = (struct Edge*) malloc( graph->E * sizeof( struct Edge ) );

    return graph;
}

// A structure to represent a subset for union-find
struct subset
{
    int parent;
    int rank;
};

// A utility function to find set of an element i
// (uses path compression technique)
int find(struct subset subsets[], int i)
{
    // find root and make root as parent of i (path compression)
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);

    return subsets[i].parent;
}

// A function that does union of two sets of x and y
// (uses union by rank)
void Union(struct subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    // Attach smaller rank tree under root of high rank tree
    // (Union by Rank)
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;

    // If ranks are same, then make one as root and increment
    // its rank by one
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Compare two edges according to their weights.
// Used in qsort() for sorting an array of edges
int myComp(const void* a, const void* b)
{
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
    return a1->weight > b1->weight;
}

// The main function to construct MST using Kruskal's algorithm
void KruskalMST(struct Graph* graph)
{
    int V = graph->V;
    struct Edge result[V];  // Tnis will store the resultant MST
    int e = 0;  // An index variable, used for result[]
    int i = 0;  // An index variable, used for sorted edges

    // Step 1:  Sort all the edges in non-decreasing order of their weight
    // If we are not allowed to change the given graph, we can create a copy of
    // array of edges
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);

    // Allocate memory for creating V ssubsets
    struct subset *subsets =
        (struct subset*) malloc( V * sizeof(struct subset) );

    // Create V subsets with single elements
    for (int v = 0; v < V; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Number of edges to be taken is equal to V-1
    while (e < V - 1)
    {
        // Step 2: Pick the smallest edge. And increment the index
        // for next iteration
        struct Edge next_edge = graph->edge[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // If including this edge does't cause cycle, include it
        // in result and increment the index of result for next edge
        if (x != y)
        {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
        // Else discard the next_edge
    }

    for (i = 0; i < e; ++i){
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
        nums[counter] = result[i].src;
        counter++;
        nums[counter] = result[i].dest;
        counter++;
        nums[counter] = result[i].weight;
        counter++;
    }
    return;
}

Kruskal::Kruskal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Kruskal)
{
    ui->setupUi(this);

    int vertices, edges, i, j, v1, v2, weight;

    edge *tempEdge = new edge();
    int tempEdges = 0;

    if(getManualGraph()) {
        tempEdge = getEdgesArrayManual();
        edges = getManualEdges(); // Edges.
        vertices = getManualNodes() + 1; // Nodes.

    }else {
        tempEdge = getAutoEdgesArray();
        edges = getAutoEdges(); // Edges.
        vertices = getAutoNodes() + 1; // Nodes.
    }

    struct node2 * adjacency_list[vertices + 1];
    struct node2 * MST[vertices + 1];

    for (i = 0; i <= vertices; ++i) {
        adjacency_list[i] = NULL;
        MST[i] = NULL;
    }

    //for (i = 1; i <= edges; ++i) {
    tempEdges = edges;
    while (tempEdges > 0){
        int v1 = stoi(tempEdge->from) + 1;
        int v2 = stoi(tempEdge->to) + 1;
        int weight = stoi(tempEdge->weight);
        adjacency_list[v1] = addEdge2(adjacency_list[v1], v2, weight);       //Adding edge v1 ---W---> v2
        adjacency_list[v2] = addEdge2(adjacency_list[v2], v1, weight);       //Adding edge v2 ---W---> v1

        tempEdges--;
        tempEdge = tempEdge->next;
    }

    // Printing Adjacency List
    QString label3;
    for (i = 1; i <= vertices; ++i) {
        string initial = to_string(i);
        QString initial2 = QString::fromStdString(initial);
        label3 = "Adyacencia de " + initial2 + " > ";

        struct node2 * temp = adjacency_list[i];

        while (temp != NULL) {
            string label0 = to_string(temp->val);
            QString label = QString::fromStdString(label0);
            label3 += label + " > ";
            temp = temp->next;
        }

        label3 += " NULL.";

        ui->dijkstra->appendPlainText(label3);
    }

    return;

    /*bool auto_manualGraph; // false = manual, true = auto.

    edge *tempEdge = new edge();
    int tempEdges = 0;

    int V;  // Number of vertices in graph
    int E;  // Number of edges in graph
    struct Graph* graph = createGraph(V, E);

    if(getManualGraph()) {
        auto_manualGraph = false;
        tempEdges = getManualEdges();
        tempEdge = getEdgesArrayManual();
        E = getManualEdges() + 1; // Edges.
        V = getManualNodes() + 1; // Nodes.
        printManualEdges();

    }else {
        auto_manualGraph = true;
        tempEdges = getAutoEdges();
        tempEdge = getAutoEdgesArray();
        E = getAutoEdges() + 1; // Edges.
        V = getAutoNodes() + 1; // Nodes.
        printEdges();
    }

    cout << "E: " << E << endl;
    cout << "V: " << V << endl;
    cout << "tempEdges: " << tempEdges << endl;

    int counter2 = 0;
    while (tempEdges >= 0){
        cout << "from: " << tempEdge->from << endl;
        cout << "to: " << tempEdge->to << endl;
        cout << "weight: " << tempEdge->weight << endl;

        int from = stoi(tempEdge->from);
        int to = stoi(tempEdge->to);
        int weight = stoi(tempEdge->weight);

        graph->edge[counter2].src = from;
        graph->edge[counter2].dest = to;
        graph->edge[counter2].weight = weight;

        counter2++;

        if(tempEdge->next == NULL) break;

        tempEdges--;

        tempEdge = tempEdge->next;
    }*/

    //KruskalMST(graph);

    /*int V = 4;  // Number of vertices in graph
        int E = 5;  // Number of edges in graph
        struct Graph* graph = createGraph(V, E);


        // add edge 0-1
        graph->edge[0].src = 0;
        graph->edge[0].dest = 1;
        graph->edge[0].weight = 10;

        // add edge 0-2
        graph->edge[1].src = 0;
        graph->edge[1].dest = 2;
        graph->edge[1].weight = 6;

        // add edge 0-3
        graph->edge[2].src = 0;
        graph->edge[2].dest = 3;
        graph->edge[2].weight = 5;

        // add edge 1-3
        graph->edge[3].src = 1;
        graph->edge[3].dest = 3;
        graph->edge[3].weight = 15;

        // add edge 2-3
        graph->edge[4].src = 2;
        graph->edge[4].dest = 3;
        graph->edge[4].weight = 4;

        KruskalMST(graph);

    // Results:
    QString label3;
    for (int i = 0; i < counter ; i++){
        string initial = to_string(nums[i]);
        i++;
        string to = to_string(nums[i]);
        i++;
        string weight = to_string(nums[i]);

        QString initial2 = QString::fromStdString(initial);
        QString to2 = QString::fromStdString(to);
        QString weight2 = QString::fromStdString(weight);

        label3 = "Origen: " + initial2 + ". Destino: " + to2 + ". Peso: " + weight2 + ".";
        ui->dijkstra->appendPlainText(label3);
    }*/
}

Kruskal::~Kruskal()
{
    delete ui;
}

