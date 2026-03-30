#include "video_drowse_play.h"
#include "ui_video_drowse_play.h"

video_drowse_play::video_drowse_play(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::video_drowse_play)
{
    ui->setupUi(this);
    currentProgress = 0.0;
    hours=0;
    minutes=0;
    seconds=0;
    timer = new QTimer(this);
    timer_socket = new QTimer(this);
    timer_switchable = new QTimer(this);

    connect(timer_switchable, &QTimer::timeout, this,[=](){
        switchable_delete_flag=0;
    });

    connect(timer, &QTimer::timeout, this, [=](){
        currentSeconds++;

        ui->horizontalSlider->setValue((currentSeconds * 100) / progress_time); //更新進度條

        hours = currentSeconds / 3600;
        minutes = (currentSeconds % 3600) / 60;
        seconds = currentSeconds % 60;

        tem_str.sprintf("%02d:%02d:%02d",hours,minutes,seconds);
        ui->label_time->setText(tem_str); //
        if (currentSeconds >= progress_time)
        {
            timer->stop();
            video_play_flag=0;
            replayFlag=true;
            ui->label_pause->setStyleSheet("image: url(:/tu/视频/影片标识.png);");
            ui->label_time->setText(tem_str);
            printf("+++++++++++++++++++++\n");
        }
    });

    connect(timer_socket, &QTimer::timeout, this, [=](){
        timer_socket->stop();
        extract_name_play(video_labelnum);
        //reset_progress_bar();
    });

    connect(ui->label_return,&Label_return_vs::clicked_1,this,[=](){
        emit socket_close_play_return();
        emit return_video();
        replayFlag = false;
        update_video_page_button();
    });
    connect(ui->label_left,&Label_left_vs::clicked_1,this,[=](){
        if(video_labelnum>0)
        {
            if(switchable_flag == 0)
            {
                switchable_flag=1;
                video_labelnum--;
                printf("==video_labelnum==%d\n",video_labelnum);
                timer->stop();
                progress_time=0;
                emit socket_close_play();
                timer_socket->start(50);
                currentSeconds = 0;
                ui->horizontalSlider->setRange(0, 100);
                ui->horizontalSlider->setValue(0);
                tem_str.sprintf("%02d:%02d:%02d",0,0,0);
                ui->label_time->setText(tem_str);
                replayFlag = false;
                update_video_page_button();
             }

        }
    });
    connect(ui->label_right,&Label_right_vs::clicked_1,this,[=](){
        if(video_labelnum<(video_max-1))
        {
            if(switchable_flag == 0)
            {
                switchable_flag=1;
                video_labelnum++;
                printf("==video_labelnum==%d\n",video_labelnum);
                timer->stop();
                progress_time=0;
                emit socket_close_play();
                timer_socket->start(50);
                currentSeconds = 0;
                ui->horizontalSlider->setRange(0, 100);
                ui->horizontalSlider->setValue(0);
                tem_str.sprintf("%02d:%02d:%02d",0,0,0);
                ui->label_time->setText(tem_str);
                replayFlag = false;
                update_video_page_button();
            }
        }

    });
    connect(ui->label_recoil,&Label_recoil_vs::clicked_1,this,[=](){
        if(currentSeconds > 7)
        {
            currentSeconds-=5;
            emit socket_fast_backward();
            printf("currentSeconds  ====  %d  \n",currentSeconds);
        }
        else
        {
            printf("时间不够  不要点了  label_recoil\n");
        }
        printf("Label_recoil_vs\n");
    });
    connect(ui->label_pause,&Label_pause_vs::clicked_1,this,[=](){
        if(video_play_flag==0)
        {
            video_play_flag=1;
            if(!replayFlag)
            {
                emit socket_play_on();
            }
            else
            {
                if(switchable_flag == 0)
                {
                    switchable_flag=1;
                    printf("==video_labelnum==%d\n",video_labelnum);
                    timer->stop();
                    progress_time=0;
                    emit socket_close_play();
                    timer_socket->start(50);
                    currentSeconds = 0;
                    ui->horizontalSlider->setRange(0, 100);
                    ui->horizontalSlider->setValue(0);
                    tem_str.sprintf("%02d:%02d:%02d",0,0,0);
                    ui->label_time->setText(tem_str);
                    replayFlag = false;
                }
            }
            ui->label_pause->setStyleSheet("image: url(:/tu/视频/暂停.png);");//播放
            timer->start();
        }
        else if(video_play_flag==1)
        {
            video_play_flag=0;
            emit socket_pause();
            ui->label_pause->setStyleSheet("image: url(:/tu/视频/影片标识.png);");
            timer->stop();
        }
        printf("====================replayFlag======%d==========video_play_flag======%d============\n",replayFlag,video_play_flag);
    });
    connect(ui->label_advance,&Label_advance_vs::clicked_1,this,[=](){
        if(progress_time-currentSeconds > 7)
        {
            currentSeconds+=5;
            emit socket_fast_forward();
            printf("currentSeconds  ====  %d  \n",currentSeconds);
        }
        else
        {
            printf("时间不够  不要点了  label_advance\n");
        }
        printf("Label_advance_vs\n");
    });
    connect(ui->label_delete,&Label_delete_vs::clicked_1,this,[=](){
        if(switchable_delete_flag == 0)
        {
            switchable_delete_flag=1;

            emit socket_close_play();

            QString firstFileName = video_name.at(video_labelnum);
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
            qDebug()<<"playback_video_name======="<<playback_video_name;
            if(flag_USB==1)
            {
                QFile file(QString("/mnt/USB_FLASH/Video/%1.mp4").arg(playback_video_name));
                if (file.exists())
                {
                    file.remove();
                }
                file.close();
                qDebug()<<"video_name====="<<QString("/mnt/USB_FLASH/Video/%1.mp4").arg(playback_video_name);
                QString filePath1 = QString("/mnt/USB_FLASH/Videohead/%1").arg(video_name.at(video_labelnum));
                QFile file1(filePath1);
                if (file1.exists())
                {
                    file1.remove();
                }
                file1.close();

                video_name.clear();

                QDir dir("/mnt/USB_FLASH/Videohead/");
                QDir::Filters filters = QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot;
                QDir::SortFlags sortFlags = QDir::DirsFirst | QDir::IgnoreCase | QDir::Name;
                QFileInfoList fileList = dir.entryInfoList(filters, sortFlags);
                video_max = fileList.size();
                for (const QFileInfo& fileInfo : fileList)
                {
                    video_name.append(fileInfo.fileName());
                }
                printf("==video_max=%d=\n",video_max);
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
                QString filePath1 = QString("/mnt/SD_CARD/Videohead/%1").arg(video_name.at(video_labelnum));
                QFile file1(filePath1);
                if (file1.exists())
                {
                    file1.remove();
                }
                file1.close();

                video_name.clear();

                QDir dir("/mnt/SD_CARD/Videohead/");
                QDir::Filters filters = QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot;
                QDir::SortFlags sortFlags = QDir::DirsFirst | QDir::IgnoreCase | QDir::Name;
                QFileInfoList fileList = dir.entryInfoList(filters, sortFlags);
                video_max = fileList.size();
                for (const QFileInfo& fileInfo : fileList)
                {
                    video_name.append(fileInfo.fileName());
                }
                printf("==video_max=%d=\n",video_max);
            }

            if(video_labelnum==video_max && video_max!=0)
            {
                video_labelnum--;
                printf("==delete==%d\n",video_labelnum);
                timer->stop();
                progress_time=0;
                emit socket_close_play();
                timer_socket->start(50);
                currentSeconds = 0;
                ui->horizontalSlider->setRange(0, 100);
                ui->horizontalSlider->setValue(0);
                tem_str.sprintf("%02d:%02d:%02d",0,0,0);
                ui->label_time->setText(tem_str);
            }
            else if(video_labelnum==video_max && video_max==0)
            {
                emit return_video();
                replayFlag = false;
            }
            else
            {
                printf("==delete==%d\n",video_labelnum);
                timer->stop();
                progress_time=0;
                emit socket_close_play();
                timer_socket->start(50);
                currentSeconds = 0;
                ui->horizontalSlider->setRange(0, 100);
                ui->horizontalSlider->setValue(0);
                tem_str.sprintf("%02d:%02d:%02d",0,0,0);
                ui->label_time->setText(tem_str);
            }
            timer_switchable->start(1000);
        }
    });

    ui->horizontalSlider->setRange(0, 100);
    ui->horizontalSlider->setValue(0);
    ui->horizontalSlider->show();
    ui->horizontalSlider->setEnabled(false);

    update_video_page_button();
}

video_drowse_play::~video_drowse_play()
{
    delete ui;
}


void video_drowse_play::update_video_page_button()
{
    prevEffect = new QGraphicsOpacityEffect(this);
    nextEffect = new QGraphicsOpacityEffect(this);

    ui->label_left->setGraphicsEffect(prevEffect);
    ui->label_right->setGraphicsEffect(nextEffect);
    // 上一頁
    if (video_labelnum == 0)
    {
        prevEffect->setOpacity(0.3);
        ui->label_left->setEnabled(false);
    }
    else
    {
        prevEffect->setOpacity(1.0);
        ui->label_left->setEnabled(true);
    }
    if (video_labelnum == (video_max -1))
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

void video_drowse_play::sd_convert_usb()
{
    emit socket_close_play_return();
    emit return_video();
    replayFlag = false;
}

void video_drowse_play::reset_progress_bar()
{
    timer->stop();
    ui->label_pause->setStyleSheet("image: url(:/tu/视频/暂停.png);");//播放
    currentSeconds = 0;
    ui->horizontalSlider->setRange(0, 100);
    ui->horizontalSlider->setValue(0);
    timer->setInterval(1000);
    timer->setSingleShot(false);
    timer->start();
}

void video_drowse_play::video_update()
{
    tem_str.sprintf("%02d:%02d:%02d",0,0,0);
    ui->label_time->setText(tem_str);
    if(video_num!=1)
    {
        video_labelnum=video_labelnum+(6*(video_num-1));
    }
    video_labelnum=video_labelnum-1;

    printf("video_labelnum===%d===88\n",video_labelnum);
    extract_name_play_one(video_labelnum);

    ui->label_pause->setStyleSheet("image: url(:/tu/视频/暂停.png);");//播放
    update_video_page_button();
}

void video_drowse_play::extract_name_play(int num)
{
    QString firstFileName = video_name.at(num);
    QStringList  strs=firstFileName.split(".");
    QByteArray byteArray = strs.at(0).toLatin1();
    char *fileName = byteArray.data();
    memset(playback_video_name,0,sizeof(playback_video_name));
    strcpy(playback_video_name, fileName);
    qDebug() << "Processed file name:" << playback_video_name;
    emit socket_play_video();
}

void video_drowse_play::extract_name_play_one(int num)
{
    QString firstFileName = video_name.at(num);
    QStringList  strs=firstFileName.split(".");
    QByteArray byteArray = strs.at(0).toLatin1();
    char *fileName = byteArray.data();
    memset(playback_video_name,0,sizeof(playback_video_name));
    strcpy(playback_video_name, fileName);
    qDebug() << "Processed file name:" << playback_video_name;
    emit socket_play_video_one();
}



Label_return_vs::Label_return_vs(QWidget *parent): QLabel(parent)
{

}
void Label_return_vs::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_left_vs::Label_left_vs(QWidget *parent): QLabel(parent)
{

}
void Label_left_vs::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_right_vs::Label_right_vs(QWidget *parent): QLabel(parent)
{

}
void Label_right_vs::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_recoil_vs::Label_recoil_vs(QWidget *parent): QLabel(parent)
{

}
void Label_recoil_vs::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_pause_vs::Label_pause_vs(QWidget *parent): QLabel(parent)
{

}
void Label_pause_vs::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_advance_vs::Label_advance_vs(QWidget *parent): QLabel(parent)
{

}
void Label_advance_vs::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_delete_vs::Label_delete_vs(QWidget *parent): QLabel(parent)
{

}
void Label_delete_vs::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
