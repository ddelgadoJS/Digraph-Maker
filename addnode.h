#ifndef ADDNODE_H
#define ADDNODE_H

#include <QDialog>

namespace Ui {
class addNode;
}

class addNode : public QDialog
{
    Q_OBJECT

public:
    explicit addNode(QWidget *parent = 0);
    ~addNode();

private slots:
    void on_add_clicked();

private:
    Ui::addNode *ui;
};

#endif // ADDNODE_H
