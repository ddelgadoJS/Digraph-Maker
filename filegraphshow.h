#ifndef FILEGRAPHSHOW_H
#define FILEGRAPHSHOW_H

#include <QDialog>

namespace Ui {
class FileGraphShow;
}

class FileGraphShow : public QDialog
{
    Q_OBJECT

public:
    explicit FileGraphShow(QWidget *parent = 0);
    ~FileGraphShow();

private:
    Ui::FileGraphShow *ui;

protected:
    void paintEvent(QPaintEvent *e);
};

#endif // FILEGRAPHSHOW_H
