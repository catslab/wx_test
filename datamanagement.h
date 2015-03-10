#ifndef DATAMANAGEMENT_H
#define DATAMANAGEMENT_H

#include <QThread>

class DataManagement : public QThread
{
    Q_OBJECT
public:
    explicit DataManagement(QObject *parent = 0);
    void run();
signals:
    void valueChanged(QVector<unsigned int>);
    void bufferFillCountChanged(int cCount);
    void consumerCountChanged(int count);
public slots:
};

#endif // DATAMANAGEMENT_H
