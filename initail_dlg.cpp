#include "initail_dlg.h"
#include "ui_initail_dlg.h"

Initail_Dlg::Initail_Dlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Initail_Dlg)
{
    ui->setupUi(this);
}

Initail_Dlg::~Initail_Dlg()
{
    delete ui;
}
