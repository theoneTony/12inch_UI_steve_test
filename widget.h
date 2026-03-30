#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mykey.h"
#include "system_setting.h"
#include "control_interface.h"
#include "no_device.h"
#include "no_memory.h"
#include "zhukuang.h"
#include "photo_browse.h"
#include "video_browse.h"
#include "photo_browse_single.h"
#include "video_drowse_play.h"

#include "formatting.h"
#include "reset_setting.h"
#include "version_number.h"
#include "time_setting.h"
#include "language_setting.h"
#include "tips_no_sd_card.h"
#include "sensor_restart.h"
#include "missing_upgrade_file.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    static Widget *mywidget;
    void Display_complete();
    void verify_sdcard();
    void Clear_record_sdfile();
    void Confirm_folder();

    void verify_usbflash();
    void Clear_record_usbflash();
    void Confirm_folder_usbflash();
    static void sd_in_re(int num);
    static void usb_in_re(int num);
    void set_language_mode();
    int get_next_photo_index(QString path);
    int get_next_video_index(QString path);
public slots:
    void onConnected();
    void onReadyRead();
    void onDisConnected();
    void onError();
private slots:
    void set_first_mipi0_key();
    void set_first_long_mipi0_key();

    void set_first_key();
    void set_second_key();
    void set_third_key();
    void set_fourth_key();
    void set_fourth_key_long();
private:
    Ui::Widget *ui;
    QThread *mythread;
    key_thread *key;
    QThread *mythread_mipi0;
    key_thread_mipi0 *key_mipi0;
    QThread *mythread_mipi3;
    key_thread_mipi3 *key_mipi3;
    QThread *mcu_thread;
    usb_mcu *usb_mcu_key;
    QThread *rev_mcu_thread;
    rev_usb_mcu *rev_usb_mcu_key;

    QThread *thread_290;
    key_thread_290 *key_290;

    QThread *thread_9anjian;
    shortcut_key *key_9anjian;

    zhukuang *zhukuang_widget;
    system_setting *system_widget;
    control_interface *control_widget;
    no_device *device_widget;
    no_memory *memory_widget;
    photo_browse *photo_widget;
    video_browse *video_widget;
    photo_browse_single *photo_single_widget;
    video_drowse_play *video_play_widget;

    formatting *formatting_widget;
    reset_setting *reset_widget;
    version_number *version_number_widget;
    time_setting *time_widget;
    language_setting *language_widget;
    sensor_restart *sensor_restart_widget;
    missing_upgrade_file *missing_widget;
    char socket_data1[5];
    char socket_data2[5];
    char cStringData[5];
    QByteArray data_socket;
    QTcpSocket *socketclient;

    QTimer *timer_1;//无SD卡提示
    tips_no_sd_card *nosdcard_wiget;

    char result[128];
    int year_w;
    int onth_w;
    int day_w;
    int hour_w;
    int minute_w;
    int second_w;
    QSettings *settings;
    int oneflag;
};
#endif // WIDGET_H
