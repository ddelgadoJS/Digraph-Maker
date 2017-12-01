#ifndef ADDEDGE_H
#define ADDEDGE_H

#include <QDialog>

namespace Ui {
class AddEdge;
}

class AddEdge : public QDialog
{
    Q_OBJECT

public:
    explicit AddEdge(QWidget *parent = 0);
    ~AddEdge();

private slots:
    void on_next_clicked();

    void on_finish_clicked();

private:
    Ui::AddEdge *ui;
};

#endif // ADDEDGE_H
