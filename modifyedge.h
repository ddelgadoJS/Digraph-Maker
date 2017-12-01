#ifndef MODIFYEDGE_H
#define MODIFYEDGE_H

#include <QDialog>

namespace Ui {
class modifyEdge;
}

class modifyEdge : public QDialog
{
    Q_OBJECT

public:
    explicit modifyEdge(QWidget *parent = 0);
    ~modifyEdge();

private slots:
    void on_next_clicked();

    void on_finish_clicked();

private:
    Ui::modifyEdge *ui;
};

#endif // MODIFYEDGE_H
