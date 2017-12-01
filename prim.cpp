#include "prim.h"
#include "ui_prim.h"

#include "testfilegraph.h"
#include "manualgraphscreen.h"

#include <string>
#include <stdio.h>
#include<iostream>
#include<stdlib.h>

#include <cstdio>
#include <cstdlib>

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
struct node2 * addEdge(struct node2 * head, int num, int weight)
{
    struct node2 * p = (struct node2 *) malloc(sizeof(struct node2));

    p->val = num;
    p->next = head;
    p->weight = weight;
    head = p;

    return p;
}

// Enqueues an entry into the Priority Queue
void Enqueue(struct edge2 heap[], int size, struct edge2 value)
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

void Heapify(struct edge2 heap[], int size, int index)
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
void DeleteNode(struct edge2 heap[], int size, int index)
{
    struct edge2 temp = heap[index];

    heap[index] = heap[size - 1];
    heap[size - 1] = temp;

    int i = index;
    --size;

    Heapify(heap, size, i);
}

// Returns the element with
// Minimum Priority and deletes it
struct edge2 ExtractMin(struct edge2 heap[], int size)
{
    struct edge2 min = heap[0];

    DeleteNode(heap, size, 0);

    return min;
}

// Prim's Algorithm function
void Prim2(struct node2 * adjacencylist[], int vertices, int edges, int startVertex, struct node2 * MST[])
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
                    Enqueue(PriorityQueue, QueueSize, var);
                    ++QueueSize;
                }

                temp = temp->next;
            }

            var = ExtractMin(PriorityQueue, QueueSize);     // The greedy choice
            --QueueSize;

            newVertex = var.v;
            current = var.u;

            if (!visited[newVertex]) {
                // If it leads to an un-visited vertex, add it to MST
                MST[current] = addEdge(MST[current], newVertex, var.weight);
                MST[newVertex] = addEdge(MST[newVertex], current, var.weight);
            }

            current = newVertex;
            ++i;
        } else {

            var = ExtractMin(PriorityQueue, QueueSize);
            --QueueSize;

            newVertex = var.v;
            current = var.u;

            if (!visited[newVertex]) {
                MST[current] = addEdge(MST[current], newVertex, var.weight);
                MST[newVertex] = addEdge(MST[newVertex], current, var.weight);
            }

            current = newVertex;
        }
    }
}

Prim::Prim(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Prim)
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
        adjacency_list[v1] = addEdge(adjacency_list[v1], v2, weight);       //Adding edge v1 ---W---> v2
        adjacency_list[v2] = addEdge(adjacency_list[v2], v1, weight);       //Adding edge v2 ---W---> v1

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
}

Prim::~Prim()
{
    delete ui;
}
