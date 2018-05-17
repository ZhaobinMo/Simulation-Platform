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
    void count_num_pass();
    void show_time();

private slots:
    void on_prompt_clicked();

    void on_Start_clicked();


private:
    Ui::MainWindow *ui;
    Initail_Dlg my2;
    Map map;
    int sum_time = 240;//倒计时
    QTimer *timer_count_down;
    QTimer *timer_showLCD;
    int click_start_time =0;
};

#endif // MAINWINDOW_H
