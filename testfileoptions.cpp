#include "testfileoptions.h"
#include "ui_testfileoptions.h"

#include "testfilegraph.h"

bool graphLabels = false;
bool graphWeights = false;
bool graphDirections = false;

bool getLabels(){
    return graphLabels;
}
bool getWeights(){
    return graphWeights;
}
bool getDirections(){
    return graphDirections;
}

TestFileOptions::TestFileOptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestFileOptions)
{
    ui->setupUi(this);
}

TestFileOptions::~TestFileOptions()
{
    delete ui;
}

void TestFileOptions::on_cont_clicked()
{
    if(ui->labels->isChecked()) graphLabels = true;
    else graphLabels = false;
    if(ui->weights->isChecked()) graphWeights = true;
    else graphWeights = false;
    if(ui->directions->isChecked()) graphDirections = true;
    else graphDirections = false;

    setAutoGraph();

    testFileGraph *testGraph = new testFileGraph(this);
    testGraph->setModal(true);
    testGraph->show();
    this->hide();
}

void TestFileOptions::on_labels_clicked()
{
    //if(graphLabels == false) graphLabels = true;
    //else graphLabels = false;
}

void TestFileOptions::on_weights_clicked()
{
    //if(graphWeights == false) graphWeights = true;
    //else graphWeights = false;
}

void TestFileOptions::on_directions_clicked()
{
    //if(graphDirections == false) graphDirections = true;
    //else graphDirections = false;
}
