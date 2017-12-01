#ifndef PRIM_H
#define PRIM_H

#include <QDialog>

namespace Ui {
class Prim;
}

class Prim : public QDialog
{
    Q_OBJECT

public:
    explicit Prim(QWidget *parent = 0);
    ~Prim();

private:
    Ui::Prim *ui;
};

#endif // PRIM_H
