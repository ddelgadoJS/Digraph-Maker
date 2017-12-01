#ifndef ALGORITHMSMENU_H
#define ALGORITHMSMENU_H

#include <QDialog>

namespace Ui {
class AlgorithmsMenu;
}

class AlgorithmsMenu : public QDialog
{
    Q_OBJECT

public:
    explicit AlgorithmsMenu(QWidget *parent = 0);
    ~AlgorithmsMenu();

private slots:
    void on_dijkstra_clicked();

    void on_prim_clicked();

    void on_kruskal_clicked();

private:
    Ui::AlgorithmsMenu *ui;
};

#endif // ALGORITHMSMENU_H
