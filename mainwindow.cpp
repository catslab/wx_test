#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>
#include <QDebug>

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <prussdrv.h>
#include <pruss_intc_mapping.h>

#define PRU_NUM 0

QT_USE_NAMESPACE

/* host pru shared memory */
/*
static int read_words(uint32_t x[2])
{
  static const size_t sharedram_offset = 2048;
  volatile uint32_t* p;

  prussdrv_map_prumem(4, (void**)&p);

  x[0] = p[sharedram_offset + 0];
  x[1] = p[sharedram_offset + 1];

  return 0;
}
*/

/*
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

    tpruss_intc_initdata pruss_intc_initdata = PRUSS_INTC_INITDATA;
    uint32_t x[2];
    ui->lcdNumber_2->display(120);
    qDebug() << "prussdrv_init";
    prussdrv_init();
    qDebug() <<"prussdrv_init end";
    if (prussdrv_open(PRU_EVTOUT_0))
    {
      ui->statusBar->showMessage("prussdrv_open open failed",3);
        //printf("prussdrv_open open failed\n");
      //return -1;
    }
    else
        ui->statusBar->showMessage("prussdrv_open succeeded",3);
        //printf("prussdrv_open succeeded\n");

    prussdrv_pruintc_init(&pruss_intc_initdata);
    qDebug() <<"prussdrv_pruintc_init";

    // execute code on pru0

    prussdrv_exec_program(PRU_NUM, "./adc.bin");
    qDebug() <<"prussdrv_exec_program";
    prussdrv_pru_clear_event (PRU_EVTOUT_0, PRU0_ARM_INTERRUPT);
    qDebug() <<"prussdrv_pru_clear_event";

    while (true)
    {
       qDebug() <<"prussdrv_pru_wait_event start";
        prussdrv_pru_wait_event (PRU_EVTOUT_0);
      //printf("\tINFO: PRU completed transfer.\r\n");
        qDebug() <<"INFO: PRU completed transfer.";
      prussdrv_pru_clear_event (PRU_EVTOUT_0, PRU0_ARM_INTERRUPT);
      qDebug() <<"prussdrv_pru_clear_event";
      read_words(x);
      //printf("0x%08x, 0x%08x\n", x[0], x[1]);
      //ui->lcdNumber_1->display((double)(x[0]&0xFFFF));
      //ui->lcdNumber_2->display(122);
  }

}

MainWindow::~MainWindow()
{
    // disable pru and close memory mapping
    delete ui;
    prussdrv_pru_disable(PRU_NUM);
    prussdrv_exit();
}

*/
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

    // connect signal/slot
    connect(mThread, SIGNAL(valueChanged(QVector<unsigned int>)), this, SLOT(onValueChanged(QVector<unsigned int>)));
    connect(mThread, SIGNAL(messageLabel(QString)), this, SLOT(onmessageLabel(QString)));
    mThread->start();
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
    qDebug() << valeurs[0];
    qDebug() << valeurs[1];

}

void MainWindow::onmessageLabel(QString msg)
{
    statusLabel->setText(msg);
}

// Start button
void MainWindow::on_pushButton_clicked()
{
    mThread->start();
}

// Stop button
void MainWindow::on_pushButton_2_clicked()
{
    mThread->Stop = true;
}
