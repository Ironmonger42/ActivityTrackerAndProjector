#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <fstream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setDefaults();

    MainWindow::makePlot();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::makePlot()
{
    // create empty bar chart objects:
    QCPBars *theoretical = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    QCPBars *actual = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    QCPBars *expected = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    ui->customPlot->addPlottable(theoretical);
    ui->customPlot->addPlottable(actual);
    ui->customPlot->addPlottable(expected);


    // set names and colors:
    QPen pen;
    pen.setWidthF(1.2);

    theoretical ->setName("Theoretical");
    pen.setColor(QColor(255, 131, 0));
    theoretical ->setPen(pen);
    theoretical ->setBrush(QColor(255, 131, 0, 50));

    actual->setName("Actual");
    pen.setColor(QColor(1, 92, 191));
    actual->setPen(pen);
    actual->setBrush(QColor(1, 92, 191, 50));

    expected->setName("Expected");
    pen.setColor(QColor(150, 222, 0));
    expected->setPen(pen);
    expected->setBrush(QColor(150, 222, 0, 70));

    // prepare x axis with country labels:
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
    if(total == 0)
    {
        ui->customPlot->yAxis->setRange(0, 5);
    }
    else
    {
        ui->customPlot->yAxis->setRange(0, total+1);
    }
    ui->customPlot->yAxis->setPadding(5); // a bit more space to the left border
    ui->customPlot->yAxis->setLabel("Total Surveys Completed");
    ui->customPlot->yAxis->grid()->setSubGridVisible(true);
    QPen gridPen;
    gridPen.setStyle(Qt::SolidLine);
    gridPen.setColor(QColor(0, 0, 0, 25));
    ui->customPlot->yAxis->grid()->setPen(gridPen);
    gridPen.setStyle(Qt::DotLine);
    ui->customPlot->yAxis->grid()->setSubGridPen(gridPen);

    // Add data:
    QVector<double> theoreticalData, actualData, expectedData;

    theoreticalData << theoretical_percent[0] << theoretical_percent[1] << theoretical_percent[2]<< theoretical_percent[3] << theoretical_percent[4];
    theoretical->setData(theoretical_ticks, theoreticalData);

    actualData << actual_total[0] << actual_total[1] << actual_total[2] << actual_total[3] << actual_total[4];
    actual->setData(actual_ticks, actualData);

    expectedData << expected_percent[0] << expected_percent[1] << expected_percent[2] << expected_percent[3] << expected_percent[4];
    expected->setData(expected_ticks, expectedData);

    // setup legend:
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignRight);
    ui->customPlot->legend->setBrush(QColor(255, 255, 255, 200));
    QPen legendPen;
    legendPen.setColor(QColor(130, 130, 130, 200));
    ui->customPlot->legend->setBorderPen(legendPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->customPlot->legend->setFont(legendFont);
    //ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}


void MainWindow::refreshGraph()
{
    checkActualButtons();

    theoretical_percent[0] = convertPercent(total, (ui->doubleSpinBox_theoretical_prospect->value()));
    theoretical_percent[1] = convertPercent(theoretical_percent[0], (ui->doubleSpinBox_theoretical_pie->value()));
    theoretical_percent[2] = convertPercent(theoretical_percent[1], (ui->doubleSpinBox_theoretical_fli->value()));
    theoretical_percent[3] = convertPercent(theoretical_percent[2], (ui->doubleSpinBox_theoretical_pi->value()));
    theoretical_percent[4] = convertPercent(theoretical_percent[3], (ui->doubleSpinBox_theoretical_ncc->value()));

    expected_percent[0] = convertPercent(total, (ui->doubleSpinBox_expected_prospect->value()));
    expected_percent[1] = convertPercent(expected_percent[0], (ui->doubleSpinBox_expected_pie->value()));
    expected_percent[2] = convertPercent(expected_percent[1], (ui->doubleSpinBox_expected_fli->value()));
    expected_percent[3] = convertPercent(expected_percent[2], (ui->doubleSpinBox_expected_pi->value()));
    expected_percent[4] = convertPercent(expected_percent[3], (ui->doubleSpinBox_expected_ncc->value()));


    ui -> customPlot->clearPlottables();
    MainWindow::makePlot();
    ui -> customPlot->replot();
}

void MainWindow::on_pushButton_Refresh_released()
{
    refreshGraph();
}

void MainWindow::setDefaults()
{
    expected_percent[0] = 100;
    expected_percent[1] = 90;
    expected_percent[2] = 85;
    expected_percent[3] = 75;
    expected_percent[4] = 60;

    ui->doubleSpinBox_expected_prospect->setValue(expected_percent[0]);
    ui->doubleSpinBox_expected_pie->setValue(expected_percent[1]);
    ui->doubleSpinBox_expected_fli->setValue(expected_percent[2]);
    ui->doubleSpinBox_expected_pi->setValue(expected_percent[3]);
    ui->doubleSpinBox_expected_ncc->setValue(expected_percent[4]);

    expected_percent[0] = convertPercent(total, (expected_percent[0]));
    expected_percent[1] = convertPercent(expected_percent[0], (expected_percent[1]));
    expected_percent[2] = convertPercent(expected_percent[1], (expected_percent[2]));
    expected_percent[3] = convertPercent(expected_percent[2], (expected_percent[3]));
    expected_percent[4] = convertPercent(expected_percent[3], (expected_percent[4]));

    checkActualButtons();

}

double MainWindow::convertPercent(int total, int convert)
{
    return ((double)total * convert)/100.0;
}

void MainWindow::on_checkBox_clicked(bool checked)
{
    if(checked == true)
    {
        ui->doubleSpinBox_expected_prospect->setEnabled(true);
        ui->doubleSpinBox_expected_pie->setEnabled(true);
        ui->doubleSpinBox_expected_fli->setEnabled(true);
        ui->doubleSpinBox_expected_pi->setEnabled(true);
        ui->doubleSpinBox_expected_ncc->setEnabled(true);
    }
    else
    {
        ui->doubleSpinBox_expected_prospect->setDisabled(true);
        ui->doubleSpinBox_expected_pie->setDisabled(true);
        ui->doubleSpinBox_expected_fli->setDisabled(true);
        ui->doubleSpinBox_expected_pi->setDisabled(true);
        ui->doubleSpinBox_expected_ncc->setDisabled(true);
    }
}

void MainWindow::on_pushButton_add_prospect_clicked()
{
    actual_total[0] +=1;
    total +=1;
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

void MainWindow::on_pushButton_sub_prospect_clicked()
{
    actual_total[0] -=1;
    total -=1;
    refreshGraph();
}

void MainWindow::on_pushButton_sub_pie_clicked()
{
    actual_total[1] -=1;
    refreshGraph();
}

void MainWindow::on_pushButton_sub_fli_clicked()
{
    actual_total[2] -=1;
    refreshGraph();
}

void MainWindow::on_pushButton_sub_pi_clicked()
{
    actual_total[3] -=1;
    refreshGraph();
}

void MainWindow::on_pushButton_sub_ncc_clicked()
{
    actual_total[4] -=1;
    refreshGraph();
}

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


void MainWindow::checkActualButtons()
{
    if(actual_total[1] + 1 > actual_total[0])
    {
        ui->pushButton_add_pie->setDisabled(true);
    }
    else
    {
        ui->pushButton_add_pie->setEnabled(true);
    }

    if(actual_total[2] + 1 > actual_total[1])
    {
        ui->pushButton_add_fli->setDisabled(true);
    }
    else
    {
        ui->pushButton_add_fli->setEnabled(true);
    }

    if(actual_total[3] + 1 > actual_total[2])
    {
        ui->pushButton_add_pi->setDisabled(true);
    }
    else
    {
        ui->pushButton_add_pi->setEnabled(true);
    }

    if(actual_total[4] + 1 > actual_total[3])
    {
        ui->pushButton_add_ncc->setDisabled(true);
    }
    else
    {
        ui->pushButton_add_ncc->setEnabled(true);
    }

    if(actual_total[0] -1 < 0)
    {
        ui->pushButton_sub_prospect->setDisabled(true);
    }
    else
    {
        ui->pushButton_sub_prospect->setEnabled(true);
    }

    if(actual_total[1] -1 < 0)
    {
        ui->pushButton_sub_pie->setDisabled(true);
    }
    else
    {
        ui->pushButton_sub_pie->setEnabled(true);
    }

    if(actual_total[2] -1 < 0)
    {
        ui->pushButton_sub_fli->setDisabled(true);
    }
    else
    {
        ui->pushButton_sub_fli->setEnabled(true);
    }

    if(actual_total[3] -1 < 0)
    {
        ui->pushButton_sub_pi->setDisabled(true);
    }
    else
    {
        ui->pushButton_sub_pi->setEnabled(true);
    }

    if(actual_total[4] -1 < 0)
    {
        ui->pushButton_sub_ncc->setDisabled(true);
    }
    else
    {
        ui->pushButton_sub_ncc->setEnabled(true);
    }
}






