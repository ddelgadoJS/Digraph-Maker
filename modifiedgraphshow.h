#ifndef MODIFIEDGRAPHSHOW_H
#define MODIFIEDGRAPHSHOW_H

#include <QDialog>

namespace Ui {
class ModifiedGraphShow;
}

class ModifiedGraphShow : public QDialog
{
    Q_OBJECT

public:
    explicit ModifiedGraphShow(QWidget *parent = 0);
    ~ModifiedGraphShow();

private:
    Ui::ModifiedGraphShow *ui;

protected:
    void paintEvent(QPaintEvent *e);
};

#endif // MODIFIEDGRAPHSHOW_H
