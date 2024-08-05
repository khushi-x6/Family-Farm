#ifndef LEVEL2_H
#define LEVEL2_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPixmap>
#include "memorywidget.h"

class QPushButton;
class QLineEdit;
class QLabel;

class Level2 : public QWidget {
    Q_OBJECT

public:
    explicit Level2(QWidget *parent = nullptr);

private slots:
    void order1();
    void sow1();
    void harvest1();

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
};

#endif // LEVEL2_H
