#ifndef COMMON
#define COMMON

#include <QVector>
#include <QSemaphore>
#include "myconstants.h"

extern QVector<convert_results> adc_buffer;
extern QSemaphore freeBytes;
extern QSemaphore usedBytes;

#endif // COMMON

