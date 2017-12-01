#ifndef DIJKSTRAINITIAL_H
#define DIJKSTRAINITIAL_H

#include <QDialog>

int getInitialDijkstra();

namespace Ui {
class DijkstraInitial;
}

class DijkstraInitial : public QDialog
{
    Q_OBJECT

public:
    explicit DijkstraInitial(QWidget *parent = 0);
    ~DijkstraInitial();

private slots:
    void on_execute_clicked();

private:
    Ui::DijkstraInitial *ui;
};

#endif // DIJKSTRAINITIAL_H
