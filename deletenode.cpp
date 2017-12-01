#include "deletenode.h"
#include "ui_deletenode.h"

#include "modifiedgraphshow.h"
#include "testfilegraph.h"
#include "manualgraphscreen.h"

#include <QMessageBox>

DeleteNode::DeleteNode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteNode)
{
    ui->setupUi(this);
}

DeleteNode::~DeleteNode()
{
    delete ui;
}

void DeleteNode::on_delete_2_clicked()
{
    bool auto_manualGraph; // false = manual, true = auto.

    if(getManualGraph()) auto_manualGraph = false;
    else auto_manualGraph = true;

    if(ui->node->text().isEmpty()){
        QMessageBox msgBox;
        msgBox.setText("Ingrese nodo a eliminar.");
        msgBox.exec();
        return;
    }

    QString node = ui->node->text();
    string node2 = node.toStdString();

    if(auto_manualGraph){ // Automatic graph.
        deleteAutoNode(node2);
        ModifiedGraphShow *ModifyGraphW = new ModifiedGraphShow(this);
        ModifyGraphW->setModal(true);
        ModifyGraphW->show();
    }else{
        deleteManualNode(node2);
        ModifiedGraphShow *ModifyGraphW = new ModifiedGraphShow(this);
        ModifyGraphW->setModal(true);
        ModifyGraphW->show();
    }
}
