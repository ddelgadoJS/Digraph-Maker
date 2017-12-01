#include "algorithmsmenu.h"
#include "ui_algorithmsmenu.h"

#include "dijkstrainitial.h"
#include "priminitial.h"
#include "kruskal.h"
#include "testfilegraph.h"
#include "manualgraphscreen.h"

#include <QMessageBox>

AlgorithmsMenu::AlgorithmsMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlgorithmsMenu)
{
    ui->setupUi(this);
}

AlgorithmsMenu::~AlgorithmsMenu()
{
    delete ui;
}

void AlgorithmsMenu::on_dijkstra_clicked()
{
    edge *tempEdge = new edge();
    int tempEdges = 0;

    if(getManualGraph()) {
        tempEdges = getManualEdges();
        tempEdge = getEdgesArrayManual();

    }else {
        tempEdges = getAutoEdges();
        tempEdge = getAutoEdgesArray();
    }

    if(tempEdge->weight.length() == 0){
        QMessageBox msgBox;
        msgBox.setText("A este grafo no se le aplicar el algoritmo Dijkstra.");
        msgBox.exec();
        return;
    }

    DijkstraInitial *DijkstraW = new DijkstraInitial(this);
    DijkstraW->setModal(true);
    DijkstraW->show();
}

void AlgorithmsMenu::on_prim_clicked()
{
    edge *tempEdge = new edge();
    int tempEdges = 0;

    if(getManualGraph()) {
        tempEdges = getManualEdges();
        tempEdge = getEdgesArrayManual();

    }else {
        tempEdges = getAutoEdges();
        tempEdge = getAutoEdgesArray();
    }

    if(tempEdge->weight.length() == 0){
        QMessageBox msgBox;
        msgBox.setText("A este grafo no se le aplicar el algoritmo Dijkstra.");
        msgBox.exec();
        return;
    }

    PrimInitial *PrimW = new PrimInitial(this);
    PrimW->setModal(true);
    PrimW->show();
}

void AlgorithmsMenu::on_kruskal_clicked()
{
    edge *tempEdge = new edge();
    int tempEdges = 0;

    if(getManualGraph()) {
        tempEdges = getManualEdges();
        tempEdge = getEdgesArrayManual();

    }else {
        tempEdges = getAutoEdges();
        tempEdge = getAutoEdgesArray();
    }

    if(tempEdge->weight.length() == 0){
        QMessageBox msgBox;
        msgBox.setText("A este grafo no se le aplicar el algoritmo Kruskal.");
        msgBox.exec();
        return;
    }

    Kruskal*PrimW = new Kruskal(this);
    PrimW->setModal(true);
    PrimW->show();
}
