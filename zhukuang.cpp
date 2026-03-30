#include "zhukuang.h"
#include "ui_zhukuang.h"

zhukuang::zhukuang(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::zhukuang)
{
    ui->setupUi(this);

    connect(ui->label_start,&Label_start::clicked_1,this,[=](){
        //usleep(100*100);
        emit clicked_start();
    });
    connect(ui->label_photo,&Label_photo::clicked_1,this,[=](){
        if(flag_SD==1 || flag_USB==1)
        {
            emit clicked_photo();
            current_interface_flag=1;

        }
        else if(flag_SD==0 || flag_USB==0)
        {
            emit nosd_card();
        }
    });
    connect(ui->label_video,&Label_video::clicked_1,this,[=](){
        if(flag_SD==1 || flag_USB==1)
        {
            emit clicked_video();

            emit clicked_enter_preview();

            current_interface_flag=3;
        }
        else if(flag_SD==0 || flag_USB==0)
        {
            emit nosd_card();
        }
    });
    connect(ui->label_system,&Label_system::clicked_1,this,[=](){
        emit clicked_system();
    });
}

zhukuang::~zhukuang()
{
    delete ui;
}

Label_start::Label_start(QWidget *parent)
   : QLabel(parent)
{

}

void Label_start::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}

Label_photo::Label_photo(QWidget *parent)
   : QLabel(parent)
{

}

void Label_photo::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}

Label_video::Label_video(QWidget *parent)
   : QLabel(parent)
{

}

void Label_video::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}

Label_system::Label_system(QWidget *parent)
   : QLabel(parent)
{

}

void Label_system::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
