#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "singleton.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Singleton<GLWidget>::createInstance(ui->glWidget);
    Singleton<QConsole>::createInstance(ui->qConsole);

}

MainWindow::~MainWindow()
{
    delete ui;
}
