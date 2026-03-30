#include "system_setting.h"
#include "ui_system_setting.h"

system_setting::system_setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::system_setting)
{
    ui->setupUi(this);

    connect(ui->label_formatting,&Label_formatting::clicked_1,this,[=](){
        emit clicked_formatting();
    });
    connect(ui->label_reset,&Label_reset::clicked_1,this,[=](){
        emit clicked_reset();
    });
    connect(ui->label_versions,&Label_versions::clicked_1,this,[=](){
        emit clicked_versions();
    });
    connect(ui->label_time,&Label_time::clicked_1,this,[=](){
        emit clicked_time();
    });
    connect(ui->label_language,&Label_language::clicked_1,this,[=](){
        emit clicked_language();
    });
    connect(ui->label_return,&Label_return::clicked_1,this,[=](){
        emit clicked_return();
    });
}

system_setting::~system_setting()
{
    delete ui;
}

Label_formatting::Label_formatting(QWidget *parent)
   : QLabel(parent)
{

}

void Label_formatting::mousePressEvent(QMouseEvent *event)
{
    //如果单击了就触发clicked信号
    if (event->button() == Qt::LeftButton) {
        //触发clicked信号
        emit clicked_1();
    }
   //将该事件传给父类处理
   QLabel::mousePressEvent(event);
}

Label_reset::Label_reset(QWidget *parent)
   : QLabel(parent)
{

}

void Label_reset::mousePressEvent(QMouseEvent *event)
{
    //如果单击了就触发clicked信号
    if (event->button() == Qt::LeftButton) {
        //触发clicked信号
        emit clicked_1();
    }
   //将该事件传给父类处理
   QLabel::mousePressEvent(event);
}

Label_versions::Label_versions(QWidget *parent)
   : QLabel(parent)
{

}

void Label_versions::mousePressEvent(QMouseEvent *event)
{
    //如果单击了就触发clicked信号
    if (event->button() == Qt::LeftButton) {
        //触发clicked信号
        emit clicked_1();
    }
   //将该事件传给父类处理
   QLabel::mousePressEvent(event);
}

Label_time::Label_time(QWidget *parent)
   : QLabel(parent)
{

}

void Label_time::mousePressEvent(QMouseEvent *event)
{
    //如果单击了就触发clicked信号
    if (event->button() == Qt::LeftButton) {
        //触发clicked信号
        emit clicked_1();
    }
   //将该事件传给父类处理
   QLabel::mousePressEvent(event);
}

Label_language::Label_language(QWidget *parent)
   : QLabel(parent)
{

}

void Label_language::mousePressEvent(QMouseEvent *event)
{
    //如果单击了就触发clicked信号
    if (event->button() == Qt::LeftButton) {
        //触发clicked信号
        emit clicked_1();
    }
   //将该事件传给父类处理
   QLabel::mousePressEvent(event);
}

Label_return::Label_return(QWidget *parent)
   : QLabel(parent)
{

}

void Label_return::mousePressEvent(QMouseEvent *event)
{
    //如果单击了就触发clicked信号
    if (event->button() == Qt::LeftButton) {
        //触发clicked信号
        emit clicked_1();
    }
   //将该事件传给父类处理
   QLabel::mousePressEvent(event);
}
