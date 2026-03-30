#include "widget.h"
#include "ui_widget.h"
Widget *Widget::mywidget=nullptr;
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mywidget=this;

    settings=new QSettings("/customer/setargument.ini", QSettings::IniFormat);
    settings->beginGroup("RPINFO");

    year_w=0;
    onth_w=0;
    day_w=0;
    hour_w=0;
    minute_w=0;
    second_w=0;

    timer_1=new QTimer(this);
    nosdcard_wiget=new tips_no_sd_card(this);

    socketclient = new QTcpSocket;

    mythread=new QThread(this);
    key=new key_thread;
    mythread_mipi0=new QThread(this);
    key_mipi0=new key_thread_mipi0;
    mythread_mipi3=new QThread(this);
    key_mipi3=new key_thread_mipi3;
    mcu_thread=new QThread(this);
    usb_mcu_key=new usb_mcu;
    rev_mcu_thread=new QThread(this);
    rev_usb_mcu_key=new rev_usb_mcu;

    thread_290=new QThread(this);
    key_290=new key_thread_290;

    thread_9anjian=new QThread(this);
    key_9anjian=new shortcut_key;



    photo_totality = photo_max / 12;
    if (photo_max % 12 != 0)
    {
        photo_totality += 1;
    }

    zhukuang_widget=new zhukuang(this);
    system_widget=new system_setting(this);
    control_widget=new control_interface(this);
    photo_widget=new photo_browse(this);
    video_widget=new video_browse(this);
    photo_single_widget=new photo_browse_single(this);
    video_play_widget=new video_drowse_play(this);

    formatting_widget=new formatting(this);
    reset_widget=new reset_setting(this);
    version_number_widget=new version_number(this);
    time_widget=new time_setting(this);
    language_widget=new language_setting(this);
    device_widget=new no_device(this);
    memory_widget=new no_memory(this);
    sensor_restart_widget=new sensor_restart(this);
    missing_widget=new missing_upgrade_file(this);

    ui->one_stack->addWidget(zhukuang_widget);
    ui->one_stack->addWidget(system_widget);
    ui->one_stack->addWidget(control_widget);
    ui->one_stack->addWidget(photo_widget);
    ui->one_stack->addWidget(video_widget);
    ui->one_stack->addWidget(photo_single_widget);
    ui->one_stack->addWidget(video_play_widget);
    ui->one_stack->setVisible(false);
    ui->one_stack->setCurrentWidget(zhukuang_widget);
    ui->one_stack->setVisible(true);

    ui->two_stack->addWidget(formatting_widget);
    ui->two_stack->addWidget(reset_widget);
    ui->two_stack->addWidget(version_number_widget);
    ui->two_stack->addWidget(time_widget);
    ui->two_stack->addWidget(language_widget);
    ui->two_stack->addWidget(nosdcard_wiget);
    ui->two_stack->addWidget(device_widget);
    ui->two_stack->addWidget(memory_widget);
    ui->two_stack->addWidget(sensor_restart_widget);
    ui->two_stack->addWidget(missing_widget);
    ui->two_stack->setVisible(false);
    ui->two_stack->setCurrentWidget(version_number_widget);
    signal(SIGUSR1,sd_in_re);
    signal(SIGUSR2,sd_in_re);
    signal(SIGRTMAX,usb_in_re);

    connect(key,&key_thread::first_key,this,[=](){
        if(freeze_flag==0 || custom1_flag==2)
        {
            if(video_flag==0)
            this->set_first_key();
        }
    });
    connect(key,&key_thread::second_key,this,[=](){
        if(freeze_flag==0 || custom2_flag==2)
        {
            if(video_flag==0)
            this->set_second_key();
        }
    });
    connect(key,&key_thread::third_key,this,[=](){
        if(freeze_flag==0 || custom3_flag==2)
        {
            if(video_flag==0)
            this->set_third_key();
        }
    });
    connect(key,&key_thread::fourth_key,this,[=](){
        if(freeze_flag==0)
            this->set_fourth_key();
    });
    connect(key,&key_thread::fourth_key_long,this,[=](){
        if(freeze_flag==0)
            this->set_fourth_key_long();
    });
    connect(key,&key_thread::insertion_key,this,[=](){
        //是否有接mipi1的发送
        printf("mipi1接入\n");
        if(label_switch_flag==1)
            control_widget->switch_off();
        memset(socket_data2,0,sizeof(socket_data2));
        socket_data2[0] = 0x54;
        socket_data2[1] = 0x02;
        socketclient->write(socket_data2,sizeof(socket_data2));
    });
    connect(key,&key_thread::uninsertion_key,this,[=](){
        //是否有接mipi1的发送
        printf("mipi1拔出\n");
        if(label_switch_flag==1)
            control_widget->switch_off();
        memset(socket_data2,0,sizeof(socket_data2));
        socket_data2[0] = 0x53;
        socket_data2[1] = 0x02;
        socketclient->write(socket_data2,sizeof(socket_data2));
    });

    connect(usb_mcu_key,&usb_mcu::update_display,this,[=](){
        control_widget->update_duration();
    });
    connect(usb_mcu_key,&usb_mcu::key_photo,this,[=](){
        if(in_control_flag==1)
            control_widget->set_photograph();
    });
    connect(usb_mcu_key,&usb_mcu::key_video,this,[=](){
        if(in_control_flag==1)
            control_widget->set_video();
    });

    connect(key_mipi0,&key_thread_mipi0::first_key,this,[=](){
        if(freeze_flag==0)
            this->set_first_mipi0_key();
    });
    connect(key_mipi0,&key_thread_mipi0::first_long_key,this,[=](){
        if(freeze_flag==0)
            this->set_first_long_mipi0_key();
    });
    connect(key_mipi0,&key_thread_mipi0::insertion_key,this,[=](){
        //是否有接mipi0的发送
        printf("mipi0接入\n");
        if(label_switch_flag==1)
            control_widget->switch_off();
        memset(socket_data2,0,sizeof(socket_data2));
        socket_data2[0] = 0x54;
        socket_data2[1] = 0x01;
        socketclient->write(socket_data2,sizeof(socket_data2));
    });
    connect(key_mipi0,&key_thread_mipi0::uninsertion_key,this,[=](){
        //是否有接mipi0的发送
        printf("mipi0拔出\n");
        if(label_switch_flag==1)
            control_widget->switch_off();
        memset(socket_data2,0,sizeof(socket_data2));
        socket_data2[0] = 0x53;
        socket_data2[1] = 0x01;
        socketclient->write(socket_data2,sizeof(socket_data2));
    });

    connect(key_mipi3,&key_thread_mipi3::insertion_key,this,[=](){
        //是否有接mipi3的发送
        printf("mipi3接入\n");
        if(label_switch_flag==1)
            control_widget->switch_off();
        control_widget->set_gpio_host_led();

        memset(socket_data2,0,sizeof(socket_data2));
        socket_data2[0] = 0x54;
        socket_data2[1] = 0x03;
        socketclient->write(socket_data2,sizeof(socket_data2));
    });
    connect(key_mipi3,&key_thread_mipi3::uninsertion_key,this,[=](){
        //是否有接mipi3的发送
        printf("mipi3拔出\n");
        if(label_switch_flag==1)
            control_widget->switch_off();
        control_widget->set_gpio_host_led_logo();

        memset(socket_data2,0,sizeof(socket_data2));
        socket_data2[0] = 0x53;
        socket_data2[1] = 0x03;
        socketclient->write(socket_data2,sizeof(socket_data2));
    });

    connect(key_290,&key_thread_290::key_photo,this,[=](){
        control_widget->set_photograph();
    });
    connect(key_290,&key_thread_290::key_video,this,[=](){
        control_widget->set_video();
    });
    connect(key_290,&key_thread_290::key_zoom_in,this,[=](){
        control_widget->set_zoomup();
    });
    connect(key_290,&key_thread_290::key_zoom_out,this,[=](){
        control_widget->set_zoomdown();
    });

    //外接按键板
    connect(key_9anjian,&shortcut_key::key_photo,this,[=](){
        control_widget->set_photograph();
    });
    connect(key_9anjian,&shortcut_key::key_video,this,[=](){
        control_widget->set_video();
    });
    connect(key_9anjian,&shortcut_key::key_freeze,this,[=](){
        control_widget->set_freeze();
    });
    connect(key_9anjian,&shortcut_key::key_mode,this,[=](){
        control_widget->click_display();
    });
    connect(key_9anjian,&shortcut_key::key_led_add,this,[=](){
        control_widget->set_ledup();
    });
    connect(key_9anjian,&shortcut_key::key_led_minus,this,[=](){
        control_widget->set_leddown();
    });
    connect(key_9anjian,&shortcut_key::key_pump,this,[=](){
        control_widget->click_pump();
    });
    connect(key_9anjian,&shortcut_key::key_wb,this,[=](){
        control_widget->set_awb();
    });
    connect(key_9anjian,&shortcut_key::key_zoom,this,[=](){
        control_widget->set_zoomup();
    });

    connect(formatting_widget,&formatting::no_SDTips,this,[=](){
        ui->two_stack->setVisible(false);
        ui->two_stack->setCurrentWidget(nosdcard_wiget);
        ui->two_stack->setVisible(true);
        timer_1->start(2000);
    });

    connect(timer_1, &QTimer::timeout, this,[=](){
        ui->two_stack->setVisible(false);
        timer_1->stop();
    });

    connect(version_number_widget,&version_number::no_SDTips,this,[=](){
        ui->two_stack->setVisible(false);
        ui->two_stack->setCurrentWidget(nosdcard_wiget);
        ui->two_stack->setVisible(true);
        timer_1->start(2000);
    });


    connect(sensor_restart_widget, &sensor_restart::clicked_return, this,[=](){
        ui->two_stack->setVisible(false);
    });

    connect(formatting_widget,&formatting::format_ok,this,[=](){
        system("umount /mnt/SD_CARD");
        system("mkfs.vfat /dev/mmcblk0p1");
        system("sync");
        system("mount -t vfat /dev/mmcblk0p1 /mnt/SD_CARD/");
        system("sync");

        system("mkdir /mnt/SD_CARD/Video");
        system("mkdir /mnt/SD_CARD/Videohead");
        system("mkdir /mnt/SD_CARD/Picture");
        ui->two_stack->setVisible(false);
    });


    //背景透明
    this->setAttribute(Qt::WA_TranslucentBackground);


    connect(version_number_widget,&version_number::missing_file,this,[=]{
        printf("无设备提示\n");
        ui->two_stack->setVisible(false);
        ui->two_stack->setCurrentWidget(missing_widget);
        ui->two_stack->setVisible(true);
        timer_1->start(2000);
    });
    //zhukuang
    connect(zhukuang_widget,&zhukuang::clicked_start,this,[=]{
        if(sensorless_flag==1)
        {
            // 如果目前顯示無設備，稍微延遲 2000ms 再檢查一次
            QTimer::singleShot(1500, this, [=](){
                if (sensorless_flag == 0) {
                    // 如果延遲後發現設備已上線，執行正常流程
                    control_widget->update_data();
                    ui->one_stack->setVisible(false);
                    ui->one_stack->setCurrentWidget(control_widget);
                    ui->one_stack->setVisible(true);
                    in_control_flag=1;
                } else {
                    // 真的沒設備才跳提示
                    printf("无设备提示\n");
                    ui->two_stack->setVisible(false);
                    ui->two_stack->setCurrentWidget(device_widget);
                    ui->two_stack->setVisible(true);
                    timer_1->start(2000);
                }
            });
        }
        else if(sensorless_flag==0 && sensor_num!=3)
        {
            control_widget->update_data();
            ui->one_stack->setVisible(false);
            ui->one_stack->setCurrentWidget(control_widget);
            ui->one_stack->setVisible(true);
            in_control_flag=1;
        }
    });
    connect(zhukuang_widget,&zhukuang::clicked_photo,this,[=]{
        photo_name.clear();
        photo_widget->photo_update();
        photo_widget->update_page_button();
        ui->one_stack->setVisible(false);
        ui->one_stack->setCurrentWidget(photo_widget);
        ui->one_stack->setVisible(true);
    });
    connect(zhukuang_widget,&zhukuang::clicked_video,this,[=]{
        video_widget->video_update();
        ui->one_stack->setVisible(false);
        ui->one_stack->setCurrentWidget(video_widget);
        ui->one_stack->setVisible(true);
    });
    connect(zhukuang_widget,&zhukuang::clicked_system,this,[=]{
        ui->one_stack->setVisible(false);
        ui->one_stack->setCurrentWidget(system_widget);
        ui->one_stack->setVisible(true);
    });

    connect(zhukuang_widget,&zhukuang::nosd_card,this,[=]{
        ui->two_stack->setVisible(false);
        ui->two_stack->setCurrentWidget(nosdcard_wiget);
        ui->two_stack->setVisible(true);
        timer_1->start(2000);
    });
    connect(zhukuang_widget,&zhukuang::clicked_enter_preview,this,[=]{
        memset(socket_data2,0,sizeof(socket_data2));
        socket_data2[0] = 0x1C;
        socket_data2[1] = 0x01;
        socketclient->write(socket_data2,sizeof(socket_data2));
    });


    //system
    connect(system_widget,&system_setting::clicked_formatting,this,[=]{
        ui->two_stack->setVisible(false);
        ui->two_stack->setCurrentWidget(formatting_widget);
        ui->two_stack->setVisible(true);
    });
    connect(system_widget,&system_setting::clicked_reset,this,[=]{
        ui->two_stack->setVisible(false);
        ui->two_stack->setCurrentWidget(reset_widget);
        ui->two_stack->setVisible(true);
    });
    connect(system_widget,&system_setting::clicked_versions,this,[=]{
        ui->two_stack->setVisible(false);
        ui->two_stack->setCurrentWidget(version_number_widget);
        ui->two_stack->setVisible(true);
    });
    connect(system_widget,&system_setting::clicked_time,this,[=]{
        ui->two_stack->setVisible(false);
        ui->two_stack->setCurrentWidget(time_widget);
        ui->two_stack->setVisible(true);
        time_widget->update_data();
    });
    connect(system_widget,&system_setting::clicked_language,this,[=]{
        ui->two_stack->setVisible(false);
        ui->two_stack->setCurrentWidget(language_widget);
        ui->two_stack->setVisible(true);
        language_widget->update_data();
        language_widget->goto_one();
    });
    connect(system_widget,&system_setting::clicked_return,this,[=]{
        ui->one_stack->setVisible(false);
        ui->one_stack->setCurrentWidget(zhukuang_widget);
        ui->one_stack->setVisible(true);
    });

    connect(formatting_widget,&formatting::clicked_return,this,[=]{
        ui->two_stack->setVisible(false);
    });
    connect(reset_widget,&reset_setting::clicked_return,this,[=]{
        ui->two_stack->setVisible(false);
    });
    connect(reset_widget,&reset_setting::reset_yes,this,[=]{
        //重置设置
        language_flag=2;//语言
        QTranslator mTranslator;
        mTranslator.load(":/Chinese.qm");
        qApp->installTranslator(&mTranslator);
        control_widget->settext();
        formatting_widget->settext();
        reset_widget->settext();
        version_number_widget->settext();
        time_widget->settext();
        language_widget->settext();
        device_widget->settext();
        memory_widget->settext();
        sensor_restart_widget->settext();
        missing_widget->settext();

        control_widget->reset_the_settings();//操作界面
    });

    connect(version_number_widget,&version_number::clicked_return,this,[=]{
        ui->two_stack->setVisible(false);
    });
    connect(time_widget,&time_setting::clicked_return,this,[=]{
        ui->two_stack->setVisible(false);
    });
    connect(language_widget,&language_setting::clicked_return,this,[=]{
        ui->two_stack->setVisible(false);
    });

    //调用各个界面的翻译
    connect(language_widget,&language_setting::save_language,this,[=]{
        this->set_language_mode();
        settings->setValue("language_flag",language_flag);
    });

    //control_widget
    connect(control_widget,&control_interface::clicked_interface,this,[=]{
        ui->one_stack->setVisible(false);
        ui->one_stack->setCurrentWidget(zhukuang_widget);
        ui->one_stack->setVisible(true);
        in_control_flag=0;
    });
    connect(control_widget,&control_interface::nosd_card,this,[=]{
        ui->two_stack->setVisible(false);
        ui->two_stack->setCurrentWidget(nosdcard_wiget);
        ui->two_stack->setVisible(true);
        timer_1->start(2000);
    });

    //相片
    connect(photo_widget,&photo_browse::clicked_return,this,[=]{
        ui->one_stack->setVisible(false);
        ui->one_stack->setCurrentWidget(zhukuang_widget);
        ui->one_stack->setVisible(true);
        photo_widget->set_deselect();
        current_interface_flag=0;
    });
    //相片->photo_single_widget
    connect(photo_widget,&photo_browse::goto_photo_browse,this,[=]{
        ui->one_stack->setVisible(false);
        ui->one_stack->setCurrentWidget(photo_single_widget);
        ui->one_stack->setVisible(true);
        photo_single_widget->photo_update();
        current_interface_flag=2;

    });

    //photo_single_widget->相片
    connect(photo_single_widget,&photo_browse_single::return_photo,this,[=]{
        ui->one_stack->setVisible(false);
        ui->one_stack->setCurrentWidget(photo_widget);
        ui->one_stack->setVisible(true);
        photo_widget->photo_update();
        current_interface_flag=1;
    });
    connect(photo_single_widget,&photo_browse_single::update_photo_name,this,[=]{
        photo_widget->init_photo_name();
    });

    //视频
    connect(video_widget,&video_browse::clicked_return,this,[=]{
        ui->one_stack->setVisible(false);
        ui->one_stack->setCurrentWidget(zhukuang_widget);
        ui->one_stack->setVisible(true);
        video_widget->set_deselect();
        current_interface_flag=0;
    });
    connect(video_widget,&video_browse::return_preview,this,[=]{
        memset(socket_data2,0,sizeof(socket_data2));
        socket_data2[0] = 0x1C;
        socket_data2[1] = 0x02;
        socketclient->write(socket_data2,sizeof(socket_data2));
    });

    //视频->video_play_widget
    connect(video_widget,&video_browse::goto_void_browse,this,[=]{
        ui->one_stack->setVisible(false);
        ui->one_stack->setCurrentWidget(video_play_widget);
        ui->one_stack->setVisible(true);
        video_play_widget->video_update();
        current_interface_flag=4;
    });

    //video_play_widget->视频
    connect(video_play_widget,&video_drowse_play::return_video,this,[=]{
        ui->one_stack->setVisible(false);
        ui->one_stack->setCurrentWidget(video_widget);
        ui->one_stack->setVisible(true);
        video_widget->video_update();
        current_interface_flag=3;
    });

    //control_widget--socket_链接
    //zoom
    connect(control_widget,&control_interface::socket_set_zoom,this,[=]{
        memset(socket_data2,0,sizeof(socket_data2));
        socket_data2[0] = 0x17;
        switch (zoom_num) {
        case 1:
            socket_data2[1] = 0x01;
            break;
        case 2:
            socket_data2[1] = 0x02;
            break;
        case 3:
            socket_data2[1] = 0x03;
            break;
        case 4:
            socket_data2[1] = 0x04;
            break;
        }
        socketclient->write(socket_data2,sizeof(socket_data2));
    });
    //atom
    connect(control_widget,&control_interface::clicked_awb_auto,this,[=]{
        memset(socket_data1,0,sizeof(socket_data1));
        socket_data1[0] = 0x04;
        socketclient->write(socket_data1,sizeof(socket_data1));
    });
    connect(control_widget,&control_interface::clicked_awb_manual,this,[=]{
        memset(socket_data1,0,sizeof(socket_data1));
        socket_data1[0] = 0x05;
        socketclient->write(socket_data1,sizeof(socket_data1));
    });

    //awb
    connect(control_widget,&control_interface::socket_awb,this,[=]{
        memset(socket_data1,0,sizeof(socket_data1));
        socket_data1[0] = 0x06;
        socketclient->write(socket_data1,sizeof(socket_data1));
    });
    //冻结
    connect(control_widget,&control_interface::socket_freeze1,this,[=]{
        memset(socket_data1,0,sizeof(socket_data1));
        socket_data1[0] = 0x02;
        socketclient->write(socket_data1,sizeof(socket_data1));

        memset(result,0,sizeof(result));
        if(flag_USB==1)
        {
            sprintf(result, "/mnt/USB_FLASH/Picture/%d%d%d%d%d%d.jpg",time_num.num_year.toInt(),time_num.num_month.toUInt(),time_num.num_day.toUInt(),time_num.num_hour.toInt(),time_num.num_minute.toUInt(),time_num.num_second.toUInt());
        }
        else if(flag_USB==0 && flag_SD==1)
        {
            sprintf(result, "/mnt/SD_CARD/Picture/%d%d%d%d%d%d.jpg",time_num.num_year.toInt(),time_num.num_month.toUInt(),time_num.num_day.toUInt(),time_num.num_hour.toInt(),time_num.num_minute.toUInt(),time_num.num_second.toUInt());
        }
        socketclient->write(result,strlen(result) + 1);
        qDebug()<<"===socket_freeze1==="<<result;
    });
    connect(control_widget,&control_interface::socket_freeze0,this,[=]{
        memset(socket_data1,0,sizeof(socket_data1));
        socket_data1[0] = 0x03;
        socketclient->write(socket_data1,sizeof(socket_data1));
    });
    //旋转
    connect(control_widget,&control_interface::socket_rotate1,this,[=]{
        memset(socket_data2,0,sizeof(socket_data2));
        socket_data2[0] = 0x0A;
        socket_data2[1] = 0x01;
        socketclient->write(socket_data2,sizeof(socket_data2));
    });
    connect(control_widget,&control_interface::socket_rotate2,this,[=]{
        memset(socket_data2,0,sizeof(socket_data2));
        socket_data2[0] = 0x0A;
        socket_data2[1] = 0x02;
        socketclient->write(socket_data2,sizeof(socket_data2));
    });
    connect(control_widget,&control_interface::socket_rotate3,this,[=]{
        socket_data2[0] = 0x0A;
        socket_data2[1] = 0x03;
        socketclient->write(socket_data2,sizeof(socket_data2));
    });
    connect(control_widget,&control_interface::socket_rotate4,this,[=]{
        memset(socket_data2,0,sizeof(socket_data2));
        socket_data2[0] = 0x0A;
        socket_data2[1] = 0x04;
        socketclient->write(socket_data2,sizeof(socket_data2));
    });
    connect(control_widget,&control_interface::socket_rotate5,this,[=]{
        memset(socket_data2,0,sizeof(socket_data2));
        socket_data2[0] = 0x0A;
        socket_data2[1] = 0x05;
        socketclient->write(socket_data2,sizeof(socket_data2));
    });

    connect(control_widget,&control_interface::socket_switch,this,[=]{
        memset(socket_data2,0,sizeof(socket_data2));
        socket_data2[0] = 0x62;
        if(label_switch_flag==1)
        {
            socket_data2[1] = 0x00;
        }
        else if(label_switch_flag==0)
        {
            socket_data2[1] = 0x01;
        }
        socketclient->write(socket_data2,sizeof(socket_data2));
    });

    connect(control_widget,&control_interface::socket_rotate_freeze1,this,[=]{
        memset(socket_data2,0,sizeof(socket_data2));
        socket_data2[0] = 0x0B;
        socket_data2[1] = 0x01;
        socketclient->write(socket_data2,sizeof(socket_data2));
    });
    connect(control_widget,&control_interface::socket_rotate_freeze2,this,[=]{
        memset(socket_data2,0,sizeof(socket_data2));
        socket_data2[0] = 0x0B;
        socket_data2[1] = 0x02;
        socketclient->write(socket_data2,sizeof(socket_data2));
    });
    connect(control_widget,&control_interface::socket_rotate_freeze3,this,[=]{
        memset(socket_data2,0,sizeof(socket_data2));
        socket_data2[0] = 0x0B;
        socket_data2[1] = 0x03;
        socketclient->write(socket_data2,sizeof(socket_data2));
    });
    connect(control_widget,&control_interface::socket_rotate_freeze4,this,[=]{
        memset(socket_data2,0,sizeof(socket_data2));
        socket_data2[0] = 0x0B;
        socket_data2[1] = 0x04;
        socketclient->write(socket_data2,sizeof(socket_data2));
    });
    connect(control_widget,&control_interface::socket_rotate_freeze5,this,[=]{
        memset(socket_data2,0,sizeof(socket_data2));
        socket_data2[0] = 0x0B;
        socket_data2[1] = 0x05;
        socketclient->write(socket_data2,sizeof(socket_data2));
    });
    //拍照
    connect(control_widget,&control_interface::socket_photograph,this,[=]{
        memset(socket_data1,0,sizeof(socket_data1));
        socket_data1[0] = 0x10;
        socketclient->write(socket_data1,sizeof(socket_data1));
    });
    connect(control_widget,&control_interface::socket_photograph_name,this,[=]{
        memset(result,0,sizeof(result));

        QString path;

        if(flag_USB==1)
        {
            //sprintf(result, "/mnt/USB_FLASH/Picture/%d%d%d%d%d%d.jpg",time_num.num_year.toInt(),time_num.num_month.toUInt(),time_num.num_day.toUInt(),time_num.num_hour.toInt(),time_num.num_minute.toUInt(),time_num.num_second.toUInt());
             path = "/mnt/USB_FLASH/Picture/";
        }
        else if(flag_USB==0 && flag_SD==1)
        {
            //sprintf(result, "/mnt/SD_CARD/Picture/%d%d%d%d%d%d.jpg",time_num.num_year.toInt(),time_num.num_month.toUInt(),time_num.num_day.toUInt(),time_num.num_hour.toInt(),time_num.num_minute.toUInt(),time_num.num_second.toUInt());
             path = "/mnt/SD_CARD/Picture/";
        }
        int index = get_next_photo_index(path);

        QString fileName = QString("IMG_%1.jpg").arg(index, 6, 10, QChar('0'));  // 補零

        QString fullPath = path + fileName;

        strcpy(result, fullPath.toStdString().c_str());
        socketclient->write(result, strlen(result) + 1);

        photo_widget->photo_update();

        if(photo_max%6==0)
            photo_num = photo_totality+1;
        else
            photo_num = photo_totality;



        qDebug()<<"===result==="<<result;

    });

    //录像
    connect(control_widget,&control_interface::socket_videoon,this,[=]{

//        year_w = time_num.num_year.toInt();
//        onth_w = time_num.num_month.toUInt();
//        day_w = time_num.num_day.toUInt();
//        hour_w = time_num.num_hour.toInt();
//        minute_w = time_num.num_minute.toUInt();
//        second_w = time_num.num_second.toUInt();


        memset(socket_data1,0,sizeof(socket_data1));
        socket_data1[0] = 0x18;
        socketclient->write(socket_data1,sizeof(socket_data1));

        QString basePath;

        memset(result,0,sizeof(result));
        if(flag_USB==1)
        {
            //sprintf(result, "/mnt/USB_FLASH/Videohead/%d%d%d%d%d%d.jpg",year_w,onth_w,day_w,hour_w,minute_w,second_w);
            basePath = "/mnt/USB_FLASH/Videohead";
        }
        else if(flag_USB==0 && flag_SD==1)
        {
            //sprintf(result, "/mnt/SD_CARD/Videohead/%d%d%d%d%d%d.jpg",year_w,onth_w,day_w,hour_w,minute_w,second_w);
            basePath = "/mnt/SD_CARD/Videohead";
        }

        int index = get_next_video_index(basePath);
        QString filePath = QString("%1/VID_%2.jpg")
                                .arg(basePath)
                                .arg(index, 6, 10, QChar('0'));
        QByteArray pathBytes = filePath.toUtf8();
        strncpy(result, pathBytes.constData(), sizeof(result) - 1);
        socketclient->write(result,strlen(result) + 1);

        video_widget->video_update();

        if(video_max%6==0)
            video_num = video_totality+1;
        else
            video_num = video_totality;
        qDebug()<<"===socket_videoon==="<<result;
    });
    connect(control_widget,&control_interface::socket_videooff,this,[=]{
        memset(socket_data1,0,sizeof(socket_data1));
        socket_data1[0] = 0x12;
        socketclient->write(socket_data1,sizeof(socket_data1));
    });
    //AE
    connect(control_widget,&control_interface::socket_ae1,this,[=]{
        memset(socket_data2,0,sizeof(socket_data2));
        socket_data2[0] = 0x07;
        socket_data2[1] = 0x01;
        socketclient->write(socket_data2,sizeof(socket_data2));
    });
    connect(control_widget,&control_interface::socket_ae2,this,[=]{
        memset(socket_data2,0,sizeof(socket_data2));
        socket_data2[0] = 0x07;
        socket_data2[1] = 0x02;
        socketclient->write(socket_data2,sizeof(socket_data2));
    });
    connect(control_widget,&control_interface::socket_ae3,this,[=]{
        memset(socket_data2,0,sizeof(socket_data2));
        socket_data2[0] = 0x07;
        socket_data2[1] = 0x03;
        socketclient->write(socket_data2,sizeof(socket_data2));
    });
    connect(control_widget,&control_interface::socket_ae4,this,[=]{
        memset(socket_data2,0,sizeof(socket_data2));
        socket_data2[0] = 0x07;
        socket_data2[1] = 0x04;
        socketclient->write(socket_data2,sizeof(socket_data2));
    });
    connect(control_widget,&control_interface::socket_ae5,this,[=]{
        memset(socket_data2,0,sizeof(socket_data2));
        socket_data2[0] = 0x07;
        socket_data2[1] = 0x05;
        socketclient->write(socket_data2,sizeof(socket_data2));
    });


    connect(control_widget,&control_interface::socket_store,this,[=]{
        memset(socket_data1,0,sizeof(socket_data1));
        socket_data1[0] = 0x08;
        socketclient->write(socket_data1,sizeof(socket_data1));
    });
    connect(control_widget,&control_interface::socket_cancel_freeze1,this,[=]{
        memset(socket_data1,0,sizeof(socket_data1));
        socket_data1[0] = 0x09;
        socketclient->write(socket_data1,sizeof(socket_data1));
    });


    //小画面和大画面切换
    connect(control_widget,&control_interface::socket_frames,this,[=]{
        memset(socket_data1,0,sizeof(socket_data1));
        socket_data1[0] = 0x01;
        socketclient->write(socket_data1,sizeof(socket_data1));
    });
    //单画面模式
    connect(control_widget,&control_interface::socket_single_screen,this,[=]{
        memset(socket_data1,0,sizeof(socket_data1));
        socket_data1[0] = 0x0C;
        socketclient->write(socket_data1,sizeof(socket_data1));
    });
    //双画面模式
    connect(control_widget,&control_interface::socket_dual_screen,this,[=]{
        memset(socket_data1,0,sizeof(socket_data1));
        socket_data1[0] = 0x0D;
        socketclient->write(socket_data1,sizeof(socket_data1));
    });
    //子母画面模式
    connect(control_widget,&control_interface::socket_size_screen,this,[=]{
        memset(socket_data2,0,sizeof(socket_data2));
        socket_data2[0] = 0x0E;
        socket_data2[1] = 0x00;
        socketclient->write(socket_data2,sizeof(socket_data2));
    });
    //双画面点左切换子母画面
    connect(control_widget,&control_interface::socket_screen_left,this,[=]{
        memset(socket_data2,0,sizeof(socket_data2));
        socket_data2[0] = 0x0E;
        socket_data2[1] = 0x01;
        socketclient->write(socket_data2,sizeof(socket_data2));
    });
    //双画面点右切换子母画面
    connect(control_widget,&control_interface::socket_screen_right,this,[=]{
        memset(socket_data2,0,sizeof(socket_data2));
        socket_data2[0] = 0x0E;
        socket_data2[1] = 0x02;
        socketclient->write(socket_data2,sizeof(socket_data2));
    });

    connect(control_widget,&control_interface::stock_full,this,[=]{
        //容量不够
        ui->two_stack->setVisible(false);
        ui->two_stack->setCurrentWidget(memory_widget);
        ui->two_stack->setVisible(true);
        timer_1->start(2000);
    });


    //回放
    connect(video_play_widget,&video_drowse_play::socket_play_video,this,[=]{
        memset(socket_data2,0,sizeof(socket_data2));
        socket_data2[0] = 0x13;
        socket_data2[1] = 0x02;
        socketclient->write(socket_data2,sizeof(socket_data2));

        memset(result,0,sizeof(result));
        if(flag_USB==1)
        {
            sprintf(result, "/mnt/USB_FLASH/Video/%s.mp4",playback_video_name);
        }
        else if(flag_USB==0 && flag_SD==1)
        {
            sprintf(result, "/mnt/SD_CARD/Video/%s.mp4",playback_video_name);
        }
        socketclient->write(result,strlen(result) + 1);


        qDebug()<<"===result==="<<result;
    });
    connect(video_play_widget,&video_drowse_play::socket_play_video_one,this,[=]{
        memset(socket_data2,0,sizeof(socket_data2));
        socket_data2[0] = 0x13;
        socket_data2[1] = 0x01;
        socketclient->write(socket_data2,sizeof(socket_data2));

        memset(result,0,sizeof(result));
        if(flag_USB==1)
        {
            sprintf(result, "/mnt/USB_FLASH/Video/%s.mp4",playback_video_name);
        }
        else if(flag_USB==0 && flag_SD==1)
        {
            sprintf(result, "/mnt/SD_CARD/Video/%s.mp4",playback_video_name);
        }
        socketclient->write(result,strlen(result) + 1);
        qDebug()<<"===result==="<<result;
    });

    connect(video_play_widget,&video_drowse_play::socket_close_play,this,[=]{
        memset(socket_data2,0,sizeof(socket_data2));
        socket_data2[0] = 0x14;
        socket_data2[1] = 0x02;
        socketclient->write(socket_data2,sizeof(socket_data2));
    });
    connect(video_play_widget,&video_drowse_play::socket_close_play_return,this,[=]{
        memset(socket_data2,0,sizeof(socket_data2));
        socket_data2[0] = 0x14;
        socket_data2[1] = 0x01;
        socketclient->write(socket_data2,sizeof(socket_data2));
    });

    connect(video_play_widget,&video_drowse_play::socket_pause,this,[=]{
        memset(socket_data1,0,sizeof(socket_data1));
        socket_data1[0] = 0x15;
        socketclient->write(socket_data1,sizeof(socket_data1));
    });
    connect(video_play_widget,&video_drowse_play::socket_play_on,this,[=]{
        memset(socket_data1,0,sizeof(socket_data1));
        socket_data1[0] = 0x16;
        socketclient->write(socket_data1,sizeof(socket_data1));
    });
    connect(video_play_widget,&video_drowse_play::socket_fast_forward,this,[=]{
        memset(socket_data1,0,sizeof(socket_data1));
        socket_data1[0] = 0x1A;
        socketclient->write(socket_data1,sizeof(socket_data1));
    });
    connect(video_play_widget,&video_drowse_play::socket_fast_backward,this,[=]{
        memset(socket_data1,0,sizeof(socket_data1));
        socket_data1[0] = 0x1B;
        socketclient->write(socket_data1,sizeof(socket_data1));
    });

    socketclient->setProxy(QNetworkProxy::NoProxy);
    connect(socketclient, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(socketclient, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(socketclient, SIGNAL(disconnected()), this, SLOT(onDisConnected()));
    connect(socketclient, SIGNAL(errorOccurred()), this, SLOT(onError()));
    socketclient->connectToHost(QHostAddress::LocalHost,2223);
    socketclient->waitForConnected();

    Display_complete();

    verify_sdcard();
    verify_usbflash();

    key->moveToThread(mythread);
    QObject::connect(mythread,SIGNAL(started()),key,SLOT(mythread_work()));
    QObject::connect(mythread,SIGNAL(finished()),mythread,SLOT(deleteLater()));
    mythread->start();

    key_mipi0->moveToThread(mythread_mipi0);
    QObject::connect(mythread_mipi0,SIGNAL(started()),key_mipi0,SLOT(mythread_work()));
    QObject::connect(mythread_mipi0,SIGNAL(finished()),mythread_mipi0,SLOT(deleteLater()));
    mythread_mipi0->start();

    key_mipi3->moveToThread(mythread_mipi3);
    QObject::connect(mythread_mipi3,SIGNAL(started()),key_mipi3,SLOT(mythread_work()));
    QObject::connect(mythread_mipi3,SIGNAL(finished()),mythread_mipi3,SLOT(deleteLater()));
    mythread_mipi3->start();

    usb_mcu_key->moveToThread(mcu_thread);
    QObject::connect(mcu_thread,SIGNAL(started()),usb_mcu_key,SLOT(mythread_work()));
    QObject::connect(mcu_thread,SIGNAL(finished()),mcu_thread,SLOT(deleteLater()));
    mcu_thread->start();

    rev_usb_mcu_key->moveToThread(rev_mcu_thread);
    QObject::connect(rev_mcu_thread,SIGNAL(started()),rev_usb_mcu_key,SLOT(mythread_work()));
    QObject::connect(rev_mcu_thread,SIGNAL(finished()),rev_mcu_thread,SLOT(deleteLater()));
    rev_mcu_thread->start();

    key_290->moveToThread(thread_290);
    QObject::connect(thread_290,SIGNAL(started()),key_290,SLOT(mythread_work()));
    QObject::connect(thread_290,SIGNAL(finished()),thread_290,SLOT(deleteLater()));
    thread_290->start();

    key_9anjian->moveToThread(thread_9anjian);
    QObject::connect(thread_9anjian,SIGNAL(started()),key_9anjian,SLOT(mythread_work()));
    QObject::connect(thread_9anjian,SIGNAL(finished()),thread_9anjian,SLOT(deleteLater()));
    thread_9anjian->start();

    QSettings settingsone("/customer/setargument.ini", QSettings::IniFormat);
    oneflag = settingsone.value("/RPINFO/flag").toInt();
    settingsone.sync();
    if(oneflag==0)
    {
        oneflag=1;
        settings->setValue("flag",oneflag);
        settings->setValue("language_flag",language_flag);
    }
    else if(oneflag==1)
    {
        language_flag=settings->value("language_flag").toInt();
    }

    QDate date = QDate::currentDate();
    QString year = QString::number(date.year());
    if(year.toInt()==1970)
    {
        system("date 090415002025.00");
        system("hwclock -w");
        system("sync");
    }

    system("echo 0 >/sys/class/pwm/pwmchip0/export");
    system("echo 100000 >/sys/devices/soc0/soc/1f203200.pwm/pwm/pwmchip0/pwm0/period");
    system("echo 0 >/sys/devices/soc0/soc/1f203200.pwm/pwm/pwmchip0/pwm0/enable");

    system("echo 5 >/sys/class/pwm/pwmchip0/export");
    system("echo 333333 >/sys/devices/soc0/soc/1f203200.pwm/pwm/pwmchip0/pwm5/period");
    system("echo 0 >/sys/devices/soc0/soc/1f203200.pwm/pwm/pwmchip0/pwm5/enable");

    system("echo 7 >/sys/class/pwm/pwmchip0/export");
    system("echo 333333 >/sys/devices/soc0/soc/1f203200.pwm/pwm/pwmchip0/pwm7/period");
    system("echo 0 >/sys/devices/soc0/soc/1f203200.pwm/pwm/pwmchip0/pwm7/enable");

    system("echo 6 >/sys/class/pwm/pwmchip0/export");
    system("echo 100000 >/sys/devices/soc0/soc/1f203200.pwm/pwm/pwmchip0/pwm6/period");
    system("echo 0 >/sys/devices/soc0/soc/1f203200.pwm/pwm/pwmchip0/pwm6/enable");

    system("sync");

    set_language_mode();

    QFile es_file("/mnt/SD_CARD/bootlogo/sp_1280x800.es");
    if(es_file.exists())
    {
        QFile sourceFile("/mnt/SD_CARD/bootlogo/sp_1280x800.es");
        QFile targetFile("/misc/sp_1280x800.es");

        if (sourceFile.open(QIODevice::ReadOnly) && targetFile.open(QIODevice::WriteOnly))
        {
            QTextStream in(&sourceFile);
            QTextStream out(&targetFile);
            out << in.readAll();
            system("sync");
            sourceFile.close();
            targetFile.close();
        }
        else
        {
            qDebug()<<"open file fail!!!!!!!!!!!!!!!!!!!!!";
        }
    }
}

Widget::~Widget()
{
    delete ui;
}
int Widget::get_next_photo_index(QString path)
{
    QDir dir(path);

    QStringList filters;
    filters << "IMG_*.jpg";
    dir.setNameFilters(filters);

    QFileInfoList list = dir.entryInfoList(QDir::Files, QDir::Name);

    int maxIndex = 0;

    for (const QFileInfo &fileInfo : list)
    {
        QString name = fileInfo.baseName(); // IMG_000123

        QString numStr = name.mid(4); // 取出 000123

        int num = numStr.toInt();

        if (num > maxIndex)
            maxIndex = num;
    }

    return maxIndex + 1;
}
int Widget::get_next_video_index(QString path)
{
    QDir dir(path);

    QStringList filters;

    if(path =="/mnt/SD_CARD/Videohead")
        filters << "VID_*.jpg";
    else if(path =="/mnt/SD_CARD/Video")
        filters << "VID_*.mp4";

    dir.setNameFilters(filters);

    QFileInfoList list = dir.entryInfoList(QDir::Files, QDir::Name);

    int maxIndex = 0;

    for (const QFileInfo &fileInfo : list)
    {
        QString name = fileInfo.baseName(); // VID_000123

        QString numStr = name.mid(4); // 取出 000123

        int num = numStr.toInt();

        if (num > maxIndex)
            maxIndex = num;
    }

    return maxIndex + 1;
}

void Widget::set_language_mode()
{
    QTranslator mTranslator;
    switch (language_flag) {
    case 1:
    {
        mTranslator.load(":/Chinese.qm");
        break;
    }
    case 2:
    {
        mTranslator.load(":/Chinese_t.qm");
        break;
    }
    case 3:
    {
        mTranslator.load(":/English.qm");
        break;
    }
    case 4:
    {
        mTranslator.load(":/Espanol.qm");
        break;
    }
    }
    qApp->installTranslator(&mTranslator);
    control_widget->settext();
    formatting_widget->settext();
    reset_widget->settext();
    version_number_widget->settext();
    time_widget->settext();
    language_widget->settext();
    device_widget->settext();
    memory_widget->settext();
    sensor_restart_widget->settext();
    missing_widget->settext();
}

//MMIPI0
void Widget::set_first_mipi0_key()
{
    if(in_control_flag==1)
    {
        if(!click_key_flag)
        {
            control_widget->fourth_key_set();
        }
    }
}

void Widget::set_first_long_mipi0_key()
{
    if(in_control_flag==1)
    {
        if(!click_key_flag)
        {
            control_widget->fourth_key_long_set();
        }
    }
}

//MIPI1
void Widget::set_first_key()
{
    if(in_control_flag==1)
    {
        if(!click_key_flag)
        {
            control_widget->first_key_set();
        }
    }
}

void Widget::set_second_key()
{
    if(in_control_flag==1)
    {
        if(!click_key_flag)
        {
            control_widget->second_key_set();
        }
    }
}

void Widget::set_third_key()
{
    if(in_control_flag==1)
    {
        if(!click_key_flag)
        {
            control_widget->third_key_set();
        }
    }
}

void Widget::set_fourth_key()
{
    if(in_control_flag==1)
    {
        if(!click_key_flag)
        {
            control_widget->fourth_key_set();
        }
    }
}

void Widget::set_fourth_key_long()
{
    if(in_control_flag==1)
    {
        if(!click_key_flag)
        {
            control_widget->fourth_key_long_set();
        }
    }
}

void Widget::sd_in_re(int num)
{
    if(num==SIGUSR1)
    {
        flag_SD=1;
        mywidget->Clear_record_sdfile();
        mywidget->Confirm_folder();
    }
    else
    {
        flag_SD=0;
        if(flag_USB==0)
        {
            switch (current_interface_flag) {
            case 1:
            {
                mywidget->photo_widget->clicked_set_return();
                break;
            }
            case 2:
            {
                mywidget->photo_single_widget->sd_convert_usb();
                mywidget->photo_widget->clicked_set_return();
                break;
            }
            case 3:
            {
                mywidget->video_widget->clicked_set_return();
                break;
            }
            case 4:
            {
                mywidget->video_play_widget->sd_convert_usb();
                mywidget->video_widget->clicked_set_return();
                break;
            }
            }
        }
    }
    printf("==sd_in_re==%d\n",flag_SD);
}

void Widget::usb_in_re(int num)
{
    if(num==SIGRTMAX)
    {
        if(flag_USB==0)
        {
            flag_USB=1;
            mywidget->Clear_record_usbflash();
            mywidget->Confirm_folder_usbflash();
            if(flag_SD==1)
            {
                switch (current_interface_flag) {
                case 1:
                {
                    mywidget->photo_widget->sd_convert_usb();
                    break;
                }
                case 2:
                {
                    mywidget->photo_single_widget->sd_convert_usb();
                    mywidget->photo_widget->sd_convert_usb();
                    break;
                }
                case 3:
                {
                    mywidget->video_widget->sd_convert_usb();
                    break;
                }
                case 4:
                {
                    mywidget->video_play_widget->sd_convert_usb();
                    mywidget->video_widget->sd_convert_usb();
                    break;
                }
                }
            }
        }
        else if(flag_USB==1)
        {
            flag_USB=0;
            if(flag_SD==1)
            {
                switch (current_interface_flag) {
                case 1:
                {
                    mywidget->photo_widget->sd_convert_usb();
                    break;
                }
                case 2:
                {
                    mywidget->photo_single_widget->sd_convert_usb();
                    mywidget->photo_widget->sd_convert_usb();
                    break;
                }
                case 3:
                {
                    mywidget->video_widget->sd_convert_usb();
                    break;
                }
                case 4:
                {
                    mywidget->video_play_widget->sd_convert_usb();
                    mywidget->video_widget->sd_convert_usb();
                    break;
                }
                }
            }
            else if(flag_SD==0)
            {
                switch (current_interface_flag) {
                case 1:
                {
                    mywidget->photo_widget->clicked_set_return();
                    break;
                }
                case 2:
                {
                    mywidget->photo_single_widget->sd_convert_usb();
                    mywidget->photo_widget->clicked_set_return();
                    break;
                }
                case 3:
                {
                    mywidget->video_widget->clicked_set_return();
                    break;
                }
                case 4:
                {
                    mywidget->video_play_widget->sd_convert_usb();
                    mywidget->video_widget->clicked_set_return();
                    break;
                }
                }
            }
        }
    }
    printf("==usb_in_re==%d\n",flag_USB);
}


void Widget::Display_complete()
{
    memset(socket_data1,0,sizeof(socket_data1));
    socket_data1[0] = 0xaa;
    socketclient->write(socket_data1,sizeof(socket_data1));
}

void Widget::onConnected()
{
    printf("链接成功  Connected to server  19 07\n");
}

void Widget::onReadyRead()
{
    printf("=======onReadyRead=======\n");
    memset(cStringData,0,sizeof(cStringData));
    data_socket = socketclient->readAll();
    cStringData[0] = data_socket[0];
    cStringData[1] = data_socket[1];
    cStringData[2] = data_socket[2];
    cStringData[3] = data_socket[3];
    cStringData[4] = data_socket[4];
    printf("读到东西   %#x %#x %#x %#x %#x  \n", cStringData[0],cStringData[1],cStringData[2],cStringData[3],cStringData[4]);

    if(cStringData[0]==ONE_CLICK_AWB)
    {
        control_widget->read_socket_awb();
    }
    else if(cStringData[0]==FREEZE_MOTHER)
    {
        control_widget->read_socket_freeze();
    }
    else if(cStringData[0]==TAKE_PICTURE)
    {
        control_widget->read_socket_photograph();
        switchable_flag=0;
    }
    else if(cStringData[0]==SINGLE_SCREEN)
    {
        display_flag=1;
        control_widget->read_socket_display();
    }
    else if(cStringData[0]==DUAL_SCREEN)
    {
        display_flag=2;
        control_widget->read_socket_display();
    }
    else if(cStringData[0]==PIP_SCREEN)
    {
        display_flag=3;
        control_widget->read_socket_display();
    }
    else if(cStringData[0]==ROTATE_MOTHER)
    {
        //旋转
        rotate_flag=cStringData[1];
        control_widget->read_rotate();
    }
    else if(cStringData[0]==SET_AE)
    {
        ae_flag=cStringData[1];
        control_widget->read_gpio_ae();
    }
    else if(cStringData[0]==TAKE_VIDOE)
    {
        memset(socket_data1,0,sizeof(socket_data1));
        socket_data1[0] = 0x11;
        socketclient->write(socket_data1,sizeof(socket_data1));

        memset(result,0,sizeof(result));

        QString basePath;

        if(flag_USB==1)
        {
            //sprintf(result, "/mnt//USB_FLASH/Video/%d%d%d%d%d%d.mp4",year_w,onth_w,day_w,hour_w,minute_w,second_w);
            basePath = "/mnt/USB_FLASH/Video";
        }
        else if(flag_USB==0 && flag_SD==1)
        {
            //sprintf(result, "/mnt//SD_CARD/Video/%d%d%d%d%d%d.mp4",year_w,onth_w,day_w,hour_w,minute_w,second_w);
            basePath = "/mnt/SD_CARD/Video";
        }

        int index = get_next_video_index(basePath); // 這個值要在 socket_videoon 時存起來
        QString videoPath = QString("%1/VID_%2.mp4")
                                    .arg(basePath)
                                    .arg(index, 6, 10, QChar('0'));

        QByteArray pathBytes = videoPath.toUtf8();
        socketclient->write(pathBytes.constData(), pathBytes.size() + 1);
        //socketclient->write(result,strlen(result) + 1);
    }
    else if(cStringData[0]==RECORD_TIME)
    {
        printf("=======识别到时间命令=======\n");
        hours_progress=cStringData[1];
        minutes_progress=cStringData[2];
        seconds_progress=cStringData[3];
        progress_time=hours_progress*3600+minutes_progress*60+seconds_progress;
        printf("时==%d 分==%d 秒s==%d\n",hours_progress,minutes_progress,seconds_progress);

        video_play_widget->reset_progress_bar();
        usleep(1000*500);
        switchable_flag=0;
    }
    else if(cStringData[0]==ALL_CAMERA_NUM)
    {
        if(label_switch_flag==1)
            control_widget->switch_off();
        sensor_num=cStringData[1];
        if(sensor_num==3)
        {
            ui->two_stack->setVisible(false);
            ui->two_stack->setCurrentWidget(sensor_restart_widget);
            ui->two_stack->setVisible(true);
        }
        else if(sensor_num==1 || sensor_num==2)
        {
            sensorless_flag=0;
        }
        else if(sensor_num==0)
        {
            if(in_control_flag==1)
            {
                ui->one_stack->setVisible(false);
                ui->one_stack->setCurrentWidget(zhukuang_widget);
                ui->one_stack->setVisible(true);
                in_control_flag=0;
            }
            sensorless_flag=1;
        }
    }
    else if(cStringData[0]==USB_MCU_)
    {
        usb_mcu_flag=cStringData[1];
    }
    else if(cStringData[0]==USB_KEY_PHOTO && in_control_flag==1)
    {
        control_widget->set_photograph();
    }
    else if(cStringData[0]==USB_KEY_VIDEO && in_control_flag==1)
    {
        control_widget->set_video();
    }
    else if(cStringData[0]==PROPORTION_KEY)
    {
        aspect_ratio_flag=cStringData[1];
    }
    data_socket.clear();
}

void Widget::onDisConnected()
{
    printf("链接失败 onDisConnected to server\n");
}

void Widget::onError()
{
    // 处理错误情况
    printf("链接失败  Socket error\n");
}

//断开连接：当通信完成或者需要断开连接时，可以调用disconnectFromHost函数断开连接并释放资源：
//socket->disconnectFromHost();
//socket->deleteLater();


void Widget::verify_sdcard()//上电第一次的sd是否挂载
{
    QFile file("/tmp/sdcard_info.log");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file.";
        flag_SD=0;
        printf("Failed to open file  =flag_SD=%d==\n",flag_SD);
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        if (line.contains("mount /dev/mmcblk0p1 on /mnt/SD_CARD"))
        {
            Confirm_folder();
            flag_SD=1;
            break;
        }
    }

    if(flag_SD != 1)
    {
        flag_SD=0;
    }

    printf("verify_sdcard ==%d==\n",flag_SD);

    file.close();

    Clear_record_sdfile();
}

void Widget::Clear_record_sdfile()
{
    QFile file("/tmp/sdcard_info.log");
    if (!file.open(QFile::WriteOnly|QFile::Truncate))
    {
        qDebug() << "Failed to open file.";
        flag_SD=0;
        return;
    }
    file.close();
}

void Widget::Confirm_folder()
{
    QString dirPath = "/mnt/SD_CARD/Picture";
    QString dirPath1 = "/mnt/SD_CARD/Videohead";
    QString dirPath2 = "/mnt/SD_CARD/Video";
    QString dirPath3 = "/mnt/SD_CARD/sd_upgrade";

    QDir dir(dirPath);
    if (dir.exists())
    {
        printf("/SD_CARD/Picture 文件夹存在\n");
    }
    else
    {
        system("mkdir /mnt/SD_CARD/Picture");
        printf("/SD_CARD/Picture 文件夹不存在\n");
    }

    QDir dir1(dirPath1);
    if (dir1.exists())
    {
        printf("/SD_CARD/Videohead 文件夹存在\n");
    }
    else
    {
        system("mkdir /mnt/SD_CARD/Videohead");
        printf("Videohead 文件夹不存在\n");
    }

    QDir dir2(dirPath2);
    if (dir2.exists())
    {
        printf("/SD_CARD/Video 文件夹存在\n");
    }
    else
    {
        system("mkdir /mnt/SD_CARD/Video");
        printf("/SD_CARD/Video 文件夹不存在\n");
    }

    QDir dir3(dirPath3);
    if (dir3.exists())
    {
        printf("/SD_CARD/sd_upgrade 文件夹存在\n");
    }
    else
    {
        system("mkdir /mnt/SD_CARD/sd_upgrade");
        printf("/SD_CARD/sd_upgrade 文件夹不存在\n");
    }
}


void Widget::verify_usbflash()//上电第一次的usb是否挂载
{
    QFile file("/tmp/usbflash_info.log");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file.";
        flag_USB=0;
        printf("Failed to open file  =flag_USB=%d==\n",flag_USB);
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        if (line.contains("mount /dev/sda1 on /mnt/USB_FLASH"))
        {
            Confirm_folder();
            flag_USB=1;
            break;
        }
    }

    if(flag_USB != 1)
    {
        flag_USB=0;
    }

    printf("verify_usbflash ==%d==\n",flag_USB);

    file.close();

    Clear_record_usbflash();
}

void Widget::Clear_record_usbflash()
{
    QFile file("/tmp/usbflash_info.log");
    if (!file.open(QFile::WriteOnly|QFile::Truncate))
    {
        qDebug() << "Failed to open file.";
        flag_USB=0;
        return;
    }
    file.close();
}

void Widget::Confirm_folder_usbflash()
{
    QString dirPath = "/mnt/USB_FLASH/Picture";
    QString dirPath1 = "/mnt/USB_FLASH/Videohead";
    QString dirPath2 = "/mnt/USB_FLASH/Video";

    QDir dir(dirPath);
    if (dir.exists())
    {
        printf("/USB_FLASH/Picture 文件夹存在\n");
    }
    else
    {
        system("mkdir /mnt/USB_FLASH/Picture");
        printf("/USB_FLASH/Picture 文件夹不存在\n");
    }

    QDir dir1(dirPath1);
    if (dir1.exists())
    {
        printf("/USB_FLASH/Videohead 文件夹存在\n");
    }
    else
    {
        system("mkdir /mnt/USB_FLASH/Videohead");
        printf("Videohead 文件夹不存在\n");
    }

    QDir dir2(dirPath2);
    if (dir2.exists())
    {
        printf("/USB_FLASH/Video 文件夹存在\n");
    }
    else
    {
        system("mkdir /mnt/USB_FLASH/Video");
        printf("/USB_FLASH/Video 文件夹不存在\n");
    }
}
