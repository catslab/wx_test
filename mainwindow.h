#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLCDNumber>
#include <QDialog>
#include <QString>

#include "adcthread.h"
#include "datamanagement.h"

#include <QSemaphore>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    AdcThread *mThread;
    DataManagement *mData;
    QLabel *statusLabel;
    QLCDNumber *lcdNumber_2;
    QLCDNumber *lcdNumber_1;

public slots:
    void onValueChanged(QVector<unsigned int> valeurs);
    void onmessageLabel(QString);
    void onBufferlevel(int);

private slots:

    // for Start button
    void on_pushButton_clicked();

    // for Stop button
    void on_pushButton_2_clicked();

};


#endif // MAINWINDOW_H
