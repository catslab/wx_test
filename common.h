#ifndef COMMON
#define COMMON

#include <QVector>
#include <QSemaphore>

const int BufferSize = 8192;

struct convert_results{
    unsigned int sensor1;
    unsigned int sensor2;
    unsigned int sensor3;
    unsigned int sensor4;

};

extern QVector<convert_results> adc_buffer;
extern QSemaphore freeBytes;
extern QSemaphore usedBytes;

#endif // COMMON

