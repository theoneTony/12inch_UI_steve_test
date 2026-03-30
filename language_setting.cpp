#include "language_setting.h"
#include "ui_language_setting.h"

language_setting::language_setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::language_setting)
{
    ui->setupUi(this);

    language_flag_t=0;

    connect(ui->label_chinese,&Label_chinese::clicked_1,this,[=](){
        language_flag=1;
        update_data();
    });
    connect(ui->label_Tchinese,&Label_Tchinese::clicked_1,this,[=](){
        language_flag=2;
        update_data();
    });
    connect(ui->label_english,&Label_english::clicked_1,this,[=](){
        language_flag=3;
        update_data();
    });
    connect(ui->label_espanol,&Label_espanol::clicked_1,this,[=](){
        language_flag=4;
        update_data();
    });
    connect(ui->label_save,&Label_save_L::clicked_1,this,[=](){
        emit save_language();
        emit clicked_return();
    });
    connect(ui->label_return,&Label_return_L::clicked_1,this,[=](){
        language_flag=language_flag_t;
        update_data();
        emit clicked_return();
    });

    ui->label_backdrop->setStyleSheet("border-radius: 30px 30px 30px 30px;background-color: rgb(110, 215, 230);");
    ui->label_save->setStyleSheet("border-radius: 10px 10px 10px 10px;background-color: rgb(151, 235, 238);");
    ui->label_return->setStyleSheet("border-radius: 10px 10px 10px 10px;background-color: rgb(151, 235, 238);");
}

language_setting::~language_setting()
{
    delete ui;
}

void language_setting::settext()
{
    ui->label_espanol->setText(tr("Espanol"));
    ui->label_chinese->setText(tr("简体中文"));
    ui->label_english->setText(tr("English"));
    ui->label_Tchinese->setText(tr("繁體中文"));
    ui->label_return->setText(tr("退出"));
    ui->label_save->setText(tr("保存"));
}

void language_setting::goto_one()
{
    language_flag_t=language_flag;
}

void language_setting::update_data()
{
    switch (language_flag) {
    case 1:
    {
        ui->label_D1->setVisible(true);
        ui->label_D2->setVisible(false);
        ui->label_D3->setVisible(false);
        ui->label_D4->setVisible(false);
        break;
    }
    case 2:
    {
        ui->label_D1->setVisible(false);
        ui->label_D2->setVisible(true);
        ui->label_D3->setVisible(false);
        ui->label_D4->setVisible(false);
        break;
    }
    case 3:
    {
        ui->label_D1->setVisible(false);
        ui->label_D2->setVisible(false);
        ui->label_D3->setVisible(true);
        ui->label_D4->setVisible(false);
        break;
    }
    case 4:
    {
        ui->label_D1->setVisible(false);
        ui->label_D2->setVisible(false);
        ui->label_D3->setVisible(false);
        ui->label_D4->setVisible(true);
        break;
    }
    }
}

Label_chinese::Label_chinese(QWidget *parent): QLabel(parent)
{

}
void Label_chinese::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}

Label_Tchinese::Label_Tchinese(QWidget *parent): QLabel(parent)
{

}
void Label_Tchinese::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_english::Label_english(QWidget *parent): QLabel(parent)
{

}
void Label_english::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_espanol::Label_espanol(QWidget *parent): QLabel(parent)
{

}
void Label_espanol::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_save_L::Label_save_L(QWidget *parent): QLabel(parent)
{

}
void Label_save_L::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_return_L::Label_return_L(QWidget *parent): QLabel(parent)
{

}
void Label_return_L::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
