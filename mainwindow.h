#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "initail_dlg.h"
#include "map.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected slots:
    void count_num_collision();
    void show_time();

private slots:
    void on_prompt_clicked();

    void on_Start_clicked();


private:
    Ui::MainWindow *ui;
    Initail_Dlg my2;
    Map map;
    int sum_time = 5;//倒计时
    int ** record_pass;//记录通过次数 8x2 两列分别表示更新前后# 1表示在cross 0表示不在  #第一列为1 第二列为0 记一次通过
    int ** record_collision;//记录碰撞次数 8x2 前后表示碰撞状态# 1表碰撞 0表正常 #第一列为0 第二列为1 记一次碰撞
    QTimer *timer_count_down;
    int click_start_time =0;
};

#endif // MAINWINDOW_H
