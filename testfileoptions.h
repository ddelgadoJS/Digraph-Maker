#ifndef TESTFILEOPTIONS_H
#define TESTFILEOPTIONS_H

#include <QDialog>

bool getLabels();
bool getWeights();
bool getDirections();

namespace Ui {
class TestFileOptions;
}

class TestFileOptions : public QDialog
{
    Q_OBJECT

public:
    explicit TestFileOptions(QWidget *parent = 0);
    ~TestFileOptions();

private slots:
    void on_cont_clicked();

    void on_labels_clicked();

    void on_weights_clicked();

    void on_directions_clicked();

private:
    Ui::TestFileOptions *ui;
};

#endif // TESTFILEOPTIONS_H
