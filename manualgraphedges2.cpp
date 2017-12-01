#include "manualgraphedges2.h"
#include "ui_manualgraphedges2.h"

#include "testfilegraph.h"
#include "manualgraph.h"
#include "manualgraphscreen.h"

#include <QMessageBox>

bool first = true;

ManualGraphEdges2::ManualGraphEdges2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManualGraphEdges2)
{
    ui->setupUi(this);

    // Disables weight text box.
    if(getWeightCB() == false){
        ui->label_6->setDisabled(true);
        ui->weight->setDisabled(true);
    }

    // Nodes:
    int tempNodes = getManualNodes();
    node *tempNode = getNodesArrayManual();
    QString label3;
    while(tempNodes >= 0){

        string label = tempNode->label;

        QString label2 = QString::fromStdString(label);

        if(tempNodes == 0) label3 += label2 + ".";
        else label3 += label2 + ", ";

        tempNode = tempNode->next;

        tempNodes--;
    }
    setManualNodesXY(); // Setting values for X & Y.
    ui->nodes->appendPlainText(label3);
}

ManualGraphEdges2::~ManualGraphEdges2()
{
    delete ui;
}

void ManualGraphEdges2::on_next_clicked()
{
    if(((ui->from->text().isEmpty() == true) & (ui->to->text().isEmpty() == false)) ||
            ((ui->from->text().isEmpty() == false) & (ui->to->text().isEmpty() == true)) ||
            ((ui->from->text().isEmpty() == true) || (ui->to->text().isEmpty() == true))){
        QMessageBox msgBox;
        msgBox.setText("Campos de Destino y Origen deben estar completos.");
        msgBox.exec();
        return;
    }

    if((getWeightCB() == true) & (ui->weight->text().isEmpty())){
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

    cout << "from2, to2, label2, weight2, first: " << from2<<" "<<to2<<" "<<label2<<" "<<weight2<<" "<<first << endl;

    createManualEdge(from2, to2, label2, weight2, first);
    first = false;

    ui->from->setText("");
    ui->to->setText("");
    ui->label->setText("");
    ui->weight->setText("");
}

void ManualGraphEdges2::on_finish_clicked()
{
    if(((ui->from->text().isEmpty() == true) & (ui->to->text().isEmpty() == false)) ||
            ((ui->from->text().isEmpty() == false) & (ui->to->text().isEmpty() == true))){
        QMessageBox msgBox;
        msgBox.setText("Campos de Destino y Origen deben estar completos.");
        msgBox.exec();
        return;
    }

    if(ui->from->text().isEmpty() & ui->to->text().isEmpty()){
        setManualEdgesXY();

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

    createManualEdge(from2, to2, label2, weight2, first);
    //first = true;

    setManualEdgesXY();

    ManualGraphScreen *manualScreen = new ManualGraphScreen(this);
    manualScreen->setModal(true);
    manualScreen->show();
    this->hide();
}
