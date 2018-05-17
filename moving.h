#ifndef MOVING_H
#define MOVING_H

#include "cor_map.h"
#include<QDebug>
#include<QTime>
#include <cstdlib>




//由坐标信息生成V控制信号
double ** decision_making(double **StudentIN)//StudentIN8行3列
{
    //定义决策程序输出StudentOUT
    double **StudentOUT = (double**)calloc(8, sizeof(double*));
    for (int i=0;i<8;i++){
        StudentOUT[i] = (double*)calloc(2,sizeof(double));
    };
    //定义中间变量
    double ID_1 = StudentIN[0][0];//第一辆小车的ID
    double x_1 = StudentIN[0][1];//第一辆小车的横坐标
    double y_1 = StudentIN[0][2];//第一辆小车的纵坐标

    double ID_2 = StudentIN[1][0];//第二辆小车的ID
    double x_2 = StudentIN[1][1];//第二辆小车的横坐标
    double y_2 = StudentIN[1][2];//第二辆小车的纵坐标

    double ID_3 = StudentIN[2][0];//第三辆小车的ID
    double x_3 = StudentIN[2][1];//第三辆小车的横坐标
    double y_3 = StudentIN[2][2];//第三辆小车的纵坐标

    double ID_4 = StudentIN[3][0];//第四辆小车的ID
    double x_4 = StudentIN[3][1];//第四辆小车的横坐标
    double y_4 = StudentIN[3][2];//第四辆小车的纵坐标

    double ID_5 = StudentIN[4][0];//第五辆小车的ID
    double x_5 = StudentIN[4][1];//第五辆小车的横坐标
    double y_5 = StudentIN[4][2];//第五辆小车的纵坐标

    double ID_6 = StudentIN[5][0];//第六辆小车的ID
    double x_6 = StudentIN[5][1];//第六辆小车的横坐标
    double y_6 = StudentIN[5][2];//第六辆小车的纵坐标

    double ID_7 = StudentIN[6][0];//第七辆小车的ID
    double x_7 = StudentIN[6][1];//第七辆小车的横坐标
    double y_7 = StudentIN[6][2];//第七辆小车的纵坐标

    double ID_8 = StudentIN[7][0];//第八辆小车的ID
    double x_8 = StudentIN[7][1];//第八辆小车的横坐标
    double y_8 = StudentIN[7][2];//第八辆小车的纵坐标
    //***************决策程序修改开始位置*************//






  //***************决策程序修改结束位置*************//
    return StudentOUT;
}

double interp(double PWM_In){
    double *PWM_map = new double[13];
    double *V_map = new double[13];
    PWM_map[0] = 0;PWM_map[1] = 9; PWM_map[2] = 17; PWM_map[3] = 26; PWM_map[4] = 34; PWM_map[5] = 43; PWM_map[6] = 52;
    PWM_map[7] = 60; PWM_map[8] = 69; PWM_map[9] = 77; PWM_map[10] = 86; PWM_map[11] = 95; PWM_map[12] = 103;

    V_map[0] = 0; V_map[1] = 10; V_map[2] = 20; V_map[3] = 30; V_map[4] = 40; V_map[5] = 50; V_map[6] = 60;
    V_map[7] = 70; V_map[8] = 80; V_map[9] = 90; V_map[10] = 100; V_map[11] = 110; V_map[12] = 120;
    double V_Out;
    int idx = 0;
    if (PWM_In>=103) V_Out = 120;
    else if(PWM_In<=0) V_Out = 0;
    else{
        for (int i=0;i<12;i++){
            if (PWM_In>=PWM_map[i] && PWM_In<PWM_map[i+1]){
                idx = i;
            }

        }
        V_Out = V_map[idx] + (PWM_In - PWM_map[idx])*(V_map[idx+1] - V_map[idx])/(PWM_map[idx+1] - PWM_map[idx]);
    }
    return V_Out;
}


extern double * big(double Dist)
{


    //如果距离大于一圈的距离，则清零
    if (Dist>OutDistDownLeft_1_End) Dist = Dist - OutDistDownLeft_1_End;



    //声明坐标变量xy以及中间变量theta
    double x,y,theta;
    double *Cor;
    Cor = new double[2];
    //距离-xy坐标的映射函数
    if (Dist>=OutDistDownLeft_1_Start && Dist<=OutDistDownLeft_2)
    {
        x = OutCorDownLeft_1_X;
        y = OutCorDownLeft_1_Y + (Dist - OutDistDownLeft_1_Start);
    }//DownLeft 1-2
    else if (Dist>OutDistDownLeft_2 && Dist<=OutDistDownLeft_3)
    {
        theta = (Dist - OutDistDownLeft_2) / R;
        x = OutCorDownLeft_2_X - R*(1 - cos(theta));
        y = OutCorDownLeft_2_Y + R*sin(theta);
    }//DownLeft 2-3
    else if (Dist>OutDistDownLeft_3 && Dist<=OutDistDownLeft_4)
    {
        x = OutCorDownLeft_3_X - (Dist - OutDistDownLeft_3);
        y = OutCorDownLeft_3_Y;
    }//DownLeft 3-4
    else if (Dist>OutDistDownLeft_4 && Dist<=OutDistDownLeft_5)
    {
        theta = (Dist - OutDistDownLeft_4) / R;
        x = OutCorDownLeft_4_X - R*sin(theta);
        y = OutCorDownLeft_4_Y - R*(1 - cos(theta));
    }//DownLeft 4-5
    else if (Dist>OutDistDownLeft_5 && Dist<=OutDistDownLeft_6)
    {
        x = OutCorDownLeft_5_X;
        y = OutCorDownLeft_5_Y - (Dist - OutDistDownLeft_5);
    }//DownLeft 5-6
    else if (Dist>OutDistDownLeft_6 && Dist<=OutDistDownLeft_7)
    {
        theta = (Dist - OutDistDownLeft_6) / R;
        x = OutCorDownLeft_6_X + R*(1 - cos(theta));
        y = OutCorDownLeft_6_Y - R*sin(theta);
        //cout<<endl<<"In big Position7"<<"x="<<x<<" y="<<y<<endl<<endl;
    }//DownLeft 6-7
    else if (Dist>OutDistDownLeft_7 && Dist<=OutDistDownLeft_8)
    {
        x = OutCorDownLeft_7_X + (Dist - OutDistDownLeft_7);
        y = OutCorDownLeft_7_Y;
    }//DownLeft 7-8
    else if (Dist>OutDistDownLeft_8 && Dist<=OutDistDownRight_1)
    {
        x = OutCorDownLeft_8_X + (Dist - OutDistDownLeft_8);
        y = OutCorDownLeft_8_Y;
    }//DownLeft 8 - DownRight 1
    /////////////////////////////////////////////////////////////

    else if (Dist>OutDistDownRight_1 && Dist<=OutDistDownRight_2)
    {
        x = OutCorDownRight_1_X + (Dist - OutDistDownRight_1);
        y = OutCorDownRight_1_Y;
    }//DownRight 1-2
    else if (Dist>OutDistDownRight_2 && Dist<=OutDistDownRight_3)
    {
        theta = (Dist - OutDistDownRight_2) / R;
        x = OutCorDownRight_2_X + R*sin(theta);
        y = OutCorDownRight_2_Y + R*(1 - cos(theta));
    }//DownRight 2-3
    else if (Dist>OutDistDownRight_3 && Dist<=OutDistDownRight_4)
    {
        x = OutCorDownRight_3_X;
        y = OutCorDownRight_3_Y + (Dist - OutDistDownRight_3);
    }//DownRight 3-4
    else if (Dist>OutDistDownRight_4 && Dist<=OutDistDownRight_5)
    {
        theta = (Dist - OutDistDownRight_4) / R;
        x = OutCorDownRight_4_X - R*(1 - cos(theta));
        y = OutCorDownRight_4_Y + R*sin(theta);
    }//DownRight 4-5
    else if (Dist>OutDistDownRight_5 && Dist<=OutDistDownRight_6)
    {
        x = OutCorDownRight_5_X - (Dist - OutDistDownRight_5);
        y = OutCorDownRight_5_Y;
    }//DownRight 5-6
    else if (Dist>OutDistDownRight_6 && Dist<=OutDistDownRight_7)
    {
        theta = (Dist - OutDistDownRight_6) / R;
        x = OutCorDownRight_6_X - R*sin(theta);
        y = OutCorDownRight_6_Y - R*(1 - cos(theta));
        //cout<<endl<<"In big Position7"<<"x="<<x<<" y="<<y<<endl<<endl;
    }//DownRight 6-7
    else if (Dist>OutDistDownRight_7 && Dist<=OutDistDownRight_8)
    {
        x = OutCorDownRight_7_X;
        y = OutCorDownRight_7_Y - (Dist - OutDistDownRight_7);
    }//DownRight 7-8
    else if (Dist>OutDistDownRight_8 && Dist<=OutDistUpRight_1)
    {
        x = OutCorDownRight_8_X;
        y = OutCorDownRight_8_Y - (Dist - OutDistDownRight_8);
    }//DownRight 8 - UpRight 1
    //////////////////////////////////////////////////////////////////

    else if (Dist>OutDistUpRight_1 && Dist<=OutDistUpRight_2)
    {
        x = OutCorUpRight_1_X;
        y = OutCorUpRight_1_Y - (Dist - OutDistUpRight_1);
    }//UpRight 1-2
    else if (Dist>OutDistUpRight_2 && Dist<=OutDistUpRight_3)
    {
        theta = (Dist - OutDistUpRight_2) / R;
        x = OutCorUpRight_2_X + R*(1 - cos(theta));
        y = OutCorUpRight_2_Y - R*sin(theta);
    }//UpRight 2-3
    else if (Dist>OutDistUpRight_3 && Dist<=OutDistUpRight_4)
    {
        x = OutCorUpRight_3_X + (Dist - OutDistUpRight_3);
        y = OutCorUpRight_3_Y;
    }//UpRight 3-4
    else if (Dist>OutDistUpRight_4 && Dist<=OutDistUpRight_5)
    {
        theta = (Dist - OutDistUpRight_4) / R;
        x = OutCorUpRight_4_X + R*sin(theta);
        y = OutCorUpRight_4_Y + R*(1 - cos(theta));
    }//UpRight 4-5
    else if (Dist>OutDistUpRight_5 && Dist<=OutDistUpRight_6)
    {
        x = OutCorUpRight_5_X;
        y = OutCorUpRight_5_Y + (Dist - OutDistUpRight_5);
    }//UpRight 5-6
    else if (Dist>OutDistUpRight_6 && Dist<=OutDistUpRight_7)
    {
        theta = (Dist - OutDistUpRight_6) / R;
        x = OutCorUpRight_6_X - R*(1 - cos(theta));
        y = OutCorUpRight_6_Y + R*sin(theta);
    //	cout<<endl<<"In big Position7"<<"x="<<x<<" y="<<y<<endl<<endl;
    }//UpRight 6-7
    else if (Dist>OutDistUpRight_7 && Dist<=OutDistUpRight_8)
    {
        x = OutCorUpRight_7_X - (Dist - OutDistUpRight_7);
        y = OutCorUpRight_7_Y;
    }//UpRight 7-8
    else if (Dist>OutDistUpRight_8 && Dist<=OutDistUpLeft_1)
    {
        x = OutCorUpRight_8_X - (Dist - OutDistUpRight_8);
        y = OutCorUpRight_8_Y;
    }//UpRight 8 - Upleft 1
    /////////////////////////////////////////////////////////////

    else if (Dist>OutDistUpLeft_1 && Dist<=OutDistUpLeft_2)
    {
        x = OutCorUpLeft_1_X - (Dist - OutDistUpLeft_1);
        y = OutCorUpLeft_1_Y;
    }//UpLeft 1-2
    else if (Dist>OutDistUpLeft_2 && Dist<=OutDistUpLeft_3)
    {
        theta = (Dist - OutDistUpLeft_2) / R;
        x = OutCorUpLeft_2_X - R*sin(theta);
        y = OutCorUpLeft_2_Y - R*(1 - cos(theta));
    }//UpLeft 2-3
    else if (Dist>OutDistUpLeft_3 && Dist<=OutDistUpLeft_4)
    {
        x = OutCorUpLeft_3_X;
        y = OutCorUpLeft_3_Y - (Dist - OutDistUpLeft_3);
    }//UpLeft 3-4
    else if (Dist>OutDistUpLeft_4 && Dist<=OutDistUpLeft_5)
    {
        theta = (Dist - OutDistUpLeft_4) / R;
        x = OutCorUpLeft_4_X + R*(1 - cos(theta));
        y = OutCorUpLeft_4_Y - R*sin(theta);
    }//UpLeft 4-5
    else if (Dist>OutDistUpLeft_5 && Dist<=OutDistUpLeft_6)
    {
        x = OutCorUpLeft_5_X + (Dist - OutDistUpLeft_5);
        y = OutCorUpLeft_5_Y;
    }//UpLeft 5-6
    else if (Dist>OutDistUpLeft_6 && Dist<=OutDistUpLeft_7)
    {
        theta = (Dist - OutDistUpLeft_6) / R;
        x = OutCorUpLeft_6_X + R*sin(theta);
        y = OutCorUpLeft_6_Y + R*(1 - cos(theta));
        //cout<<endl<<"In big Position7"<<"x="<<x<<" y="<<y<<endl<<endl;
    }//UpLeft 6-7
    else if (Dist>OutDistUpLeft_7 && Dist<=OutDistUpLeft_8)
    {
        x = OutCorUpLeft_7_X;
        y = OutCorUpLeft_7_Y + (Dist - OutDistUpLeft_7);
    }//UpLeft 7-8
    else if (Dist>OutDistUpLeft_8 && Dist<=OutDistDownLeft_1_End)
    {
        x = OutCorUpLeft_8_X;
        y = OutCorUpLeft_8_Y + (Dist - OutDistUpLeft_8);
    }//UpLeft 8 - DownLeft 1 End
    else
    {
        printf("error");
    }
    Cor[0] = x;
    Cor[1] = y;
    ////**
    //cout<<"In big"<<endl;
    //cout<<"x="<<x<<" y="<<y<<endl<<endl;
    ////**
    return Cor;
}

//小圈的Dist到x，y的映射
extern double *  small(double Dist)
{


    //如果距离大于一圈的距离，则清零
    if (Dist>InDistDownLeft_1_End) Dist = Dist - InDistDownLeft_1_End;



    //声明坐标变量xy以及中间变量theta
    double x,y,theta;

    double *Cor;
    Cor = new double[2];
    //距离-xy坐标的映射函数
    if (Dist>=InDistDownLeft_1_Start && Dist<=InDistDownLeft_2)
    {
        x = InCorDownLeft_1_X;
        y = InCorDownLeft_1_Y + (Dist - InDistDownLeft_1_Start);
    }//DownLeft 1-2
    else if (Dist>InDistDownLeft_2 && Dist<=InDistDownLeft_3)
    {
        theta = (Dist - InDistDownLeft_2) / r;
        x = InCorDownLeft_2_X - r*(1 - cos(theta));
        y = InCorDownLeft_2_Y + r*sin(theta);
    }//DownLeft 2-3
    else if (Dist>InDistDownLeft_3 && Dist<=InDistDownLeft_4)
    {
        x = InCorDownLeft_3_X - (Dist - InDistDownLeft_3);
        y = InCorDownLeft_3_Y;
    }//DownLeft 3-4
    else if (Dist>InDistDownLeft_4 && Dist<=InDistDownLeft_5)
    {
        theta = (Dist - InDistDownLeft_4) / r;
        x = InCorDownLeft_4_X - r*sin(theta);
        y = InCorDownLeft_4_Y - r*(1 - cos(theta));
    }//DownLeft 4-5
    else if (Dist>InDistDownLeft_5 && Dist<=InDistDownLeft_6)
    {
        x = InCorDownLeft_5_X;
        y = InCorDownLeft_5_Y - (Dist - InDistDownLeft_5);
    }//DownLeft 5-6
    else if (Dist>InDistDownLeft_6 && Dist<=InDistDownLeft_7)
    {
        theta = (Dist - InDistDownLeft_6) / r;
        x = InCorDownLeft_6_X + r*(1 - cos(theta));
        y = InCorDownLeft_6_Y - r*sin(theta);
    }//DownLeft 6-7
    else if (Dist>InDistDownLeft_7 && Dist<=InDistDownLeft_8)
    {
        x = InCorDownLeft_7_X + (Dist - InDistDownLeft_7);
        y = InCorDownLeft_7_Y;
    }//DownLeft 7-8
    else if (Dist>InDistDownLeft_8 && Dist<=InDistDownRight_1)
    {
        x = InCorDownLeft_8_X + (Dist - InDistDownLeft_8);
        y = InCorDownLeft_8_Y;
    }//DownLeft 8 - DownRight 1
    /////////////////////////////////////////////////////////////

    else if (Dist>InDistDownRight_1 && Dist<=InDistDownRight_2)
    {
        x = InCorDownRight_1_X + (Dist - InDistDownRight_1);
        y = InCorDownRight_1_Y;
    }//DownRight 1-2
    else if (Dist>InDistDownRight_2 && Dist<=InDistDownRight_3)
    {
        theta = (Dist - InDistDownRight_2) / r;
        x = InCorDownRight_2_X + r*sin(theta);
        y = InCorDownRight_2_Y + r*(1 - cos(theta));
    }//DownRight 2-3
    else if (Dist>InDistDownRight_3 && Dist<=InDistDownRight_4)
    {
        x = InCorDownRight_3_X;
        y = InCorDownRight_3_Y + (Dist - InDistDownRight_3);
    }//DownRight 3-4
    else if (Dist>InDistDownRight_4 && Dist<=InDistDownRight_5)
    {
        theta = (Dist - InDistDownRight_4) / r;
        x = InCorDownRight_4_X - r*(1 - cos(theta));
        y = InCorDownRight_4_Y + r*sin(theta);
    }//DownRight 4-5
    else if (Dist>InDistDownRight_5 && Dist<=InDistDownRight_6)
    {
        x = InCorDownRight_5_X - (Dist - InDistDownRight_5);
        y = InCorDownRight_5_Y;
    }//DownRight 5-6
    else if (Dist>InDistDownRight_6 && Dist<=InDistDownRight_7)
    {
        theta = (Dist - InDistDownRight_6) / r;
        x = InCorDownRight_6_X - r*sin(theta);
        y = InCorDownRight_6_Y - r*(1 - cos(theta));
    }//DownRight 6-7
    else if (Dist>InDistDownRight_7 && Dist<=InDistDownRight_8)
    {
        x = InCorDownRight_7_X;
        y = InCorDownRight_7_Y - (Dist - InDistDownRight_7);
    }//DownRight 7-8
    else if (Dist>InDistDownRight_8 && Dist<=InDistUpRight_1)
    {
        x = InCorDownRight_8_X;
        y = InCorDownRight_8_Y - (Dist - InDistDownRight_8);
    }//DownRight 8 - UpRight 1
    //////////////////////////////////////////////////////////////////

    else if (Dist>InDistUpRight_1 && Dist<=InDistUpRight_2)
    {
        x = InCorUpRight_1_X;
        y = InCorUpRight_1_Y - (Dist - InDistUpRight_1);
    }//UpRight 1-2
    else if (Dist>InDistUpRight_2 && Dist<=InDistUpRight_3)
    {
        theta = (Dist - InDistUpRight_2) / r;
        x = InCorUpRight_2_X + r*(1 - cos(theta));
        y = InCorUpRight_2_Y - r*sin(theta);
    }//UpRight 2-3
    else if (Dist>InDistUpRight_3 && Dist<=InDistUpRight_4)
    {
        x = InCorUpRight_3_X + (Dist - InDistUpRight_3);
        y = InCorUpRight_3_Y;
    }//UpRight 3-4
    else if (Dist>InDistUpRight_4 && Dist<=InDistUpRight_5)
    {
        theta = (Dist - InDistUpRight_4) / r;
        x = InCorUpRight_4_X + r*sin(theta);
        y = InCorUpRight_4_Y + r*(1 - cos(theta));
    }//UpRight 4-5
    else if (Dist>InDistUpRight_5 && Dist<=InDistUpRight_6)
    {
        x = InCorUpRight_5_X;
        y = InCorUpRight_5_Y + (Dist - InDistUpRight_5);
    }//UpRight 5-6
    else if (Dist>InDistUpRight_6 && Dist<=InDistUpRight_7)
    {
        theta = (Dist - InDistUpRight_6) / r;
        x = InCorUpRight_6_X - r*(1 - cos(theta));
        y = InCorUpRight_6_Y + r*sin(theta);
    }//UpRight 6-7
    else if (Dist>InDistUpRight_7 && Dist<=InDistUpRight_8)
    {
        x = InCorUpRight_7_X - (Dist - InDistUpRight_7);
        y = InCorUpRight_7_Y;
    }//UpRight 7-8
    else if (Dist>InDistUpRight_8 && Dist<=InDistUpLeft_1)
    {
        x = InCorUpRight_8_X - (Dist - InDistUpRight_8);
        y = InCorUpRight_8_Y;
    }//UpRight 8 - Upleft 1
    /////////////////////////////////////////////////////////////

    else if (Dist>InDistUpLeft_1 && Dist<=InDistUpLeft_2)
    {
        x = InCorUpLeft_1_X - (Dist - InDistUpLeft_1);
        y = InCorUpLeft_1_Y;
    }//UpLeft 1-2
    else if (Dist>InDistUpLeft_2 && Dist<=InDistUpLeft_3)
    {
        theta = (Dist - InDistUpLeft_2) / r;
        x = InCorUpLeft_2_X - r*sin(theta);
        y = InCorUpLeft_2_Y - r*(1 - cos(theta));
    }//UpLeft 2-3
    else if (Dist>InDistUpLeft_3 && Dist<=InDistUpLeft_4)
    {
        x = InCorUpLeft_3_X;
        y = InCorUpLeft_3_Y - (Dist - InDistUpLeft_3);
    }//UpLeft 3-4
    else if (Dist>InDistUpLeft_4 && Dist<=InDistUpLeft_5)
    {
        theta = (Dist - InDistUpLeft_4) / r;
        x = InCorUpLeft_4_X + r*(1 - cos(theta));
        y = InCorUpLeft_4_Y - r*sin(theta);
    }//UpLeft 4-5
    else if (Dist>InDistUpLeft_5 && Dist<=InDistUpLeft_6)
    {
        x = InCorUpLeft_5_X + (Dist - InDistUpLeft_5);
        y = InCorUpLeft_5_Y;
    }//UpLeft 5-6
    else if (Dist>InDistUpLeft_6 && Dist<=InDistUpLeft_7)
    {
        theta = (Dist - InDistUpLeft_6) / r;
        x = InCorUpLeft_6_X + r*sin(theta);
        y = InCorUpLeft_6_Y + r*(1 - cos(theta));
    }//UpLeft 6-7
    else if (Dist>InDistUpLeft_7 && Dist<=InDistUpLeft_8)
    {
        x = InCorUpLeft_7_X;
        y = InCorUpLeft_7_Y + (Dist - InDistUpLeft_7);
    }//UpLeft 7-8
    else if (Dist>InDistUpLeft_8 && Dist<=InDistDownLeft_1_End)
    {
        x = InCorUpLeft_8_X;
        y = InCorUpLeft_8_Y + (Dist - InDistUpLeft_8);
    }//UpLeft 8 - DownLeft 1 End
    else
    {
        qDebug()<<11111;
    }
    Cor[0] = x;
    Cor[1] = y;

       // qDebug()<<x<<' '<<y;

    ////**
    //cout<<"In small"<<endl;
    //cout<<"x="<<x<<" y="<<y<<endl<<endl;
    ////**
    return Cor;
}


//

//
//生成随机数函数
double get_random_error() //limit 为0到100
{
    static QTime t = QTime::currentTime();
    QTime T = QTime::currentTime();
    int i = T.msecsTo(t);
    qsrand(i*qrand()*qrand()*qrand());

    int a = qrand()%(100+1);   //随机生成0到limit的随机数
    double a_minus = double(a)/100; //
    int b = qrand()%2; //生成0,1随机数
    double error;
    if (b==1)
        error = 1 * a_minus;
    else
        error = -1 * a_minus;
   // qDebug()<<error;

    return error;
}

double ** dist2cor(double *Dist_Car, int n_car_sum, int n_car_big)
{
    //把Dist信息转换为Cor信息
    double ** Cor_Car;
    Cor_Car = new double*[8];
    for (int i=0;i<8;i++)
        Cor_Car[i] = new double[3];



    //	//test the Dist_Car
    //	for (int i=0;i<8;i++)
    //		cout<<"Dist_Car"<<i<<": "<<Dist_Car[i][1]<<endl;
    //	getchar();
    Cor_Car[0][0] = 7;
    Cor_Car[1][0] = 5;
    Cor_Car[2][0] = 3;
    Cor_Car[3][0] = 1;
    Cor_Car[4][0] = 6;
    Cor_Car[5][0] = 4;
    Cor_Car[6][0] = 2;
    Cor_Car[7][0] = 8;
    double *temp;
    temp = new double[2];
    int i;
    for (i=0;i<n_car_big;i++)
    {
        temp = big(Dist_Car[i]);
        Cor_Car[i][1] = temp[0];
        Cor_Car[i][2] = temp[1];
    }

    for (int i=n_car_big;i<n_car_sum;i++)
    {
        temp = small(Dist_Car[i]);
        Cor_Car[i][1] = temp[0];
        Cor_Car[i][2] = temp[1];
    }

    return Cor_Car;

}



int func_sgn(double n){
    if (n>=0)
        return 1;
    else
        return -1;
}
double func_min(double a, double b){
    if (a<= b)
        return a;
    else
        return b;
}

double func_tag_v_tag(double Dist_Car, int i){
    double tag;
    if (i<NUM_BIG_CAR){
        if ((Dist_Car<OutDistDownLeft_2) ||
                (Dist_Car>OutDistDownLeft_7 && Dist_Car<OutDistDownRight_2) ||
                (Dist_Car>OutDistDownRight_7 && Dist_Car<OutDistUpRight_2) ||
                (Dist_Car>OutDistUpRight_7 && Dist_Car<OutDistUpLeft_2) ||
                (Dist_Car>OutDistUpLeft_7 && Dist_Car<OutDistDownLeft_1_End))
            tag = 1;
        else
            tag = 0;
    }
    if (i>=NUM_BIG_CAR){
        if ((Dist_Car<InDistDownLeft_2) ||
                (Dist_Car>InDistDownLeft_7 && Dist_Car<InDistDownRight_2) ||
                (Dist_Car>InDistDownRight_7 && Dist_Car<InDistUpRight_2) ||
                (Dist_Car>InDistUpRight_7 && Dist_Car<InDistUpLeft_2) ||
                (Dist_Car>InDistUpLeft_7 && Dist_Car<InDistDownLeft_1_End))
            tag = 1;
        else
            tag = 0;
    }
    return tag;
}
double ** func_tag_v_main(double**V_Car, double* Dist_Car){
    for (int i=0;i<8;i++){
        V_Car[i][1] = func_tag_v_tag(Dist_Car[i],i);
    }
    return V_Car;
}
double ** func_real_v(double **V_Car_real, double **V_Car, double ACCLERATE){
    for (int i=0;i<8;i++){
        V_Car_real[i][0] = V_Car_real[i][0] + func_sgn( V_Car[i][0] - V_Car_real[i][0] )
                *func_min( (V_Car[i][0] - V_Car_real[i][0]) * func_sgn(V_Car[i][0] - V_Car_real[i][0])/t_paint,ACCLERATE )*t_paint;
        V_Car_real[i][1] = V_Car[i][1];
    }
    return V_Car_real;
}

//根据V更新坐标信息
double * update_position(double **V_Car, double *Dist_Car, int n_car_sum,int n_car_big, double t)
{

    for (int i=0;i<n_car_big;i++)
    {
        Dist_Car[i] = Dist_Car[i] + V_Car[i][1]*t/1000;
        if (Dist_Car[i]>OutDistDownLeft_1_End) Dist_Car[i] = Dist_Car[i] - OutDistDownLeft_1_End;
    }
    for (int i=n_car_big;i<n_car_sum;i++)
    {
        Dist_Car[i] = Dist_Car[i] + V_Car[i][1]*t/1000;
        if (Dist_Car[i]>InDistDownLeft_1_End) Dist_Car[i] = Dist_Car[i] - InDistDownLeft_1_End;
    }

    return Dist_Car;

}

//是否撞车

int collision_info(double * Dist_Car, double * V_Car)
{
    int collision = 0;
//    p->setBrush(Qt::blue);
//    p->setPen(Qt::blue);
    //大圈内部是否发生追尾
    double Dist1;
    double Dist2;
    double dist_temp;
    double f_thresh = 40;//OutBridge/10;
    double b_thresh = 0;
    int flag = 0;
//    for (int i=0;i<4;i++)
//    {
//        for (int j=0;j<4;j++)
//        {
//            if (i>j)
//            {
//                Dist1 = Dist_Car[i];
//                Dist2 = Dist_Car[j];
//                dist_temp = func_min(abs(Dist1-Dist2),(OutDistDownLeft_1_End-abs(Dist1-Dist2))); //sqrt(pow(x1-x2,2) + pow(y1-y2,2));//abs(x1-x2)+abs(y1-y2);
//                if (dist_temp < 35)
//                {
//                    collision = 1;
//                    ////**看相撞时的position
//                    //cout<<"i="<<i<<" j="<<j<<endl<<"  dist= "<<dist<<endl;
//                    //cout<<"Position_"<<i<<" X="<<x1<<" Y="<<y1<<endl;
//                    //cout<<"Position_"<<j<<" X="<<x2<<" Y="<<y2<<endl<<endl;
//                    ////**
//                    break;
//                }
//            }
//        }
//    }
//    //小圈内部是否发生追尾
//    for (int i=4;i<8;i++)
//    {
//        for (int j=4;j<8;j++)
//        {
//            if (i>j)
//            {
//                Dist1 = Dist_Car[i];
//                Dist2 = Dist_Car[j];
//                dist_temp = func_min(abs(Dist1-Dist2),(InDistDownLeft_1_End-abs(Dist1-Dist2)));//sqrt(pow(x1-x2,2) + pow(y1-y2,2));//abs(x1-x2)+abs(y1-y2);
//                if (dist_temp < 35)
//                {
//                    collision = 1;
//                    break;
//                }
//            }
//        }
//    }
//    //给Cell_Point加tag，通过两个方向tag的比较可以判断是否相撞S

//    for (int i=0;i<16;i++){
//        //竖的方向

//        if (Cell_Point[i][0] == 0){
//            for (int j=4;j<8;j++){
//                dist_temp = Cell_Point[i][1]-Dist_Car[j];
//                if((dist_temp<f_thresh)&(dist_temp>-1*b_thresh))
//                {
//                    flag = 1;
//                    p->drawEllipse(QPoint(Cell_Point[i][6],Cell_Point[i][7]),10,10);
//                }
//            }
//        }//小圈
//        else{
//            for (int j=0;j<4;j++){
//                dist_temp = Cell_Point[i][1] - Dist_Car[j];
//                if ((Cell_Point[i][1]>1846.72)&(Cell_Point[i][1]<1846.74))
//                    qDebug()<<dist_temp;
//                if((dist_temp<f_thresh)&(dist_temp>-1*b_thresh)){
//                  {
//                        flag = 1;
//                        p->drawEllipse(QPoint(Cell_Point[i][6],Cell_Point[i][7]),10,10);
//                    }

//                }
//            }
//        }
//        if (flag==1){
//           Cell_Point[i][2] = 1;
//           flag = 0;
//        }
//        else{
//            Cell_Point[i][2] = 0;
//        }

//        //横的方向
//        if (Cell_Point[i][3] == 0){
//            for (int j=4;j<8;j++){
//                dist_temp = Cell_Point[i][4]-Dist_Car[j];
//                if((dist_temp<f_thresh)&(dist_temp>-1*b_thresh))
//                    flag = 1;
//                    p->drawEllipse(QPoint(Cell_Point[i][6],Cell_Point[i][7]),10,10);
//            }
//        }//小圈
//        else{
//            for (int j=0;j<4;j++){
//                dist_temp = Cell_Point[i][4] - Dist_Car[j];
//                if((dist_temp<f_thresh)&(dist_temp>-1*b_thresh))
//                    flag = 1;
//                    p->drawEllipse(QPoint(Cell_Point[i][6],Cell_Point[i][7]),10,10);
//            }
//        }

//        if (flag==1){
//           Cell_Point[i][5] = 1;
//           flag = 0;
//        }
//        else{
//            Cell_Point[i][5] = 0;
//        }
//    }


//    //判断是否相撞
//    for (int i=0;i<16;i++){
//        if ( (Cell_Point[i][2] == 1) & (Cell_Point[i][5] == 1) ) {
//            collision = 1;
//            //qDebug()<<i<<endl;
//            qDebug()<<Cell_Point[i][0]<<Cell_Point[i][1]<<Cell_Point[i][2]<<Cell_Point[i][3]<<Cell_Point[i][4]<<Cell_Point[i][5];
//            }
//    }





    return collision;
}



#endif // MOVING_H
