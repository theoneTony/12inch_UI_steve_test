#include "time_setting.h"
#include "ui_time_setting.h"

time_setting::time_setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::time_setting)
{
    ui->setupUi(this);

    connect(ui->label_return,&Label_return_time::clicked_1,this,[=](){
        emit clicked_return();
    });

    connect(ui->label_save,&Label_save_time::clicked_1,this,[=](){
        //保存date -s "2024-06-03 12:00:00"
        splice_data=QString("date %1%2%3%4%5.%6").arg(ui->label_month->text()).arg(ui->label_day->text()).arg(ui->label_hour->text()).arg(ui->label_minute->text()).arg(year_data_use).arg(time_num.num_second);
        set_time = splice_data.toLatin1();//QString → C字串
        system(set_time.data());
        usleep(1000*50);
        system("hwclock -w");//同步
        emit clicked_return();
    });

    connect(ui->label_up1,&Label_up1_time::clicked_1,this,[=](){
        switch (time_flag) {
        case 1:
        {
            if(year1_data_use<9)
            {
                year1_data_use++;
                ui->label_year1->setText(QString::number(year1_data_use));
            }
            break;
        }
        case 2:
        {
            if(year2_data_use<9)
            {
                year2_data_use++;
                ui->label_year2->setText(QString::number(year2_data_use));
            }
            break;
        }
        case 3:
        {
            if(year3_data_use<9)
            {
                year3_data_use++;
                ui->label_year3->setText(QString::number(year3_data_use));
            }
            break;
        }
        case 4:
        {
            if(year4_data_use<9)
            {
                year4_data_use++;
                ui->label_year4->setText(QString::number(year4_data_use));
            }
            break;
        }
        }
        qsyear_data_use=QString("%1%2%3%4").arg(year1_data_use).arg(year2_data_use).arg(year3_data_use).arg(year4_data_use);
        year_data_use=qsyear_data_use.toInt();
    });
    connect(ui->label_down1,&Label_down1_time::clicked_1,this,[=](){
        switch (time_flag) {
        case 1:
        {
            if(year1_data_use>1)
            {
                year1_data_use--;
                ui->label_year1->setText(QString::number(year1_data_use));
            }
            break;
        }
        case 2:
        {
            if(year2_data_use>0)
            {
                year2_data_use--;
                ui->label_year2->setText(QString::number(year2_data_use));
            }
            break;
        }
        case 3:
        {
            if(year3_data_use>0)
            {
                year3_data_use--;
                ui->label_year3->setText(QString::number(year3_data_use));
            }
            break;
        }
        case 4:
        {
            if(year4_data_use>0)
            {
                year4_data_use--;
                ui->label_year4->setText(QString::number(year4_data_use));
            }
            break;
        }
        }
        qsyear_data_use=QString("%1%2%3%4").arg(year1_data_use).arg(year2_data_use).arg(year3_data_use).arg(year4_data_use);
        year_data_use=qsyear_data_use.toInt();
    });

    connect(ui->label_up2,&Label_up2_time::clicked_1,this,[=](){
        switch (time_flag) {
        case 5:
        {
            if(month_data_use<12)
            {
                month_data_use++;
                if(month_data_use>9)
                {
                    ui->label_month->setText(QString::number(month_data_use));
                }
                else
                {
                    ui->label_month->setText(QString("0%1").arg(month_data_use));
                }
                if((month_data_use==4 || month_data_use==6 || month_data_use==9 || month_data_use==11) && day_data_use > 30)
                {
                    day_data_use=30;
                }
                else if(month_data_use==2 && day_data_use > 28)
                {
                    if ((year_data_use%4 == 0 && year_data_use%100 != 0) || (year_data_use%400 == 0))
                    {
                        day_data_use=29;
                    }
                    else
                    {
                        day_data_use=28;
                    }
                }
            }
            break;
        }
        case 6:
        {
            if(month_data_use==1 || month_data_use==3 || month_data_use==5 || month_data_use==7 || month_data_use==8 || month_data_use==10 || month_data_use==12)
            {
                if(day_data_use<31)
                {
                    day_data_use++;
                    if(day_data_use>9)
                    {
                        ui->label_day->setText(QString::number(day_data_use));
                    }
                    else
                    {
                        ui->label_day->setText(QString("0%1").arg(day_data_use));

                    }
                }
            }
            else if(month_data_use==4 || month_data_use==6 || month_data_use==9 || month_data_use==11)
            {
                if(day_data_use<30)
                {
                    day_data_use++;
                    if(day_data_use>9)
                    {
                        ui->label_day->setText(QString::number(day_data_use));
                    }
                    else
                    {
                        ui->label_day->setText(QString("0%1").arg(day_data_use));
                    }
                }
            }
            else
            {
                 if ((year_data_use%4 == 0 && year_data_use%100 != 0) || (year_data_use%400 == 0))
                 {
                     if(day_data_use<29)
                     {
                         day_data_use++;
                         if(day_data_use>9)
                         {
                             ui->label_day->setText(QString::number(day_data_use));
                         }
                         else
                         {
                             ui->label_day->setText(QString("0%1").arg(day_data_use));

                         }
                     }
                 }
                 else
                 {
                     if(day_data_use<28)
                     {
                         day_data_use++;
                         if(day_data_use>9)
                         {
                             ui->label_day->setText(QString::number(day_data_use));
                         }
                         else
                         {
                             ui->label_day->setText(QString("0%1").arg(day_data_use));

                         }
                     }
                 }
            }
            break;
        }
        }
    });
    connect(ui->label_down2,&Label_down2_time::clicked_1,this,[=](){
        switch (time_flag) {
        case 5:
        {
            if(month_data_use>1)
            {
                month_data_use--;
                if(month_data_use>9)
                {
                    ui->label_month->setText(QString::number(month_data_use));
                }
                else
                {
                    ui->label_month->setText(QString("0%1").arg(month_data_use));
                }
            }
            break;
        }
        case 6:
        {
            if(day_data_use>1)
            {
                day_data_use--;
                if(day_data_use>9)
                {
                    ui->label_day->setText(QString::number(day_data_use));
                }
                else
                {
                    ui->label_day->setText(QString("0%1").arg(day_data_use));

                }
            }
        }
        }
    });

    connect(ui->label_up3,&Label_up3_time::clicked_1,this,[=](){
        switch (time_flag) {
        case 7:
        {
            if(hour_data_use<23)
            {
                hour_data_use++;
                if(hour_data_use>9)
                {
                    ui->label_hour->setText(QString::number(hour_data_use));
                }
                else
                {
                    ui->label_hour->setText(QString("0%1").arg(hour_data_use));
                }
            }
            break;
        }
        case 8:
        {
            if(minute_data_use<59)
            {
                minute_data_use++;
                if(minute_data_use>9)
                {
                    ui->label_minute->setText(QString::number(minute_data_use));
                }
                else
                {
                    ui->label_minute->setText(QString("0%1").arg(minute_data_use));
                }
            }
            break;
        }
        }
    });
    connect(ui->label_down3,&Label_down3_time::clicked_1,this,[=](){
        switch (time_flag) {
        case 7:
        {
            if(hour_data_use>0)
            {
                hour_data_use--;
                if(hour_data_use>9)
                {
                    ui->label_hour->setText(QString::number(hour_data_use));
                }
                else
                {
                    ui->label_hour->setText(QString("0%1").arg(hour_data_use));
                }
            }
            break;
        }
        case 8:
        {
            if(minute_data_use>0)
            {
                minute_data_use--;
                if(minute_data_use>9)
                {
                    ui->label_minute->setText(QString::number(minute_data_use));
                }
                else
                {
                    ui->label_minute->setText(QString("0%1").arg(minute_data_use));
                }
            }
            break;
        }
        }
    });

    connect(ui->label_year1,&Label_year1_time::clicked_1,this,[=](){
        time_flag=1;
        update_setStyleSheet();
    });
    connect(ui->label_year2,&Label_year2_time::clicked_1,this,[=](){
        time_flag=2;
        update_setStyleSheet();
    });
    connect(ui->label_year3,&Label_year3_time::clicked_1,this,[=](){
        time_flag=3;
        update_setStyleSheet();
    });
    connect(ui->label_year4,&Label_year4_time::clicked_1,this,[=](){
        time_flag=4;
        update_setStyleSheet();
    });
    connect(ui->label_month,&Label_month_time::clicked_1,this,[=](){
        time_flag=5;
        update_setStyleSheet();
    });
    connect(ui->label_day,&Label_day_time::clicked_1,this,[=](){
        time_flag=6;
        update_setStyleSheet();
    });
    connect(ui->label_hour,&Label_hour_time::clicked_1,this,[=](){
        time_flag=7;
        update_setStyleSheet();
    });
    connect(ui->label_minute,&Label_minute_time::clicked_1,this,[=](){
        time_flag=8;
        update_setStyleSheet();
    });


    ui->label_backdrop->setStyleSheet("border-radius: 30px 30px 30px 30px;background-color: rgb(110, 215, 230);");
    ui->label_save->setStyleSheet("border-radius: 10px 10px 10px 10px;background-color: rgb(151, 235, 238);");
    ui->label_return->setStyleSheet("border-radius: 10px 10px 10px 10px;background-color: rgb(151, 235, 238);");
}

time_setting::~time_setting()
{
    delete ui;
}

void time_setting::update_setStyleSheet()
{
    ui->label_year1->setStyleSheet("background-color: rgb(58, 167, 242);");
    ui->label_year2->setStyleSheet("background-color: rgb(58, 167, 242);");
    ui->label_year3->setStyleSheet("background-color: rgb(58, 167, 242);");
    ui->label_year4->setStyleSheet("background-color: rgb(58, 167, 242);");
    ui->label_month->setStyleSheet("background-color: rgb(58, 167, 242);");
    ui->label_day->setStyleSheet("background-color: rgb(58, 167, 242);");
    ui->label_hour->setStyleSheet("background-color: rgb(58, 167, 242);");
    ui->label_minute->setStyleSheet("background-color: rgb(58, 167, 242);");
    switch (time_flag) {
    case 1:
    {
        ui->label_year1->setStyleSheet("background-color: rgb(8, 93, 147);");
        break;
    }
    case 2:
    {
        ui->label_year2->setStyleSheet("background-color: rgb(8, 93, 147);");
        break;
    }
    case 3:
    {
        ui->label_year3->setStyleSheet("background-color: rgb(8, 93, 147);");
        break;
    }
    case 4:
    {
        ui->label_year4->setStyleSheet("background-color: rgb(8, 93, 147);");
        break;
    }
    case 5:
    {
        ui->label_month->setStyleSheet("background-color: rgb(8, 93, 147);");
        break;
    }
    case 6:
    {
        ui->label_day->setStyleSheet("background-color: rgb(8, 93, 147);");
        break;
    }
    case 7:
    {
        ui->label_hour->setStyleSheet("background-color: rgb(8, 93, 147);");
        break;
    }
    case 8:
    {
        ui->label_minute->setStyleSheet("background-color: rgb(8, 93, 147);");
        break;
    }
    }
}

void time_setting::update_data()
{
    ui->label_year1->setText(time_num.num_year1);
    ui->label_year2->setText(time_num.num_year2);
    ui->label_year3->setText(time_num.num_year3);
    ui->label_year4->setText(time_num.num_year4);
    ui->label_month->setText(time_num.num_month);
    ui->label_day->setText(time_num.num_day);
    ui->label_hour->setText(time_num.num_hour);
    ui->label_minute->setText(time_num.num_minute);

    year_data_use=time_num.num_year.toInt();
    year1_data_use=time_num.num_year1.toInt();
    year2_data_use=time_num.num_year2.toInt();
    year3_data_use=time_num.num_year3.toInt();
    year4_data_use=time_num.num_year4.toInt();
    month_data_use=time_num.num_month.toInt();
    day_data_use=time_num.num_day.toInt();
    hour_data_use=time_num.num_hour.toInt();
    minute_data_use=time_num.num_minute.toInt();

    update_setStyleSheet();
}

void time_setting::settext()
{
    ui->label_num->setText(tr("时间设置"));
    ui->label_return->setText(tr("退出"));
    ui->label_save->setText(tr("保存"));
}



Label_up1_time::Label_up1_time(QWidget *parent): QLabel(parent)
{

}
void Label_up1_time::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_up2_time::Label_up2_time(QWidget *parent): QLabel(parent)
{

}
void Label_up2_time::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}Label_up3_time::Label_up3_time(QWidget *parent): QLabel(parent)
{

}
void Label_up3_time::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_down1_time::Label_down1_time(QWidget *parent): QLabel(parent)
{

}
void Label_down1_time::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_down2_time::Label_down2_time(QWidget *parent): QLabel(parent)
{

}
void Label_down2_time::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_down3_time::Label_down3_time(QWidget *parent): QLabel(parent)
{

}
void Label_down3_time::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}



Label_year1_time::Label_year1_time(QWidget *parent): QLabel(parent)
{

}
void Label_year1_time::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_year2_time::Label_year2_time(QWidget *parent): QLabel(parent)
{

}
void Label_year2_time::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_year3_time::Label_year3_time(QWidget *parent): QLabel(parent)
{

}
void Label_year3_time::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_year4_time::Label_year4_time(QWidget *parent): QLabel(parent)
{

}
void Label_year4_time::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_month_time::Label_month_time(QWidget *parent): QLabel(parent)
{

}
void Label_month_time::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_day_time::Label_day_time(QWidget *parent): QLabel(parent)
{

}
void Label_day_time::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_hour_time::Label_hour_time(QWidget *parent): QLabel(parent)
{

}
void Label_hour_time::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_minute_time::Label_minute_time(QWidget *parent): QLabel(parent)
{

}
void Label_minute_time::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}


Label_return_time::Label_return_time(QWidget *parent): QLabel(parent)
{

}
void Label_return_time::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
Label_save_time::Label_save_time(QWidget *parent): QLabel(parent)
{

}
void Label_save_time::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
