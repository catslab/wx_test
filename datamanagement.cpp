#include "datamanagement.h"
#include <QThread>
#include <QSemaphore>
#include "common.h"
#include <QDebug>


DataManagement::DataManagement(QObject *parent) : QThread(parent)
{

}

void DataManagement::run()
{
    int BufferRead = 0;
    double mediane2 = 0, mediane3 = 0;
    QVector<unsigned int> adc_data(4);
    forever
    {
        usedBytes.acquire();
        //fprintf(stderr, "%c", buffer[i % BufferSize]);
        //enregistrement des valeurs

        //extraction pour affichage
        /*
        qDebug() << adc_buffer[BufferRead].sensor1;
        qDebug() << adc_buffer[BufferRead].sensor2;
        qDebug() << adc_buffer[BufferRead].sensor3;
        qDebug() << adc_buffer[BufferRead].sensor4;
        */
        adc_data[0] = adc_buffer[BufferRead].sensor1;
        adc_data[1] = adc_buffer[BufferRead].sensor2;
        adc_data[2] = adc_buffer[BufferRead].sensor3>>4;
        adc_data[3] = adc_buffer[BufferRead].sensor4;

        mediane3 += (adc_buffer[BufferRead].sensor3>>4)/CountDelta;
        mediane2 += (adc_buffer[BufferRead].sensor2)/CountDelta;

        freeBytes.release();
        if ( BufferRead % CountDelta == 0)
        {
            adc_data[2] = (int)mediane3;
            adc_data[1] = (int)mediane2;
            mediane3 = 0;
            mediane2 = 0;
            emit valueChanged(adc_data);
            emit bufferFillCountChanged(BufferRead);
        }

        //emit bufferFillCountChanged(usedBytes.available());

        emit consumerCountChanged(BufferRead);
        if ( BufferRead++ == BufferSize )
            BufferRead = 0;
    }

}

/*
DataManagement::~DataManagement()
{

}
*/
