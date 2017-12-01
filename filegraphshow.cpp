#include "filegraphshow.h"
#include "ui_filegraphshow.h"

#include "testfilegraph.h"
#include "manualgraphscreen.h"

node *nodesArrayFile;
edge *edgesArrayFile;
int NodeFile, EdgeFile;
int tmp = -1;
bool first1 = true;

FileGraphShow::FileGraphShow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileGraphShow)
{
    ui->setupUi(this);

    // Load
    QString qsLine;
    string sLine, nodeLabel, tempSline, posx, posy;

    QFile file("/home/delgados/Desktop/ED/Repositorio Tareas/Tareas_ED/Proyecto_2/Grafos/Test_Nodes2.txt");
    if(file.open(QIODevice::ReadOnly)){
        QTextStream in(&file);
        while(!in.atEnd()){
            qsLine = in.readLine();
            sLine = qsLine.toStdString();
            if(sLine == "//") break;
            int tempos = sLine.find(",");
            nodeLabel = sLine.substr(0,tempos);
            tempSline = sLine.substr(tempos+1);

            tempos = tempSline.find(".");
            posx = tempSline.substr(0, tempos);
            tempSline = tempSline.substr(tempos+1);

            tempos = tempSline.find(";");
            posy = tempSline.substr(0,tempos);

            //setPosX(posx2, posy2, first1);

            if(tmp == -1){
                first1 = false;
                tmp = 0;
            }
        }
    }
    file.close();
}

FileGraphShow::~FileGraphShow()
{
    delete ui;
}

void FileGraphShow::paintEvent(QPaintEvent *e){

    QPainter painter(this);
    node *tempNode;
    int tempEdges;
    edge *tempEdge;


    bool auto_manualGraph; // false = manual, true = auto.

    if(getManualGraph()) auto_manualGraph = false;
    else auto_manualGraph = true;

    if(auto_manualGraph){ // Automatic graph.
        tempNode = getAutoNodesArray();
        tempEdge = getAutoEdgesArray();
        tempEdges = getAutoEdges();
    }else{
        tempNode = getNodesArrayManual();
        tempEdge = getEdgesArrayManual();
        tempEdges = getManualEdges();
    }



    // Painting graph



    // Background.
    QBrush brush = QBrush(Qt::black);
    painter.fillRect(0,0,1920,1080, brush);

    // Painting edges.

    while(true){
        painter.setPen(Qt::blue);
        painter.drawLine(tempEdge->x1 + 10, tempEdge->y1 + 10, tempEdge->x2 + 10, tempEdge->y2 + 10);

        // Weight.

            painter.setPen(Qt::white);
            QString weight = weight.fromStdString(tempEdge->weight);
            painter.drawStaticText((tempEdge->x1 + tempEdge->x2) / 2, (tempEdge->y1 + tempEdge->y2) / 2, weight);

            if(tempEdge->next == NULL) break;

        tempEdge = tempEdge->next; // Move to next edge.

    }

    // Painting nodes.
    painter.setBrush(QBrush(Qt::green));
    while(true){
        painter.drawEllipse(tempNode->x, tempNode->y, 20, 20);

        // Label
            painter.setPen(Qt::black);
            QString label = label.fromStdString(tempNode->label);
            if(label.length() == 1)
                painter.drawStaticText(tempNode->x + 6, tempNode->y + 2, label);
            else
                painter.drawStaticText(tempNode->x + 2, tempNode->y + 2, label);

        if(tempNode->next == NULL) break;

        tempNode = tempNode->next; // Move to next node.
    }

    brush = QBrush(Qt::black);
    painter.fillRect(0,0,1920,28, brush);
    painter.fillRect(0,0,18,1080, brush);
}
