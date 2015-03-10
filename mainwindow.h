#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLCDNumber>
#include <QDialog>
#include <QString>
#include "adcthread.h"
/*
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
    QLabel *statusLabel;
    QLCDNumber *lcdNumber_2;
    QLCDNumber *lcdNumber_1;
};
*/

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    AdcThread *mThread;

private:
    Ui::MainWindow *ui;
    QLabel *statusLabel;
    QLCDNumber *lcdNumber_2;
    QLCDNumber *lcdNumber_1;

public slots:
    void onValueChanged(QVector<unsigned int> valeurs);
    void onmessageLabel(QString);

private slots:

    // for Start button
    void on_pushButton_clicked();

    // for Stop button
    void on_pushButton_2_clicked();

};


#endif // MAINWINDOW_H
