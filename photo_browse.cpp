#include "photo_browse.h"
#include "ui_photo_browse.h"

photo_browse::photo_browse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::photo_browse)
{
    ui->setupUi(this);


    labels << ui->label_1 << ui->label_2 << ui->label_3 << ui->label_4 << ui->label_5 << ui->label_6;
    label_tick << ui->label_tick1 << ui->label_tick2 << ui->label_tick3 << ui->label_tick4 << ui->label_tick5 << ui->label_tick6;
    tick_flag << 0 << 0 << 0 << 0 << 0 << 0 << 0;

    connect(ui->label_return,&Label_return_p::clicked_1,this,[=](){
        clicked_set_return();
    });
    connect(ui->label_select,&Label_select_p::clicked_1,this,[=](){
        if(photo_select_flag==0)
        {
            photo_select_flag=1;
            photo_select_all_flag=0;
            deselect_all_false();
            update_page_button();
            ui->label_select->setStyleSheet("image: url(:/tu/相片/单选模式.png);");
            ui->label_deselect_all->setStyleSheet("image: url(:/tu/相片/取消全选.png);");
            ui->label_select_all->setStyleSheet("image: url(:/tu/相片/全选.png);");
        }
        else if(photo_select_flag==1)
        {

            photo_select_flag=0;
            update_page_button();
            ui->label_select->setStyleSheet("image: url(:/tu/相片/单选.png);");
            deselect_all_false();
        }
    });
    connect(ui->label_select_all,&Label_select_all_p::clicked_1,this,[=](){
        if(photo_select_all_flag==0)
        {
            photo_select_all_flag=1;
            photo_select_flag=0;
            update_page_button();
            ui->label_select_all->setStyleSheet("image: url(:/tu/相片/全选模式.png);");
            ui->label_select->setStyleSheet("image: url(:/tu/相片/单选.png);");
            ui->label_deselect_all->setStyleSheet("image: url(:/tu/相片/取消全选.png);");
            select_all_mode();
        }
        else if(photo_select_all_flag==1)
        {
            photo_select_all_flag=0;
            update_page_button();
            ui->label_select_all->setStyleSheet("image: url(:/tu/相片/全选.png);");
            deselect_all_false();
        }
    });
    connect(ui->label_deselect_all,&Label_deselect_all_p::clicked_1,this,[=](){
        set_deselect();
        update_page_button();
    });
    connect(ui->label_left,&Label_left_p::clicked_1,this,[=](){
        if(photo_num>1)
        {
            //qDebug()<<"after clidked_left_p ----------";
            //qDebug()<<"page:" << photo_num << tickFlag[photo_num-1];

            photo_num--;
            photo_update();

            update_page_button();
        }
    });
    connect(ui->label_right,&Label_right_p::clicked_1,this,[=](){
        if(photo_num<photo_totality)
        {   

            //qDebug()<<"after clidked_right_p ----------";
            //qDebug()<<"page:" << photo_num << tickFlag[photo_num-1];

            photo_num++;
            photo_update();

            update_page_button();

        }
    });
    connect(ui->label_delete,&Label_delete_p::clicked_1,this,[=](){

        for(int i =1,j=0;i<=6;i++,j++)
        {
            if(tick_flag[i]==1)
            {
                delete_photo(j+(6*(photo_num-1)));
            }
        }


        if(tick_flag[1]==1)
        {
            delete_photo(6*(photo_num-1));
        }
        if(tick_flag[2]==1)
        {
            delete_photo(1+(6*(photo_num-1)));
        }
        if(tick_flag[3]==1)
        {
            delete_photo(2+(6*(photo_num-1)));
        }
        if(tick_flag[4]==1)
        {
            delete_photo(3+(6*(photo_num-1)));
        }
        if(tick_flag[5]==1)
        {
            delete_photo(4+(6*(photo_num-1)));
        }
        if(tick_flag[6]==1)
        {
            delete_photo(5+(6*(photo_num-1)));
        }

        if(tick_flag[1]==1 || tick_flag[2]==1 || tick_flag[3]==1 || tick_flag[4]==1 || tick_flag[5]==1 || tick_flag[6]==1)
        {
            photo_name.clear();
            photo_update();
            deselect_all_false();
        }

        if(photo_select_all_flag==1)
        {
            photo_select_all_flag=0;
            ui->label_select_all->setStyleSheet("image: url(:/tu/相片/全选.png);");
            deselect_all_false();
        }

        if(photo_totality == 0)
        {
            photo_num = 1;
        }
        else
        {
            if(photo_num > photo_totality)
                photo_num = photo_totality;

            if(photo_num < 1)
                photo_num = 1;
        }

        photo_name.clear();
        photo_update();
        ui->label_num->setText(QString("%1/%2").arg(photo_num).arg(photo_totality));

        update_page_button();

    });


    connect(ui->label_1,&Label_photo_1::clicked_1,this,[=](){
        if(photo_select_flag==1)
        {
            ui->label_tick1->setVisible(true);
            tick_flag[1]=1;
        }
        else
        {
            photo_labelnum=1;
            emit goto_photo_browse();
        }
    });
    connect(ui->label_2,&Label_photo_2::clicked_1,this,[=](){
        if(photo_select_flag==1)
        {
            ui->label_tick2->setVisible(true);
            tick_flag[2]=1;
        }
        else
        {
            photo_labelnum=2;
            emit goto_photo_browse();
        }
    });
    connect(ui->label_3,&Label_photo_3::clicked_1,this,[=](){
        if(photo_select_flag==1)
        {
            ui->label_tick3->setVisible(true);
            tick_flag[3]=1;
        }
        else
        {
            photo_labelnum=3;
            emit goto_photo_browse();
        }
    });
    connect(ui->label_4,&Label_photo_4::clicked_1,this,[=](){
        if(photo_select_flag==1)
        {
            ui->label_tick4->setVisible(true);
            tick_flag[4]=1;
        }
        else
        {
            photo_labelnum=4;
            emit goto_photo_browse();
        }
    });
    connect(ui->label_5,&Label_photo_5::clicked_1,this,[=](){
        if(photo_select_flag==1)
        {
            ui->label_tick5->setVisible(true);
            tick_flag[5]=1;
        }
        else
        {
            photo_labelnum=5;
            emit goto_photo_browse();
        }
    });
    connect(ui->label_6,&Label_photo_6::clicked_1,this,[=](){
        if(photo_select_flag==1)
        {
            ui->label_tick6->setVisible(true);
            tick_flag[6]=1;
        }
        else
        {
            photo_labelnum=6;
            emit goto_photo_browse();
        }
    });

    deselect_all_false();

}

photo_browse::~photo_browse()
{
    delete ui;
}

void photo_browse::update_page_button() //判斷上下頁按鈕鎖定、顏色變化
{
    prevEffect = new QGraphicsOpacityEffect(this);
    nextEffect = new QGraphicsOpacityEffect(this);

    ui->label_left->setGraphicsEffect(prevEffect);
    ui->label_right->setGraphicsEffect(nextEffect);
    // 上一頁
    if (photo_num == 1 ||photo_select_flag ==1 ||photo_select_all_flag == 1)
    {
        prevEffect->setOpacity(0.3);
        ui->label_left->setEnabled(false);
    }
    else
    {
        prevEffect->setOpacity(1.0);
        ui->label_left->setEnabled(true);
    }

    // 下一頁
    if (photo_num == photo_totality ||photo_select_flag ==1 ||photo_select_all_flag == 1)
    {
        nextEffect->setOpacity(0.3);
        ui->label_right->setEnabled(false);
    }
    else
    {
        nextEffect->setOpacity(1.0);
        ui->label_right->setEnabled(true);
    }
}

void photo_browse::sd_convert_usb()
{
    photo_name.clear();
    photo_update();
}

void photo_browse::clicked_set_return()
{
    photo_name.clear();
    emit clicked_return();
}

void photo_browse::set_deselect()
{
    ui->label_select_all->setStyleSheet("image: url(:/tu/相片/全选.png);");
    ui->label_select->setStyleSheet("image: url(:/tu/相片/单选.png);");
    photo_select_flag=0;
    photo_select_all_flag=0;
    deselect_all_false();
}

void photo_browse::delete_photo(int num)
{
    if(flag_USB==1)
    {
        QString filePath = QString("/mnt/USB_FLASH/Picture/%1").arg(photo_name.at(num));
        QFile file(filePath);
        if (file.exists())
        {
            file.remove();
        }
        file.close();
    }
    else if(flag_USB==0 && flag_SD==1)
    {
        QString filePath = QString("/mnt/SD_CARD/Picture/%1").arg(photo_name.at(num));
        QFile file(filePath);
        if (file.exists())
        {
            file.remove();
        }
        file.close();
    }
}

void photo_browse::photo_update()
{
    init_photo_name();

    photo_totality = photo_max / 6;

    if(photo_max<6 && photo_max>0) //判斷頁數，顯示在右上角
    {
        photo_totality += 1;
    }
    else if(photo_max>6 && (photo_max % 6 !=0))
    {
        photo_totality += 1;
    }
    else if (photo_max==0)
    {
        photo_totality=1;
    }

    int photo_start = (photo_num-1)*6;

    if(photo_max!=0) //判斷UI顯示幾張照片
    {

        if(photo_max<6 && photo_max>0)
        {
            for(i_num=0;i_num<photo_max;i_num++)
            {
                if(flag_USB==1)
                {
                    labels.at(i_num)->setStyleSheet(QString("image: url(/mnt/USB_FLASH/Picture/%1);").arg(photo_name.at(i_num)));
                }
                else if(flag_USB==0 && flag_SD==1)
                {
                    labels.at(i_num)->setStyleSheet(QString("image: url(/mnt/SD_CARD/Picture/%1);").arg(photo_name.at(i_num)));
                }
            }
            label_all_false();

            for(i_num=0;i_num<photo_max;i_num++)
            {
                labels.at(i_num)->setVisible(true);
            }
        }
        else if(photo_max==6)
        {
            for(i_num=0;i_num<photo_max;i_num++)
            {
                if(flag_USB==1)
                {
                    labels.at(i_num)->setStyleSheet(QString("image: url(/mnt/USB_FLASH/Picture/%1);").arg(photo_name.at(i_num)));
                }
                else if(flag_USB==0 && flag_SD==1)
                {
                    labels.at(i_num)->setStyleSheet(QString("image: url(/mnt/SD_CARD/Picture/%1);").arg(photo_name.at(i_num)));
                }
            }
            label_all_false();
            for(i_num=0; i_num<6; i_num++)
            {
                labels.at(i_num)->setVisible(true);
            }
        }
        else if(photo_max>6)  //超過6張
        {
            if(photo_num==1)
            {


                for(i_num=0;i_num<6;i_num++)
                {
                    if(flag_USB==1)
                    {
                        labels.at(i_num)->setStyleSheet(QString("image: url(/mnt/USB_FLASH/Picture/%1);").arg(photo_name.at(i_num)));
                    }
                    else if(flag_USB==0 && flag_SD==1)
                    {
                        labels.at(i_num)->setStyleSheet(QString("image: url(/mnt/SD_CARD/Picture/%1);").arg(photo_name.at(i_num)));
                    }

                }
                label_all_false();
                for(i_num=0; i_num<6; i_num++)
                {
                    labels.at(i_num)->setVisible(true);
                }
            } //假設第3頁，p_num = 3*6-6 = 12 → 從第 12 張照片開始
            else if(photo_num>1 && (photo_num<(photo_totality-1) || photo_num==(photo_totality-1)))
            {
                for(i_num=0,p_num=(photo_num*6-6); i_num<6 && p_num<photo_num*6; i_num++,p_num++)
                {
                    if(flag_USB==1)
                    {
                        labels.at(i_num)->setStyleSheet(QString("image: url(/mnt/USB_FLASH/Picture/%1);").arg(photo_name.at(p_num)));
                    }
                    else if(flag_USB==0 && flag_SD==1)
                    {
                        labels.at(i_num)->setStyleSheet(QString("image: url(/mnt/SD_CARD/Picture/%1);").arg(photo_name.at(p_num)));
                    }

                }
                label_all_false();
                for(i_num=0; i_num<6; i_num++)
                {
                    labels.at(i_num)->setVisible(true);
                }
            }
            else if(photo_num>1 && photo_num==photo_totality)
            {
                for(i_num=0,p_num=photo_start; i_num<(photo_max-photo_start) && p_num<photo_max; i_num++,p_num++)
                {

                    if(flag_USB==1)
                    {
                        labels.at(i_num)->setStyleSheet(QString("image: url(/mnt/USB_FLASH/Picture/%1);").arg(photo_name.at(p_num)));
                    }
                    else if(flag_USB==0 && flag_SD==1)
                    {
                        labels.at(i_num)->setStyleSheet(QString("image: url(/mnt/SD_CARD/Picture/%1);").arg(photo_name.at(p_num)));
                    }
                }
                label_all_false();
                for(i_num=0; i_num<(photo_max-photo_start); i_num++)
                {
                    labels.at(i_num)->setVisible(true);
                }

            }
        }
    }
    else if(photo_max==0)
    {
        label_all_false();
    }

    ui->label_num->setText(QString("%1/%2").arg(photo_num).arg(photo_totality));



}

void photo_browse::init_photo_name()
{
    //photo_name.clear();

    if(flag_USB==1)
    {
        //初始化数据
        QDir dir("/mnt/USB_FLASH/Picture/");
        QDir::Filters filters = QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot;
        QDir::SortFlags sortFlags = QDir::DirsFirst | QDir::IgnoreCase | QDir::Name;
        QFileInfoList fileList = dir.entryInfoList(filters, sortFlags);
        photo_max = fileList.size();
        for (const QFileInfo& fileInfo : fileList)
        {
            photo_name.append(fileInfo.fileName());
        }
    }
    else if(flag_USB==0 && flag_SD==1)
    {
        //初始化数据
        QDir dir("/mnt/SD_CARD/Picture/");
        QDir::Filters filters = QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot;
        QDir::SortFlags sortFlags = QDir::DirsFirst | QDir::IgnoreCase | QDir::Name;
        QFileInfoList fileList = dir.entryInfoList(filters, sortFlags);
        photo_max = fileList.size();
        for (const QFileInfo& fileInfo : fileList)
        {
            photo_name.append(fileInfo.fileName());
        }
    }
    update_page_button();
}

void photo_browse::select_all_mode()
{
    if(photo_max<6 && photo_max>0)
    {
        for(i_num=0; i_num<photo_max; i_num++)
        {
            label_tick.at(i_num)->setVisible(true);
            tick_flag[i_num+1]=1;
        }
    }
    else if(photo_max==6)
    {
        deselect_all_true();
    }
    else if(photo_max>6)
    {
        if(photo_max % 6 != 0)
        {
            if(photo_num == photo_totality)
            {
                for(i_num=0; i_num<(photo_max % 6); i_num++)
                {
                    label_tick.at(i_num)->setVisible(true);
                    tick_flag[i_num+1]=1;
                }

            }
            else
            {
                deselect_all_true();
            }
        }
        else if(photo_max % 6 == 0)
        {
            deselect_all_true();
        }
    }
}

void photo_browse::deselect_all_false()
{
    ui->label_tick1->setVisible(false);
    ui->label_tick2->setVisible(false);
    ui->label_tick3->setVisible(false);
    ui->label_tick4->setVisible(false);
    ui->label_tick5->setVisible(false);
    ui->label_tick6->setVisible(false);
    tick_flag[1]=0;
    tick_flag[2]=0;
    tick_flag[3]=0;
    tick_flag[4]=0;
    tick_flag[5]=0;
    tick_flag[6]=0;
}



void photo_browse::deselect_all_true()
{
    ui->label_tick1->setVisible(true);
    ui->label_tick2->setVisible(true);
    ui->label_tick3->setVisible(true);
    ui->label_tick4->setVisible(true);
    ui->label_tick5->setVisible(true);
    ui->label_tick6->setVisible(true);
    tick_flag[1]=1;
    tick_flag[2]=1;
    tick_flag[3]=1;
    tick_flag[4]=1;
    tick_flag[5]=1;
    tick_flag[6]=1;
}

void photo_browse::label_all_false()
{
    ui->label_1->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);
}

void photo_browse::label_all_true()
{
    ui->label_1->setVisible(true);
    ui->label_2->setVisible(true);
    ui->label_3->setVisible(true);
    ui->label_4->setVisible(true);
    ui->label_5->setVisible(true);
    ui->label_6->setVisible(true);
}

Label_return_p::Label_return_p(QWidget *parent): QLabel(parent)
{

}
void Label_return_p::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_select_p::Label_select_p(QWidget *parent): QLabel(parent)
{

}
void Label_select_p::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_select_all_p::Label_select_all_p(QWidget *parent): QLabel(parent)
{

}
void Label_select_all_p::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_deselect_all_p::Label_deselect_all_p(QWidget *parent): QLabel(parent)
{

}
void Label_deselect_all_p::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_left_p::Label_left_p(QWidget *parent): QLabel(parent)
{

}
void Label_left_p::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_right_p::Label_right_p(QWidget *parent): QLabel(parent)
{

}
void Label_right_p::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_delete_p::Label_delete_p(QWidget *parent): QLabel(parent)
{

}
void Label_delete_p::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}




Label_photo_1::Label_photo_1(QWidget *parent): QLabel(parent)
{

}
void Label_photo_1::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_photo_2::Label_photo_2(QWidget *parent): QLabel(parent)
{

}
void Label_photo_2::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_photo_3::Label_photo_3(QWidget *parent): QLabel(parent)
{

}
void Label_photo_3::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_photo_4::Label_photo_4(QWidget *parent): QLabel(parent)
{

}
void Label_photo_4::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_photo_5::Label_photo_5(QWidget *parent): QLabel(parent)
{

}
void Label_photo_5::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_photo_6::Label_photo_6(QWidget *parent): QLabel(parent)
{

}
void Label_photo_6::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
