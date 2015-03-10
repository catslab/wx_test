#ifndef ADCTHREAD_H
#define ADCTHREAD_H
#include <QThread>
#include <stdint.h>
#include <QVector>

class AdcThread: public QThread
{
    Q_OBJECT

public:
    explicit AdcThread(QObject *parent = 0, bool b = false);
    void run();
    bool Stop;
    QVector<unsigned int> adc_data;

signals:
    // To communicate with Gui Thread
    // we need to emit a signal
    void valueChanged(QVector<unsigned int>);
    void messageLabel(QString);

public slots:

private:
    static int read_words(uint32_t x[]);

    //static QMutex mutex;
};

#endif // ADCTHREAD_H
