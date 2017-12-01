//#include "mainwindow.h"
//#include "testfilegraph.h"
#include "testfileoptions.h"
#include "testfilegraph.h"
#include "manualgraph.h"
#include "modifygraph.h"
#include "modifiedgraphshow.h"
#include "algorithmsmenu.h"
#include <QApplication>
#include "menu.h"
#include "ui_menu.h"
#include <QFileDialog>
#include <fstream>
#include <QMessageBox>
#include "filegraphshow.h"
#include "manualgraphscreen.h"

Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);

    // Disables buttons save and load.
    ui->save->setDisabled(true);
    ui->load->setDisabled(true);

    //this->setStyleSheet("background-image:url(/home/delgados/Desktop/ED/Repositorio Tareas/Tareas_ED/Proyecto_2/Grafos/mainBackground.jpg)");
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_testFile_clicked()
{
    if(getManualGraph()){
        QMessageBox msgBox;
        msgBox.setText("Ya existe un grafo creado :)");
        msgBox.exec();
        return;
    }

    TestFileOptions *testOptions = new TestFileOptions(this);
    testOptions->setModal(true);
    testOptions->show();
}

void Menu::on_manual_clicked()
{
    if(getManualGraph() || getAutoGraph()){
        QMessageBox msgBox;
        msgBox.setText("Ya existe un grafo creado :)");
        msgBox.exec();
        return;
    }

    ManualGraph *manualGraph = new ManualGraph(this);
    manualGraph->setModal(true);
    manualGraph->show();

    //Enable buttons save and load
    ui->save->setDisabled(false);
    ui->load->setDisabled(false);
}

void Menu::on_modify_clicked()
{
    if((getManualGraph() || getAutoGraph()) == false){
        QMessageBox msgBox;
        msgBox.setText("Debe crear un grafo previamente.");
        msgBox.exec();
        return;
    }

    ModifyGraph *ModifyGraphW = new ModifyGraph(this);
    ModifyGraphW->setModal(true);
    ModifyGraphW->show();
}

void Menu::on_showModify_clicked()
{
    if((getManualGraph() || getAutoGraph()) == false){
        QMessageBox msgBox;
        msgBox.setText("Debe crear un grafo previamente.");
        msgBox.exec();
        return;
    }
    ModifiedGraphShow *ModifyGraphW = new ModifiedGraphShow(this);
    ModifyGraphW->setModal(true);
    ModifyGraphW->show();
}

void Menu::on_algorithms_clicked()
{
    if((getManualGraph() || getAutoGraph()) == false){
        QMessageBox msgBox;
        msgBox.setText("Debe crear un grafo previamente.");
        msgBox.exec();
        return;
    }
    AlgorithmsMenu *AlgGraphW = new AlgorithmsMenu(this);
    AlgGraphW->setModal(true);
    AlgGraphW->show();
}


void Menu::on_save_clicked()
{
    ofstream write_node;

    int tmp_nodes;
    node *tmpNode;
    edge *tmpEdge;
    int tmp_edge;

    bool auto_manualGraph; // false = manual, true = auto.

    if(getManualGraph()) auto_manualGraph = false;
    else auto_manualGraph = true;

    if(auto_manualGraph){ // Automatic graph.
        tmpNode = getAutoNodesArray();
        tmp_nodes = getAutoNodes();
        tmpEdge = getAutoEdgesArray();
        tmp_edge = getAutoEdges();
    }else{
        tmpNode = getNodesArrayManual();
        tmp_nodes = getManualNodes();
        tmpEdge = getEdgesArrayManual();
        tmp_edge = getManualEdges();
    }

    write_node.open("/home/delgados/Desktop/ED/Repositorio Tareas/Tareas_ED/Proyecto_2/Grafos/Test_Nodes2.txt");
    while(tmp_nodes >= 0){
        write_node << tmpNode->label;
        write_node << ",";
        write_node << tmpNode->x;
        write_node << ".";
        write_node << tmpNode->y;
        write_node << ";";
        tmp_nodes--;
        tmpNode = tmpNode->next;
    }
    write_node << "//";
    write_node.close();

    ofstream write_edge;

    write_edge.open("/home/delgados/Desktop/ED/Repositorio Tareas/Tareas_ED/Proyecto_2/Grafos/Test_Edges.txt");

    while(tmp_edge >= 0){
        write_edge << tmpEdge->x1;
        write_edge << ",";
        write_edge << tmpEdge->y1;
        write_edge << ",";
        write_edge << tmpEdge->x2;
        write_edge << ",";
        write_edge << tmpEdge->y1;
        write_edge << ";";
        tmp_edge--;
        tmpEdge = tmpEdge->next;
    }
    write_edge << "//";
    write_edge.close();

    QMessageBox msgBox;
    msgBox.setText("Grafo guardado.");
    msgBox.exec();
}

void Menu::on_load_clicked()
{
    ModifiedGraphShow *ModifyGraphW = new ModifiedGraphShow(this);
    ModifyGraphW->setModal(true);
    ModifyGraphW->show();
}
