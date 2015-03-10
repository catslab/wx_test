#include "mainwindow.h"
#include <QApplication>
#include <QVector>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    qRegisterMetaType<QVector<unsigned int> >("QVector<unsigned int>");
    return a.exec();
}
