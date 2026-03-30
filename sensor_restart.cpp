#include "sensor_restart.h"
#include "ui_sensor_restart.h"

sensor_restart::sensor_restart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sensor_restart)
{
    ui->setupUi(this);
    ui->label_b->setStyleSheet("border-radius: 30px 30px 30px 30px;background-color: rgb(110, 215, 230);");
    ui->label_ok->setStyleSheet("border-radius: 10px 10px 10px 10px;background-color: rgb(151, 235, 238);");

    connect(ui->label_ok,&Label_sensor::clicked_1,this,[=](){
        emit clicked_return();
    });
}

sensor_restart::~sensor_restart()
{
    delete ui;
}

void sensor_restart::settext()
{
    ui->label_num1->setText(tr("检测到已插入三条手柄"));
    ui->label_num2->setText(tr("为确保正常使用请拔出其中一条手柄重启！"));
    ui->label_ok->setText(tr("确定"));
}

Label_sensor::Label_sensor(QWidget *parent): QLabel(parent)
{

}
void Label_sensor::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
