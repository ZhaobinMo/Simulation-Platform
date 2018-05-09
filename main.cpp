#include "mainwindow.h"
#include <QApplication>
#include <QtGui>
#include <QLibrary>
#include <QMessageBox>
#include "initail_dlg.h"
#include "map.h"



typedef double (*Fun)(double **);


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    MainWindow w;
    w.show();
    return a.exec();



}
