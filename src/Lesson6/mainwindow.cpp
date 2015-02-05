#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "singleton.h"
#include <QList>
#include "mesh.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Singleton<GLWidget>::createInstance(ui->glWidget);
    Singleton<QConsole>::createInstance(ui->qConsole);
    ui->glWidget->setTreeWidget(ui->scene);

    Mesh* b1 = ui->glWidget->addMesh("bunny00", "../Lesson4/bunny.obj");
    Mesh* b2 = ui->glWidget->addMesh("bunny10", "../Lesson4/bunny.obj");

    Mesh* b3 = ui->glWidget->addMesh("bunny11", "../Lesson4/bunny.obj", b2);


    b2->getPosition().setX(2.);
    b2->getPosition().setY(-1.);

    b1->getPosition().setY(-1.);

    b3->getPosition().setX(2.);

    ui->scene->setColumnCount(1);

    /*
    QList<QTreeWidgetItem *> items;
    for (int i = 0; i < 10; ++i)
    {
        items.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("item: %1").arg(i))));
        items.back()->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("item: %1").arg(i))));

    }
    ui->scene->insertTopLevelItems(0, items);
    */
}

MainWindow::~MainWindow()
{
    delete ui;
}
