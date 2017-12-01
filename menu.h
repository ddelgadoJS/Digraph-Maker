#ifndef MENU_H
#define MENU_H

#include <QDialog>

namespace Ui {
class Menu;
}

class Menu : public QDialog
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();

private slots:
    void on_testFile_clicked();

    void on_manual_clicked();

    void on_modify_clicked();

    void on_showModify_clicked();

    void on_algorithms_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_save_clicked();

    void on_load_clicked();

private:
    Ui::Menu *ui;
};

#endif // MENU_H
