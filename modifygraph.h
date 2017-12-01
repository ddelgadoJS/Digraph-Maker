#ifndef MODIFYGRAPH_H
#define MODIFYGRAPH_H

#include <QDialog>

namespace Ui {
class ModifyGraph;
}

class ModifyGraph : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyGraph(QWidget *parent = 0);
    ~ModifyGraph();

private slots:
    void on_addNode_clicked();

    void on_addEdge_clicked();

    void on_modifyEdge_clicked();

    void on_removeNode_clicked();

    void on_removeEdge_clicked();

private:
    Ui::ModifyGraph *ui;
};

#endif // MODIFYGRAPH_H
