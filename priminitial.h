#ifndef PRIMINITIAL_H
#define PRIMINITIAL_H

#include <QDialog>

namespace Ui {
class PrimInitial;
}

class PrimInitial : public QDialog
{
    Q_OBJECT

public:
    explicit PrimInitial(QWidget *parent = 0);
    ~PrimInitial();

private slots:
    void on_execute_clicked();

private:
    Ui::PrimInitial *ui;
};

#endif // PRIMINITIAL_H
