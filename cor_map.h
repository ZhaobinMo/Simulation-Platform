#ifndef COR_MAP_H
#define COR_MAP_H

float PI = 3.1415926;//acos(-1.0);

 double L_Vertical = 70;//弯道之间连接的线段距离 L2 = 20
 double L_Horizon = 20;
 double t_update = 67;//ms
 double t_paint = t_update / 2;//ms
 double t_delay = t_update+30.0;
 int count = 0; // 用来在画图循环里面自增用的
 int count_all = 0;// 用来停止循环的，因为用时间的话不准，4min对应7164次循环
 int count_file = 0;//用来记录txt
 int count_limit = 7164;
 int NUM_BIG_CAR = 4;
 int NUM_SUM_CAR = 8;
 double vers = -1;
//大圈：正方形左下角为起点（距离为0）定义各控制点的距离、圆的半径

 double R = 110;
 double OutBridge = 40;
 double r = 70;
 double InBridge = 120;//1320



//控制点距离
//大圈
 double OutCircle4_1 = PI/2*R;
 double OutDistDownLeft_1_Start = 0;
 double OutDistDownLeft_2 = OutDistDownLeft_1_Start + L_Vertical;
 double OutDistDownLeft_3 = OutDistDownLeft_2 + OutCircle4_1;
 double OutDistDownLeft_4 = OutDistDownLeft_3 + L_Horizon;
 double OutDistDownLeft_5 = OutDistDownLeft_4 + OutCircle4_1;
 double OutDistDownLeft_6 = OutDistDownLeft_5 + L_Vertical;
 double OutDistDownLeft_7 = OutDistDownLeft_6 + OutCircle4_1;
 double OutDistDownLeft_8 = OutDistDownLeft_7 + L_Horizon;

 double OutDistDownRight_1 = OutDistDownLeft_8 + 2*R + OutBridge;
 double OutDistDownRight_2 = OutDistDownRight_1 + L_Horizon;
 double OutDistDownRight_3 = OutDistDownRight_2 + OutCircle4_1;
 double OutDistDownRight_4 = OutDistDownRight_3 + L_Vertical;
 double OutDistDownRight_5 = OutDistDownRight_4 + OutCircle4_1;
 double OutDistDownRight_6 = OutDistDownRight_5 + L_Horizon;
 double OutDistDownRight_7 = OutDistDownRight_6 + OutCircle4_1;
 double OutDistDownRight_8 = OutDistDownRight_7 + L_Vertical;

 double OutDistUpRight_1 = OutDistDownRight_8 + 2*R + OutBridge;
 double OutDistUpRight_2 = OutDistUpRight_1 + L_Vertical;
 double OutDistUpRight_3 = OutDistUpRight_2 + OutCircle4_1;
 double OutDistUpRight_4 = OutDistUpRight_3 + L_Horizon;
 double OutDistUpRight_5 = OutDistUpRight_4 + OutCircle4_1;
 double OutDistUpRight_6 = OutDistUpRight_5 + L_Vertical;
 double OutDistUpRight_7 = OutDistUpRight_6 + OutCircle4_1;
 double OutDistUpRight_8 = OutDistUpRight_7 + L_Horizon;
 double OutDistUpLeft_1 = OutDistUpRight_8 + 2*R + OutBridge;
 double OutDistUpLeft_2 = OutDistUpLeft_1 + L_Horizon;
 double OutDistUpLeft_3 = OutDistUpLeft_2 + OutCircle4_1;
 double OutDistUpLeft_4 = OutDistUpLeft_3 + L_Vertical;
 double OutDistUpLeft_5 = OutDistUpLeft_4 + OutCircle4_1;
 double OutDistUpLeft_6 = OutDistUpLeft_5 + L_Horizon;
 double OutDistUpLeft_7 = OutDistUpLeft_6 + OutCircle4_1;
 double OutDistUpLeft_8 = OutDistUpLeft_7 + L_Vertical;
 double OutDistDownLeft_1_End = OutDistUpLeft_8 + 2*R + OutBridge;
//小圈
 double InCircle4_1 = PI/2*r;
 double InDistDownLeft_1_Start = 0;
 double InDistDownLeft_2 = InDistDownLeft_1_Start + L_Vertical;
 double InDistDownLeft_3 = InDistDownLeft_2 + InCircle4_1;
 double InDistDownLeft_4 = InDistDownLeft_3 + L_Horizon;
 double InDistDownLeft_5 = InDistDownLeft_4 + InCircle4_1;
 double InDistDownLeft_6 = InDistDownLeft_5 + L_Vertical;
 double InDistDownLeft_7 = InDistDownLeft_6 + InCircle4_1;
 double InDistDownLeft_8 = InDistDownLeft_7 + L_Horizon;

 double InDistDownRight_1 = InDistDownLeft_8 + 2*r + InBridge;
 double InDistDownRight_2 = InDistDownRight_1 + L_Horizon;
 double InDistDownRight_3 = InDistDownRight_2 + InCircle4_1;
 double InDistDownRight_4 = InDistDownRight_3 + L_Vertical;
 double InDistDownRight_5 = InDistDownRight_4 + InCircle4_1;
 double InDistDownRight_6 = InDistDownRight_5 + L_Horizon;
 double InDistDownRight_7 = InDistDownRight_6 + InCircle4_1;
 double InDistDownRight_8 = InDistDownRight_7 + L_Vertical;

 double InDistUpRight_1 = InDistDownRight_8 + 2*r + InBridge;
 double InDistUpRight_2 = InDistUpRight_1 + L_Vertical;
 double InDistUpRight_3 = InDistUpRight_2 + InCircle4_1;
 double InDistUpRight_4 = InDistUpRight_3 + L_Horizon;
 double InDistUpRight_5 = InDistUpRight_4 + InCircle4_1;
 double InDistUpRight_6 = InDistUpRight_5 + L_Vertical;
 double InDistUpRight_7 = InDistUpRight_6 + InCircle4_1;
 double InDistUpRight_8 = InDistUpRight_7 + L_Horizon;

 double InDistUpLeft_1 = InDistUpRight_8 + 2*r + InBridge;
 double InDistUpLeft_2 = InDistUpLeft_1 + L_Horizon;
 double InDistUpLeft_3 = InDistUpLeft_2 + InCircle4_1;
 double InDistUpLeft_4 = InDistUpLeft_3 + L_Vertical;
 double InDistUpLeft_5 = InDistUpLeft_4 + InCircle4_1;
 double InDistUpLeft_6 = InDistUpLeft_5 + L_Horizon;
 double InDistUpLeft_7 = InDistUpLeft_6 + InCircle4_1;
 double InDistUpLeft_8 = InDistUpLeft_7 + L_Vertical;
 double InDistDownLeft_1_End = InDistUpLeft_8 + 2*r + InBridge;


//大圈：起点即其他各点的映射的xy坐标;
 double OutCorDownLeft_1_X = -OutBridge/2;              double OutCorDownLeft_1_Y = vers*(-OutBridge/2 - R);
 double OutCorDownLeft_2_X = -OutBridge/2;              double OutCorDownLeft_2_Y = vers*(-OutBridge/2 - R - L_Vertical);
 double OutCorDownLeft_3_X = -OutBridge/2 - R;          double OutCorDownLeft_3_Y = vers*(-OutBridge/2 - 2*R - L_Vertical);
 double OutCorDownLeft_4_X = -OutBridge/2 - R - L_Horizon;      double OutCorDownLeft_4_Y = vers*(-OutBridge/2 - 2*R - L_Vertical);
 double OutCorDownLeft_5_X = -OutBridge/2 - 2*R - L_Horizon;    double OutCorDownLeft_5_Y = vers*(-OutBridge/2 - R - L_Vertical);
 double OutCorDownLeft_6_X = -OutBridge/2 - 2*R - L_Horizon;    double OutCorDownLeft_6_Y = vers*(-OutBridge/2 - R);
 double OutCorDownLeft_7_X = -OutBridge/2 - R - L_Horizon;      double OutCorDownLeft_7_Y = vers*(-OutBridge/2);
 double OutCorDownLeft_8_X = -OutBridge/2 - R;          double OutCorDownLeft_8_Y = vers*(-OutBridge/2);

 double OutCorDownRight_1_X = OutBridge/2 + R;          double OutCorDownRight_1_Y = vers*(-OutBridge/2);
 double OutCorDownRight_2_X = OutBridge/2 + R + L_Horizon;      double OutCorDownRight_2_Y = vers*(-OutBridge/2);
 double OutCorDownRight_3_X = OutBridge/2 + 2*R + L_Horizon;    double OutCorDownRight_3_Y = vers*(-OutBridge/2 - R);
 double OutCorDownRight_4_X = OutBridge/2 + 2*R + L_Horizon;    double OutCorDownRight_4_Y = vers*(-OutBridge/2 - R - L_Vertical);
 double OutCorDownRight_5_X = OutBridge/2 + R + L_Horizon;      double OutCorDownRight_5_Y = vers*(-OutBridge/2 - 2*R - L_Vertical);
 double OutCorDownRight_6_X = OutBridge/2 + R;          double OutCorDownRight_6_Y = vers*(-OutBridge/2 - 2*R - L_Vertical);
 double OutCorDownRight_7_X = OutBridge/2;              double OutCorDownRight_7_Y = vers*(-OutBridge/2 - R - L_Vertical);
 double OutCorDownRight_8_X = OutBridge/2;              double OutCorDownRight_8_Y = vers*(-OutBridge/2 - R);

 double OutCorUpRight_1_X = -OutCorDownLeft_1_X;        double OutCorUpRight_1_Y = (-OutCorDownLeft_1_Y);
 double OutCorUpRight_2_X = -OutCorDownLeft_2_X;        double OutCorUpRight_2_Y = (-OutCorDownLeft_2_Y);
 double OutCorUpRight_3_X = -OutCorDownLeft_3_X;        double OutCorUpRight_3_Y = (-OutCorDownLeft_3_Y);
 double OutCorUpRight_4_X = -OutCorDownLeft_4_X;        double OutCorUpRight_4_Y = (-OutCorDownLeft_4_Y);
 double OutCorUpRight_5_X = -OutCorDownLeft_5_X;        double OutCorUpRight_5_Y = (-OutCorDownLeft_5_Y);
 double OutCorUpRight_6_X = -OutCorDownLeft_6_X;        double OutCorUpRight_6_Y = (-OutCorDownLeft_6_Y);
 double OutCorUpRight_7_X = -OutCorDownLeft_7_X;        double OutCorUpRight_7_Y = (-OutCorDownLeft_7_Y);
 double OutCorUpRight_8_X = -OutCorDownLeft_8_X;        double OutCorUpRight_8_Y = (-OutCorDownLeft_8_Y);

 double OutCorUpLeft_1_X = -OutCorDownRight_1_X;        double OutCorUpLeft_1_Y = (-OutCorDownRight_1_Y);
 double OutCorUpLeft_2_X = -OutCorDownRight_2_X;        double OutCorUpLeft_2_Y = (-OutCorDownRight_2_Y);
 double OutCorUpLeft_3_X = -OutCorDownRight_3_X;        double OutCorUpLeft_3_Y = (-OutCorDownRight_3_Y);
 double OutCorUpLeft_4_X = -OutCorDownRight_4_X;        double OutCorUpLeft_4_Y = (-OutCorDownRight_4_Y);
 double OutCorUpLeft_5_X = -OutCorDownRight_5_X;        double OutCorUpLeft_5_Y = (-OutCorDownRight_5_Y);
 double OutCorUpLeft_6_X = -OutCorDownRight_6_X;        double OutCorUpLeft_6_Y = (-OutCorDownRight_6_Y);
 double OutCorUpLeft_7_X = -OutCorDownRight_7_X;        double OutCorUpLeft_7_Y = (-OutCorDownRight_7_Y);
 double OutCorUpLeft_8_X = -OutCorDownRight_8_X;        double OutCorUpLeft_8_Y = (-OutCorDownRight_8_Y);

//小圈：起点即其他各点的映射的xy坐标;
 double InCorDownLeft_1_X = -InBridge/2;                double InCorDownLeft_1_Y = vers*(-InBridge/2 - r);
 double InCorDownLeft_2_X = -InBridge/2;                double InCorDownLeft_2_Y = vers*(-InBridge/2 - r - L_Vertical);
 double InCorDownLeft_3_X = -InBridge/2 - r;            double InCorDownLeft_3_Y = vers*(-InBridge/2 - 2*r - L_Vertical);
 double InCorDownLeft_4_X = -InBridge/2 - r - L_Horizon;        double InCorDownLeft_4_Y = vers*(-InBridge/2 - 2*r - L_Vertical);
 double InCorDownLeft_5_X = -InBridge/2 - 2*r - L_Horizon;      double InCorDownLeft_5_Y = vers*(-InBridge/2 - r - L_Vertical);
 double InCorDownLeft_6_X = -InBridge/2 - 2*r - L_Horizon;      double InCorDownLeft_6_Y = vers*(-InBridge/2 - r);
 double InCorDownLeft_7_X = -InBridge/2 - r - L_Horizon;        double InCorDownLeft_7_Y = vers*(-InBridge/2);
 double InCorDownLeft_8_X = -InBridge/2 - r;            double InCorDownLeft_8_Y = vers*(-InBridge/2);

 double InCorDownRight_1_X = InBridge/2 + r;            double InCorDownRight_1_Y = vers*(-InBridge/2);
 double InCorDownRight_2_X = InBridge/2 + r + L_Horizon;        double InCorDownRight_2_Y = vers*(-InBridge/2);
 double InCorDownRight_3_X = InBridge/2 + 2*r + L_Horizon;      double InCorDownRight_3_Y = vers*(-InBridge/2 - r);
 double InCorDownRight_4_X = InBridge/2 + 2*r + L_Horizon;      double InCorDownRight_4_Y = vers*(-InBridge/2 - r - L_Vertical);
 double InCorDownRight_5_X = InBridge/2 + r + L_Horizon;        double InCorDownRight_5_Y = vers*(-InBridge/2 - 2*r - L_Vertical);
 double InCorDownRight_6_X = InBridge/2 + r;            double InCorDownRight_6_Y = vers*(-InBridge/2 - 2*r - L_Vertical);
 double InCorDownRight_7_X = InBridge/2;                double InCorDownRight_7_Y = vers*(-InBridge/2 - r - L_Vertical);
 double InCorDownRight_8_X = InBridge/2;                double InCorDownRight_8_Y = vers*(-InBridge/2 - r);

 double InCorUpRight_1_X = -InCorDownLeft_1_X;          double InCorUpRight_1_Y = (-InCorDownLeft_1_Y);
 double InCorUpRight_2_X = -InCorDownLeft_2_X;          double InCorUpRight_2_Y = (-InCorDownLeft_2_Y);
 double InCorUpRight_3_X = -InCorDownLeft_3_X;          double InCorUpRight_3_Y = (-InCorDownLeft_3_Y);
 double InCorUpRight_4_X = -InCorDownLeft_4_X;          double InCorUpRight_4_Y = (-InCorDownLeft_4_Y);
 double InCorUpRight_5_X = -InCorDownLeft_5_X;          double InCorUpRight_5_Y = (-InCorDownLeft_5_Y);
 double InCorUpRight_6_X = -InCorDownLeft_6_X;          double InCorUpRight_6_Y = (-InCorDownLeft_6_Y);
 double InCorUpRight_7_X = -InCorDownLeft_7_X;          double InCorUpRight_7_Y = (-InCorDownLeft_7_Y);
 double InCorUpRight_8_X = -InCorDownLeft_8_X;          double InCorUpRight_8_Y = (-InCorDownLeft_8_Y);

 double InCorUpLeft_1_X = -InCorDownRight_1_X;          double InCorUpLeft_1_Y = (-InCorDownRight_1_Y);
 double InCorUpLeft_2_X = -InCorDownRight_2_X;          double InCorUpLeft_2_Y = (-InCorDownRight_2_Y);
 double InCorUpLeft_3_X = -InCorDownRight_3_X;          double InCorUpLeft_3_Y = (-InCorDownRight_3_Y);
 double InCorUpLeft_4_X = -InCorDownRight_4_X;          double InCorUpLeft_4_Y = (-InCorDownRight_4_Y);
 double InCorUpLeft_5_X = -InCorDownRight_5_X;          double InCorUpLeft_5_Y = (-InCorDownRight_5_Y);
 double InCorUpLeft_6_X = -InCorDownRight_6_X;          double InCorUpLeft_6_Y = (-InCorDownRight_6_Y);
 double InCorUpLeft_7_X = -InCorDownRight_7_X;          double InCorUpLeft_7_Y = (-InCorDownRight_7_Y);
 double InCorUpLeft_8_X = -InCorDownRight_8_X;          double InCorUpLeft_8_Y = (-InCorDownRight_8_Y);



#endif // COR_MAP_H
