#include "map.h"
#include "ui_map.h"
#include "moving.h"

#include<QApplication>
#include<QPixmap>
#include<QThread>
#include <QEventLoop>
#include <QTimer>
#include <QDebug>
#include <QFile>
#include <QString>
#include <iostream>
#include <stdio.h>
#include <QBuffer>

#include "mainwindow.h"

QFile data1("V_assemble.txt");
QFile data2("dist.txt");

//用来记录单纯的8个dist
QFile data3("8Cor.txt");

Map::Map(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Map)
{
    data1.open(QFile::WriteOnly | QIODevice::Text);
//    data2.open(QFile::WriteOnly | QIODevice::Text);
    data3.open(QFile::WriteOnly | QIODevice::Text);
//    buffer1.open(QIODevice::WriteOnly);
//    buffer2.open(QIODevice::WriteOnly);




    ui->setupUi(this);
    timer = new QTimer(this);

//    id_delay = startTimer(t_delay);
//    id_display = startTimer(t_update);
    timer->start(t_paint);//  67/2 ms

    connect(timer,SIGNAL(timeout()),this,SLOT(update()));




    resize(1000, 1000);
    ACCLERATE = 130000000;//最大减速度
    NUM_COLLISION = 0;//碰撞次数
    NUM_PASS = 0;//通过次数
    Dist_Car = new double[8];
    Fake_Dist_Car = new double[8];
    V_Car = new double*[8];
    line_tag = new int[8];
    for (int i=0;i<8;i++){
        V_Car[i] = new double[2];
    }

    //地图信息
    line_box = new double[4];
    line_box[0] = InCorDownLeft_7_X;
    line_box[1] = InCorDownRight_2_X;
    line_box[2] = InCorUpLeft_7_Y;
    line_box[3] = InCorDownLeft_2_Y;

    //小车位置初始化
    Dist_Car[0] = OutDistDownLeft_7;
    Dist_Car[1] = OutDistDownRight_7;
    Dist_Car[2] = OutDistUpRight_7;
    Dist_Car[3] = OutDistUpLeft_7;
    Dist_Car[4] = InDistDownLeft_7;
    Dist_Car[5] = InDistDownRight_7;
    Dist_Car[6] = InDistUpRight_7;
    Dist_Car[7] = InDistUpLeft_7;
    Fake_Dist_Car = Dist_Car;

    //id编码成比赛要求的id
    ID_map = new int[8];
    ID_map[0] = 7;
    ID_map[1] = 5;
    ID_map[2] = 3;
    ID_map[3] = 1;
    ID_map[4] = 6;
    ID_map[5] = 4;
    ID_map[6] = 2;
    ID_map[7] = 8;

    V_Car[0][0] = 7;
    V_Car[1][0] = 5;
    V_Car[2][0] = 3;
    V_Car[3][0] = 1;
    V_Car[4][0] = 6;
    V_Car[5][0] = 4;
    V_Car[6][0] = 2;
    V_Car[7][0] = 8;
    for (int i=0;i<8;i++){
        V_Car[i][1] = 103;
        line_tag[i] = 0;
    }
    V_Car_real = V_Car;
    //初始化 control point
    double * temp_xy;
    temp_xy = new double[2];

    Cell_Point = new double *[16];
    for (int i=0;i<16;i++){
        Cell_Point[i] = new double[8];
        for (int j=0;j<8;j++){
            Cell_Point[i][j]=0;
        }
    }
    //***********最下层*************//
    //1(左下角)
    Cell_Point[0][0] = 0;// 0表示小圈 （tag）第一列和第二列是竖的方向的tag和距离
    Cell_Point[0][1] = InDistDownLeft_1_End - r; // 点在（tag）圈上的位置距初始点的距离

    Cell_Point[0][3] = 0;//第三列和第四列是横的方向的
    Cell_Point[0][4] = InDistDownLeft_8 + r;
    temp_xy = small(Cell_Point[0][1]);
    //qDebug()<<temp_xy[0]<<' '<<temp_xy[1];
    Cell_Point[0][6] = temp_xy[0];//InCorDownLeft_1_X;
    Cell_Point[0][7] = temp_xy[1];//InCorDownLeft_7_Y;

    //2
    Cell_Point[1][0] = 1;
    Cell_Point[1][1] = OutDistDownLeft_1_End - r;
    Cell_Point[1][3] = 0;
    Cell_Point[1][4] = Cell_Point[0][4] + OutBridge;
    temp_xy = big(Cell_Point[1][1]);
    //qDebug()<<temp_xy[0]<<' '<<temp_xy[1];
    Cell_Point[1][6] = temp_xy[0];//OutCorDownLeft_1_X;
    Cell_Point[1][7] = temp_xy[1];//InCorDownLeft_7_Y;
    //3
    Cell_Point[2][0] = 1;
    Cell_Point[2][1] = OutDistDownRight_8 + r;
    Cell_Point[2][3] = 0;
    Cell_Point[2][4] = Cell_Point[1][4] + OutBridge;
    temp_xy = big(Cell_Point[2][1]);
    //qDebug()<<temp_xy[0]<<' '<<temp_xy[1];
    Cell_Point[2][6] = temp_xy[0];//OutCorDownRight_8_X;
    Cell_Point[2][7] = temp_xy[1];//InCorDownLeft_7_Y;
    //4（右下角）
    Cell_Point[3][0] = 0;
    Cell_Point[3][1] = InDistDownRight_8 + r;
    Cell_Point[3][3] = 0;
    Cell_Point[3][4] = Cell_Point[2][4] + OutBridge;
    temp_xy = small(Cell_Point[3][1]);
    //qDebug()<<temp_xy[0]<<' '<<temp_xy[1];
    Cell_Point[3][6] = temp_xy[0];//InCorDownRight_8_X;
    Cell_Point[3][7] = temp_xy[1];//InCorDownLeft_7_Y;


    //***********第二层*************//
    //5
    Cell_Point[4][0] = 0;
    Cell_Point[4][1] = Cell_Point[0][1] - OutBridge;
    Cell_Point[4][3] = 1;
    Cell_Point[4][4] = OutDistDownLeft_8 + r;
    temp_xy = small(Cell_Point[4][1]);
    //qDebug()<<temp_xy[0]<<' '<<temp_xy[1];
    Cell_Point[4][6] = temp_xy[0];//Cell_Point[0][6];
    Cell_Point[4][7] = temp_xy[1];//Cell_Point[0][7] - OutBridge;
    //6
    Cell_Point[5][0] = 1;
    Cell_Point[5][1] = Cell_Point[1][1] - OutBridge;
    Cell_Point[5][3] = 1;
    Cell_Point[5][4] = Cell_Point[4][4] + OutBridge;
    temp_xy = big(Cell_Point[5][1]);
    //qDebug()<<temp_xy[0]<<' '<<temp_xy[1];
    Cell_Point[5][6] = temp_xy[0];//Cell_Point[1][6];
    Cell_Point[5][7] = temp_xy[1];//Cell_Point[1][7] - OutBridge;
    //7
    Cell_Point[6][0] = 1;
    Cell_Point[6][1] = Cell_Point[2][1] + OutBridge;
    Cell_Point[6][3] = 1;
    Cell_Point[6][4] = Cell_Point[5][4] + OutBridge;
    temp_xy = big(Cell_Point[6][1]);
    //qDebug()<<temp_xy[0]<<' '<<temp_xy[1];
    Cell_Point[6][6] = temp_xy[0];//Cell_Point[2][6];
    Cell_Point[6][7] = temp_xy[1];//Cell_Point[2][7] - OutBridge;
    //8
    Cell_Point[7][0] = 0;
    Cell_Point[7][1] = Cell_Point[3][1] + OutBridge;
    Cell_Point[7][3] = 1;
    Cell_Point[7][4] = Cell_Point[6][4] + OutBridge;
    temp_xy = small(Cell_Point[7][1]);
    //qDebug()<<temp_xy[0]<<' '<<temp_xy[1];
    Cell_Point[7][6] = temp_xy[0];//Cell_Point[3][6];
    Cell_Point[7][7] = temp_xy[1];//Cell_Point[3][7] - OutBridge;

    //***********第三层*************//
    //9
    Cell_Point[8][0] = 0;//
    Cell_Point[8][1] = Cell_Point[4][1] - OutBridge;
    Cell_Point[8][3] = 1;//
    Cell_Point[8][4] = OutDistUpLeft_1 - r;
    temp_xy = small(Cell_Point[8][1]);
    //qDebug()<<temp_xy[0]<<' '<<temp_xy[1];
    Cell_Point[8][6] = temp_xy[0];//[4][6];
    Cell_Point[8][7] = temp_xy[1];//Cell_Point[4][7] - OutBridge;
    //10
    Cell_Point[9][0] = 1;
    Cell_Point[9][1] = Cell_Point[5][1] - OutBridge;
    Cell_Point[9][3] = 1;
    Cell_Point[9][4] = Cell_Point[8][4] - OutBridge;
    temp_xy = big(Cell_Point[9][1]);
    //qDebug()<<temp_xy[0]<<' '<<temp_xy[1];
    Cell_Point[9][6] = temp_xy[0];//Cell_Point[5][6];
    Cell_Point[9][7] = temp_xy[1];//Cell_Point[5][7] - OutBridge;
    //11
    Cell_Point[10][0] = 1;
    Cell_Point[10][1] = Cell_Point[6][1] + OutBridge;
    Cell_Point[10][3] = 1;
    Cell_Point[10][4] = Cell_Point[9][4] - OutBridge;
    temp_xy = big(Cell_Point[10][1]);
    //qDebug()<<temp_xy[0]<<' '<<temp_xy[1];
    Cell_Point[10][6] = temp_xy[0];//Cell_Point[6][6];
    Cell_Point[10][7] = temp_xy[1];//Cell_Point[6][7] - OutBridge;
    //12
    Cell_Point[11][0] = 0;
    Cell_Point[11][1] = Cell_Point[7][1] + OutBridge;
    Cell_Point[11][3] = 1;
    Cell_Point[11][4] = Cell_Point[10][4] - OutBridge;
    temp_xy = small(Cell_Point[11][1]);
    //qDebug()<<temp_xy[0]<<' '<<temp_xy[1];
    Cell_Point[11][6] = temp_xy[0];//Cell_Point[7][6];
    Cell_Point[11][7] = temp_xy[1];//Cell_Point[7][7] - OutBridge;

    //***********第四层*************//
    //13
    Cell_Point[12][0] = 0;
    Cell_Point[12][1] = Cell_Point[8][1] - OutBridge;
    Cell_Point[12][3] = 0;
    Cell_Point[12][4] = InDistUpLeft_1- r;
    temp_xy = small(Cell_Point[12][4]);
    //qDebug()<<temp_xy[0]<<' '<<temp_xy[1];
    Cell_Point[12][6] = temp_xy[0];//Cell_Point[8][6];
    Cell_Point[12][7] = temp_xy[1];//Cell_Point[8][7] - OutBridge;
    //14
    Cell_Point[13][0] = 1;
    Cell_Point[13][1] = Cell_Point[9][1] - OutBridge;
    Cell_Point[13][3] = 0;
    Cell_Point[13][4] = Cell_Point[12][4] - OutBridge;
    temp_xy = small(Cell_Point[13][4]);
    //qDebug()<<temp_xy[0]<<' '<<temp_xy[1];
    Cell_Point[13][6] = temp_xy[0];//Cell_Point[9][6];
    Cell_Point[13][7] = temp_xy[1];//Cell_Point[9][7] - OutBridge;
    //15
    Cell_Point[14][0] = 1;
    Cell_Point[14][1] = Cell_Point[10][1] + OutBridge;
    Cell_Point[14][3] = 0;
    Cell_Point[14][4] = Cell_Point[13][4] - OutBridge;
    temp_xy = small(Cell_Point[14][4]);
    //qDebug()<<temp_xy[0]<<' '<<temp_xy[1];
    Cell_Point[14][6] = temp_xy[0];//Cell_Point[10][6];
    Cell_Point[14][7] = temp_xy[1];//Cell_Point[10][7] - OutBridge;
    //16（右下角）
    Cell_Point[15][0] = 0;
    Cell_Point[15][1] = Cell_Point[11][1] + OutBridge;
    Cell_Point[15][3] = 0;
    Cell_Point[15][4] = Cell_Point[14][4] - OutBridge;
    temp_xy = small(Cell_Point[15][4]);
    //qDebug()<<temp_xy[0]<<' '<<temp_xy[1];
    Cell_Point[15][6] = temp_xy[0];//Cell_Point[11][6];
    Cell_Point[15][7] = temp_xy[1];//Cell_Point[11][7] - OutBridge;

//    for (int i=0;i<16;i++){
//        //p->drawEllipse(QPoint(Cell_Point[i][6],Cell_Point[i][7]),10,10);
//        qDebug()<<QString('i=')<<i<<' '<<Cell_Point[i][6]<<' '<<Cell_Point[i][7];
//    }


    //碰撞状态记录的初始化
    record_pass = new int*[8];
    record_collision_cross = new int*[16];
    record_collision_front_old = new int*[8];
    record_collision_front_new = new int*[8];

    for (int i=0;i<8;i++){
        record_pass[i] = new int[2];
        record_pass[i][0] = 0;
        record_pass[i][1] = 0;

        record_collision_front_new[i] = new int[8];
        record_collision_front_old[i] = new int[8];
        for (int j=0;j<8;j++){
            record_collision_front_new[i][j] = 0;
            record_collision_front_old[i][j] = 0;
        }
    }

    for (int i=0;i<16;i++){
        record_collision_cross[i] = new int[2];
        record_collision_cross[i][0] = 0;
        record_collision_cross[i][1] = 0;
    }



//    DIST_OUTPUT = new double[6];
//    V_OUTPUT = new double[25];

//    for (int j=0;j<6;j++){
//        DIST_OUTPUT[j] = 0;
//    }

//    for (int k=0;k<25;k++){
//        DIST_OUTPUT[k] = 0;
//    }



}


Map::~Map()
{
    delete ui;
}

void Map::end_game(){
    timer->stop();
    qDebug()<<"stop";
}
int Map::show_num_collision(){
    return NUM_COLLISION;
}



int Map::show_num_pass(){
    return NUM_PASS;
}

void Map::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setWindow(0, 0, 1000, 1000);
    p.translate(500,500);//重新设定坐标原点
    drawmap(&p);
    drawcircles(&p);
}

void Map::drawmap(QPainter *p)
{
    p->setBrush(Qt::black);
    p->setPen(Qt::black);
    //画大圈的直线
    p->drawLine(QPoint(OutCorDownLeft_1_X, OutCorDownLeft_1_Y), QPoint(OutCorDownLeft_2_X, OutCorDownLeft_2_Y));
    p->drawLine(QPoint(OutCorDownLeft_3_X, OutCorDownLeft_3_Y), QPoint(OutCorDownLeft_4_X, OutCorDownLeft_4_Y));
    p->drawLine(QPoint(OutCorDownLeft_5_X, OutCorDownLeft_5_Y), QPoint(OutCorDownLeft_6_X, OutCorDownLeft_6_Y));
    p->drawLine(QPoint(OutCorDownLeft_7_X, OutCorDownLeft_7_Y), QPoint(OutCorDownRight_2_X, OutCorDownRight_2_Y));
    p->drawLine(QPoint(OutCorDownRight_3_X, OutCorDownRight_3_Y), QPoint(OutCorDownRight_4_X, OutCorDownRight_4_Y));
    p->drawLine(QPoint(OutCorDownRight_5_X, OutCorDownRight_5_Y), QPoint(OutCorDownRight_6_X, OutCorDownRight_6_Y));
    p->drawLine(QPoint(OutCorDownRight_7_X, OutCorDownRight_7_Y), QPoint(OutCorUpRight_2_X, OutCorUpRight_2_Y));
    p->drawLine(QPoint(OutCorUpRight_3_X, OutCorUpRight_3_Y), QPoint(OutCorUpRight_4_X, OutCorUpRight_4_Y));
    p->drawLine(QPoint(OutCorUpRight_5_X, OutCorUpRight_5_Y), QPoint(OutCorUpRight_6_X, OutCorUpRight_6_Y));
    p->drawLine(QPoint(OutCorUpRight_7_X, OutCorUpRight_7_Y), QPoint(OutCorUpLeft_2_X, OutCorUpLeft_2_Y));
    p->drawLine(QPoint(OutCorUpLeft_3_X, OutCorUpLeft_3_Y), QPoint(OutCorUpLeft_4_X, OutCorUpLeft_4_Y));
    p->drawLine(QPoint(OutCorUpLeft_5_X, OutCorUpLeft_5_Y), QPoint(OutCorUpLeft_6_X, OutCorUpLeft_6_Y));
    p->drawLine(QPoint(OutCorUpLeft_7_X, OutCorUpLeft_7_Y), QPoint(OutCorDownLeft_1_X, OutCorDownLeft_1_Y));
    //画大圈的弧
    p->drawArc(OutCorDownLeft_3_X-R,OutCorDownLeft_2_Y-R,2*R,2*R,0*90*16,-90*16);
    p->drawArc(OutCorDownLeft_5_X,OutCorDownLeft_5_Y-R,2*R,2*R,3*90*16,-90*16);
    p->drawArc(OutCorDownLeft_6_X,OutCorDownLeft_6_Y-R,2*R,2*R,180*16,-90*16);
    p->drawArc(OutCorDownRight_2_X-R,OutCorDownRight_2_Y,2*R,2*R,90*16,-90*16);
    p->drawArc(OutCorDownRight_5_X-R,OutCorDownRight_4_Y-R,2*R,2*R,0,-90*16);
    p->drawArc(OutCorDownRight_7_X,OutCorDownRight_7_Y-R,2*R,2*R,3*90*16,-90*16);
    p->drawArc(OutCorUpRight_2_X,OutCorUpRight_2_Y-R,2*R,2*R,2*90*16,-90*16);
    p->drawArc(OutCorUpRight_4_X-R,OutCorUpRight_4_Y,2*R,2*R,90*16,-90*16);
    p->drawArc(OutCorUpRight_7_X-R,OutCorUpRight_6_Y-R,2*R,2*R,0,-90*16);
    p->drawArc(OutCorUpLeft_3_X,OutCorUpLeft_3_Y-R,2*R,2*R,3*90*16,-90*16);
    p->drawArc(OutCorUpLeft_4_X,OutCorUpLeft_4_Y-R,2*R,2*R,2*90*16,-90*16);
    p->drawArc(OutCorUpLeft_6_X-R,OutCorUpLeft_6_Y,2*R,2*R,90*16,-90*16);
    //画小圈的直线
    p->drawLine(QPoint(InCorDownLeft_1_X, InCorDownLeft_1_Y), QPoint(InCorDownLeft_2_X, InCorDownLeft_2_Y));
    p->drawLine(QPoint(InCorDownLeft_3_X, InCorDownLeft_3_Y), QPoint(InCorDownLeft_4_X, InCorDownLeft_4_Y));
    p->drawLine(QPoint(InCorDownLeft_5_X, InCorDownLeft_5_Y), QPoint(InCorDownLeft_6_X, InCorDownLeft_6_Y));
    p->drawLine(QPoint(InCorDownLeft_7_X, InCorDownLeft_7_Y), QPoint(InCorDownRight_2_X, InCorDownRight_2_Y));
    p->drawLine(QPoint(InCorDownRight_3_X, InCorDownRight_3_Y), QPoint(InCorDownRight_4_X, InCorDownRight_4_Y));
    p->drawLine(QPoint(InCorDownRight_5_X, InCorDownRight_5_Y), QPoint(InCorDownRight_6_X, InCorDownRight_6_Y));
    p->drawLine(QPoint(InCorDownRight_7_X, InCorDownRight_7_Y), QPoint(InCorUpRight_2_X, InCorUpRight_2_Y));
    p->drawLine(QPoint(InCorUpRight_3_X, InCorUpRight_3_Y), QPoint(InCorUpRight_4_X, InCorUpRight_4_Y));
    p->drawLine(QPoint(InCorUpRight_5_X, InCorUpRight_5_Y), QPoint(InCorUpRight_6_X, InCorUpRight_6_Y));
    p->drawLine(QPoint(InCorUpRight_7_X, InCorUpRight_7_Y), QPoint(InCorUpLeft_2_X, InCorUpLeft_2_Y));
    p->drawLine(QPoint(InCorUpLeft_3_X, InCorUpLeft_3_Y), QPoint(InCorUpLeft_4_X, InCorUpLeft_4_Y));
    p->drawLine(QPoint(InCorUpLeft_5_X, InCorUpLeft_5_Y), QPoint(InCorUpLeft_6_X, InCorUpLeft_6_Y));
    p->drawLine(QPoint(InCorUpLeft_7_X, InCorUpLeft_7_Y), QPoint(InCorDownLeft_1_X, InCorDownLeft_1_Y));
    //画小圈的弧

    p->drawArc(InCorDownLeft_3_X-r,InCorDownLeft_2_Y-r,2*r,2*r,0*90*16,-90*16);
    p->drawArc(InCorDownLeft_5_X,InCorDownLeft_5_Y-r,2*r,2*r,3*90*16,-90*16);
    p->drawArc(InCorDownLeft_6_X,InCorDownLeft_6_Y-r,2*r,2*r,180*16,-90*16);
    p->drawArc(InCorDownRight_2_X-r,InCorDownRight_2_Y,2*r,2*r,90*16,-90*16);
    p->drawArc(InCorDownRight_5_X-r,InCorDownRight_4_Y-r,2*r,2*r,0,-90*16);
    p->drawArc(InCorDownRight_7_X,InCorDownRight_7_Y-r,2*r,2*r,3*90*16,-90*16);
    p->drawArc(InCorUpRight_2_X,InCorUpRight_2_Y-r,2*r,2*r,2*90*16,-90*16);
    p->drawArc(InCorUpRight_4_X-r,InCorUpRight_4_Y,2*r,2*r,90*16,-90*16);
    p->drawArc(InCorUpRight_7_X-r,InCorUpRight_6_Y-r,2*r,2*r,0,-90*16);
    p->drawArc(InCorUpLeft_3_X,InCorUpLeft_3_Y-r,2*r,2*r,3*90*16,-90*16);
    p->drawArc(InCorUpLeft_4_X,InCorUpLeft_4_Y-r,2*r,2*r,2*90*16,-90*16);
    p->drawArc(InCorUpLeft_6_X-r,InCorUpLeft_6_Y,2*r,2*r,90*16,-90*16);

//    for (int i=12;i<16;i++){
//    p->drawEllipse(QPoint(Cell_Point[i][6],Cell_Point[i][7]),10,10);
//}

    //




    //p->restore();

}

void Map::drawcircles(QPainter *p)
{
    count++;
    count_all++;
    if (count>1){
        count = count - 2;
    }
    p->setBrush(Qt::red);
    p->setPen(Qt::red);

    //距离转换到坐标
    double ** Cor_Car;
    double ** Fake_Cor_Car;
    Cor_Car = new double*[8];
    for (int i=0;i<8;i++)
        Cor_Car[i] = new double[3];
    Fake_Cor_Car = Cor_Car;//初始化
    Cor_Car = dist2cor(Dist_Car,NUM_SUM_CAR,NUM_BIG_CAR);
    Fake_Cor_Car = dist2cor(Fake_Dist_Car,NUM_SUM_CAR,NUM_BIG_CAR);//赋值

    //由Cor判断line_tag的状态
       for (int i=0;i<8;i++){
           if (Cor_Car[i][1]>=line_box[0] & Cor_Car[i][1]<=line_box[1] & Cor_Car[i][2]>=line_box[2] & Cor_Car[i][3]<=line_box[3]){
               line_tag[i] = 1;
           }
           else{
               line_tag[i] = 0;
           }
       }

    //记录crosspoint
    double *smallest_cross_dist_v;
    double *smallest_cross_dist_h;
    smallest_cross_dist_v = new double[2];      smallest_cross_dist_v[0] = 0;
    smallest_cross_dist_h = new double[2];      smallest_cross_dist_h[0] = 0;

    //由距离判断是否通过cross区域
        //首先把改状态更新 相当于pop up
    for (int i = 0;i<8;i++){
        record_pass[i][0] = record_pass[i][1];
    }

        //然后通过坐标来判断是否在区域内
    for (int i = 0;i<8;i++){
        if (Cor_Car[i][1]>=InCorDownLeft_1_X & Cor_Car[i][1]<=InCorDownRight_8_X & Cor_Car[i][2]>=InCorUpRight_8_Y & Cor_Car[i][2]<=InCorDownRight_1_Y){
            record_pass[i][1] = 1;
        }
        else{
            record_pass[i][1] = 0;
        }
    }

    //给Fake_Cor_Car加上噪声信号
    for (int i=0;i<8;i++){
        Fake_Cor_Car[i][1] += 3*get_random_error();
        Fake_Cor_Car[i][2] += 3*get_random_error();
    }

    //得到控制信号V

    if (count == 1){
        V_Car = decision_making(Fake_Cor_Car);//给的是有误差的位置

        //判断脉冲
        for (int i=0;i<8;i++){
            V_Car[i][1] = interp(V_Car[i][1]);
        }


        //V_Car = func_tag_v_main(V_Car,Dist_Car);
        //加入控制误差
        for (int i=0;i<8;i++){
           if (V_Car[i][1] <= 50)
               V_Car[i][1] = V_Car[i][1] * (1 + 0.1*get_random_error());
           else
               V_Car[i][1] = V_Car[i][1] * (1 + 0.25*get_random_error());
        }

    }

    //更新实际的速度
    V_Car_real = func_real_v(V_Car_real,V_Car,ACCLERATE);
    //******************把速度大小、速度tag记录在.txt文件中*****************//
    //判断车是否在中间的区域，来更新line_tag
    for (int i=0;i<8;i++){
        if( (Cor_Car[i][1]>=line_box[0]) & (Cor_Car[i][1]<=line_box[1]) & (Cor_Car[i][2]>=line_box[2]) & (Cor_Car[i][2]<=line_box[3])){
            line_tag[i] = 1;
        }
        else{
            line_tag[i] = 0;
        }
    }
//            QFile data("file.txt");
//            if (data.open(QFile::WriteOnly | QIODevice::Append)) {
//                QTextStream out(&data);
//                for (int i=0;i<8;i++){
//                    for (int j=0;j<2;j++){
//                        out << V_Car_real[i][j] <<"\t";
//                    }
//                }
//                out<<"\r\n";
//            }

    //都记录在一个.txt文件中




        QTextStream out(&data1);
        out << count_all << "\t";
        //time_step//
    if (count_all > 0){
        for (int i=0;i<8;i++){

            out << V_Car_real[i][0] << "\t" << V_Car_real[i][1]<< "\t" << line_tag[i] << "\t";
            //ID//                       //Velocity//              //Tag//
        }
        out<<"\r\n";
    }

        //data1.close();



    //先缓存起来
//    V_OUTPUT[count_all-1][0] = count_all;
//    for (int i=0;i<8;i++){
//        V_OUTPUT[count_all-1][3*i + 1] = V_Car_real[i][0];//ID
//        V_OUTPUT[count_all-1][3*i + 2] = V_Car_real[i][1];
//        V_OUTPUT[count_all-1][3*i + 3] = line_tag[i];
//    }
    //****************************************************************//







    //更新距离位置
    //Fake_Dist_Car 比Dist_Car 晚一步， Dist_Car得到Cor_Car（当前步）来判断碰撞，Fake_Dist_Car得到Fake_Cor_Car来输入学生端

    Fake_Dist_Car = Dist_Car;
    Dist_Car = update_position(V_Car_real,Dist_Car,NUM_SUM_CAR,NUM_BIG_CAR,t_paint);



    //新距离转换到新坐标
    Cor_Car = dist2cor(Dist_Car,NUM_SUM_CAR,NUM_BIG_CAR);

    //画车的位置
    for (int i=0;i<8;i++){
        p->drawEllipse(QPoint(Cor_Car[i][1],Cor_Car[i][2]),10,10);
    }

    //判断有没有撞
    //int flag=0;

//    flag = collision_info(Dist_Car,V_Car);
    //*********************inline
    int collision = 0;

    //大圈内部是否发生追尾
    double *Dist1 = new double[2];          Dist1[0] = 0; Dist1[1] = 0;
    double *Dist2 = new double[2];          Dist2[0] = 0; Dist1[1] = 0;
    double dist_temp = 0;
    double f_thresh_base = 20;
    double f_thresh = 0;//等于f_thresh_base加上一个和速度有关的
    double b_thresh = 15;
    double cf_thresh = 0;//前后跟车的最小距离，V<80是35，V>=80是45
    double *Dist_Forward = new double[2];   Dist_Forward[0] = 0; Dist_Forward[1] = 0;
    double *Dist_Backward = new double[2];  Dist_Backward[0] = 0; Dist_Backward[1] = 0;
    double *Dist_Big = new double[2];       Dist_Big[0] = 0; Dist_Big[1] = 0;
    double *Dist_Small = new double[2];     Dist_Small[0] = 0; Dist_Small[1] = 0;
    int flag = 0;
    int idx_big = 1;
    int idx_small = 1;
    int idx_forward = 1;
    int idx_backward = 1;


    //********************判断碰撞******************************
    //碰撞更新 相当于pop up
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            record_collision_front_old[i][j] = record_collision_front_new[i][j];
        }
    }

    for (int i=0;i<4;i++)
    {                
        //判断碰撞
        for (int j=0;j<4;j++)
        {
            if (i>j)
            {
                Dist1[0] = i;
                Dist2[0] = j;
                Dist1[1] = Dist_Car[i];
                Dist2[1] = Dist_Car[j];
                if(Dist1[1]>=Dist2[1]) {
                    Dist_Big = Dist1;
                    Dist_Small = Dist2;
                    idx_big = i;
                    idx_small = j;
                }
                else {
                    Dist_Big = Dist2;
                    Dist_Small = Dist1;
                    idx_big = j;
                    idx_small = i;
                }
                if ((Dist_Big[1]-Dist_Small[1])<=(OutDistDownLeft_1_End-(Dist_Big[1]-Dist_Small[1]))){
                    Dist_Forward = Dist_Big;
                    Dist_Backward = Dist_Small;
                    idx_forward = idx_big;
                    idx_backward = idx_small;
                    dist_temp = Dist_Big[1]-Dist_Small[1];
                }
                else {
                    Dist_Forward = Dist_Small;
                    Dist_Backward = Dist_Big;
                    idx_forward = idx_small;
                    idx_backward = idx_big;
                    dist_temp = OutDistDownLeft_1_End-(Dist_Big[1]-Dist_Small[1]);
                }
                if(V_Car[idx_backward][1]<80){
                    cf_thresh = 35;
                }
                else{cf_thresh = 45;}
                if (dist_temp < cf_thresh)
                {
                    collision = 1;
                    p->setBrush(Qt::white);
                    p->setPen(Qt::white);
                    p->drawEllipse(QPoint(Cor_Car[i][1],Cor_Car[i][2]),10,10);
                    p->drawEllipse(QPoint(Cor_Car[j][1],Cor_Car[j][2]),10,10);
                    ////**看相撞时的position
                    //cout<<"i="<<i<<" j="<<j<<endl<<"  dist= "<<dist<<endl;
                    //cout<<"Position_"<<i<<" X="<<x1<<" Y="<<y1<<endl;
                    //cout<<"Position_"<<j<<" X="<<x2<<" Y="<<y2<<endl<<endl;
                    ////**

                    //记录碰撞状态
                    record_collision_front_new[i][j] = 1;
                }
                else{
                    record_collision_front_new[i][j] = 0;
                }
            }
        }
    }
    //小圈内部是否发生追尾

    for (int i=4;i<8;i++)
    {
        for (int j=4;j<8;j++)
        {
            if (i>j)
            {
                Dist1[0] = i;
                Dist2[0] = j;
                Dist1[1] = Dist_Car[i];
                Dist2[1] = Dist_Car[j];
                if(Dist1[1]>=Dist2[1]) {
                    Dist_Big = Dist1;
                    Dist_Small = Dist2;
                    idx_big = i;
                    idx_small = j;
                }
                else {
                    Dist_Big = Dist2;
                    Dist_Small = Dist1;
                    idx_big = j;
                    idx_small = i;
                }
                if ((Dist_Big[1]-Dist_Small[1])<=(InDistDownLeft_1_End-(Dist_Big[1]-Dist_Small[1]))){
                    Dist_Forward = Dist_Big;
                    Dist_Backward = Dist_Small;
                    idx_forward = idx_big;
                    idx_backward = idx_small;
                    dist_temp = Dist_Big[1]-Dist_Small[1];
                }
                else {
                    Dist_Forward = Dist_Small;
                    Dist_Backward = Dist_Big;
                    idx_forward = idx_small;
                    idx_backward = idx_big;
                    dist_temp = InDistDownLeft_1_End-(Dist_Big[1]-Dist_Small[1]);
                }
                if(V_Car[idx_backward][1]<80){
                    cf_thresh = 35;
                }
                else{cf_thresh = 45;}
                if (dist_temp < cf_thresh)
                {
                    collision = 1;
                    p->setBrush(Qt::white);
                    p->setPen(Qt::white);
                    p->drawEllipse(QPoint(Cor_Car[i][1],Cor_Car[i][2]),10,10);
                    p->drawEllipse(QPoint(Cor_Car[j][1],Cor_Car[j][2]),10,10);
                    ////**看相撞时的position
                    //cout<<"i="<<i<<" j="<<j<<endl<<"  dist= "<<dist<<endl;
                    //cout<<"Position_"<<i<<" X="<<x1<<" Y="<<y1<<endl;
                    //cout<<"Position_"<<j<<" X="<<x2<<" Y="<<y2<<endl<<endl;
                    ////**
                    record_collision_front_new[i][j] = 1;
                }
                else{
                    record_collision_front_new[i][j] = 0;
                }
            }
        }
    }






    //给Cell_Point加tag，通过两个方向tag的比较可以判断是否相撞S
    p->setBrush(Qt::blue);
    p->setPen(Qt::blue);

    double *dist_temp_v;//竖的记录每辆车到cross的距离，想从中间选最大的那个
    dist_temp_v = new double[8]; for (int i=0;i<8;i++){dist_temp_v[i] = 0;}

    double *dist_temp_h;//横的记录每辆车到cross的距离，想从中间选最大的那个
    dist_temp_h = new double[8]; for (int i=0;i<8;i++){dist_temp_h[i] = 0;}

    int cross_ID = 0;
    for (int i=0;i<16;i++){
        //竖的方向--v

        if (Cell_Point[i][0] == 0){//[i][0]这一列就是竖的方向，是否为0来判断大小圈
            for (int j=4;j<8;j++){
                dist_temp_v[j] = Cell_Point[i][1]-Dist_Car[j];
                if (V_Car[j][1]<80){
                    f_thresh = f_thresh_base+35;
                }
                else{
                    f_thresh = f_thresh_base+45;
                }
                if((dist_temp_v[j]<f_thresh)&(dist_temp_v[j]>-1*b_thresh))
                {
                    flag = 1;

                }
            }
        }//小圈
        else{
            for (int j=0;j<4;j++){
                dist_temp_v[j] = Cell_Point[i][1] - Dist_Car[j];
                if (V_Car[j][1]<80){
                    f_thresh = f_thresh_base+35;
                }
                else{
                    f_thresh = f_thresh_base+45;
                }
                if((dist_temp_v[j]<f_thresh)&(dist_temp_v[j]>-1*b_thresh)){
                  {
                        flag = 1;

                    }

                }
            }
        }



        if (flag==1){
           Cell_Point[i][2] = 1;
          // p->drawEllipse(QPoint(Cell_Point[i][6],Cell_Point[i][7]),5,5);
           flag = 0;
        }
        else{
            Cell_Point[i][2] = 0;
        }





        //横的方向
        if (Cell_Point[i][3] == 0){
            for (int j=4;j<8;j++){
                dist_temp_h[j] = Cell_Point[i][4]-Dist_Car[j];
                if (V_Car[j][1]<80){
                    f_thresh = f_thresh_base+35;
                }
                else{
                    f_thresh = f_thresh_base+45;
                }
                if((dist_temp_h[j]<f_thresh)&(dist_temp_h[j]>-1*b_thresh))
                    flag = 1;

            }
        }//小圈
        else{
            for (int j=0;j<4;j++){
                dist_temp_h[j] = Cell_Point[i][4] - Dist_Car[j];
                if (V_Car[j][1]<80){
                    f_thresh = f_thresh_base+35;
                }
                else{
                    f_thresh = f_thresh_base+45;
                }
                if((dist_temp_h[j]<f_thresh)&(dist_temp_h[j]>-1*b_thresh))
                    flag = 1;

            }
        }

        if (flag==1){
           Cell_Point[i][5] = 1;
          // p->drawEllipse(QPoint(Cell_Point[i][6],Cell_Point[i][7]),5,5);
           flag = 0;
        }
        else{
            Cell_Point[i][5] = 0;
        }




        cross_ID = i;
        smallest_cross_dist_v = f_min_positive(dist_temp_v);
        smallest_cross_dist_h = f_min_positive(dist_temp_h);




        //$$$$$$$$$$$$$$$$$$$$$把dist记录在.txt文件中$$$$$$$$$$$$$$$$$//



//        if (count_all > 1000){

//                QTextStream out1(&data2);
//                int v_idx = int(smallest_cross_dist_v[0]);
//                int h_idx = int(smallest_cross_dist_h[0]);
//                out1<<count_all<<"\t"<<cross_ID<<"\t"<<ID_map[v_idx]<<"\t"<<smallest_cross_dist_v[1]<<"\t"<<ID_map[h_idx]<<"\t"<<smallest_cross_dist_h[1];
//                out1<<"\r\n";
//               // data2.close();
//        }

//        //先缓存起来

//        DIST_OUTPUT[count_all-1][0] = count_all;
//        DIST_OUTPUT[count_all-1][1] = cross_ID;//ID
//        DIST_OUTPUT[count_all-1][2] = ID_map[v_idx];
//        DIST_OUTPUT[count_all-1][3] = smallest_cross_dist_v[1];
//        DIST_OUTPUT[count_all-1][4] = ID_map[h_idx];
//        DIST_OUTPUT[count_all-1][5] = smallest_cross_dist_h[1];




        //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$//

    }
    //   单纯地记录8个Cor
            if (count_all > 0){

                QTextStream out3(&data3);
                out3<<count_all<<"\t";
                for (int i = 0;i<7;i++){
                    out3<<Cor_Car[i][1]<<"\t"<<Cor_Car[i][2]<<"\t";
                }
                out3<<Cor_Car[7][1]<<"\t"<<Cor_Car[7][2]<<"\r\n";
                // data2.close();
            }

    //判断是否相撞
    for (int i=0;i<16;i++){
        //把碰撞状态更新 相当于pop up
        record_collision_cross[i][0] = record_collision_cross[i][1];

        //判断碰撞
        if ( (Cell_Point[i][2] == 1) & (Cell_Point[i][5] == 1) ) {
            collision = 1;
            //qDebug()<<i<<endl;
            //qDebug()<<Cell_Point[i][0]<<Cell_Point[i][1]<<Cell_Point[i][2]<<Cell_Point[i][3]<<Cell_Point[i][4]<<Cell_Point[i][5];
            p->setBrush(Qt::yellow);
            p->setPen(Qt::yellow);
            p->drawEllipse(QPoint(Cell_Point[i][6],Cell_Point[i][7]),10,10);

            //把碰撞状态记录下来
            record_collision_cross[i][1] = 1;
            }
        else{
            record_collision_cross[i][1] = 0;
        }
    }

    //碰撞次数更新
    for (int i=0;i<16;i++){
        if( (record_collision_cross[i][0] == 0)&(record_collision_cross[i][1] == 1)){
            NUM_COLLISION = NUM_COLLISION + 1;
        }
    }

    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            if (i>j){
                if((record_collision_front_old[i][j] == 0)&(record_collision_front_new[i][j] == 1)){
                    NUM_COLLISION = NUM_COLLISION +1;
                }
            }
        }
    }

    //通过次数更新
    for (int i=0;i<8;i++){

        if (record_pass[i][0] == 1 & record_pass[i][1] == 0){
            NUM_PASS = NUM_PASS + 1;
        }
    }



    //判断是否到时间
    qDebug()<<count_all;
    if (count_all == count_limit){



//        // 存dist
//        QFile data("dist.txt");
//        if (data.open(QFile::WriteOnly | QIODevice::Append)) {
//            QTextStream out(&data);

//            for (int i=0;i<count_all;i++){
//                for (int j=0;j<6;j++){
//                    out << DIST_OUTPUT[i][j];
//                }
//                out << "/r/n";
//            }
//        }



//        // 存v
//        QFile data1("V_assemble.txt");
//        if (data.open(QFile::WriteOnly | QIODevice::Append)) {
//            QTextStream out(&data1);

//            out << count_all << "\t";
//            for (int i=0;i<count_all;i++){
//                for (int j=0;j<25;j++){
//                    out << V_OUTPUT[i][j];
//                }
//                out << "/r/n";
//            }


//        }
        end_game();
    }

//    delete &smallest_cross_dist_h;
//    delete &smallest_cross_dist_v;
//    delete &collision;
//    delete &dist_temp;
//    delete &dist_temp_h;
//    delete &dist_temp_v;
//    delete &f_thresh;
//    delete &cf_thresh;
//    delete &flag;
//    delete &idx_backward;
//    delete &idx_forward;
//    delete &idx_small;
//    delete &idx_big;
}



