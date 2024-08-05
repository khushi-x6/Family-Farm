#include "memorywidget.h"
#include <QPainter>
#include <cmath>
#include <QMessageBox>
#include <QDebug>

MemoryWidget::MemoryWidget(QWidget *parent)
    : QWidget(parent), size(0) {
    setFixedSize(1050, 150);
}

void MemoryWidget::initialize(int sz) {
    int n = std::ceil(std::log(sz) / std::log(2));
    size = n + 1;

    free_list.resize(size);
    for (int i = 0; i <= n; i++) {
        free_list[i].clear();
    }

    free_list[n].append(qMakePair(0, sz - 1));
    update();
}

void MemoryWidget::allocate(int sz, QColor color) {
    int n = std::ceil(std::log(sz) / std::log(2));

    if (free_list[n].size() > 0) {
        QPair<int, int> temp = free_list[n][0];
        free_list[n].remove(0);
        allocated_map[temp.first] = qMakePair(temp.second - temp.first + 1, color);
    } else {
        int i;
        for (i = n + 1; i < size; i++) {
            if (free_list[i].size() != 0)
                break;
        }

        if (i == size) {
            QMessageBox::warning(this, "", "Sorry, failed to allocate memory");
        } else {
            QPair<int, int> temp;
            temp = free_list[i][0];
            free_list[i].remove(0);
            i--;

            for (; i >= n; i--) {
                QPair<int, int> pair1, pair2;
                pair1 = qMakePair(temp.first, temp.first + (temp.second - temp.first) / 2);
                pair2 = qMakePair(temp.first + (temp.second - temp.first + 1) / 2, temp.second);

                free_list[i].append(pair1);
                free_list[i].append(pair2);
                temp = free_list[i][0];
                free_list[i].remove(0);
            }
            allocated_map[temp.first] = qMakePair(temp.second - temp.first + 1, color);
        }
    }
    update();
}

void MemoryWidget::deallocate(int startAddress) {
    qDebug() << "Attempting to deallocate block starting at address:" << startAddress;

    if (allocated_map.contains(startAddress)) {
        int blockSize = allocated_map[startAddress].first;
        qDebug() << "Found allocated block of size:" << blockSize;
        int n = std::ceil(std::log(blockSize) / std::log(2));
        allocated_map.remove(startAddress);
        free_list[n].append(qMakePair(startAddress, startAddress + blockSize - 1));

        // Attempt to merge with buddy
        coalesce(n);
        update();
    } else {
        qDebug() << "No allocated block found at address:" << startAddress;
        QMessageBox::warning(this, "", "No such block allocated");
    }
}

void MemoryWidget::coalesce(int n) {
    qDebug() << "Starting coalescing at level:" << n;
    for (int i = n; i < size - 1; ++i) {
        QVector<QPair<int, int>> newFreeList;
        std::sort(free_list[i].begin(), free_list[i].end());

        while (!free_list[i].isEmpty()) {
            QPair<int, int> block = free_list[i].takeFirst();
            bool merged = false;

            for (int j = 0; j < free_list[i].size(); ++j) {
                QPair<int, int> buddy = free_list[i][j];

                if ((block.first / (int)pow(2, i) % 2 == 0 && block.second + 1 == buddy.first) ||
                    (block.first / (int)pow(2, i) % 2 == 1 && buddy.second + 1 == block.first)) {
                    qDebug() << "Merging blocks:" << block << "and" << buddy;
                    block.first = std::min(block.first, buddy.first);
                    block.second = std::max(block.second, buddy.second);
                    free_list[i].remove(j);
                    merged = true;
                    break;
                }
            }

            if (merged) {
                free_list[i + 1].append(block);
            } else {
                newFreeList.append(block);
            }
        }

        free_list[i] = newFreeList;
    }
    qDebug() << "Finished coalescing";
}

void MemoryWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::white);
    painter.drawRect(10, 10, width() - 20, height() - 20);

    int totalSize = pow(2, size - 1);
    int blockWidth = (width() - 20) / totalSize;

    for (auto it = allocated_map.begin(); it != allocated_map.end(); ++it) {
        int startAddress = it.key();
        int blockSize = it.value().first;
        QColor color = it.value().second;

        int x = 10 + startAddress * blockWidth;
        int w = blockSize * blockWidth;
        painter.setBrush(color);
        painter.drawRect(x, 10, w, height() - 20);
    }
}
