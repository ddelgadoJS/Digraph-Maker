#include "manualgraphscreen.h"
#include "ui_manualgraphscreen.h"

#include "testfilegraph.h"

#include <QMessageBox>

node *nodesArrayManual, *actualNodeManual;
edge *edgesArrayManual, *actualEdgeManual;
int Nodes2 = -1;
int Edges2 = -1;

void printManualNodes(){
    node *tempNode = nodesArrayManual;
    while(true){
        cout << tempNode->label << " - " << tempNode->x << " - " << tempNode->y << endl;
        if(tempNode->next == NULL) break;

        tempNode = tempNode->next;
    }
}

void printManualEdges(){
    edge *tempEdge = edgesArrayManual;
    int tempEdges = Edges2;
    while(tempEdges >= 0){
        //cout << tempEdge->from << " - " << tempEdge->to << endl;
        cout << tempEdge->from << " - " << tempEdge->to << " - ";
        cout << tempEdge->label << " - " << tempEdge->weight << " - ";
        cout << tempEdge->x1 << " - " << tempEdge->x2 << " - ";
        cout << tempEdge->y1 << " - " << tempEdge->y2 << endl;
        //if(tempEdge->next == NULL) break;

        tempEdge = tempEdge->next;
        tempEdges--;
    }
}

bool valManualXY(int x, int y){
    node *tempNode = nodesArrayManual;
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

void addManualNodes(int quantity){ // This function is to add nodes to an manual made graph.
    nodesArrayManual->prior = NULL;
    node *tempNode = nodesArrayManual;
    while(true){
        if(tempNode->next == NULL) break;

        tempNode = tempNode->next; // Move to next node.
    }

    for(int i = Nodes2 + 1; i <= Nodes2 + quantity; i++){
        node *tempNode2 = new node;
        tempNode2->prior = tempNode;
        tempNode2->next = NULL;
        tempNode2->label = to_string(i);

        tempNode->next = tempNode2;

        tempNode = tempNode2;
    }
    setManualNodesXY();

    Nodes2 += quantity;
}

void setManualEdgesXY(){
    node *tempNode = nodesArrayManual;
    edge *tempEdge = edgesArrayManual;
    int tempEdges = Edges2;
    int tempNodes = Nodes2;

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
        tempNode = nodesArrayManual;

        tempEdges--;
        tempNodes = Nodes2;
        fromFL = toFL = false;
    }
}

void setManualNodesXY(){
    int x, y;
    node *tempNode = nodesArrayManual;
    int counter;
    while(true){ // Iterating the nodes.
        counter = 0;
        while(true){
            if(tempNode->x == 0){
                x = rand() % 1860 + 20;
                y = rand() % 970 + 30;
                if(valManualXY(x, y) == true){
                    tempNode->x = x;
                    tempNode->y = y;
                    break;
                }

                counter++;
                if(counter == 50){
                    for(x = 30; x <= 1860; x++){
                        for(y = 50; y <= 970; y++){
                            if(valManualXY(x, y) == true){
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
    cout << "setNodesXY " << Nodes2 << endl;
}

void setManualEdgeXY(edge *tempEdge){
    node *tempNode = nodesArrayManual;
    int tempNodes = Nodes2;

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

void addManualEdge(string from, string to, string label, string weight){
    //printManualEdges();
    edge *Edge3;
    int tempEdges3 = Edges2;
    int tempNodes = Nodes2;
    if(Edges2 == -1){
        edgesArrayManual = new edge;

        edgesArrayManual->from = from;
        edgesArrayManual->to = to;
        edgesArrayManual->weight = weight;
        edgesArrayManual->label = label;
        edgesArrayManual->prior = NULL;
        edgesArrayManual->next = NULL;
        Edge3 = edgesArrayManual;
    }else{
        edge *tempEdge = edgesArrayManual;
        while(tempNodes >= 0){
            if(tempEdge->next == NULL) break;

            tempEdge = tempEdge->next; // Move to next edge.
            tempNodes--;
        }

        edge *tempEdge2 = new edge;
        tempEdge2->from = from;
        tempEdge2->to = to;
        tempEdge2->weight = weight;
        tempEdge2->label = label;

        tempEdge2->prior = tempEdge;
        tempEdge2->next = NULL;

        tempEdge->next = tempEdge2;
        Edge3 = tempEdge2;
    }
    Edges2++;

    setManualEdgeXY(Edge3);
}

void createManualEdge(string from, string to, string label, string weight, bool first){
    if(first == true){
        edge *tempEdge = new edge;
        tempEdge->from = from;
        tempEdge->to = to;
        tempEdge->weight = weight;
        tempEdge->label = label;
        actualEdgeManual = tempEdge;
        edgesArrayManual = actualEdgeManual;
    }else{
        edge *tempEdge = new edge;
        tempEdge->from = from;
        tempEdge->to = to;
        tempEdge->weight = weight;
        tempEdge->label = label;

        actualEdgeManual->next = tempEdge;
        tempEdge->prior = actualEdgeManual;
        tempEdge->next = NULL;
        actualEdgeManual = tempEdge;
    }
    Edges2++;
}

void createManualNodes(int quantity){
    nodesArrayManual = new node; // Head.
    actualNodeManual = new node;
    actualNodeManual = nodesArrayManual;
    //edgesArray = new edge; // Head.
    //actualEdge = edgesArray;
    Nodes2 = quantity - 1;

    for(int i = 0; i < quantity; i++){
        if(i == 0){
            nodesArrayManual->label = to_string(i);
        }else{
            node *tempNode = new node;
            actualNodeManual->next = tempNode;

            tempNode->prior = actualNodeManual;
            tempNode->next = NULL;
            tempNode->label = to_string(i);

            actualNodeManual = tempNode;
        }
    }
}

void deleteManualNode(string label){
    node *tempNode = nodesArrayManual;
    int tempNodes = Nodes2;

    edge *tempEdge = edgesArrayManual;
    int tempEdges = Edges2;
    while(tempEdges > 0){
        if(((tempEdge->from == label) || (tempEdge->to == label)) & (tempEdges == Edges2)){
            QMessageBox msgBox;
            msgBox.setText("Este nodo no puede eliminarse.");
            msgBox.exec();
            return;
        }else if(((tempEdge->from == label) || (tempEdge->to == label))&(Edges2 == 0)){
            Edges2--;
            edgesArrayManual = NULL;
            break;
        }else if(((tempEdge->from == label) || (tempEdge->to == label))){
            Edges2--;
            tempEdge->prior->next = tempEdge->next;
            tempEdge->next->prior = tempEdge->prior;
            tempEdge = tempEdge->next;
        }else{
            tempEdge = tempEdge->next;
        }
        tempEdges--;
    }

    while(tempNodes >= 0){
        if((tempNode->label == label)&(tempNodes == Nodes2)){
            Nodes2--;
            nodesArrayManual = tempNode->next;
            break;
        }else if((tempNode->label == label)&(Nodes2 == 0)){
            Nodes2--;
            nodesArrayManual = NULL;
        }else if(tempNode->label == label){
            Nodes2--;
            tempNode->prior->next = tempNode->next;
            tempNode->next->prior = tempNode->prior;
            break;
        }
        tempNode = tempNode->next;
        tempNodes--;
    }
}

void deleteManualEdge(string from, string to){
    node *tempNode = nodesArrayManual;
    int tempNodes = Nodes2;

    edge *tempEdge = edgesArrayManual;
    int tempEdges = Edges2;
    while(tempEdges >= 0){
        if(((tempEdge->from == from) & (tempEdge->to == to)) & (tempEdges == Edges2)){
            QMessageBox msgBox;
            msgBox.setText("Este nodo no puede eliminarse.");
            msgBox.exec();
            return;
        }else if(((tempEdge->from == from) & (tempEdge->to == to))&(Edges2 == 0)){
            Edges2--;
            edgesArrayManual = NULL;
            return;
        }else if(((tempEdge->from == from) & (tempEdge->to == to))){
            Edges2--;
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

node* getNodesArrayManual(){
    return nodesArrayManual;
}

edge* getEdgesArrayManual(){
    return edgesArrayManual;
}


int getManualNodes(){
    return Nodes2;
}

int getManualEdges(){
    return Edges2;
}

ManualGraphScreen::ManualGraphScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManualGraphScreen)
{
    ui->setupUi(this);
}

ManualGraphScreen::~ManualGraphScreen()
{
    delete ui;
}

void ManualGraphScreen::paintEvent(QPaintEvent *e){
    QPainter painter(this);
    node *tempNode = nodesArrayManual;

    // Background.
    QBrush brush = QBrush(Qt::black);
    painter.fillRect(0,0,1920,1080, brush);

    // Painting edges.
    edge *tempEdge = edgesArrayManual;

    int tempEdges = Edges2;
    while(tempEdges >= 0){
        painter.setPen(Qt::blue);
        painter.drawLine(tempEdge->x1 + 10, tempEdge->y1 + 10, tempEdge->x2 + 10, tempEdge->y2 + 10);

        // Weight.
        //if(getWeights() == true){
        painter.setPen(Qt::white);
        QString weight = weight.fromStdString(tempEdge->label) + "/" + weight.fromStdString(tempEdge->weight);
        painter.drawStaticText((tempEdge->x1 + tempEdge->x2) / 2, (tempEdge->y1 + tempEdge->y2) / 2, weight);
        //}

        tempEdge = tempEdge->next; // Move to next edge.

        tempEdges--;
    }

    // Painting nodes.
    painter.setBrush(QBrush(Qt::green));
    while(true){
        painter.drawEllipse(tempNode->x, tempNode->y, 20, 20);

        // Label
        //if(getLabels() == true){
        painter.setPen(Qt::black);
        QString label = label.fromStdString(tempNode->label);
        if(label.length() == 1)
            painter.drawStaticText(tempNode->x + 6, tempNode->y + 2, label);
        else
            painter.drawStaticText(tempNode->x + 2, tempNode->y + 2, label);
        //}

        if(tempNode->next == NULL) break;

        tempNode = tempNode->next; // Move to next node.
    }

    // Painting directions.
    //if(getDirections() == true){
    tempEdge = edgesArrayManual;
    painter.setPen(Qt::white);
    painter.setBrush(QBrush(Qt::red));
    while(tempEdges >= 0){
        // Direction.
        painter.drawEllipse(tempEdge->x2, tempEdge->y2, 10, 10);

        tempEdge = tempEdge->next; // Move to next edge.

        tempEdges--;
    }
    //}

    brush = QBrush(Qt::black);
    painter.fillRect(0,0,1920,28, brush);
    painter.fillRect(0,0,18,1080, brush);
}
