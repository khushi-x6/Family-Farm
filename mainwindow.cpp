#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "memorywidget.h"
//#include "level1.h"
#include <QMessageBox>

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

void MainWindow::on_About_clicked()
{
    QMessageBox::about(this,"About","A buddy algorithm simulation\nmade by:Norin\n\tSanya\n\tKhushi");
}

void MainWindow::on_AboutQt_clicked()
{
    //sQMessageBox.setStyleSheet("color:black");
    QMessageBox::aboutQt(this,"AboutQt");
}

void MainWindow::on_start_clicked()
{
    qDebug() << "Start button clicked";
    Level1 *level1 = new Level1();
    level1->show();
    this->close();
}

