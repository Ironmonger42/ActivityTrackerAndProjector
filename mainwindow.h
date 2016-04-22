#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void makePlot(int prospect_Param, int pie_Param, int fli_Param, int pi_Param, int ncc_Param);

    void on_pushButton_Refresh_released();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
