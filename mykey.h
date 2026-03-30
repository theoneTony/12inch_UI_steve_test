#ifndef MYKEY_H
#define MYKEY_H

#include "UsbMcu.h"
#include <QSettings>
#include <QObject>
#include <QDebug>
#include <QThread>
#include <QFile>
#include <QTranslator>
#include <QLabel>
#include <QMouseEvent>
#include<QVector>
#include <QtDebug>
#include <QDir>
#include <QTimer>
#include <QList>
#include <QDateTime>
#include <QElapsedTimer>
#include <QGraphicsView>
#include <QGraphicsOpacityEffect>

#include <QGesture>
#include <QGestureEvent>
#include <QPinchGesture>

#include <QHostAddress>
#include <iostream>
#include <cstring>
#include <QtNetwork/QTcpSocket>
#include <QNetworkProxy>
#include <QtGlobal>

#define ZERO               		0x00
#define SWAP_PIP 				0x01	//切换画中画
#define FREEZE_MOTHER 			0x02	//冻结母画面
#define THAW_MOTHER 			0x03	//冻结母画面
#define SET_AWB_M				0x04	//手动白平衡
#define SET_AWB_A				0x05	//自动白平衡
#define ONE_CLICK_AWB			0x06	//一键白平衡
#define SET_AE		 			0x07	//设置曝光
#define FREEZE_SAVE 			0x08	//冻结画面保存
#define FREEZE_DELE 			0x09	//冻结画面删除
#define ROTATE_MOTHER 			0x0A	//旋转镜像母画面
#define ROTATE_SUB 				0x0B	//旋转镜像子画面
#define SINGLE_SCREEN			0x0C    //单画面模式
#define DUAL_SCREEN        		0x0D    //双画面模式
#define PIP_SCREEN       		0x0E    //子母画面模式
#define UI_IS_OK				0xaa	//UI加载完毕
#define TAKE_PICTURE			0x10	//拍照
#define TAKE_VIDOE				0x11	//开始录像
#define STOP_VIDOE				0x12	//停止录像
#define OPEN_RECORD             0x13	//xx		//播放录像视频 xx--01 预览播放  															xx--02   左右切换播放
#define CLOSE_RECORD			0x14	//xx		//关闭录像视频 xx--01 预览关闭 															    xx--02   左右切换关闭
#define PAUSE_RECORD			0x15	//录像视频暂停播放
#define PLAY_RECORD				0x16	//录像视频继续播放
#define SCLING_UP				0x17	//画面放大缩小 ，  第二位 写 放大倍数（10~20）
#define VIDEO_HEAD_PICTURE		0x18    //保存视频头帧照片
#define RECORD_TIME				0x19   	//XX  XX  XX  // 时 分 秒
#define FAST_FORWARD			0x1A	//视频回放快进
#define FAST_BACKWARD			0x1B	//视频回放快退
#define ENTER_PREVIEW			0x1C	//xx		//进入视频预览 xx--01 进入 															    xx--02   退出
#define USB_MCU_				0x1D    //00/01

#define SWITCH_OFF_MIPI      	0x53   	//XX		//MIPI1拔掉手柄给UVC发送
#define SWITCH_ON_MIPI      	0x54	//XX    //MIPI1接入手柄给UVC发送
//XX——>01		MIPI0
//XX——>02		MIPI1

#define MIPI_CAMERA_NUM			0x55
//MIPI摄像头数量 cmd[0]=0x55
//cmd[1]:接入摄像头个数
//cmd[2]:第一路摄像头型号
//cmd[3]:第二路摄像头型号

#define ALL_CAMERA_NUM			0x56	 //当前接入的摄像头数量 MIPI+USB

#define USB_KEY_PHOTO			0x60 //USB按键短按拍照
#define USB_KEY_VIDEO 			0x61 //USB按键长按录像
#define CAMERA_PROPORTION 		0x62 //摄像头比例16:9显示，UI隐藏 cmd[0]=0x62  cmd[1]=0->16:9  cmd[1]=1->1:1
#define PROPORTION_KEY 			0x63 //当前母画面摄像头是否16:9比例，cmd[0]=0x63 cmd[1]=1 是 16:9 cmd[1]=0不是 16:9比例按键失能

#ifdef __cplusplus
extern "C"
{
#endif
#include <fcntl.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <linux/input.h>
#include <sys/statfs.h>
#include <stdint.h>
#include <signal.h>
#include <termios.h>

#define SARADC_IOC_MAGIC 'a'
#define MDRV_SARADC_SET_CHANNEL_MODE_READ_ADC _IO(SARADC_IOC_MAGIC, 1)
#define MS_SAR_INIT                         _IO(SARADC_IOC_MAGIC, 0)

#define FIRST_KEY                   stCfg.adc_value > 270 && stCfg.adc_value <= 335
#define SECOND_KEY                  stCfg.adc_value > 580 && stCfg.adc_value <= 650
#define THIRD_KEY                   stCfg.adc_value > 670 && stCfg.adc_value <= 730
#define FOURTH_KEY                  stCfg.adc_value > 500 && stCfg.adc_value <= 555//有长按
//#define INSERTION_KEY               stCfg.adc_value > 780 && stCfg.adc_value <= 820
#define INSERTION_KEY               stCfg.adc_value > 800 && stCfg.adc_value <= 845
#define PULL_OUT_KEY                stCfg.adc_value > 1000

#define MIPI0_KEY                   stCfg.adc_value > 325 && stCfg.adc_value <= 365
#define INSERTION_MIPI0_KEY         stCfg.adc_value > 650 && stCfg.adc_value <= 690
#define PULL_OUT_MIPI0_KEY          stCfg.adc_value > 980

#define INSERTION_MIPI3_KEY         stCfg.adc_value < 10
#define PULL_OUT_MIPI3_KEY          stCfg.adc_value > 1000
typedef struct
{
    int channel_value;
    int adc_value;
} ADC_CONFIG_READ_ADC;
#ifdef __cplusplus
}
#endif

extern int iRemainTime;
extern int iTotalCount;
extern int  usb_mcu_flag;

class usb_mcu : public QObject
{
    Q_OBJECT
public:
    explicit usb_mcu(QObject *parent = nullptr);
    int GetCmdDataOfUsbMcu(uint8_t *pData);
    void GetCmdDataOfUsbMcuAndDeal();
public slots:
    void mythread_work();
signals:
    void update_display();
    void key_photo();
    void key_video();
};

class rev_usb_mcu : public QObject
{
    Q_OBJECT
public:
    explicit rev_usb_mcu(QObject *parent = nullptr);
public slots:
    void mythread_work();
};

class key_thread : public QObject
{
    Q_OBJECT
public:
    explicit key_thread(QObject *parent = nullptr);

public slots:
    void mythread_work();
signals:
    void first_key();
    void second_key();
    void third_key();
    void fourth_key();
    void fourth_key_long();
    void insertion_key();
    void uninsertion_key();
private:
    int mipi1_flag=1;
    int unmipi1_flag=1;
};

class key_thread_mipi0 : public QObject
{
    Q_OBJECT
public:
    explicit key_thread_mipi0(QObject *parent = nullptr);
public slots:
    void mythread_work();
signals:
    void first_key();
    void first_long_key();
    void insertion_key();
    void uninsertion_key();
private:
    int mipi0_flag=1;
    int unmipi0_flag=1;
};

class key_thread_mipi3 : public QObject
{
    Q_OBJECT
public:
    explicit key_thread_mipi3(QObject *parent = nullptr);
public slots:
    void mythread_work();
signals:
    void insertion_key();
    void uninsertion_key();
private:
    int mipi3_flag=1;
    int unmipi3_flag=1;
};

class key_thread_290 : public QObject
{
    Q_OBJECT
public:
    explicit key_thread_290(QObject *parent = nullptr);

    void open_uart(char *file);
    void init_uart(int baudrate_cmd);
    int uart_send_fv();
    void close_uart();
public slots:
    void mythread_work();
signals:
    void key_photo();
    void key_video();
    void key_zoom_in();
    void key_zoom_out();
private:
    int fd_uart1=0;
};

class shortcut_key : public QObject
{
    Q_OBJECT
public:
    explicit shortcut_key(QObject *parent = nullptr);

    void open_uart(char *file);
    void init_uart(int baudrate_cmd);
    int uart_send_fv();
    void close_uart();
public slots:
    void mythread_work();
signals:
    void key_photo();
    void key_video();
    void key_freeze();
    void key_mode();
    void key_led_add();
    void key_led_minus();
    void key_pump();
    void key_wb();
    void key_zoom();
private:

};

class Time_set
{
public:
    QString num_year;
    QString num_month;
    QString num_day;
    QString num_hour;
    QString num_minute;
    QString num_second;

    QString num_year1;
    QString num_year2;
    QString num_year3;
    QString num_year4;
};

struct SocketData_photo
{
    int socket_data;
    char result[128];
};
extern int label_switch_flag;
extern int aspect_ratio_flag;
extern int mipi3_in_flag;

extern bool click_key_flag;
extern SocketData_photo data_photo;

extern Time_set time_num;

extern int time_flag;

extern int custom_show_flag;
extern int custom1_flag;
extern int custom2_flag;
extern int custom3_flag;

extern int sensor_flag;
extern int awb_atom_flag;//自动
extern int picture_flag;
extern int display_flag;
extern int language_flag;

extern int ae_flag;
extern int rotate_flag;
extern int freeze_flag;
extern int video_flag;
extern int led_host_flag;
extern int led_flag;
extern int pump_flag;

extern int photo_select_flag;//单选
extern int photo_select_all_flag;//全选
extern int photo_deselect_all_flag;//取消选择
extern int photo_delete_flag;//删除
extern int photo_totality;//页面总数
extern int photo_num;//当前页面
extern int photo_max;//单张总数
extern int photo_labelnum;//单击label记录



extern int video_select_flag;
extern int video_select_all_flag;
extern int video_deselect_all_flag;
extern int void_delete_flag;//删除
extern int video_totality;//页面总数
extern int video_num;//当前页面
extern int video_max;//单张总数
extern int video_labelnum;//单击label记录
extern int video_play_flag;//播放暂停标志位
extern int progress_time;//进度条
extern int progress_flag_time;//进度条
extern int hours_progress;
extern int minutes_progress;
extern int seconds_progress;
extern char playback_video_name[64];

extern int clicked_frames_flag;
extern int sensorless_flag;
extern QStringList photo_name;
extern QStringList video_name;

extern int in_control_flag;//在操作界面的标志
extern int flag_SD;
extern int flag_USB;
extern int sensor_num;
extern int current_interface_flag;
extern int switchable_flag;
extern int switchable_delete_flag;
extern int check_disk();
extern int zoom_num;
extern int fd_uartkey;//按键板串口
#endif // MYKEY_H

