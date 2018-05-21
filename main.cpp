#include "mainwindow.h"
#include <QApplication>
#include <QtGui>
#include <QLibrary>
#include <QMessageBox>
#include "initail_dlg.h"
#include "map.h"

using namespace std;
bool Isinstreet(double d)
{
    double street[4]={-60,-20,20,60};
    if ((abs(d-street[0])<5)|| (abs(d-street[1])<5) || (abs(d-street[2])<5) ||(abs(d-street[3])<5))
        return true;
    else
        return false;
}

bool Isinsq(double d)
{
    double street1[2]={120,140};
    if (d>= street1[0]||d<= street1[1])
        return true;
    else
        return false;
}


bool ifsafe1 (double x1,double y1,double x2,double y2)
{
    double leg=abs(x1-x2)+abs(y1-y2);
    double safe=60;
    double leg1=min(abs(x1-x2),abs(y1-y2));


    if (leg<safe&&leg1<5)
    {
        return true;
    }
    else
        return false;
}
bool ifsafe2 (double x1,double y1,double x2,double y2)
{
    double leg=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    double safe=60;


    if (leg<safe)
    {
        return true;
    }
    else
        return false;
}


typedef double (*Fun)(double **);


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    MainWindow w;
    w.show();
    return a.exec();



}
