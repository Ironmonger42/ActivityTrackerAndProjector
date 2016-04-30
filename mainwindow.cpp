#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSettings>
#include "qsettings.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadData();
    setDefaults();
    refreshGraph();
    MainWindow::makePlot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * makePlot()
 *
 * This function deals with creating a fully modifable bar graph based on the totals
 * of the surveys. It fully sets up the graph with plottting, the legend, and anything related
 * with the graphing.
*/
void MainWindow::makePlot()
{
     ui -> customPlot->clearPlottables();

    // create empty bar chart objects:
    QCPBars *theoretical = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    QCPBars *actual = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    QCPBars *expected = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    ui->customPlot->addPlottable(actual);
    ui->customPlot->addPlottable(expected);
    ui->customPlot->addPlottable(theoretical);

    // set names and colors:
    QPen pen;
    pen.setWidthF(1.2);

    theoretical ->setName("Personal Goal");
    pen.setColor(QColor(255, 131, 0));
    theoretical ->setPen(pen);
    theoretical ->setBrush(QColor(255, 131, 0, 50));

    actual->setName("Actual");
    pen.setColor(QColor(1, 92, 191));
    actual->setPen(pen);
    actual->setBrush(QColor(1, 92, 191, 50));

    expected->setName("Trainer Goal");
    pen.setColor(QColor(150, 222, 0));
    expected->setPen(pen);
    expected->setBrush(QColor(150, 222, 0, 50));

    // prepare x axis with labels:
    QVector<double> actual_ticks , expected_ticks, theoretical_ticks;
    QVector<QString> labels;
    actual_ticks<< 1 << 4 << 7 << 10 << 13;
    expected_ticks << 2 << 5 << 8 << 11 << 14;
    theoretical_ticks << 3 << 6 << 9 << 12 << 15;

    labels << "Prospect" << "PIE" << "FLI" << "PI" << "NCC";
    ui->customPlot->xAxis->setAutoTicks(false);
    ui->customPlot->xAxis->setAutoTickLabels(false);
    ui->customPlot->xAxis->setTickVector(actual_ticks);
    ui->customPlot->xAxis->setTickVectorLabels(labels);
    ui->customPlot->xAxis->setTickLabelRotation(50);
    ui->customPlot->xAxis->setSubTickCount(0);
    ui->customPlot->xAxis->setTickLength(0,5);
    ui->customPlot->xAxis->grid()->setVisible(true);
    ui->customPlot->xAxis->setRange(0, 16);

    // prepare y axis:
    if(actual_total[0] == 0)
        ui->customPlot->yAxis->setRange(0, 9);
    else
        ui->customPlot->yAxis->setRange(0, actual_total[0]+2);

    ui->customPlot->yAxis->setPadding(5);
    ui->customPlot->yAxis->setLabel("Total Surveys Completed");
    ui->customPlot->yAxis->grid()->setSubGridVisible(true);
    QPen gridPen;
    gridPen.setStyle(Qt::SolidLine);
    gridPen.setColor(QColor(0, 0, 0, 25));
    ui->customPlot->yAxis->grid()->setPen(gridPen);
    gridPen.setStyle(Qt::DotLine);
    ui->customPlot->yAxis->grid()->setSubGridPen(gridPen);

    // Add data points:
    QVector<double> theoreticalData, actualData, expectedData;

    theoreticalData << theoretical_total[0] << theoretical_total[1] << theoretical_total[2]<< theoretical_total[3] << theoretical_total[4];
    theoretical->setData(theoretical_ticks, theoreticalData);

    actualData << actual_total[0] << actual_total[1] << actual_total[2] << actual_total[3] << actual_total[4];
    actual->setData(actual_ticks, actualData);

    expectedData << expected_total[0] << expected_total[1] << expected_total[2] << expected_total[3] << expected_total[4];
    expected->setData(expected_ticks, expectedData);

    // setup legend:
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignRight);
    ui->customPlot->legend->setBrush(QColor(255, 255, 255, 200));
    QPen legendPen;
    legendPen.setColor(QColor(130, 130, 130, 200));
    ui->customPlot->legend->setBorderPen(legendPen);
    QFont legendFont = font();
    legendFont.setPointSize(15);
    ui->customPlot->legend->setFont(legendFont);

}


/*
 * refreshGraph()
 *
 * This is called anytime a theortcial, actual, or expected is changed.
 *It checks the actual buttons and decides weather to enable/disable buttons.
 * Loads values from double spin box theortical and double spin box expected
 * It then converts the percent into a total number and stores the theoretical total
 * and expected total in memory. The graph is then cleared and then replotted with new values.
*/
void MainWindow::refreshGraph()
{
    checkActualButtons(); // Enable/Disable Actual add/sub buttons

    //Set theoretical percent for each survey type to the value in the double spin box.
    theoretical_percent[0] = ui->doubleSpinBox_theoretical_prospect->value();
    theoretical_percent[1] = ui->doubleSpinBox_theoretical_pie->value();
    theoretical_percent[2] = ui->doubleSpinBox_theoretical_fli->value();
    theoretical_percent[3] = ui->doubleSpinBox_theoretical_pi->value();
    theoretical_percent[4] = ui->doubleSpinBox_theoretical_ncc->value();

    //Set expected percent for each survey type to the value in the double spin box.
    expected_percent[0] = ui->doubleSpinBox_expected_prospect->value();
    expected_percent[1] = ui->doubleSpinBox_expected_pie->value();
    expected_percent[2] = ui->doubleSpinBox_expected_fli->value();
    expected_percent[3] = ui->doubleSpinBox_expected_pi->value();
    expected_percent[4] = ui->doubleSpinBox_expected_ncc->value();

    //Set theoretical total for each survey type based on percentages of the other surveys.
    theoretical_total[0] = convertPercent(actual_total[0], theoretical_percent[0]);
    theoretical_total[1] = convertPercent(theoretical_total[0], theoretical_percent[1]);
    theoretical_total[2] = convertPercent(theoretical_total[1], theoretical_percent[2]);
    theoretical_total[3] = convertPercent(theoretical_total[2], theoretical_percent[3]);
    theoretical_total[4] = convertPercent(theoretical_total[3], theoretical_percent[4]);

    //Set expected total for each survey type based on percentages of the other surveys.
    expected_total[0] = convertPercent(actual_total[0], expected_percent[0]);
    expected_total[1] = convertPercent(expected_total[0], expected_percent[1]);
    expected_total[2] = convertPercent(expected_total[1], expected_percent[2]);
    expected_total[3] = convertPercent(expected_total[2], expected_percent[3]);
    expected_total[4] = convertPercent(expected_total[3], expected_percent[4]);

    MainWindow::makePlot(); //Call makePlot, which sets up the graph / plot again.
    ui -> customPlot->replot(); //replot the values that were stored in memory.
}

/*
 * on_pushButton_Refresh_released()
 *
 * This function is used when the refresh button is clicked.
 * It calls the refreshGraph() function.
 *
*/
void MainWindow::on_pushButton_Refresh_released()
{
    refreshGraph();
}


/*
 * setDefaults()
 *
 * This function sets the default expected percetage of surveys. It then puts the percentage value
 * inside the double spin box. It then refreshes the graph, and enables/disables the actual buttons based
 * on values.
*/
void MainWindow::setDefaults()
{
    ui->doubleSpinBox_expected_prospect->setValue(expected_percent[0]);
    ui->doubleSpinBox_expected_pie->setValue(expected_percent[1]);
    ui->doubleSpinBox_expected_fli->setValue(expected_percent[2]);
    ui->doubleSpinBox_expected_pi->setValue(expected_percent[3]);
    ui->doubleSpinBox_expected_ncc->setValue(expected_percent[4]);

    checkActualButtons();
}


/*
 * convertPercent(int total, double convert)
 *
 * This function takes the total number of surveys (total actual prospects) and a percentage
 * it converts the percentage to a number to be plotted on the graph.
*/
double MainWindow::convertPercent(int total, double convert)
{
    return ((double)total * convert)/100.0;
}


/*
 * on_checkBox_clicked(bool checked)
 *
 * This function controls weather the user is an Admin or a regular user.
 * When the check box is checked the bool checked is set to true and it will allow the Admin
 * to change the expected survey values. When the value is unchecked then the expected double spin box fields
 * are disabled.
*/

void MainWindow::on_checkBox_clicked(bool checked)
{
    if(checked == true) //If check box is checked. (Admin Mode)
    {
        ui->doubleSpinBox_expected_prospect->setEnabled(true); //Enable: double Spin Box Prospect
        ui->doubleSpinBox_expected_pie->setEnabled(true);//Enable: double Spin Box pie
        ui->doubleSpinBox_expected_fli->setEnabled(true);//Enable: double Spin Box fli
        ui->doubleSpinBox_expected_pi->setEnabled(true);//Enable: double Spin Box pi
        ui->doubleSpinBox_expected_ncc->setEnabled(true);//Enable: double Spin Box ncc
    }
    else //If check box is unchecked. (User Mode)
    {
        ui->doubleSpinBox_expected_prospect->setDisabled(true); //Disable: double Spin Box Prospect
        ui->doubleSpinBox_expected_pie->setDisabled(true);//Disable: double Spin Box pie
        ui->doubleSpinBox_expected_fli->setDisabled(true);//Disable: double Spin Box fli
        ui->doubleSpinBox_expected_pi->setDisabled(true);//Disable: double Spin Box pi
        ui->doubleSpinBox_expected_ncc->setDisabled(true);//Disable: double Spin Box ncc
    }
}

/*
 * The functions below are triggered by the add buttons and add a actual survey to the
 * designated survey (prospect, pie, fli, pi, or ncc).
 * Then refresh the graph to display the new infromation.
*/
void MainWindow::on_pushButton_add_prospect_clicked()
{
    actual_total[0] +=1;
    refreshGraph();
}

void MainWindow::on_pushButton_add_pie_clicked()
{
    actual_total[1] +=1;
    refreshGraph();
}

void MainWindow::on_pushButton_add_fli_clicked()
{
    actual_total[2] +=1;
    refreshGraph();
}

void MainWindow::on_pushButton_add_pi_clicked()
{
    actual_total[3] +=1;
    refreshGraph();
}

void MainWindow::on_pushButton_add_ncc_clicked()
{
    actual_total[4] +=1;
    refreshGraph();
}


/*
 * The functions below are triggered by the subtract buttons and subtract a actual survey from the
 * designated survey (prospect, pie, fli, pi, or ncc).
 * Then refresh the graph to display the new infromation.
 * These functions also subtract one from the value infront of them, FLI - 1 does FLI -1, PI -1, and NCC-1
*/
void MainWindow::on_pushButton_sub_prospect_clicked()
{
    actual_total[0] -=1;

    if(actual_total[1] > 0)
        actual_total[1] -=1;

    if(actual_total[2] > 0)
        actual_total[2] -=1;

    if(actual_total[3] > 0)
        actual_total[3] -=1;

    if(actual_total[4] > 0)
        actual_total[4] -=1;

    refreshGraph();
}

void MainWindow::on_pushButton_sub_pie_clicked()
{
    actual_total[1] -=1;

    if(actual_total[2] > 0)
        actual_total[2] -=1;

    if(actual_total[3] > 0)
        actual_total[3] -=1;

    if(actual_total[4] > 0)
        actual_total[4] -=1;

    refreshGraph();
}

void MainWindow::on_pushButton_sub_fli_clicked()
{
    actual_total[2] -=1;

    if(actual_total[3] > 0)
        actual_total[3] -=1;

    if(actual_total[4] > 0)
        actual_total[4] -=1;

    refreshGraph();
}

void MainWindow::on_pushButton_sub_pi_clicked()
{
    actual_total[3] -=1;

    if(actual_total[4] > 0)
        actual_total[4] -=1;
    refreshGraph();
}

void MainWindow::on_pushButton_sub_ncc_clicked()
{
    actual_total[4] -=1;
    refreshGraph();
}

/*
 * The functions below control the events triggered from a user finishing editing the Theortical
 * double Spin box values, which then calls the function refreshGraph() which will update the graph with the new values.
*/
void MainWindow::on_doubleSpinBox_theoretical_prospect_editingFinished()
{
    refreshGraph();
}

void MainWindow::on_doubleSpinBox_theoretical_pie_editingFinished()
{
    refreshGraph();
}

void MainWindow::on_doubleSpinBox_theoretical_fli_editingFinished()
{
    refreshGraph();
}

void MainWindow::on_doubleSpinBox_theoretical_pi_editingFinished()
{
    refreshGraph();
}

void MainWindow::on_doubleSpinBox_theoretical_ncc_editingFinished()
{
    refreshGraph();
}

/*
 * The functions below control the events triggered from a user finishing editing the expected
 * double Spin box values, which then calls the function refreshGraph() which will update the graph with the new values.
*/
void MainWindow::on_doubleSpinBox_expected_prospect_editingFinished()
{
    refreshGraph();
}

void MainWindow::on_doubleSpinBox_expected_pie_editingFinished()
{
    refreshGraph();
}

void MainWindow::on_doubleSpinBox_expected_fli_editingFinished()
{
    refreshGraph();
}

void MainWindow::on_doubleSpinBox_expected_pi_editingFinished()
{
    refreshGraph();
}

void MainWindow::on_doubleSpinBox_expected_ncc_editingFinished()
{
    refreshGraph();
}


/*
 * checkActualButtons()
 *
 * Enables and Disabled the Addition buttons and Subtraction buttons for the user controlling the actual surveys.
 *
 * This prevents the user from having more PIEs than PROSPECTS, FLIs than PIEs, etc.
 * This also prevents the user from subtracting surveys to where the value would go below zero.
 *
*/
void MainWindow::checkActualButtons()
{
    //Addition Buttons
    if(actual_total[1] + 1 > actual_total[0]) //If number of PIE + 1 is greater than Prospects
        ui->pushButton_add_pie->setDisabled(true);//Diable PIE Add Button
    else
        ui->pushButton_add_pie->setEnabled(true);//Enable PIE Add Button

    if(actual_total[2] + 1 > actual_total[1]) //If number of FLI + 1 is greater than PIE
        ui->pushButton_add_fli->setDisabled(true);// Diable FLI Add Button
    else
        ui->pushButton_add_fli->setEnabled(true);//Enable FLI Add Button

    if(actual_total[3] + 1 > actual_total[2])//If number of PI + 1 is greater than FLI
        ui->pushButton_add_pi->setDisabled(true);// Diable PI Add Button
    else
        ui->pushButton_add_pi->setEnabled(true);//Enable PI Add Button

    if(actual_total[4] + 1 > actual_total[3])//If number of NCC + 1 is greater than PI
        ui->pushButton_add_ncc->setDisabled(true);// Diable NCC Add Button
    else
        ui->pushButton_add_ncc->setEnabled(true);//Enable NCC Add Button

    //Subtraction Buttons
    if(actual_total[0] -1 < 0)// If number of Prospects -1 is less than 0
        ui->pushButton_sub_prospect->setDisabled(true); //Disable Prospect Sub Button
    else
        ui->pushButton_sub_prospect->setEnabled(true);//Enable Prospect Sub Button

    if(actual_total[1] -1 < 0)// If number of PIE -1 is less than 0
        ui->pushButton_sub_pie->setDisabled(true);//Disable PIE Sub Button
    else
        ui->pushButton_sub_pie->setEnabled(true);//Enable PIE Sub Button

    if(actual_total[2] -1 < 0)// If number of FLI -1 is less than 0
        ui->pushButton_sub_fli->setDisabled(true);//Disable FLI Sub Button
    else
        ui->pushButton_sub_fli->setEnabled(true);//Enable FLI Sub Button

    if(actual_total[3] -1 < 0)// If number of PI -1 is less than 0
        ui->pushButton_sub_pi->setDisabled(true);//Disable PI Sub Button
    else
        ui->pushButton_sub_pi->setEnabled(true);//Enable PI Sub Button

    if(actual_total[4] -1 < 0)// If number of NCC -1 is less than 0
        ui->pushButton_sub_ncc->setDisabled(true);//Disable NCC Sub Button
    else
        ui->pushButton_sub_ncc->setEnabled(true);//Enable NCC Sub Button
}


/*
 * saveData()
 *
 * This function uses Qts settings which is used to save data even after the user exits the program.
 * The only part thats important to store is the actual totals which is when the user inputs when they have
 * completed a new survey.
*/

void MainWindow::saveData()
{
    QSettings settings("TylerGeoffrey", "ActivityTracker");

    settings.setValue("actual_total_prospect", actual_total[0]);
    settings.setValue("actual_total_pie", actual_total[1]);
    settings.setValue("actual_total_fli", actual_total[2]);
    settings.setValue("actual_total_pi", actual_total[3]);
    settings.setValue("actual_total_ncc", actual_total[4]);

}

/*
 * loadData()
 *
 * Loads the actual totals for each of the survey types from memory into the program to
 * be used from a past use of the program.
*/
void MainWindow::loadData()
{
    QSettings settings("TylerGeoffrey", "ActivityTracker");

    actual_total[0] = settings.value("actual_total_prospect").toInt();
    actual_total[1] = settings.value("actual_total_pie").toInt();
    actual_total[2] = settings.value("actual_total_fli").toInt();
    actual_total[3] = settings.value("actual_total_pi").toInt();
    actual_total[4] = settings.value("actual_total_ncc").toInt();
}


/*
 * closeEvent()
 *
 * This event is called anytime the program exits, usally when the user presses the X button.
 * It calls saveData() to save the actual totals
 * Warning: Not a threat but we do not need to use *event
*/
void MainWindow::closeEvent (QCloseEvent *event)
{
    saveData();
}
