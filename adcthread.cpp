#include "adcthread.h"
#include "common.h"
#include <QDebug>
#include <prussdrv.h>
#include <pruss_intc_mapping.h>
#include <stdint.h>


AdcThread::AdcThread(QObject *parent, bool b) :
    QThread(parent), Stop(b)
{
}

/* host pru shared memory */

int AdcThread::read_words(uint32_t x[2])
{
  static const size_t sharedram_offset = 2048;
  volatile uint32_t* p;

  prussdrv_map_prumem(4, (void**)&p);

  x[0] = p[sharedram_offset + 0];
  x[1] = p[sharedram_offset + 1];

  return 0;
}

//QMutex AdcThread::mutex;

// run() will be called when a thread starts
void AdcThread::run()
{
     tpruss_intc_initdata pruss_intc_initdata = PRUSS_INTC_INITDATA;
     qRegisterMetaType<QVector<unsigned int> >("QVector<unsigned int>");
     //QVector<unsigned int> adc_data(4);

    int BufferCount = 0;
        uint32_t x[2];
        qDebug() << "prussdrv_init";
        prussdrv_init();
        qDebug() <<"prussdrv_init end";
        if (prussdrv_open(PRU_EVTOUT_0))
        {
          //ui->statusBar->showMessage("prussdrv_open open failed",3);
            //printf("prussdrv_open open failed\n");
          //return -1;
            qDebug() << "prussdrv_open open failed";
        }
        else
            //ui->statusBar->showMessage("prussdrv_open succeeded",3);
            qDebug() <<"prussdrv_open succeeded";

        prussdrv_pruintc_init(&pruss_intc_initdata);
        qDebug() <<"prussdrv_pruintc_init";

        // execute code on pru0
        prussdrv_exec_program(0, "./adc.bin");
        qDebug() <<"prussdrv_exec_program";
        prussdrv_pru_clear_event (PRU_EVTOUT_0, PRU0_ARM_INTERRUPT);
        qDebug() <<"prussdrv_pru_clear_event";

        emit messageLabel("Debut");
        while (true)
        {
            
            qDebug() <<"prussdrv_pru_wait_event start";
            prussdrv_pru_wait_event (PRU_EVTOUT_0);
            //printf("\tINFO: PRU completed transfer.\r\n");
            qDebug() <<"INFO: PRU completed transfer.";
            prussdrv_pru_clear_event (PRU_EVTOUT_0, PRU0_ARM_INTERRUPT);
            qDebug() <<"prussdrv_pru_clear_event";
            read_words(x);
            /*
            adc_data[0] = (unsigned int)(x[0] & 0xFFFF);
            adc_data[1] = (unsigned int)((x[0] >>16) & 0XFFFF);
            adc_data[2] = (unsigned int)(x[1] & 0XFFFF);
            adc_data[3] = (unsigned int)((x[1] >>16) & 0XFFFF);
            */
            if (!this->Stop)
            {
                freeBytes.acquire();
                adc_buffer[BufferCount].sensor1 = (unsigned int)(x[0] & 0xFFFF);
                adc_buffer[BufferCount].sensor2 = (unsigned int)((x[0] >>16) & 0XFFFF);
                adc_buffer[BufferCount].sensor3 = (unsigned int)(x[1] & 0XFFFF);
                adc_buffer[BufferCount].sensor4 = (unsigned int)((x[1] >>16) & 0XFFFF);
                usedBytes.release();
            }
            //emit producerCountChanged(BufferCount);
            
            if ( BufferCount++ == BufferSize )
                BufferCount = 0;
            // emit the signal for the count label
            //emit valueChanged(adc_data);
        }
        prussdrv_pru_disable(0);
        prussdrv_exit();
        emit messageLabel("Fermeture pru");
}
