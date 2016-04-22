#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MainWindow::makePlot(0,0,0,0,0);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::makePlot(int prospect_Param, int pie_Param, int fli_Param, int pi_Param, int ncc_Param)
{
    // create empty bar chart objects:
    QCPBars *A = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    ui->customPlot->addPlottable(A);

    // set names and colors:
    QPen pen;
    pen.setWidthF(1.2);
    pen.setColor(QColor(255, 131, 0));
    pen.setColor(QColor(1, 92, 191));
    A->setName("Actual");
    pen.setColor(QColor(150, 222, 0));
    A->setPen(pen);
    A->setBrush(QColor(150, 222, 0, 70));

    // prepare x axis with country labels:
    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1 << 2 << 3 << 4 << 5;
    labels << "Prospect" << "PIE" << "FLI" << "PI" << "NCC";
    ui->customPlot->xAxis->setAutoTicks(false);
    ui->customPlot->xAxis->setAutoTickLabels(false);
    ui->customPlot->xAxis->setTickVector(ticks);
    ui->customPlot->xAxis->setTickVectorLabels(labels);
    ui->customPlot->xAxis->setTickLabelRotation(60);
    ui->customPlot->xAxis->setSubTickCount(0);
    ui->customPlot->xAxis->setTickLength(0,5);
    ui->customPlot->xAxis->grid()->setVisible(true);
    ui->customPlot->xAxis->setRange(0, 6);

    // prepare y axis:
    ui->customPlot->yAxis->setRange(0, 100);
    ui->customPlot->yAxis->setPadding(5); // a bit more space to the left border
    ui->customPlot->yAxis->setLabel("% Of Total Surveys Completed");
    ui->customPlot->yAxis->grid()->setSubGridVisible(true);
    QPen gridPen;
    gridPen.setStyle(Qt::SolidLine);
    gridPen.setColor(QColor(0, 0, 0, 25));
    ui->customPlot->yAxis->grid()->setPen(gridPen);
    gridPen.setStyle(Qt::DotLine);
    ui->customPlot->yAxis->grid()->setSubGridPen(gridPen);

    // Add data:
    QVector<double> AData;
    AData << prospect_Param << pie_Param << fli_Param << pi_Param << ncc_Param ;
    A->setData(ticks, AData);

    // setup legend:
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->customPlot->legend->setBrush(QColor(255, 255, 255, 200));
    QPen legendPen;
    legendPen.setColor(QColor(130, 130, 130, 200));
    ui->customPlot->legend->setBorderPen(legendPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->customPlot->legend->setFont(legendFont);
   // ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}




void MainWindow::on_pushButton_Refresh_released()
{
    int prospect = 0;
    int pie = 0;
    int fli = 0;
    int pi = 0;
    int ncc = 0;

    prospect=ui->spinBox_Prospect->value();
    pie=ui->spinBox_PIE->value();
    fli=ui->spinBox_FLI->value();
    pi=ui->spinBox_PI->value();
    ncc=ui->spinBox_NCC->value();


    ui -> customPlot->clearPlottables();
    MainWindow::makePlot(prospect, pie, fli, pi, ncc);
    ui -> customPlot->replot();

}
