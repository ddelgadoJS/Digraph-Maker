#include "modifygraph.h"
#include "ui_modifygraph.h"

#include "addnode.h"
#include "addedge.h"
#include "modifyedge.h"
#include "deletenode.h"
#include "deleteedge.h"

ModifyGraph::ModifyGraph(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifyGraph)
{
    ui->setupUi(this);
}

ModifyGraph::~ModifyGraph()
{
    delete ui;
}

void ModifyGraph::on_addNode_clicked()
{
    addNode *addNodeW = new addNode(this);
    addNodeW->setModal(true);
    addNodeW->show();
}

void ModifyGraph::on_addEdge_clicked()
{
    AddEdge *addEdgeW = new AddEdge(this);
    addEdgeW->setModal(true);
    addEdgeW->show();
}

void ModifyGraph::on_modifyEdge_clicked()
{
    modifyEdge *modifyEdgeW = new modifyEdge(this);
    modifyEdgeW->setModal(true);
    modifyEdgeW->show();
}

void ModifyGraph::on_removeNode_clicked()
{
    DeleteNode *DeleteW = new DeleteNode(this);
    DeleteW->setModal(true);
    DeleteW->show();
}

void ModifyGraph::on_removeEdge_clicked()
{
    DeleteEdge *DeleteW = new DeleteEdge(this);
    DeleteW->setModal(true);
    DeleteW->show();
}
