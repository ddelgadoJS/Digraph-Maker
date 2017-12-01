#include "modifiedgraphshow.h"
#include "ui_modifiedgraphshow.h"
//Pelo Rules(que ahco!)
#include "testfilegraph.h"
#include "manualgraphscreen.h"

node *nodesArray3;
edge *edgesArray3;
int Nodes3, Edges3;

ModifiedGraphShow::ModifiedGraphShow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifiedGraphShow)
{
    ui->setupUi(this);

    bool auto_manualGraph; // false = manual, true = auto.

    if(getManualGraph()) auto_manualGraph = false;
    else auto_manualGraph = true;

    if(auto_manualGraph){ // Automatic graph.
        nodesArray3 = getAutoNodesArray();
        edgesArray3 = getAutoEdgesArray();
        Nodes3 = getAutoNodes();
        Edges3 = getAutoEdges();
    }else{
        nodesArray3 = getNodesArrayManual();
        edgesArray3 = getEdgesArrayManual();
        Nodes3 = getManualNodes();
        Edges3 = getManualEdges();
    }
}

ModifiedGraphShow::~ModifiedGraphShow()
{
    delete ui;
}

void ModifiedGraphShow::paintEvent(QPaintEvent *e){
    QPainter painter(this);
    node *tempNode = nodesArray3;

    // Background.
    QBrush brush = QBrush(Qt::black);
    painter.fillRect(0,0,1920,1080, brush);

    // Painting edges.
    edge *tempEdge = edgesArray3;

    int tempEdges = Edges3;
    while(tempEdges >= 0){
        painter.setPen(Qt::blue);
        painter.drawLine(tempEdge->x1 + 10, tempEdge->y1 + 10, tempEdge->x2 + 10, tempEdge->y2 + 10);

        painter.setPen(Qt::white);
        QString weight = weight.fromStdString(tempEdge->label) + "/" + weight.fromStdString(tempEdge->weight);
        painter.drawStaticText((tempEdge->x1 + tempEdge->x2) / 2, (tempEdge->y1 + tempEdge->y2) / 2, weight);


        tempEdge = tempEdge->next; // Move to next edge.

        tempEdges--;
    }

    // Painting nodes.
    painter.setBrush(QBrush(Qt::green));
    while(true){
        painter.drawEllipse(tempNode->x, tempNode->y, 20, 20);

        painter.setPen(Qt::black);
        QString label = label.fromStdString(tempNode->label);
        if(label.length() == 1)
            painter.drawStaticText(tempNode->x + 6, tempNode->y + 2, label);
        else
            painter.drawStaticText(tempNode->x + 2, tempNode->y + 2, label);


        if(tempNode->next == NULL) break;

        tempNode = tempNode->next; // Move to next node.
    }

    // Painting directions.
    /*if(getDirections() == true){
        tempEdge = edgesArray;
        painter.setPen(Qt::white);
        painter.setBrush(QBrush(Qt::red));
        while(tempEdges >= 0){
            // Direction.
            painter.drawEllipse(tempEdge->x2, tempEdge->y2, 10, 10);

            tempEdge = tempEdge->next; // Move to next edge.

            tempEdges--;
        }
    }*/

    brush = QBrush(Qt::black);
    painter.fillRect(0,0,1920,28, brush);
    painter.fillRect(0,0,18,1080, brush);
}
