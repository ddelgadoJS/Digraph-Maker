#include "priminitial.h"
#include "ui_priminitial.h"

#include "testfilegraph.h"
#include "manualgraphscreen.h"
#include "prim.h"

int initialPrim = 0;

int getInitialPrim(){
    return initialPrim;
}

PrimInitial::PrimInitial(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrimInitial)
{
    ui->setupUi(this);

    int tempNodes;
    node *tempNode;
    bool auto_manualGraph;

    if(getManualGraph()) auto_manualGraph = false;
    else auto_manualGraph = true;

    if(auto_manualGraph){ // Automatic graph.
        tempNode = getAutoNodesArray();
        tempNodes = getAutoNodes();
    }else{
        tempNode = getNodesArrayManual();
        tempNodes = getManualNodes();
    }

    // Nodes:
    QString label3;
    while(tempNodes >= 0){

        string label = tempNode->label;

        QString label2 = QString::fromStdString(label);

        if(tempNodes == 0) label3 += label2 + ".";
        else label3 += label2 + ", ";

        tempNode = tempNode->next;

        tempNodes--;
    }
    if(auto_manualGraph) setNodesXY(); // Setting values for X & Y.
    else setManualNodesXY();
    ui->nodes->appendPlainText(label3);
}

PrimInitial::~PrimInitial()
{
    delete ui;
}

void PrimInitial::on_execute_clicked()
{
    QString initialQ = ui->initial->text();
    initialPrim = initialQ.toInt();

    Prim *PrimW = new Prim(this);
    PrimW->setModal(true);
    PrimW->show();
}
