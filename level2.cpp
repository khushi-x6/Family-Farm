#include "level2.h"
#include "qlabel.h"
#include "qlineedit.h"
#include "level2.h"
#include "memorywidget.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QRandomGenerator>
#include <QMessageBox>

Level2::Level2(QWidget *parent)
    : QWidget(parent), orderedSize(0) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Set the background color of the Level2 widget
    this->setStyleSheet("background-color: rgb(255, 255, 127); color: black;");

    memoryWidget = new MemoryWidget(this); // Create an instance of MemoryWidget
    layout->addWidget(memoryWidget);

    // Create and style the "Order" button
    QPushButton *orderButton = new QPushButton("Order", this);
    orderButton->setStyleSheet("background-color: rgb(0, 170, 255);");
    layout->addWidget(orderButton);
    connect(orderButton, &QPushButton::clicked, this, &::Level2::order1);

    // Create and style the "Sow" button
    QPushButton *sowButton = new QPushButton("Sow", this);
    sowButton->setStyleSheet("background-color: rgb(0, 170, 255);");
    layout->addWidget(sowButton);
    connect(sowButton, &QPushButton::clicked, this, &Level2::sow1);

    // Create the label to display the random number and icon
    infoTextLabel = new QLabel(this);
    infoIconLabel = new QLabel(this);
    layout->addWidget(infoTextLabel);
    layout->addWidget(infoIconLabel);
    infoTextLabel->setStyleSheet("background-color: white; color: black;");
    infoIconLabel->setStyleSheet("background-color: white; color: black;");
    infoTextLabel->setAlignment(Qt::AlignCenter); // Center align the text
    infoIconLabel->setAlignment(Qt::AlignCenter); // Center align the icon

    // Create and style the QLineEdit for deallocation
    addressLineEdit = new QLineEdit(this);
    addressLineEdit->setPlaceholderText("Enter start address for deallocation");
    layout->addWidget(addressLineEdit);

    // Create and style the "Harvest" button
    QPushButton *harvestButton = new QPushButton("Harvest", this);
    harvestButton->setStyleSheet("background-color: rgb(0, 170, 255);");
    layout->addWidget(harvestButton);
    connect(harvestButton, &QPushButton::clicked, this, &::Level2::harvest1);

    // Load the icons
    colorIcons.append(QPixmap(":/images/carrot.png"));
    colorIcons.append(QPixmap(":/images/wheat.png"));
    colorIcons.append(QPixmap(":/images/strawberry.png"));
    colorIcons.append(QPixmap(":/images/tomato.png"));

    memoryWidget->initialize(512);
}

void Level2::order1() {
    // Define the possible colors
    QVector<QColor> colors = {QColor(255, 136, 0), QColor(184, 184, 0), QColor(255, 0, 120), QColor(255, 0, 0)};

    // Randomly select a size and color
    orderedSize = QRandomGenerator::global()->bounded(1, 257); // Random numbers
    int colorIndex = QRandomGenerator::global()->bounded(colors.size());
    orderedColor = colors[colorIndex];

    infoTextLabel->setText(QString("<center><font size=\"6\">%1</font></center>").arg(orderedSize)); // Set font size to 6 and center the text
    infoTextLabel->setAlignment(Qt::AlignCenter); // Center align the text
    infoIconLabel->setPixmap(colorIcons[colorIndex].scaled(50, 50, Qt::KeepAspectRatio)); // Set the icon in the label
    infoIconLabel->setAlignment(Qt::AlignCenter); // Center align the icon
}

void Level2::sow1() {
    if (orderedSize > 0) {
        memoryWidget->allocate(orderedSize, orderedColor);
    }
}

void Level2::harvest1() {
    bool ok;
    int address = addressLineEdit->text().toInt(&ok);
    if (ok) {
        memoryWidget->deallocate(address);
    } else {
        QMessageBox::warning(this, "", "Please enter a valid start address");
    }
}
