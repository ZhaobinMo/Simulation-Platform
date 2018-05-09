#ifndef INITAIL_DLG_H
#define INITAIL_DLG_H

#include <QDialog>

namespace Ui {
class Initail_Dlg;
}

class Initail_Dlg : public QDialog
{
    Q_OBJECT

public:
    explicit Initail_Dlg(QWidget *parent = 0);
    ~Initail_Dlg();

private:
    Ui::Initail_Dlg *ui;
};

#endif // INITAIL_DLG_H
