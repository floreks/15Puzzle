#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <QTime>
#include <QFileDialog>
#include <QTextStream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    //okienko do wczytywania grafu i rozwiazania
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"",tr("Files (*.*)"));
    QFile file(fileName);
    if(!file.open( QIODevice::ReadWrite | QIODevice::Text) || fileName=="") this->close(); //do poprawy
    QString move;
    double value;
    QTextStream in(&file);
    in >> rowCount >> columnCount;
    for(int i=0; i<rowCount*columnCount; i++)
    {
        in >> value;
        board.push_back(value);
    }
    in >> move;
    moves = move.toStdString();
    file.close();
    step = 0;
    firstDraw = true;

    //ustawienie okna glownego
    ui->setupUi(this);
    this->setWindowTitle("Fifteen Visualiser");
    this->setFixedHeight(100+rowCount*81);
    this->setFixedWidth(20+columnCount*81);

    //ustawienie tabelki
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->setRowCount(rowCount);
    ui->tableWidget->setColumnCount(columnCount);
    for(int i=0; i<rowCount; i++) ui->tableWidget->setRowHeight(i,80);
    for(int i=0; i<columnCount; i++) ui->tableWidget->setColumnWidth(i,80);
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->horizontalHeader()->hide();
    ui->tableWidget->setGeometry(10,10,rowCount*81,columnCount*81);

    //ustawienie przyciskow
    ui->pushButton->setGeometry(10,15+rowCount*81,columnCount*23,25); //load
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setGeometry(15+columnCount*23,15+rowCount*81,columnCount*23,25); //next
    ui->pushButton_2->setDisabled(true);
    ui->pushButton_3->setGeometry(20+columnCount*46,15+rowCount*81,columnCount*23,25); //previous
    ui->pushButton_3->setDisabled(true);

    //ustawienie checkboxa i opisu
    ui->checkBox->setGeometry(10,45+rowCount*81,115,20); //checkbox
    ui->checkBox->setChecked(true);
    ui->label->setGeometry(120,45+rowCount*81,100,20); //opis
    ui->label->setText("Step: -/-");

    //wyrysowanie planszy
    draw();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::draw()
{
    QString *str = new QString();
    for(int i=0; i<board.size(); i++)
    {
        if(board[i]!=0)*str = "  " + QString::number(board[i]);
        else *str = " ";
        QTableWidgetItem *txt = new QTableWidgetItem(*str);
        ui->tableWidget->setItem(i/columnCount,i%rowCount,txt);
    }
    delete str;

    if(!firstDraw)
    {
        QString steps = "Step: " + QString::number(step) + "/" + QString::number(moves.size());
        ui->label->setText(steps);
    }
    else firstDraw = false;
}

int MainWindow::zeroPosition()
{
    int zeroPosition = 0;
    for(int i=0; i<board.size(); i++) if(board[i]==0) zeroPosition = i;
    return zeroPosition;
}

void MainWindow::forward()
{
    if(moves[step]=='L') //przenosimy zero w lewo
    {
        int zero = zeroPosition();
        board[zero] = board[zero-1];
        board[zero-1] = 0;
    }
    if(moves[step]=='P') //przenosimy zero w prawo
    {
        int zero = zeroPosition();
        board[zero] = board[zero+1];
        board[zero+1] = 0;
    }
    if(moves[step]=='G') //przenosimy zero w gore
    {
        int zero = zeroPosition();
        board[zero] = board[zero-columnCount];
        board[zero-columnCount] = 0;
    }
    if(moves[step]=='D') //przenosimy zero w dol
    {
        int zero = zeroPosition();
        board[zero] = board[zero+columnCount];
        board[zero+columnCount] = 0;
    }
    step++;
}

void MainWindow::backward()
{
    step--;
    if(moves[step]=='L') //cofamy przeniesienie w lewo
    {
        int zero = zeroPosition();
        board[zero] = board[zero+1];
        board[zero+1] = 0;
    }
    if(moves[step]=='P') //cofamy przeniesienie w prawo
    {
        int zero = zeroPosition();
        board[zero] = board[zero-1];
        board[zero-1] = 0;
    }
    if(moves[step]=='G') //cofamy przeniesienie w gore
    {
        int zero = zeroPosition();
        board[zero] = board[zero+columnCount];
        board[zero+columnCount] = 0;

    }
    if(moves[step]=='D') //cofamy przeniesienie w dol
    {
        int zero = zeroPosition();
        board[zero] = board[zero-columnCount];
        board[zero-columnCount] = 0;
    }
}

void MainWindow::on_pushButton_clicked()
{
    ui->checkBox->setDisabled(true);
    ui->pushButton->setDisabled(true);

    if(ui->checkBox->isChecked())
    {
        while(step<moves.size())
        {
            QTime t;
            t.start();
            while(t.elapsed() < 1000) QCoreApplication::processEvents(QEventLoop::AllEvents, 1000-t.elapsed());
            forward();
            draw();
        }
        ui->pushButton_3->setEnabled(true);
    }
    else ui->pushButton_2->setEnabled(true);
}

void MainWindow::on_pushButton_2_clicked()
{
    forward();
    draw();
    ui->pushButton_3->setEnabled(true);
    if(step>=moves.size()) ui->pushButton_2->setDisabled(true);
}

void MainWindow::on_pushButton_3_clicked()
{
    backward();
    draw();
    ui->pushButton_2->setEnabled(true);
    if(step<=0) ui->pushButton_3->setDisabled(true);
}
