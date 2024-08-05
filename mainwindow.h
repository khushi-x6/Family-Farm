#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "level1.h"
#include "memorywidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Level1;

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_About_clicked();
    void on_AboutQt_clicked();
    void on_start_clicked();
    //void showMainWindow();

private:
    Ui::MainWindow *ui;
    Level1 *level1;
    MemoryWidget *memorywidget;
};

#endif // MAINWINDOW_H


