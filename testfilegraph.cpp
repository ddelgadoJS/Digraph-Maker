#include "testfilegraph.h"
#include "ui_testfilegraph.h"
#include "testfileoptions.h"

#include <iostream>
#include <string>
#include <QString>

#include <QMessageBox>

using namespace std;

position *positionHead, *actualPosition;
node *nodesArray, *actualNode;
edge *edgesArray, *actualEdge;
int Nodes = -1;
int Edges = -1;
int NodesFile = -1;
int EdgesFile = -1;
bool autoGraph = false;
bool manualGraph = false;

void deleteAutoNode(string label){
    node *tempNode = nodesArray;
    int tempNodes = Nodes;

    edge *tempEdge = edgesArray;
    int tempEdges = Edges;
    while(tempEdges > 0){
        if(((tempEdge->from == label) || (tempEdge->to == label)) & (tempEdges == Edges)){
            QMessageBox msgBox;
            msgBox.setText("Este nodo no puede eliminarse.");
            msgBox.exec();
            return;
        }else if(((tempEdge->from == label) || (tempEdge->to == label))&(Edges == 0)){
            Edges--;
            edgesArray = NULL;
            break;
        }else if(((tempEdge->from == label) || (tempEdge->to == label))){
            Edges--;
            tempEdge->prior->next = tempEdge->next;
            tempEdge->next->prior = tempEdge->prior;
            tempEdge = tempEdge->next;
        }else{
            tempEdge = tempEdge->next;
        }
        tempEdges--;
    }

    while(tempNodes >= 0){
        if((tempNode->label == label)&(tempNodes == Nodes)){
            Nodes--;
            nodesArray = tempNode->next;
            break;
        }else if((tempNode->label == label)&(Nodes == 0)){
            Nodes--;
            nodesArray = NULL;
        }else if(tempNode->label == label){
            Nodes--;
            tempNode->prior->next = tempNode->next;
            tempNode->next->prior = tempNode->prior;
            break;
        }
        tempNode = tempNode->next;
        tempNodes--;
    }
}

void deleteAutoEdge(string from, string to){
    edge *tempEdge = edgesArray;
    int tempEdges = Edges;
    while(tempEdges >= 0){
        if(((tempEdge->from == from) & (tempEdge->to == to)) & (tempEdges == Edges)){
            QMessageBox msgBox;
            msgBox.setText("Este nodo no puede eliminarse.");
            msgBox.exec();
            return;
        }else if(((tempEdge->from == from) & (tempEdge->to == to))&(Edges == 0)){
            Edges--;
            edgesArray = NULL;
            return;
        }else if(((tempEdge->from == from) & (tempEdge->to == to))){
            Edges--;
            tempEdge->prior->next = tempEdge->next;
            tempEdge->next->prior = tempEdge->prior;
            tempEdge = tempEdge->next;
            return;
        }else{
            tempEdge = tempEdge->next;
        }
        tempEdges--;
    }
}

void setPosX(int x, int y, bool first){
    if(first){
        positionHead = new position; // Head.
        actualPosition = positionHead;

        actualPosition->x = x;
        actualPosition->y = y;
        actualPosition->next = NULL;
    }else{
        position *tempPosition = new position;
        tempPosition->x = x;
        tempPosition->y = y;
        tempPosition->next = NULL;

        actualPosition->next = tempPosition;
        tempPosition->prior = actualPosition;
        actualPosition = tempPosition;
    }
    NodesFile++;
}// Tests


void printNodes(){
    node *tempNode = nodesArray;
    while(true){
        cout << tempNode->label << " - " << tempNode->x << " - " << tempNode->y << endl;
        if(tempNode->next == NULL) break;

        tempNode = tempNode->next;
    }
}

void printEdges(){
    edge *tempEdge = edgesArray;
    int tempEdges = Edges;
    while(tempEdges >= 0){
        //cout << tempEdge->from << " - " << tempEdge->to << endl;
        cout << tempEdge->from << " - " << tempEdge->to << " - ";
        cout << tempEdge->x1 << " - " << tempEdge->x2 << " - ";
        cout << tempEdge->y1 << " - " << tempEdge->y2 << endl;
        //if(tempEdge->next == NULL) break;

        tempEdge = tempEdge->next;
        tempEdges--;
    }
}

// Functions
node* getAutoNodesArray(){
    return nodesArray;
}

edge* getAutoEdgesArray(){
    return edgesArray;
}

int getAutoNodes(){
    return Nodes;
}

int getAutoEdges(){
    return Edges;
}

bool getAutoGraph(){
    return autoGraph;
}

void setAutoGraph(){
    autoGraph = true;
}

bool getManualGraph(){
    return manualGraph;
}

void setManualGraph(){
    manualGraph = true;
}

bool valXY(int x, int y){
    node *tempNode = nodesArray;
    while(true){
        if((tempNode->x == 0) & (tempNode->y == 0)) break; // This node hasn't been set.

        int rangex1 = tempNode->x - 20;
        int rangex2 = tempNode->x + 40;
        int rangey1 = tempNode->y - 20;
        int rangey2 = tempNode->y + 40;
        //cout << rangex1 << " -*" << x << "*- " << rangex2 << " - " << rangey1 << " -*" << y << "*- " << rangey2 << endl;
        if((x >= rangex1) & (x <= rangex2)){
            if((y >= rangey1) & (y <= rangey2)){
                //cout << "False" << endl;
                return false;
            }
        }

        if(tempNode->next == NULL) break;

        tempNode = tempNode->next; // Move to next node.
    }
    //cout << "True" << endl;
    return true;
}

void setNodesXY(){
    int x, y;
    node *tempNode = nodesArray;
    int counter;
    while(true){ // Iterating the nodes.
        counter = 0;
        while(true){
            if(tempNode->x == 0){
                x = rand() % 1860 + 20;
                y = rand() % 970 + 30;
                if(valXY(x, y) == true){
                    tempNode->x = x;
                    tempNode->y = y;
                    break;
                }

                counter++;
                if(counter == 50){
                    for(x = 30; x <= 1860; x++){
                        for(y = 50; y <= 970; y++){
                            if(valXY(x, y) == true){
                                tempNode->x = x;
                                break;
                            }
                        }
                        break;
                    }
                    break;
                }
            }else break;
        }
        //cout << "NODE CREATED" << endl;
        if(tempNode->next == NULL) break;

        tempNode = tempNode->next;
    }
    cout << "setNodesXY " << Nodes << endl;
}

void setEdgesXY(){
    node *tempNode = nodesArray;
    edge *tempEdge = edgesArray;
    int tempEdges = Edges;
    int tempNodes = Nodes;

    // Flags to know if the edge is done.
    bool fromFL = false;
    bool toFL = false;

    while(tempEdges >= 0){
        while(tempNodes >= 0){
            if(tempNode->label == tempEdge->from){
                tempEdge->x1 = tempNode->x;
                tempEdge->y1 = tempNode->y;
                fromFL = true;
            }else if(tempNode->label == tempEdge->to){
                tempEdge->x2 = tempNode->x;
                tempEdge->y2 = tempNode->y;
                toFL = true;
            }

            if((fromFL & toFL) == true) break;

            tempNode = tempNode->next;
            tempNodes--;
        }
        tempEdge = tempEdge->next;
        tempNode = nodesArray;

        tempEdges--;
        tempNodes = Nodes;
        fromFL = toFL = false;
    }
}

void setAutoEdgeXY(edge *tempEdge){
    node *tempNode = nodesArray;
    int tempNodes = Nodes;

    // Flags to know if the edge is done.
    bool fromFL = false;
    bool toFL = false;

    while(tempNodes >= 0){
        if(tempNode->label == tempEdge->from){
            tempEdge->x1 = tempNode->x;
            tempEdge->y1 = tempNode->y;
            fromFL = true;
        }else if(tempNode->label == tempEdge->to){
            tempEdge->x2 = tempNode->x;
            tempEdge->y2 = tempNode->y;
            toFL = true;
        }

        if((fromFL & toFL) == true) break;

        tempNode = tempNode->next;
        tempNodes--;
    }
}

void createNodes(int quantity){ // This function is for ManualGraph.
    nodesArray = new node; // Head.
    actualNode = nodesArray;
    //edgesArray = new edge; // Head.
    //actualEdge = edgesArray;
    Nodes = quantity - 1;

    for(int i = 0; i < quantity; i++){
        if(i == 0){
            actualNode->label = to_string(i);
        }else{
            node *tempNode = new node;
            actualNode->next = tempNode;

            tempNode->prior = actualNode;
            tempNode->next = NULL;
            tempNode->label = to_string(i);

            actualNode = tempNode;
        }
    }
}

void createNode(string nodeLabel){ // Create a node from Test_File.txt
    node *tempNode = new node;
    tempNode->prior = actualNode;
    actualNode->next = tempNode;
    actualNode->label = nodeLabel;
    actualNode = tempNode;

    Nodes++;
}

void createEdge(string from, string to, string weight, bool first){
    if(first == true){
        actualEdge->from = from;
        actualEdge->to = to;
        actualEdge->weight = weight;
    }else{
        edge *tempEdge = new edge;
        tempEdge->from = from;
        tempEdge->to = to;
        tempEdge->weight = weight;

        actualEdge->next = tempEdge;
        tempEdge->prior = actualEdge;
        tempEdge->next = NULL;
        actualEdge = tempEdge;
    }
    Edges++;

    cout << "createEdge " << Nodes << endl;
}

void createEdge(string from, string to, string label, string weight, bool first){
    if(first == true){
        edge *tempEdge = new edge;
        tempEdge->from = from;
        tempEdge->to = to;
        tempEdge->weight = weight;
        tempEdge->label = label;
        actualEdge = tempEdge;
        edgesArray = actualEdge;
    }else{
        edge *tempEdge = new edge;
        tempEdge->from = from;
        tempEdge->to = to;
        tempEdge->weight = weight;
        tempEdge->label = label;

        actualEdge->next = tempEdge;
        tempEdge->prior = actualEdge;
        tempEdge->next = NULL;
        actualEdge = tempEdge;
    }
    Edges++;
}

void createEdges(){
    node *tempNode = nodesArray;
    bool FL1 = false;
    bool FL2 = false;

    edge *tempEdge = new edge;
    tempEdge->prior = actualEdge;
    tempEdge->x1 = 0;
    tempEdge->x2 = 0;
    tempEdge->y1 = 0;
    tempEdge->y2 = 0;
    tempEdge->weight = "";
    tempEdge->label = "";
    tempEdge->from = "";
    tempEdge->to = "";
    actualEdge->from = "2";
    actualEdge->to = "12";
    while(true){
        if(tempNode->label == actualEdge->from){
            actualEdge->x1 = tempNode->x;
            actualEdge->y1 = tempNode->y;
            FL1 = true;
        }
        if(tempNode->label == actualEdge->to){
            actualEdge->x2 = tempNode->x;
            actualEdge->y2 = tempNode->y;
            FL2 = true;
        }
        if((FL1 & FL2) == true) break;

        if(tempNode->next == NULL) break;

        tempNode = tempNode->next;
    }
    actualEdge->next = tempEdge;
    actualEdge = tempEdge;

    FL1 = false;
    FL2 = false;

    tempNode = nodesArray;

    actualEdge->from = "5";
    actualEdge->to = "1";
    while(true){
        if(tempNode->label == actualEdge->from){
            actualEdge->x1 = tempNode->x;
            actualEdge->y1 = tempNode->y;
            FL1 = true;
        }
        if(tempNode->label == actualEdge->to){
            actualEdge->x2 = tempNode->x;
            actualEdge->y2 = tempNode->y;
            FL2 = true;
        }
        if(((FL1 & FL2)) == true) break;

        if(tempNode->next == NULL) break;

        tempNode = tempNode->next;
    }
    //actualEdge->next = tempEdge;
    //actualEdge = tempEdge;
}

void addAutoNodes(int quantity){ // This function is to add nodes to an automatic made graph.
    node *tempNode = nodesArray;
    while(true){
        if(tempNode->next == NULL) break;

        tempNode = tempNode->next; // Move to next node.
    }

    for(int i = Nodes + 1; i <= Nodes + quantity; i++){
        node *tempNode2 = new node;
        tempNode2->prior = tempNode;
        tempNode2->next = NULL;
        tempNode2->label = to_string(i);

        tempNode->next = tempNode2;

        tempNode = tempNode2;
    }
    setNodesXY();
    printNodes();

    Nodes += quantity;
}

void addAutoEdge(string from, string to, string label, string weight){
    edge *Edge3;
    if(Edges == -1){
        edgesArray = new edge;

        edgesArray->from = from;
        edgesArray->to = to;
        edgesArray->weight = weight;
        edgesArray->label = label;
        edgesArray->prior = NULL;
        edgesArray->next = NULL;
        Edge3 = edgesArray;
    }else{
        edge *tempEdge = edgesArray;
        while(true){
            if(tempEdge->next == NULL) break;

            tempEdge = tempEdge->next; // Move to next edge.
        }

        edge *tempEdge2 = new edge;
        tempEdge2->from = from;
        tempEdge2->to = to;
        tempEdge2->label = label;
        tempEdge2->weight = weight;

        tempEdge2->prior = tempEdge;
        tempEdge2->next = NULL;

        tempEdge->next = tempEdge2;
        Edge3 = tempEdge2;
    }
    Edges++;

    setAutoEdgeXY(Edge3);
}

void readTestFile(){
    QString qsLine;
    string sLine, nodeLabel, tempSLine, connections, connection, weights, weight;

    QFile file("/home/delgados/Desktop/ED/Repositorio Tareas/Tareas_ED/Proyecto_2/Grafos/Test_Nodes.txt");
    if (file.open(QIODevice::ReadOnly)){
        QTextStream in(&file);
        Edges = Nodes = -1;
        while(!in.atEnd()){
            qsLine = in.readLine();
            sLine = qsLine.toStdString();
            if(sLine == "//") break; // EOF
            int tempPos = sLine.find(";"); // Finds the position of first ';'.
            nodeLabel = sLine.substr(0, tempPos); // Node label.
            tempSLine = sLine.substr(tempPos + 1); // Slices the line, removes node label.

            tempPos = tempSLine.find(";"); // Finds the position of second ';'.
            connections = tempSLine.substr(0, tempPos); // Node connections.
            tempSLine = tempSLine.substr(tempPos + 1); // Slices the line, removes node connections.

            tempPos = tempSLine.find(";"); // Finds the position of third ';'.
            weights = tempSLine.substr(0, tempPos); // Edges weights.

            createNode(nodeLabel);

            while(connections.length() > 0){
                tempPos = connections.find(",");
                connection = connections.substr(0, tempPos);
                connections = connections.substr(tempPos + 1); // Slices connections.

                tempPos = weights.find(",");
                weight = weights.substr(0, tempPos);
                weights = weights.substr(tempPos + 1); // Slices weights.

                if(Edges == -1) createEdge(nodeLabel, connection, weight, true);
                else createEdge(nodeLabel, connection, weight, false);
            }
        }

    }
    file.close();

    delete(actualNode->prior->next); // Removes last node created, unused.
    actualNode->prior->next = NULL; // Sets last node pointing to NULL.

    setNodesXY(); // Random values for x & y for each node.
    setEdgesXY();
}

testFileGraph::testFileGraph(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::testFileGraph)
{
    nodesArray = new node; // Head.
    actualNode = nodesArray;
    edgesArray = new edge; // Head.
    actualEdge = edgesArray;

    //Graph->head = nodesArray; // This is the graph.

    readTestFile(); // Creating test nodes.

    ui->setupUi(this);
}

testFileGraph::~testFileGraph()
{
    delete ui;
}

void testFileGraph::paintEvent(QPaintEvent *e){
    QPainter painter(this);
    node *tempNode = nodesArray;

    // Background.
    QBrush brush = QBrush(Qt::black);
    painter.fillRect(0,0,1920,1080, brush);

    // Painting edges.
    edge *tempEdge = edgesArray;

    int tempEdges = Edges;
    while(tempEdges >= 0){
        painter.setPen(Qt::blue);
        painter.drawLine(tempEdge->x1 + 10, tempEdge->y1 + 10, tempEdge->x2 + 10, tempEdge->y2 + 10);

        // Weight.
        if(getWeights() == true){
            painter.setPen(Qt::white);
            QString weight = weight.fromStdString(tempEdge->weight);
            painter.drawStaticText((tempEdge->x1 + tempEdge->x2) / 2, (tempEdge->y1 + tempEdge->y2) / 2, weight);
        }

        tempEdge = tempEdge->next; // Move to next edge.

        tempEdges--;
    }

    // Painting nodes.
    painter.setBrush(QBrush(Qt::green));
    while(true){
        painter.drawEllipse(tempNode->x, tempNode->y, 20, 20);

        // Label
        if(getLabels() == true){
            painter.setPen(Qt::black);
            QString label = label.fromStdString(tempNode->label);
            if(label.length() == 1)
                painter.drawStaticText(tempNode->x + 6, tempNode->y + 2, label);
            else
                painter.drawStaticText(tempNode->x + 2, tempNode->y + 2, label);
        }

        if(tempNode->next == NULL) break;

        tempNode = tempNode->next; // Move to next node.
    }

    // Painting directions.
    if(getDirections() == true){
        tempEdge = edgesArray;
        painter.setPen(Qt::white);
        painter.setBrush(QBrush(Qt::red));
        while(tempEdges >= 0){
            // Direction.
            painter.drawEllipse(tempEdge->x2, tempEdge->y2, 10, 10);

            tempEdge = tempEdge->next; // Move to next edge.

            tempEdges--;
        }
    }

    brush = QBrush(Qt::black);
    painter.fillRect(0,0,1920,28, brush);
    painter.fillRect(0,0,18,1080, brush);
}
