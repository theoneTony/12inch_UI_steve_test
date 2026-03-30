#include "video_browse.h"
#include "ui_video_browse.h"

video_browse::video_browse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::video_browse)
{
    ui->setupUi(this);

    labels << ui->label_1 << ui->label_2 << ui->label_3 << ui->label_4 << ui->label_5 << ui->label_6;
    label_tick << ui->label_tick1 << ui->label_tick2 << ui->label_tick3 << ui->label_tick4 << ui->label_tick5 << ui->label_tick6;
    label_play << ui->label_play_1 << ui->label_play_2 << ui->label_play_3 << ui->label_play_4 << ui->label_play_5 << ui->label_play_6;
    tick_flag << 0 << 0 << 0 << 0 << 0 << 0;
    connect(ui->label_return,&Label_return_v::clicked_1,this,[=](){
            clicked_set_return();
    });
    connect(ui->label_select,&Label_select_v::clicked_1,this,[=](){
        if(video_select_flag==0)
        {
            video_select_flag=1;
            video_select_all_flag=0;
            deselect_all_false();
            update_page_button();
            ui->label_select->setStyleSheet("image: url(:/tu/相片/单选模式.png);");
            ui->label_deselect_all->setStyleSheet("image: url(:/tu/相片/取消全选.png);");
            ui->label_select_all->setStyleSheet("image: url(:/tu/相片/全选.png);");
        }
        else if(video_select_flag==1)
        {
            video_select_flag=0;
            update_page_button();
            ui->label_select->setStyleSheet("image: url(:/tu/相片/单选.png);");
            deselect_all_false();
        }
    });
    connect(ui->label_select_all,&Label_select_all_v::clicked_1,this,[=](){
        if(video_select_all_flag==0)
        {
            video_select_all_flag=1;
            video_select_flag=0;
            update_page_button();
            ui->label_select_all->setStyleSheet("image: url(:/tu/相片/全选模式.png);");
            ui->label_select->setStyleSheet("image: url(:/tu/相片/单选.png);");
            ui->label_deselect_all->setStyleSheet("image: url(:/tu/相片/取消全选.png);");
            select_all_mode();
        }
        else if(video_select_all_flag==1)
        {
            video_select_all_flag=0;
            update_page_button();
            ui->label_select_all->setStyleSheet("image: url(:/tu/相片/全选.png);");
            deselect_all_false();
        }
    });
    connect(ui->label_deselect_all,&Label_deselect_all_v::clicked_1,this,[=](){
        set_deselect();
        update_page_button();
    });
    connect(ui->label_left,&Label_left_v::clicked_1,this,[=](){
        if(video_num>1)
        {
            video_num--;
            video_update();
            update_page_button();
        }
    });
    connect(ui->label_right,&Label_right_v::clicked_1,this,[=](){
        if(video_num<video_totality)
        {
            video_num++;
            video_update();
            update_page_button();
        }
    });
    connect(ui->label_delete,&Label_delete_v::clicked_1,this,[=](){
        if(tick_flag[1]==1)
        {
            delete_video(6*(video_num-1));
        }
        if(tick_flag[2]==1)
        {
            delete_video(1+(6*(video_num-1)));
        }
        if(tick_flag[3]==1)
        {
            delete_video(2+(6*(video_num-1)));
        }
        if(tick_flag[4]==1)
        {
            delete_video(3+(6*(video_num-1)));
        }
        if(tick_flag[5]==1)
        {
            delete_video(4+(6*(video_num-1)));
        }
        if(tick_flag[6]==1)
        {
            delete_video(5+(6*(video_num-1)));
        }  //可改成for迴圈形式,

        if(tick_flag[1]==1 || tick_flag[2]==1 || tick_flag[3]==1 || tick_flag[4]==1 || tick_flag[5]==1 || tick_flag[6]==1)
        {
            video_name.clear();
            video_update();
            deselect_all_false();
        }//更新影片列表

        if(video_select_all_flag==1)
        {
            video_select_all_flag=0;
            ui->label_select_all->setStyleSheet("image: url(:/tu/相片/全选.png);");
            deselect_all_false();
        }

        if(video_totality == 0)
        {
            video_num = 1;
        }
        else
        {
            if(video_num > video_totality)
                video_num = video_totality;

            if(video_num < 1)
                video_num = 1;
        }

        video_name.clear();
        video_update();
        ui->label_num->setText(QString("%1/%2").arg(video_num).arg(video_totality));

        update_page_button();

    });


    connect(ui->label_play_1,&Label_video_1::clicked_1,this,[=](){
        if(video_select_flag==1)
        {
            ui->label_tick1->setVisible(true);
            tick_flag[1]=1;
        }
        else
        {
            video_labelnum=1;
            emit goto_void_browse();
        }
    });
    connect(ui->label_play_2,&Label_video_2::clicked_1,this,[=](){
        if(video_select_flag==1)
        {
            ui->label_tick2->setVisible(true);
            tick_flag[2]=1;
        }
        else
        {
            video_labelnum=2;
            emit goto_void_browse();
        }
    });
    connect(ui->label_play_3,&Label_video_3::clicked_1,this,[=](){
        if(video_select_flag==1)
        {
            ui->label_tick3->setVisible(true);
            tick_flag[3]=1;
        }
        else
        {
            video_labelnum=3;
            emit goto_void_browse();
        }
    });
    connect(ui->label_play_4,&Label_video_4::clicked_1,this,[=](){
        if(video_select_flag==1)
        {
            ui->label_tick4->setVisible(true);
            tick_flag[4]=1;
        }
        else
        {
            video_labelnum=4;
            emit goto_void_browse();
        }
    });
    connect(ui->label_play_5,&Label_video_5::clicked_1,this,[=](){
        if(video_select_flag==1)
        {
            ui->label_tick5->setVisible(true);
            tick_flag[5]=1;
        }
        else
        {
            video_labelnum=5;
            emit goto_void_browse();
        }
    });
    connect(ui->label_play_6,&Label_video_6::clicked_1,this,[=](){
        if(video_select_flag==1)
        {
            ui->label_tick6->setVisible(true);
            tick_flag[6]=1;
        }
        else
        {
            video_labelnum=6;
            emit goto_void_browse();
        }
    });

    deselect_all_false();
}

video_browse::~video_browse()
{
    delete ui;
}

void video_browse::update_page_button()
{
    prevEffect = new QGraphicsOpacityEffect(this);
    nextEffect = new QGraphicsOpacityEffect(this);

    ui->label_left->setGraphicsEffect(prevEffect);
    ui->label_right->setGraphicsEffect(nextEffect);
    // 上一頁
    if (video_num == 1 ||video_select_flag ==1 ||video_select_all_flag == 1)
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
    if (video_num == video_totality ||video_select_flag ==1 ||video_select_all_flag == 1)
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



void video_browse::sd_convert_usb()
{
    video_name.clear();
    video_update();
}

void video_browse::clicked_set_return()
{
    video_name.clear();
    emit clicked_return();

    emit return_preview();
}

void video_browse::set_deselect()
{
    ui->label_select_all->setStyleSheet("image: url(:/tu/相片/全选.png);");
    ui->label_select->setStyleSheet("image: url(:/tu/相片/单选.png);");
    video_select_flag=0;
    video_select_all_flag=0;
    deselect_all_false();
}

void video_browse::delete_video(int num)
{
    QString firstFileName = video_name.at(num);
    QByteArray byteArray = firstFileName.toLatin1();
    const char *fileName = byteArray.data();
    memset(playback_video_name,0,sizeof(playback_video_name));
    strcpy(playback_video_name, fileName);

    for (int i = strlen(playback_video_name) - 1; i >= 0; --i)
    {
        if (playback_video_name[i] == '.')
        {
            playback_video_name[i] = '\0';
            break;
        }
    }
    if(flag_USB==1)
    {
        QFile file(QString("/mnt/USB_FLASH/Video/%1.mp4").arg(playback_video_name));
        if (file.exists())
        {
            file.remove();
        }
        file.close();
        qDebug()<<"video_name====="<<QString("/mnt/USB_FLASH/Video/%1.mp4").arg(playback_video_name);
        QFile file1(QString("/mnt/USB_FLASH/Videohead/%1").arg(video_name.at(num)));
        if (file1.exists())
        {
            file1.remove();
        }
        file1.close();
    }
    else if(flag_USB==0 && flag_SD==1)
    {
        QFile file(QString("/mnt/SD_CARD/Video/%1.mp4").arg(playback_video_name));
        if (file.exists())
        {
            file.remove();
        }
        file.close();
        qDebug()<<"video_name====="<<QString("/mnt/SD_CARD/Video/%1.mp4").arg(playback_video_name);
        QFile file1(QString("/mnt/SD_CARD/Videohead/%1").arg(video_name.at(num)));
        if (file1.exists())
        {
            file1.remove();
        }
        file1.close();
    }
}

void video_browse::video_update()  //計算第幾頁，並在第(video_num)頁將影片預覽顯示出來
{
    init_video_name();

    video_totality = video_max / 6;

    if(video_max<6 && video_max>0)
    {
        video_totality += 1;
    }
    else if(video_max>6 && (video_max % 6 !=0))
    {
        video_totality += 1;
    }
    else if (video_max==0)
    {
        video_totality=1;
    }

    int video_start = (video_num-1)*6;

    if(video_max!=0)
    {
        if(video_max<6 && video_max>0)
        {
            for(i_num=0;i_num<video_max;i_num++)
            {
                if(flag_USB==1)
                {
                    labels.at(i_num)->setStyleSheet(QString("image: url(/mnt/USB_FLASH/Videohead/%1);").arg(video_name.at(i_num)));
                }
                else if(flag_USB==0 && flag_SD==1)
                {
                    labels.at(i_num)->setStyleSheet(QString("image: url(/mnt/SD_CARD/Videohead/%1);").arg(video_name.at(i_num)));
                }
            }
            label_all_false();
            label_play_all_false();
            for(i_num=0;i_num<video_max;i_num++)
            {
                labels.at(i_num)->setVisible(true);
                label_play.at(i_num)->setVisible(true);
            }
        }
        else if(video_max==6)
        {
            for(i_num=0;i_num<video_max;i_num++)
            {
                if(flag_USB==1)
                {
                    labels.at(i_num)->setStyleSheet(QString("image: url(/mnt/USB_FLASH/Videohead/%1);").arg(video_name.at(i_num)));
                }
                else if(flag_USB==0 && flag_SD==1)
                {
                    labels.at(i_num)->setStyleSheet(QString("image: url(/mnt/SD_CARD/Videohead/%1);").arg(video_name.at(i_num)));
                }
            }
            label_all_false();
            label_play_all_false();
            for(i_num=0; i_num<6; i_num++)
            {
                labels.at(i_num)->setVisible(true);
                label_play.at(i_num)->setVisible(true);
            }
        }
        else if(video_max>6)
        {
            if(video_num==1)
            {
                for(i_num=0;i_num<6;i_num++)
                {
                    if(flag_USB==1)
                    {
                        labels.at(i_num)->setStyleSheet(QString("image: url(/mnt/USB_FLASH/Videohead/%1);").arg(video_name.at(i_num)));
                    }
                    else if(flag_USB==0 && flag_SD==1)
                    {
                        labels.at(i_num)->setStyleSheet(QString("image: url(/mnt/SD_CARD/Videohead/%1);").arg(video_name.at(i_num)));
                    }
                }
                label_all_false();
                label_play_all_false();
                for(i_num=0; i_num<6; i_num++)
                {
                    labels.at(i_num)->setVisible(true);
                    label_play.at(i_num)->setVisible(true);
                }
            }
            else if(video_num>1 && (video_num<(video_totality-1) || video_num==(video_totality-1)))
            {
                for(i_num=0,p_num=(video_num*6-6); i_num<6 && p_num<video_num*6; i_num++,p_num++)
                {
                    if(flag_USB==1)
                    {
                        labels.at(i_num)->setStyleSheet(QString("image: url(/mnt/USB_FLASH/Videohead/%1);").arg(video_name.at(p_num)));
                    }
                    else if(flag_USB==0 && flag_SD==1)
                    {
                        labels.at(i_num)->setStyleSheet(QString("image: url(/mnt/SD_CARD/Videohead/%1);").arg(video_name.at(p_num)));
                    }
                }
                label_all_false();
                label_play_all_false();
                for(i_num=0; i_num<6; i_num++)
                {
                    labels.at(i_num)->setVisible(true);
                    label_play.at(i_num)->setVisible(true);
                }
            }
            else if(video_num>1 && video_num==video_totality)
            {
                for(i_num=0,p_num=video_start; i_num<(video_max-video_start) && p_num<video_max; i_num++,p_num++)
                {
                    if(flag_USB==1)
                    {
                        labels.at(i_num)->setStyleSheet(QString("image: url(/mnt/USB_FLASH/Videohead/%1);").arg(video_name.at(p_num)));
                    }
                    else if(flag_USB==0 && flag_SD==1)
                    {
                        labels.at(i_num)->setStyleSheet(QString("image: url(/mnt/SD_CARD/Videohead/%1);").arg(video_name.at(p_num)));
                    }
                }
                label_all_false();
                label_play_all_false();
                for(i_num=0; i_num<(video_max-video_start); i_num++)
                {
                    labels.at(i_num)->setVisible(true);
                    label_play.at(i_num)->setVisible(true);
                }
            }
        }
    }
    else if(video_max==0)
    {
        label_all_false();
        label_play_all_false();
    }

    ui->label_num->setText(QString("%1/%2").arg(video_num).arg(video_totality));
}

void video_browse::init_video_name()
{

    if(flag_USB==1)
    {
        //初始化数据
        QDir dir("/mnt/USB_FLASH/Videohead/");
        QDir::Filters filters = QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot;
        QDir::SortFlags sortFlags = QDir::DirsFirst | QDir::IgnoreCase | QDir::Name;
        QFileInfoList fileList = dir.entryInfoList(filters, sortFlags);
        video_max = fileList.size();
        for (const QFileInfo& fileInfo : fileList)
        {
            video_name.append(fileInfo.fileName());
        }
        printf("=USB_FLASH=video_max=%d=\n",video_max);
    }
    else if(flag_USB==0 && flag_SD==1)
    {
        //初始化数据
        QDir dir("/mnt/SD_CARD/Videohead/");
        QDir::Filters filters = QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot;
        QDir::SortFlags sortFlags = QDir::DirsFirst | QDir::IgnoreCase | QDir::Name;
        QFileInfoList fileList = dir.entryInfoList(filters, sortFlags);
        video_max = fileList.size();
        for (const QFileInfo& fileInfo : fileList)
        {
            video_name.append(fileInfo.fileName());
        }
        printf("=SD_CARD=video_max=%d=\n",video_max);
    }
    update_page_button();
}

void video_browse::select_all_mode()
{
    if(video_max<6 && video_max>0)
    {
        for(i_num=0; i_num<video_max; i_num++)
        {
            label_tick.at(i_num)->setVisible(true);
            tick_flag[i_num+1]=1;
        }
    }
    else if(video_max==6)
    {
        deselect_all_true();
    }
    else if(video_max>6)
    {
        if(video_max % 6 != 0)
        {
            if(video_num == video_totality)
            {
                for(i_num=0; i_num<(video_max % 6); i_num++)
                {
                    label_tick.at(i_num)->setVisible(true);
                    tick_flag[i_num+1]=1;
                }
                printf("video_num == video_totality\n");
            }
            else
            {
                deselect_all_true();
            }
        }
        else if(video_max % 6 == 0)
        {
            deselect_all_true();
        }
    }
}

void video_browse::deselect_all_false()
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

void video_browse::deselect_all_true()
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

void video_browse::label_all_false()
{
    ui->label_1->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);
}

void video_browse::label_play_all_false()
{
    ui->label_play_1->setVisible(false);
    ui->label_play_2->setVisible(false);
    ui->label_play_3->setVisible(false);
    ui->label_play_4->setVisible(false);
    ui->label_play_5->setVisible(false);
    ui->label_play_6->setVisible(false);
}

Label_return_v::Label_return_v(QWidget *parent): QLabel(parent)
{

}
void Label_return_v::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_select_v::Label_select_v(QWidget *parent): QLabel(parent)
{

}
void Label_select_v::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_select_all_v::Label_select_all_v(QWidget *parent): QLabel(parent)
{

}
void Label_select_all_v::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_deselect_all_v::Label_deselect_all_v(QWidget *parent): QLabel(parent)
{

}
void Label_deselect_all_v::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_left_v::Label_left_v(QWidget *parent): QLabel(parent)
{

}
void Label_left_v::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_right_v::Label_right_v(QWidget *parent): QLabel(parent)
{

}
void Label_right_v::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_delete_v::Label_delete_v(QWidget *parent): QLabel(parent)
{

}
void Label_delete_v::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}





Label_video_1::Label_video_1(QWidget *parent): QLabel(parent)
{

}
void Label_video_1::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_video_2::Label_video_2(QWidget *parent): QLabel(parent)
{

}
void Label_video_2::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_video_3::Label_video_3(QWidget *parent): QLabel(parent)
{

}
void Label_video_3::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_video_4::Label_video_4(QWidget *parent): QLabel(parent)
{

}
void Label_video_4::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_video_5::Label_video_5(QWidget *parent): QLabel(parent)
{

}
void Label_video_5::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_video_6::Label_video_6(QWidget *parent): QLabel(parent)
{

}
void Label_video_6::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
