// level1.h
#ifndef LEVEL1_H
#define LEVEL1_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPixmap>
#include "memorywidget.h"
#include "level2.h" // Include the header for Level2

class Level1 : public QWidget {
    Q_OBJECT

public:
    explicit Level1(QWidget *parent = nullptr);

private slots:
    void order();
    void sow();
    void harvest();

private:
    MemoryWidget *memoryWidget;
    QLabel *infoTextLabel;
    QLabel *infoIconLabel;
    QLineEdit *addressLineEdit;
    QWidget *infoLabel;
    QVector<QPixmap> colorIcons;
    int orderedSize;
    QColor orderedColor;
    int allocationCount; // Track the number of allocations

    void openLevel2(); // Method to open Level2
};

#endif // LEVEL1_H
