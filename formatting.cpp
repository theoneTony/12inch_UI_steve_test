#include "formatting.h"
#include "ui_formatting.h"

formatting::formatting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::formatting)
{
    ui->setupUi(this);

    connect(ui->label_no,&Label_no_format::clicked_1,this,[=](){
        emit clicked_return();
    });

    connect(ui->label_yes,&Label_yes_format::clicked_1,this,[=](){
        if(flag_SD==1 || flag_USB==1)
        {
            emit format_ok();
        }
        else if(flag_SD==0 || flag_USB==0)
        {
            emit no_SDTips();
        }
    });
    ui->label_backdrop->setStyleSheet("border-radius: 30px 30px 30px 30px;background-color: rgb(110, 215, 230);");
    ui->label_no->setStyleSheet("border-radius: 10px 10px 10px 10px;background-color: rgb(151, 235, 238);");
    ui->label_yes->setStyleSheet("border-radius: 10px 10px 10px 10px;background-color: rgb(151, 235, 238);");
}

formatting::~formatting()
{
    delete ui;
}

void formatting::settext()
{
    ui->label_num->setText(tr("是否进行格式化？"));
    ui->label_yes->setText(tr("是"));
    ui->label_no->setText(tr("否"));
}

Label_no_format::Label_no_format(QWidget *parent): QLabel(parent)
{

}
void Label_no_format::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}

Label_yes_format::Label_yes_format(QWidget *parent): QLabel(parent)
{

}
void Label_yes_format::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
