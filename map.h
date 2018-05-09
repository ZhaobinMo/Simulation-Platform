#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>

namespace Ui {
class Map;
}

class Map : public QWidget
{
    Q_OBJECT

public:
    explicit Map(QWidget *parent = 0);
    ~Map();
    int show_num_collision();
    void end_game();

protected:
    void paintEvent(QPaintEvent *event);
    void drawmap(QPainter *p);
    void drawcircles(QPainter *painter);


private:
    Ui::Map *ui;
    double *Dist_Car;
    double *Fake_Dist_Car;
    double **V_Car;
    double **V_Car_real;
    double ACCLERATE;
    QTimer *timer;
    double **Cell_Point;
    int NUM_COLLISION;

};

#endif // MAP_H
