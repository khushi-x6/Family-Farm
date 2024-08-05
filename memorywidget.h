#ifndef MEMORYWIDGET_H
#define MEMORYWIDGET_H

#include <QWidget>
#include <QVector>
#include <QMap>
#include <QPair>
#include <QColor>

class MemoryWidget : public QWidget {
    Q_OBJECT

public:
    explicit MemoryWidget(QWidget *parent = nullptr);
    void initialize(int size);
    void allocate(int size, QColor color);
    void deallocate(int startAddress);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int size;
    QVector<QVector<QPair<int, int>>> free_list;
    QMap<int, QPair<int, QColor>> allocated_map;

    void coalesce(int n);
};

#endif // MEMORYWIDGET_H
