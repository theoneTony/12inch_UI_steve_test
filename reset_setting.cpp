#include "reset_setting.h"
#include "ui_reset_setting.h"

reset_setting::reset_setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::reset_setting)
{
    ui->setupUi(this);

    connect(ui->label_no,&Label_no_reset::clicked_1,this,[=](){
        emit clicked_return();
    });

    connect(ui->label_yes,&Label_yes_reset::clicked_1,this,[=](){
        emit reset_yes();
        emit clicked_return();
    });

    ui->label_backdrop->setStyleSheet("border-radius: 30px 30px 30px 30px;background-color: rgb(110, 215, 230);");
    ui->label_no->setStyleSheet("border-radius: 10px 10px 10px 10px;background-color: rgb(151, 235, 238);");
    ui->label_yes->setStyleSheet("border-radius: 10px 10px 10px 10px;background-color: rgb(151, 235, 238);");
}

reset_setting::~reset_setting()
{
    delete ui;
}

void reset_setting::settext()
{
    ui->label_num->setText(tr("是否重置设定？"));
    ui->label_yes->setText(tr("是"));
    ui->label_no->setText(tr("否"));
}

Label_no_reset::Label_no_reset(QWidget *parent): QLabel(parent)
{

}
void Label_no_reset::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}

Label_yes_reset::Label_yes_reset(QWidget *parent): QLabel(parent)
{

}
void Label_yes_reset::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
