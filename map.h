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
    int show_num_collision();               //给主界面传递碰撞次数
    int show_num_pass();                    //给主界面传递通过次数
    void end_game();                        //结束程序

protected:
    void paintEvent(QPaintEvent *event);    //画map的事件
    void drawmap(QPainter *p);              //画赛道
    void drawcircles(QPainter *painter);    //画小车


private:

    Ui::Map *ui;

    double *Dist_Car;                       //dist真值，是在地图上显示的dist

    double *Fake_Dist_Car;                  //加入噪声、延迟的车的Dist

    double **V_Car;                         //车的控制速度信号

    double **V_Car_real;                    //车的实际速度

    double ACCLERATE;                       //最大减速度

    QTimer *timer;                          //更新地图的时间 67/2 ms， 每偶数次同时给学生端发一次坐标信号（即每67ms）

    int * ID_map;                           //小车的ID不是1-8，用这个map来记录

    double **Cell_Point;                    //以‘crosspoint观察者’ 来记录两个方向approaching vehicle 的距离，来记录碰撞，以及2个方向最近车的距离（Felix）要求

    int ** record_pass;                     //记录通过次数 8x2 两列分别表示更新前后# 1表示在cross 0表示不在  #第一列为1 第二列为0 记一次通过

    int ** record_collision_front_old;      //8*8的上三角矩阵 记录前后追尾的情况

    int ** record_collision_front_new;      //比*_old晚一个步长

    int ** record_collision_cross;          //记录cross的碰撞次数 16x2 表碰撞 0表正常 1表碰撞

    double record_second_close;             //记录当一个方向的车通过时： 通过的车的ID,

    int *line_tag;                          //车是否在中间直道;//8*1    --1 车进入了中间直线区域     --0 车没有在中间直线区域

    double *line_box;                       //地图信息    0-x左   1-x右    2-y上(坐标是倒着的)    3-y下

    int NUM_COLLISION;                      //碰撞次数

    int NUM_PASS;                           //通过次数

//    double *DIST_OUTPUT;                 //输出dist.txt文件的缓存

//    double *V_OUTPUT;                      //输出V_assemble.txt文件的缓存



};

#endif // MAP_H
