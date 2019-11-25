#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getFileName()
{
    file_path = QFileDialog::getOpenFileName(this, tr("Open File"),NULL, tr("csvFile(*.* *.csv)"));
}

bool MainWindow::openfile()
{
    if(file_path.isEmpty())
    {
        QMessageBox::warning(this, tr("Read File"), tr("No file selected"));
        return false;
    }
    QString file_type = file_path.split('.').last();
    if(file_type!="CSV"&&file_type!="csv")
    {
        QMessageBox::warning(this, tr("Read File"), tr("Invalid file type!"));
        return false;
    }
    file = new QFile(file_path);
    if(!file->exists())
    {
        QMessageBox::warning(this, tr("Read File"), tr("File doesn't exist!"));
        return false;
    }
    if(!file->open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, tr("Read File"), tr("Cannot open this file!"));
        return false;
    }
    return true;
}

void MainWindow::readData()
{
    QTextStream stream(file);
    while(!stream.atEnd())
    {
        data.push_back(stream.readLine());
    }
    file->close();
    for(int i=1;i<data.size();i++)
    {
        QString tmp = data.at(i);
        name.push_back(tmp.split(',')[0]);
        population.push_back(tmp.split(',')[1]);
    }
}

void MainWindow::draw()
{
    srand(time(NULL));
    QtCharts::QPieSeries *series = new QtCharts::QPieSeries();
    for(int i=0;i<name.size();i++)
    {
        series->append(name.at(i), population.at(i).toInt());
    }
    series->setLabelsVisible();
    QtCharts::QPieSlice **Color = new QtCharts::QPieSlice*[name.size()];
    for(int i=0;i<name.size();i++)
    {
        Color[i] = series->slices().at(i);
        Color[i]->setColor(qRgb(rand()%256,rand()%256,rand()%256));
        Color[i]->setLabelFont(QFont("Microsoft YaHei", 10, 75));
        Color[i]->setExploded();
        Color[i]->setExplodeDistanceFactor(0.05);
    }

    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Assignment11");
    chart->setTitleFont(QFont("Microsoft YaHei", 10, 75));
    chart->legend()->setFont(QFont("Microsoft YaHei", 10, 75));
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    this->setCentralWidget(chartView);
}

void sleep(unsigned int t)
{
    QTime reachTime = QTime::currentTime().addMSecs(t);
    while(QTime::currentTime()<reachTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::run()
{
    do
    {
        clear();
        getFileName();
        if(openfile())
        {
            readData();
            draw();
            sleep(1000);
        }
    }while(ask());
    this->close();
}

void MainWindow::clear()
{
    file_path.clear();
    data.clear();
    name.clear();
    population.clear();
}

bool MainWindow::ask()
{
    QMessageBox::StandardButton answer;
    answer=QMessageBox::question(this, tr("question"), tr("continue?"), QMessageBox::Yes|QMessageBox::No);
    if(answer == QMessageBox::Yes) return true;
    else return false;
}
void MainWindow::on_pushButton_clicked()
{
    run();
}
