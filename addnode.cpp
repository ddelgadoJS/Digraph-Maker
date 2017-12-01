#include "addnode.h"
#include "ui_addnode.h"

#include "testfilegraph.h"
#include "modifiedgraphshow.h"
#include "manualgraphscreen.h"

#include <QMessageBox>

addNode::addNode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addNode)
{
    ui->setupUi(this);
}

addNode::~addNode()
{
    delete ui;
}

void addNode::on_add_clicked()
{
    bool auto_manualGraph; // false = manual, true = auto.

    if(getManualGraph()) auto_manualGraph = false;
    else auto_manualGraph = true;

    if(ui->quantity->text().isEmpty()){
        QMessageBox msgBox;
        msgBox.setText("Ingrese cantidad de nodos que desea.");
        msgBox.exec();
        return;
    }

    QString quantity = ui->quantity->text();
    int quantity2 = quantity.toInt();

    if(auto_manualGraph){ // Automatic graph.
        addAutoNodes(quantity2);
        ModifiedGraphShow *ModifyGraphW = new ModifiedGraphShow(this);
        ModifyGraphW->setModal(true);
        ModifyGraphW->show();
    }else{
        addManualNodes(quantity2);
        ModifiedGraphShow *ModifyGraphW = new ModifiedGraphShow(this);
        ModifyGraphW->setModal(true);
        ModifyGraphW->show();
    }
    this->hide();
}
