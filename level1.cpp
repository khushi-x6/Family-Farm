#include "level1.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QRandomGenerator>
#include <QMessageBox>

Level1::Level1(QWidget *parent)
    : QWidget(parent), orderedSize(0) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Create and style the execution label
    QLabel *executionLabel = new QLabel("Execution", this);
    executionLabel->setAlignment(Qt::AlignCenter); // Center align the text
    executionLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: black;");
    layout->addWidget(executionLabel);

    // Set the background color of the Level1 widget
    this->setStyleSheet("background-color: rgb(255, 255, 127); color: black;");

    memoryWidget = new MemoryWidget(this);
    layout->addWidget(memoryWidget);


    // Create and style the execution label
    QLabel *descriptionLabel = new QLabel("", this);
    //executionLabel->setAlignment(Qt::AlignCenter); // Center align the text
    descriptionLabel->setStyleSheet("font-size: 14px; font-weight: bold; color:rgb(0, 170, 255) ;margin-left:20px;margin-botton:0px;");
    layout->addWidget(descriptionLabel);

    // Create and style the "Order" button
    QPushButton *orderButton = new QPushButton("Order", this);
    orderButton->setStyleSheet("background-color: rgb(0, 170, 255);selection-color: rgb(0, 0, 0);color:rgb(255, 255, 255);selection-color: rgb(255, 255, 255);selection-background-color: rgb(0, 170, 255);font: 18pt;border-radius:5px;");
    layout->addWidget(orderButton);
    connect(orderButton, &QPushButton::clicked, this, &Level1::order);

    // Create and style the "Sow" button
    QPushButton *sowButton = new QPushButton("Sow", this);
    sowButton->setStyleSheet("background-color: rgb(0, 170, 255);selection-color: rgb(0, 0, 0);color:rgb(255, 255, 255);selection-color: rgb(255, 255, 255);selection-background-color: rgb(0, 170, 255);font: 18pt;border-radius:5px;");
    layout->addWidget(sowButton);
    connect(sowButton, &QPushButton::clicked, this, &Level1::sow);

    // Create the label to display the random number and icon
    infoLabel = new QWidget(this);
    QHBoxLayout *infoLayout = new QHBoxLayout(infoLabel);
    infoTextLabel = new QLabel(infoLabel);
    infoIconLabel = new QLabel(infoLabel);
    infoLayout->addWidget(infoTextLabel);
    infoLayout->addWidget(infoIconLabel);
    infoLabel->setLayout(infoLayout);
    infoLabel->setStyleSheet("background-color: white; color: black;");
    layout->addWidget(infoLabel);


    // Create and style the QLineEdit for deallocation
    addressLineEdit = new QLineEdit(this);
    addressLineEdit->setPlaceholderText("Enter start address for deallocation");
    addressLineEdit->setStyleSheet("font: 10pt;");
    layout->addWidget(addressLineEdit);

    // Create and style the "Harvest" button
    QPushButton *harvestButton = new QPushButton("Harvest", this);
    harvestButton->setStyleSheet("background-color: rgb(0, 170, 255);selection-color: rgb(0, 0, 0);color:rgb(255, 255, 255);selection-color: rgb(255, 255, 255);selection-background-color: rgb(0, 170, 255);font: 18pt;border-radius:5px;");
    layout->addWidget(harvestButton);
    connect(harvestButton, &QPushButton::clicked, this, &Level1::harvest);

    // Load the icons
    colorIcons.append(QPixmap(":/images/carrot.png"));
    colorIcons.append(QPixmap(":/images/wheat.png"));
    colorIcons.append(QPixmap(":/images/strawberry.png"));
    colorIcons.append(QPixmap(":/images/tomato.png"));

    memoryWidget->initialize(1024);
}

void Level1::order() {
    // Define the possible colors
    QVector<QColor> colors = {QColor(255, 136, 0), QColor(184, 184, 0), QColor(255, 0, 120), QColor(255, 0, 0)};

    // Randomly select a size and color
    orderedSize = QRandomGenerator::global()->bounded(1, 513); // Random numbers
    int colorIndex = QRandomGenerator::global()->bounded(colors.size());
    orderedColor = colors[colorIndex];

    infoTextLabel->setText(QString("<center><font size=\"6\">%1</font></center>").arg(orderedSize));
    infoTextLabel->setAlignment(Qt::AlignCenter); // Center align the text
    infoIconLabel->setPixmap(colorIcons[colorIndex].scaled(50, 50, Qt::KeepAspectRatio));
    infoIconLabel->setAlignment(Qt::AlignCenter); // Center align the icon
}

void Level1::sow() {
    if (orderedSize > 0) {
        memoryWidget->allocate(orderedSize, orderedColor);
    }
}

void Level1::harvest() {
    bool ok;
    int address = addressLineEdit->text().toInt(&ok);
    if (ok) {
        memoryWidget->deallocate(address);
    } else {
        QMessageBox::warning(this, "", "Please enter a valid start address");
    }
}
