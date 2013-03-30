#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include "graph.h"
#include <QDebug>

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
    void on_pushButton_clicked();
    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_3_clicked();

    void onGraphUpdate(int);

private:
    Ui::MainWindow *ui;
    void drawValues(Node3 *node);
    void drawValues();
    Graph g;
    bool firstRun;
    int tab[9];
    unsigned int step;
    bool smartRand;
};

#endif // MAINWINDOW_H
