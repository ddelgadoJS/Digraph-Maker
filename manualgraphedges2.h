#ifndef MANUALGRAPHEDGES2_H
#define MANUALGRAPHEDGES2_H

#include <QDialog>

namespace Ui {
class ManualGraphEdges2;
}

class ManualGraphEdges2 : public QDialog
{
    Q_OBJECT

public:
    explicit ManualGraphEdges2(QWidget *parent = 0);
    ~ManualGraphEdges2();

private slots:
    void on_next_clicked();

    void on_finish_clicked();

private:
    Ui::ManualGraphEdges2 *ui;
};

#endif // MANUALGRAPHEDGES2_H
