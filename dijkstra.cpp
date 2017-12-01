#include "dijkstra.h"
#include "ui_dijkstra.h"

#include "testfilegraph.h"
#include "dijkstrainitial.h"
#include "manualgraphscreen.h"

#include "menu.h"

#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
#define MAX 10005 //maximo numero de vértices
#define Node pair< int , int > //definimos el nodo como un par( first , second ) donde first es el vertice adyacente y second el peso de la arista
#define INF 1<<30 //definimos un valor grande que represente la distancia infinita inicial, basta conque sea superior al maximo valor del peso en alguna de las aristas

//La cola de prioridad de C++ por default es un max-Heap (elemento de mayor valor en el tope)
//por ello es necesario realizar nuestro comparador para que sea un min-Heap
struct cmp {
    bool operator() (const Node &a, const Node &b) {
        return a.second > b.second;
    }
};
vector< Node > ady[MAX]; //lista de adyacencia
int distancia[MAX];      //distancia[ u ] distancia de vértice inicial a vértice con ID = u
bool visitado[MAX];      //para vértices visitados
priority_queue< Node, vector<Node>, cmp > Q; //priority queue propia del c++, usamos el comparador definido para que el de menor valor este en el tope
int V;                     //numero de vertices
int previo[MAX];         //para la impresion de caminos

//función de inicialización
void init(){
    for (int i = 0; i <= V; ++i){
        distancia[i] = INF;  //inicializamos todas las distancias con valor infinito
        visitado[i] = false; //inicializamos todos los vértices como no visitados
        previo[i] = -1;      //inicializamos el previo del vertice i con -1
    }
}

//Paso de relajacion
void relajacion(int actual, int adyacente, int peso){
    //Si la distancia del origen al vertice actual + peso de su arista es menor a la distancia del origen al vertice adyacente
    if (distancia[actual] + peso < distancia[adyacente]){
        distancia[adyacente] = distancia[actual] + peso;  //relajamos el vertice actualizando la distancia
        previo[adyacente] = actual;                         //a su vez actualizamos el vertice previo
        Q.push(Node(adyacente, distancia[adyacente])); //agregamos adyacente a la cola de prioridad
    }
}

//Impresion del camino mas corto desde el vertice inicial y final ingresados
void print(int destino){
    if (previo[destino] != -1)    //si aun poseo un vertice previo
        print(previo[destino]);  //recursivamente sigo explorando
    printf("%d ", destino);        //terminada la recursion imprimo los vertices recorridos
}

void dijkstra(int inicial){
    init(); //inicializamos nuestros arreglos
    Q.push(Node(inicial, 0)); //Insertamos el vértice inicial en la Cola de Prioridad
    distancia[inicial] = 0;      //Este paso es importante, inicializamos la distancia del inicial como 0
    int actual, adyacente, peso;
    while (!Q.empty()){                   //Mientras cola no este vacia
        actual = Q.top().first;            //Obtengo de la cola el nodo con menor peso, en un comienzo será el inicial
        Q.pop();                           //Sacamos el elemento de la cola
        if (visitado[actual]) continue; //Si el vértice actual ya fue visitado entonces sigo sacando elementos de la cola
        visitado[actual] = true;         //Marco como visitado el vértice actual

        for (int i = 0; i < ady[actual].size(); ++i){ //reviso sus adyacentes del vertice actual
            adyacente = ady[actual][i].first;   //id del vertice adyacente
            peso = ady[actual][i].second;        //peso de la arista que une actual con adyacente ( actual , adyacente )
            if (!visitado[adyacente]){        //si el vertice adyacente no fue visitado
                relajacion(actual, adyacente, peso); //realizamos el paso de relajacion
            }
        }
    }
}

Dijkstra::Dijkstra(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dijkstra)
{
    ui->setupUi(this);

    int E, origen, destino, peso, inicial;

    bool auto_manualGraph; // false = manual, true = auto.

    edge *tempEdge = new edge();
    int tempEdges = 0;

    if(getManualGraph()) {
        auto_manualGraph = false;
        tempEdges = getManualEdges();
        tempEdge = getEdgesArrayManual();
        E = getManualEdges(); // Edges.
        V = getManualNodes() + 1; // Nodes.

    }else {
        auto_manualGraph = true;
        tempEdges = getAutoEdges();
        tempEdge = getAutoEdgesArray();
        E = getAutoEdges(); // Edges.
        V = getAutoNodes() + 1; // Nodes.
    }

    while (E >= 0){
        int origen = stoi(tempEdge->from);
        int destino = stoi(tempEdge->to);
        int peso = stoi(tempEdge->weight);

        cout << "Peso: " << peso << endl;

        ady[origen + 1].push_back(Node(destino + 1, peso));

        E--;

        tempEdge = tempEdge->next;
    }
    inicial = getInitialDijkstra() + 1;
    dijkstra(inicial);


    // Results:
    QString label3;
    string initial = to_string(getInitialDijkstra());
    QString initial2 = QString::fromStdString(initial);
    label3 = "Vértice inicial: " + initial2 + ".";
    ui->dijkstra->appendPlainText(label3);

    for(int i = 1; i <= V; i++){
        string initial = to_string(getInitialDijkstra());
        string vertex = to_string((i - 1));
        string distance = to_string(distancia[i]);

        if(distance == "1073741824") distance = "Sin acceso";

        QString initial2 = QString::fromStdString(initial);
        QString vertex2 = QString::fromStdString(vertex);
        QString distance2 = QString::fromStdString(distance);

        label3 = "Destino: " + vertex2 + " - Distancia: " + distance2 + ".";
        ui->dijkstra->appendPlainText(label3);
    }
}

Dijkstra::~Dijkstra()
{
    delete ui;
}
