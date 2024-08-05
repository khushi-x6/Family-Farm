#include "memorywidget.h"
#include <QPainter>
#include <cmath>
#include <iostream>

MemoryWidget::MemoryWidget(QWidget *parent)
    : QWidget(parent), size(0) {
    setFixedSize(500, 300);
}

void MemoryWidget::initialize(int sz) {
    int n = std::ceil(std::log(sz) / std::log(2));
    size = n + 1;

    free_list.resize(size);
    for(int i = 0; i <= n; i++) {
        free_list[i].clear();
    }

    free_list[n].append(qMakePair(0, sz - 1));
    update();
}

void MemoryWidget::allocate(int sz) {
    int n = std::ceil(std::log(sz) / std::log(2));

    if (free_list[n].size() > 0) {
        QPair<int, int> temp = free_list[n][0];
        free_list[n].remove(0);
        mp[temp.first] = temp.second - temp.first + 1;
    } else {
        int i;
        for(i = n + 1; i < size; i++) {
            if(free_list[i].size() != 0)
                break;
        }

        if (i == size) {
            std::cout << "Sorry, failed to allocate memory \n";
        } else {
            QPair<int, int> temp;
            temp = free_list[i][0];
            free_list[i].remove(0);
            i--;

            for(; i >= n; i--) {
                QPair<int, int> pair1, pair2;
                pair1 = qMakePair(temp.first, temp.first + (temp.second - temp.first) / 2);
                pair2 = qMakePair(temp.first + (temp.second - temp.first + 1) / 2, temp.second);

                free_list[i].append(pair1);
                free_list[i].append(pair2);
                temp = free_list[i][0];
                free_list[i].remove(0);
            }
            mp[temp.first] = temp.second - temp.first + 1;
        }
    }
    update();
}

void MemoryWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setPen(Qt::black);
    int width = this->width();

    for (auto it = mp.begin(); it != mp.end(); ++it) {
        int start = it.key();
        int sz = it.value();
        int startX = (start * width) / 128;
        int endX = ((start + sz) * width) / 128;
        QRect rect(startX, 100, endX - startX, 50);
        painter.fillRect(rect, Qt::red);
        painter.drawRect(rect);
    }

    for (int i = 0; i < size; ++i) {
        for (auto &block : free_list[i]) {
            int start = block.first;
            int sz = block.second - block.first + 1;
            int startX = (start * width) / 128;
            int endX = ((start + sz) * width) / 128;
            QRect rect(startX, 100, endX - startX, 50);
            painter.fillRect(rect, Qt::green);
            painter.drawRect(rect);
        }
    }
}
