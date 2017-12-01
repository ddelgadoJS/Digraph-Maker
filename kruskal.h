#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <QDialog>

namespace Ui {
class Kruskal;
}

class Kruskal : public QDialog
{
    Q_OBJECT

public:
    explicit Kruskal(QWidget *parent = 0);
    ~Kruskal();

private:
    Ui::Kruskal *ui;
};

#endif // KRUSKAL_H
