#include "modifyedge.h"
#include "ui_modifyedge.h"

#include "testfilegraph.h"
#include "manualgraphscreen.h"
#include "modifiedgraphshow.h"

#include <QMessageBox>

modifyEdge::modifyEdge(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modifyEdge)
{
    ui->setupUi(this);



    bool auto_manualGraph; // false = manual, true = auto.

    edge *tempEdge = new edge();
    int tempEdges = 0;

    if(getManualGraph()) {
        auto_manualGraph = false;
        tempEdges = getManualEdges();
        tempEdge = getEdgesArrayManual();

    }
    else {
        auto_manualGraph = true;
        tempEdges = getAutoEdges();
        tempEdge = getAutoEdgesArray();
    }

    // Edges:
    QString label3;
    while(tempEdges >= 0){

        string from = tempEdge->from;
        string to = tempEdge->to;
        string label = tempEdge->label;
        string weight = tempEdge->weight;

        QString from2 = QString::fromStdString(from);
        QString to2 = QString::fromStdString(to);
        QString label2 = QString::fromStdString(label);
        QString weight2 = QString::fromStdString(weight);

        ui->edges->appendPlainText(from2 + ">" + to2 + ". Label: " + label2 + ". Peso: " + weight2 + ".");

        tempEdge = tempEdge->next;

        tempEdges--;
    }
}

modifyEdge::~modifyEdge()
{
    delete ui;
}

void modifyEdge::on_next_clicked()
{
    if(((ui->from->text().isEmpty() == true) & (ui->to->text().isEmpty() == false)) ||
            ((ui->from->text().isEmpty() == false) & (ui->to->text().isEmpty() == true)) ||
            ((ui->from->text().isEmpty() == true) || (ui->to->text().isEmpty() == true))){
        QMessageBox msgBox;
        msgBox.setText("Campos de Destino y Origen deben estar completos.");
        msgBox.exec();
        return;
    }

    QString from = ui->from->text();
    QString to = ui->to->text();
    QString label = ui->label->text();
    QString weight = ui->weight->text();

    string from2 = from.toStdString();
    string to2 = to.toStdString();
    string label2 = label.toStdString();
    string weight2 = weight.toStdString();

    if(getManualGraph()) { // Manual.
        edge *tempEdge = getEdgesArrayManual();
        int tempEdges = getManualEdges();

        if((tempEdge->weight.length() > 0) & (weight2.length() == 0)){
            QMessageBox msgBox;
            msgBox.setText("Debe agregar peso para este arco.");
            msgBox.exec();
            return;
        }

        while(tempEdges >= 0){
            if((tempEdge->from == from2) & (tempEdge->to == to2)){
                tempEdge->label = label2;
                tempEdge->weight = weight2;

                QMessageBox msgBox;
                msgBox.setText("Arco modificado.");
                msgBox.exec();
                break;
            }

            tempEdge = tempEdge->next;
            tempEdges--;

            if(tempEdges < 0){
                QMessageBox msgBox;
                msgBox.setText("Arco no encontrado.");
                msgBox.exec();
                return;
            }
        }

    }
    else {
        edge *tempEdge = getAutoEdgesArray();
        int tempEdges = getAutoEdges();

        if((tempEdge->weight.length() > 0) & (weight2.length() == 0)){
            QMessageBox msgBox;
            msgBox.setText("Debe agregar peso para este arco.");
            msgBox.exec();
            return;
        }

        while(tempEdges >= 0){
            if((tempEdge->from == from2) & (tempEdge->to == to2)){
                tempEdge->label = label2;
                tempEdge->weight = weight2;

                QMessageBox msgBox;
                msgBox.setText("Arco modificado.");
                msgBox.exec();
                break;
            }

            tempEdge = tempEdge->next;
            tempEdges--;

            if(tempEdges < 0){
                QMessageBox msgBox;
                msgBox.setText("Arco no encontrado.");
                msgBox.exec();
                return;
            }
        }
    }

    ui->from->setText("");
    ui->to->setText("");
    ui->label->setText("");
    ui->weight->setText("");
}

void modifyEdge::on_finish_clicked()
{
    if(((ui->from->text().isEmpty() == true) & (ui->to->text().isEmpty() == false)) ||
            ((ui->from->text().isEmpty() == false) & (ui->to->text().isEmpty() == true)) ||
            ((ui->from->text().isEmpty() == true) || (ui->to->text().isEmpty() == true))){
        QMessageBox msgBox;
        msgBox.setText("Campos de Destino y Origen deben estar completos.");
        msgBox.exec();
        return;
    }

    if(ui->from->text().isEmpty() & ui->to->text().isEmpty()){
        ModifiedGraphShow *ModifyGraphW = new ModifiedGraphShow(this);
        ModifyGraphW->setModal(true);
        ModifyGraphW->show();
        this->hide();
        return;
    }

    QString from = ui->from->text();
    QString to = ui->to->text();
    QString label = ui->label->text();
    QString weight = ui->weight->text();

    string from2 = from.toStdString();
    string to2 = to.toStdString();
    string label2 = label.toStdString();
    string weight2 = weight.toStdString();

    if(getManualGraph()) { // Manual.
        edge *tempEdge = getEdgesArrayManual();
        int tempEdges = getManualEdges();

        if((tempEdge->weight.length() > 0) & (weight2.length() == 0)){
            QMessageBox msgBox;
            msgBox.setText("Debe agregar peso para este arco.");
            msgBox.exec();
            return;
        }

        while(tempEdges >= 0){
            if((tempEdge->from == from2) & (tempEdge->to == to2)){
                tempEdge->label = label2;
                tempEdge->weight = weight2;

                QMessageBox msgBox;
                msgBox.setText("Arco modificado.");
                msgBox.exec();
                break;
            }

            tempEdge = tempEdge->next;
            tempEdges--;

            if(tempEdges < 0){
                QMessageBox msgBox;
                msgBox.setText("Arco no encontrado.");
                msgBox.exec();
                return;
            }
        }

    }
    else {
        edge *tempEdge = getAutoEdgesArray();
        int tempEdges = getAutoEdges();

        if((tempEdge->weight.length() > 0) & (weight2.length() == 0)){
            QMessageBox msgBox;
            msgBox.setText("Debe agregar peso para este arco.");
            msgBox.exec();
            return;
        }

        while(tempEdges >= 0){
            if((tempEdge->from == from2) & (tempEdge->to == to2)){
                tempEdge->label = label2;
                tempEdge->weight = weight2;

                QMessageBox msgBox;
                msgBox.setText("Arco modificado.");
                msgBox.exec();
                break;
            }

            tempEdge = tempEdge->next;
            tempEdges--;

            if(tempEdges < 0){
                QMessageBox msgBox;
                msgBox.setText("Arco no encontrado.");
                msgBox.exec();
                return;
            }
        }
    }

    ui->from->setText("");
    ui->to->setText("");
    ui->label->setText("");
    ui->weight->setText("");

    ModifiedGraphShow *ModifyGraphW = new ModifiedGraphShow(this);
    ModifyGraphW->setModal(true);
    ModifyGraphW->show();
}
