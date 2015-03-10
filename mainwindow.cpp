#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>
#include <QDebug>

#include <stdio.h>
#include <stdint.h>
#include "mainwindow.h"
#include <QSemaphore>
#include "myconstants.h"

#define PRU_NUM 0

QSemaphore freeBytes(BufferSize);
QSemaphore usedBytes;
QVector<convert_results> adc_buffer (BufferSize);

QT_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

     statusLabel = new QLabel(this);
     //lcdNumber_1 = new QLCDNumber(this);
     //lcdNumber_2 = new QLCDNumber(this);
    statusLabel->setText("Status Label");
    ui->statusBar->addPermanentWidget(statusLabel);
    // create an instance of MyThread
    mThread = new AdcThread(this);

    mData = new DataManagement(this);

    // connect signal/slot
    connect(mThread, SIGNAL(valueChanged(QVector<unsigned int>)), this, SLOT(onValueChanged(QVector<unsigned int>)));
    connect(mData, SIGNAL(valueChanged(QVector<unsigned int>)), this, SLOT(onValueChanged(QVector<unsigned int>)));
    connect(mThread, SIGNAL(messageLabel(QString)), this, SLOT(onmessageLabel(QString)));
    connect(mData, SIGNAL(bufferFillCountChanged(int)), this, SLOT(onBufferlevel(int)));
    mThread->start();
    mData->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Absorb the signal emitted from a run() method
// and reflect the count change to the count label
// in our dialog

void MainWindow::onValueChanged(QVector<unsigned int> valeurs)
{
    ui->lcdNumber_1->display((int)valeurs[0]);
    ui->lcdNumber_2->display((int)valeurs[1]);
    ui->lcdNumber_3->display((int)valeurs[2]);
    ui->lcdNumber_4->display((int)valeurs[3]);
}

void MainWindow::onmessageLabel(QString msg)
{
    statusLabel->setText(msg);
}

void MainWindow::onBufferlevel(int level)
{
    statusLabel->setText(QString::number(level));
}

// Start button
void MainWindow::on_pushButton_clicked()
{
   mThread->Stop = false;
}

// Stop button
void MainWindow::on_pushButton_2_clicked()
{
    mThread->Stop = true;
}
