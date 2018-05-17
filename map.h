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
    int show_num_pass();
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
    int ** record_pass;//记录通过次数 8x2 两列分别表示更新前后# 1表示在cross 0表示不在  #第一列为1 第二列为0 记一次通过
    int ** record_collision_front_old;//8*8的上三角矩阵 记录前后追尾的情况
    int ** record_collision_front_new;//比*_old晚一个步长
    int ** record_collision_cross;//记录cross的碰撞次数 16x2 表碰撞 0表正常 1表碰撞
    int NUM_COLLISION;
    int NUM_PASS;

};

#endif // MAP_H
