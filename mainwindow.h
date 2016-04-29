#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>


namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    //Module Event Calls

    //     Double Spin Boxes - Theoretical
    void on_doubleSpinBox_theoretical_prospect_editingFinished();
    void on_doubleSpinBox_theoretical_pie_editingFinished();
    void on_doubleSpinBox_theoretical_fli_editingFinished();
    void on_doubleSpinBox_theoretical_pi_editingFinished();
    void on_doubleSpinBox_theoretical_ncc_editingFinished();

    //     Double Spin Boxes - Expected
    void on_doubleSpinBox_expected_prospect_editingFinished();
    void on_doubleSpinBox_expected_pie_editingFinished();
    void on_doubleSpinBox_expected_fli_editingFinished();
    void on_doubleSpinBox_expected_pi_editingFinished();
    void on_doubleSpinBox_expected_ncc_editingFinished();

    //    Push Buttons  - Subtract From Actual
    void on_pushButton_sub_prospect_clicked();
    void on_pushButton_sub_pie_clicked();
    void on_pushButton_sub_fli_clicked();
    void on_pushButton_sub_pi_clicked();
    void on_pushButton_sub_ncc_clicked();

    //    Push Buttons  - Add to Actual
    void on_pushButton_add_prospect_clicked();
    void on_pushButton_add_pie_clicked();
    void on_pushButton_add_fli_clicked();
    void on_pushButton_add_pi_clicked();
    void on_pushButton_add_ncc_clicked();

    //Other
    void on_checkBox_clicked(bool checked);
    void on_pushButton_Refresh_released();
    void closeEvent (QCloseEvent *event);
    void makePlot();
    double convertPercent(int total, double convert);
    void setDefaults();
    void refreshGraph();
    void checkActualButtons();

    //Save and Load Data
    void saveData();
    void loadData();
    void on_pushButton_save_clicked();

private:
    Ui::MainWindow *ui;

    double expected_percent[5] = {100,90,85,70,60};
    //double actual_percent[5] = {0,0,0,0,0};
    double theoretical_percent[5] = {0,0,0,0,0};

    int expected_total[5] = {0,0,0,0,0};
    int actual_total[5] = {0,0,0,0,0};
    int theoretical_total[5] = {0,0,0,0,0};
};

#endif // MAINWINDOW_H
