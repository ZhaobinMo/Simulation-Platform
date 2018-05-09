#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->display_LCD->display(map.show_num_collision());
    timer_count_down = new QTimer(this);
    connect(timer_count_down,SIGNAL(timeout()),this,SLOT(show_time()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_prompt_clicked()
{
    my2.show();
}


void MainWindow::on_Start_clicked()
{
    click_start_time = click_start_time + 1;
    if (click_start_time == 1){
        map.show();
        timer_count_down->start(1000);
        QString num = QString::number(sum_time);
      //  ui->label_time->setText(num);
    }
    else{
        QString num = QString::number(sum_time);
       // ui->label_time->setText(num);
    }

}

void MainWindow::count_num_collision(){
   // ui->display_LCD->display(map.show_num_collision());
}

void MainWindow::show_time(){
    if(sum_time > 0){
        //sum_time = sum_time - 1;
        //QString num = QString::number(sum_time);
        //ui->label_time->setText(num);
    }
    else{
        //timer_count_down->stop();
        //map.end_game();
    }
}
