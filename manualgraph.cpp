#include "manualgraph.h"
#include "ui_manualgraph.h"

#include "manualgraphedges2.h"
#include "testfilegraph.h"
#include "manualgraphscreen.h"

bool Weights = false;

bool getWeightCB(){
    return Weights;
}

ManualGraph::ManualGraph(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManualGraph)
{
    ui->setupUi(this);
}

ManualGraph::~ManualGraph()
{
    delete ui;
}

void ManualGraph::on_cont_clicked()
{
    setManualGraph();

    if(ui->weights->isChecked()) Weights = true;
    else Weights = false;

    QString nodes = ui->nodesTXT->text();
    int nodes2 = nodes.toInt();
    createManualNodes(nodes2);

    ManualGraphEdges2 *manualGraphEdges = new ManualGraphEdges2(this);
    manualGraphEdges->setModal(true);
    manualGraphEdges->show();
    this->hide();
}
