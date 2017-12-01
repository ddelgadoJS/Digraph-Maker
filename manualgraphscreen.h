#ifndef MANUALGRAPHSCREEN_H
#define MANUALGRAPHSCREEN_H

#include <QDialog>
#include "testfilegraph.h"

void addManualNodes(int);
node* getNodesArrayManual();
edge* getEdgesArrayManual();
int getManualNodes();
int getManualEdges();
void setManualEdgesXY();
void setManualNodesXY();
void addManualEdge(string, string, string, string);
void createManualEdge(string, string, string, string, bool);
void createManualNodes(int);
void printManualNodes();
bool valManualXY(int x, int y);
void printManualEdges();
void deleteManualNode(string);
void deleteManualEdge(string, string);

namespace Ui {
class ManualGraphScreen;
}

class ManualGraphScreen : public QDialog
{
    Q_OBJECT

public:
    explicit ManualGraphScreen(QWidget *parent = 0);
    ~ManualGraphScreen();

private:
    Ui::ManualGraphScreen *ui;

protected:
    void paintEvent(QPaintEvent *e);
};

#endif // MANUALGRAPHSCREEN_H
