#ifndef MANUALGRAPH_H
#define MANUALGRAPH_H

#include <QDialog>

bool getWeightCB();

namespace Ui {
class ManualGraph;
}

class ManualGraph : public QDialog
{
    Q_OBJECT

public:
    explicit ManualGraph(QWidget *parent = 0);
    ~ManualGraph();

private slots:
    void on_cont_clicked();

private:
    Ui::ManualGraph *ui;
};

#endif // MANUALGRAPH_H
