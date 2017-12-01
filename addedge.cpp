#include "addedge.h"
#include "ui_addedge.h"

#include "testfilegraph.h"
#include "manualgraphscreen.h"
#include "manualgraph.h"
#include "modifiedgraphshow.h"

#include <QMessageBox>

bool auto_manualGraph; // false = manual, true = auto.

AddEdge::AddEdge(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEdge)
{
    ui->setupUi(this);

    int tempNodes;
    node *tempNode;

    if(getManualGraph()) auto_manualGraph = false;
    else auto_manualGraph = true;

    if(auto_manualGraph){ // Automatic graph.
        tempNode = getAutoNodesArray();
        tempNodes = getAutoNodes();
    }else{
        tempNode = getNodesArrayManual();
        tempNodes = getManualNodes();
    }

    // Disables weight text box.
    if(getWeightCB() == false & auto_manualGraph == false){
        ui->label_6->setDisabled(true);
        ui->weight->setDisabled(true);
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

AddEdge::~AddEdge()
{
    delete ui;
}

void AddEdge::on_next_clicked()
{
    if(((ui->from->text().isEmpty() == true) & (ui->to->text().isEmpty() == false)) ||
            ((ui->from->text().isEmpty() == false) & (ui->to->text().isEmpty() == true)) ||
            ((ui->from->text().isEmpty() == true) || (ui->to->text().isEmpty() == true))){
        QMessageBox msgBox;
        msgBox.setText("Campos de Destino y Origen deben estar completos.");
        msgBox.exec();
        return;
    }

    if(((getWeightCB() == true) & (ui->weight->text().isEmpty())) || auto_manualGraph){
        QMessageBox msgBox;
        msgBox.setText("Complete peso de arco.");
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

    bool auto_manualGraph; // false = manual, true = auto.

    if(getManualGraph()) auto_manualGraph = false;
    else auto_manualGraph = true;

    if(auto_manualGraph) addAutoEdge(from2, to2, label2, weight2);
    else addManualEdge(from2, to2, label2, weight2);

    ui->from->setText("");
    ui->to->setText("");
    ui->label->setText("");
    ui->weight->setText("");
}

void AddEdge::on_finish_clicked()
{
    if(((ui->from->text().isEmpty() == true) & (ui->to->text().isEmpty() == false)) ||
            ((ui->from->text().isEmpty() == false) & (ui->to->text().isEmpty() == true))){
        QMessageBox msgBox;
        msgBox.setText("Campos de Destino y Origen deben estar completos.");
        msgBox.exec();
        return;
    }

    if(ui->from->text().isEmpty() & ui->to->text().isEmpty()){
        ManualGraphScreen *manualScreen = new ManualGraphScreen(this);
        manualScreen->setModal(true);
        manualScreen->show();
        this->hide();
        return;
    }else if((getWeightCB() == true) & (ui->weight->text().isEmpty())){
        QMessageBox msgBox;
        msgBox.setText("Complete peso de arco.");
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

    bool auto_manualGraph; // false = manual, true = auto.

    if(getManualGraph()) auto_manualGraph = false;
    else auto_manualGraph = true;

    if(auto_manualGraph) addAutoEdge(from2, to2, label2, weight2);
    else addManualEdge(from2, to2, label2, weight2);

    ModifiedGraphShow *ModifyGraphW = new ModifiedGraphShow(this);
    ModifyGraphW->setModal(true);
    ModifyGraphW->show();
}
