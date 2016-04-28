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
    void makePlot();

    void on_pushButton_Refresh_released();

    double convertPercent(int total, int convert);

    void on_checkBox_clicked(bool checked);

    void setDefaults();

    void on_pushButton_add_prospect_clicked();

    void on_pushButton_add_pie_clicked();

    void on_pushButton_add_fli_clicked();

    void on_pushButton_add_pi_clicked();

    void on_pushButton_add_ncc_clicked();

    void refreshGraph();

    void on_pushButton_sub_prospect_clicked();

    void on_pushButton_sub_pie_clicked();

    void on_pushButton_sub_fli_clicked();

    void on_pushButton_sub_pi_clicked();

    void on_pushButton_sub_ncc_clicked();

    void on_doubleSpinBox_theoretical_prospect_editingFinished();

    void on_doubleSpinBox_theoretical_pie_editingFinished();

    void on_doubleSpinBox_theoretical_fli_editingFinished();

    void on_doubleSpinBox_theoretical_pi_editingFinished();

    void on_doubleSpinBox_theoretical_ncc_editingFinished();

    void checkActualButtons();

private:
    Ui::MainWindow *ui;

    int total = 0;

    double expected_percent[5] = {0,0,0,0,0};
    double actual_percent[5] = {0,0,0,0,0};
    double theoretical_percent[5] = {0,0,0,0,0};

    int expected_total[5] = {0,0,0,0,0};
    int actual_total[5] = {0,0,0,0,0};
    int theoretical_total[5] = {0,0,0,0,0};
};

#endif // MAINWINDOW_H
