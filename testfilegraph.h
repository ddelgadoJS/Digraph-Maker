#ifndef TESTFILEGRAPH_H
#define TESTFILEGRAPH_H

#include <QDialog>

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <iostream>
#include <string>
using namespace std;

// Classes
class node {
public :
    string label;
    int x = 0;
    int y = 0;
    node *next;
    node *prior;
};

class edge {
public:
    string from, to, weight, label;
    int x1, y1, x2, y2;
    edge *next;
    edge *prior;
};

class position{
public :
    int x = 0;
    int y = 0;
    position *next;
    position *prior;
};

class position_edge{
public:
    int x1, y1, x2, y2;
    position_edge *next;
    position_edge *prior;
};

// Functions
node* getAutoNodesArray();
edge* getAutoEdgesArray();
int getAutoNodes();
int getAutoEdges();
bool getAutoGraph();
void setAutoGraph();
bool getManualGraph();
void setManualGraph();
void setNodesXY();
void setEdgesXY();
void createEdge(string, string, string, string, bool);
void createEdge(string, string, string, bool);
void addAutoNodes(int);
void addAutoEdge(string, string, string, string);
void deleteAutoNode(string);
void printEdges();
void deleteAutoEdge(string, string);

void setPosX(int, int, bool);

namespace Ui {
class testFileGraph;
}

class testFileGraph : public QDialog
{
    Q_OBJECT

public:
    explicit testFileGraph(QWidget *parent = 0);
    ~testFileGraph();

private:
    Ui::testFileGraph *ui;

protected:
    void paintEvent(QPaintEvent *e);
};

#endif // TESTFILEGRAPH_H
