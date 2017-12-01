#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <QDialog>

namespace Ui {
class Dijkstra;
}

class Dijkstra : public QDialog
{
    Q_OBJECT

public:
    explicit Dijkstra(QWidget *parent = 0);
    ~Dijkstra();

private:
    Ui::Dijkstra *ui;
};

#endif // DIJKSTRA_H
