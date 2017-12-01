#include "deleteedge.h"
#include "ui_deleteedge.h"

#include "testfilegraph.h"
#include "manualgraphscreen.h"

#include "modifiedgraphshow.h"

#include <QMessageBox>

DeleteEdge::DeleteEdge(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteEdge)
{
    ui->setupUi(this);
}

DeleteEdge::~DeleteEdge()
{
    delete ui;
}

void DeleteEdge::on_delete_2_clicked()
{
    bool auto_manualGraph; // false = manual, true = auto.

    if(getManualGraph()) auto_manualGraph = false;
    else auto_manualGraph = true;

    if((ui->from->text().isEmpty()) || (ui->to->text().isEmpty())){
        QMessageBox msgBox;
        msgBox.setText("Ingrese arco a eliminar.");
        msgBox.exec();
        return;
    }

    QString from = ui->from->text();
    string from2 = from.toStdString();

    QString to = ui->to->text();
    string to2 = to.toStdString();

    if(auto_manualGraph){ // Automatic graph.
        deleteAutoEdge(from2, to2);
        ModifiedGraphShow *ModifyGraphW = new ModifiedGraphShow(this);
        ModifyGraphW->setModal(true);
        ModifyGraphW->show();
    }else{
        deleteManualEdge(from2, to2);
        ModifiedGraphShow *ModifyGraphW = new ModifiedGraphShow(this);
        ModifyGraphW->setModal(true);
        ModifyGraphW->show();
    }
}
