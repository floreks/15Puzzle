#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <ctime>
#include <QProgressDialog>
#include "GUIMove.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Fifteen");
    ui->progressBar->setValue(0);
    ui->progressBar->setTextVisible(0);

    //zmiana wymiarow planszy i jej parametrow
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->setRowCount(3);
    ui->tableWidget->setColumnCount(3);
    for(int i=0;i<3;i++)
    {
        ui->tableWidget->setColumnWidth(i,80);
        ui->tableWidget->setRowHeight(i,80);
    }
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->horizontalHeader()->hide();

    // wylaczenie przyciskow
    ui->pushButton->setDisabled(true);      // solve
    ui->pushButton_2->setDisabled(true);    // next step
    ui->pushButton_3->setDisabled(true);    // previous step

    // zaznaczenie checkboxa
    ui->checkBox->setChecked(true);

    // inicjalizacja zmiennych
    firstRun = true;
    smartRand = true;
    step = 0;

    // inicjalizacja wartosci poczatkowych na planszy
    //for(int i=1; i<10; i++) tab[i-1]=i%9;

    // do testow
    ui->pushButton->setEnabled(true);
    tab[0]=2; tab[1]=4; tab[2]=0;
    tab[3]=1; tab[4]=6; tab[5]=3;
    tab[6]=7; tab[7]=5; tab[8]=8;

    // pierwsze wyrysowanie planszy
    drawValues();

    QString cs = "Current step: -";
    ui->label->setText(cs);
    QString ts = "Total steps: -";
    ui->label_2->setText(ts);

    // TODO mozliwosc przeciagania klockow
}

void MainWindow::drawValues(Node3 *node)
{
    QString *str = new QString();
    for(int i=0; i<9; i++)
    {
        if(node->getValue(i)!=0)*str = "  " + QString::number(node->getValue(i));
        else *str = " ";
        QTableWidgetItem *txt = new QTableWidgetItem(*str);

        if(i==0) ui->tableWidget->setItem(0,0,txt);
        if(i==1) ui->tableWidget->setItem(0,1,txt);
        if(i==2) ui->tableWidget->setItem(0,2,txt);

        if(i==3) ui->tableWidget->setItem(1,0,txt);
        if(i==4) ui->tableWidget->setItem(1,1,txt);
        if(i==5) ui->tableWidget->setItem(1,2,txt);

        if(i==6) ui->tableWidget->setItem(2,0,txt);
        if(i==7) ui->tableWidget->setItem(2,1,txt);
        if(i==8) ui->tableWidget->setItem(2,2,txt);
    }
    delete str;
}

void MainWindow::drawValues()
{
    QString *str = new QString();
    for(int i=0; i<9; i++)
    {
        if(tab[i]!=0)*str = "  " + QString::number(tab[i]);
        else *str = " ";
        QTableWidgetItem *txt = new QTableWidgetItem(*str);

        if(i==0) ui->tableWidget->setItem(0,0,txt);
        if(i==1) ui->tableWidget->setItem(0,1,txt);
        if(i==2) ui->tableWidget->setItem(0,2,txt);

        if(i==3) ui->tableWidget->setItem(1,0,txt);
        if(i==4) ui->tableWidget->setItem(1,1,txt);
        if(i==5) ui->tableWidget->setItem(1,2,txt);

        if(i==6) ui->tableWidget->setItem(2,0,txt);
        if(i==7) ui->tableWidget->setItem(2,1,txt);
        if(i==8) ui->tableWidget->setItem(2,2,txt);
    }
    delete str;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onGraphUpdate(int arg)
{
    ui->label_3->setText("Graph size: " + QString::number(arg));
}

void MainWindow::on_pushButton_clicked()
{
    // TODO trzeba by to jeszcze zamknac po stworzeniu grafu
    ui->progressBar->setMaximum(0);
    ui->progressBar->setMinimum(0);
    connect(&g,SIGNAL(update(int)),ui->progressBar,SLOT(repaint()));
    connect(&g,SIGNAL(update(int)),this,SLOT(onGraphUpdate(int)));
    g.create(tab);
    ui->progressBar->setMaximum(1);


    ui->pushButton->setDisabled(true);
    ui->pushButton_4->setDisabled(true);

    if(step>0)ui->pushButton_3->setEnabled(true);
    if(step<g.getPath().size()) ui->pushButton_2->setEnabled(true);

    firstRun = false;

    QString cs = "Current step: " + QString::number(step+1);
    ui->label->setText(cs);
    QString ts = "Total steps: " + QString::number(g.getPath().size());
    ui->label_2->setText(ts);
}

void MainWindow::on_pushButton_4_clicked()
{
    srand(time(NULL));
    int temp = 0;
    int r1, r2, index = 0;

    if(!smartRand)
    {
        for(int i=0; i<10; i++)
        {
            r1 = rand()%9;
            r2 = rand()%9;
            temp = tab[r1];
            tab[r1] = tab[r2];
            tab[r2] = temp;
        }
    }
    else
    {
        // szukamy 0
        for(int i=0;i<9;i++)
            if(tab[i] == 0)
                index = i;
        int r;
        for(int i=0;i<25;i++)
        {
            r = rand()%4;
            if(r == 0)up(tab,index);
            if(r == 1)left(tab,index);
            if(r == 2)down(tab,index);
            if(r == 3)right(tab,index);
        }
    }

    if(firstRun)
    {
        ui->pushButton->setEnabled(true);
        ui->pushButton_4->setEnabled(true);
    }
    else
    {
        ui->pushButton->setDisabled(true);
        ui->pushButton_4->setDisabled(true);
    }

    drawValues();
}

void MainWindow::on_pushButton_2_clicked()
{
    if(step<g.getPath().size()) drawValues(g.getPath()[++step]);
    if(step>0) ui->pushButton_3->setEnabled(true);
    if(step==g.getPath().size()-1) ui->pushButton_2->setDisabled(true);

    QString cs = "Current step: " + QString::number(step+1);
    ui->label->setText(cs);
    QString ts = "Total steps: " + QString::number(g.getPath().size());
    ui->label_2->setText(ts);
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(ui->checkBox->isChecked()) smartRand = arg1-1;
    else smartRand = arg1;
}

void MainWindow::on_pushButton_3_clicked()
{
    if(step>0) drawValues(g.getPath()[--step]);
    if(step<g.getPath().size()) ui->pushButton_2->setEnabled(true);
    if(step==0) ui->pushButton_3->setDisabled(true);

    QString cs = "Current step: " + QString::number(step+1);
    ui->label->setText(cs);
    QString ts = "Total steps: " + QString::number(g.getPath().size());
    ui->label_2->setText(ts);
}
