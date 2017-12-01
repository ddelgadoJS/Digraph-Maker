#ifndef DELETEEDGE_H
#define DELETEEDGE_H

#include <QDialog>

namespace Ui {
class DeleteEdge;
}

class DeleteEdge : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteEdge(QWidget *parent = 0);
    ~DeleteEdge();

private slots:
    void on_delete_2_clicked();

private:
    Ui::DeleteEdge *ui;
};

#endif // DELETEEDGE_H
