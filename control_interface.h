#ifndef CONTROL_INTERFACE_H
#define CONTROL_INTERFACE_H

#include <QWidget>
#include "mykey.h"
#include <QGestureEvent>
#include <QGesture>
#include <QPinchGesture>
#include <QTransform>
#include <QTouchEvent>
namespace Ui {
class control_interface;
}

class control_interface : public QWidget
{
    Q_OBJECT

public:
    explicit control_interface(QWidget *parent = nullptr);
    ~control_interface();

    void update_data();  //UI_update
    void update_picture_mode();

    void set_gpio_host_led();  //gpio
    void set_gpio_host_led_logo();
    void set_gpio_led();
    void set_gpio_pump();
    void set_gpio_ae();

    void read_socket_awb(); //socket
    void read_socket_freeze();
    void read_socket_photograph();
    void read_socket_display();
    void read_rotate();
    void read_gpio_ae();

    void set_display_mode();
    void set_rotate();
    void reset_the_settings();
    void settext();

    void custom_add_switch(int data);
    void set_awb();
    void set_freeze();
    void set_video();
    void set_photograph();
    void set_zoomup();
    void set_zoomdown();
    void set_ledup();
    void set_leddown();
    void click_display();
    void click_pump();

    void first_key_set();
    void second_key_set();
    void third_key_set();
    void fourth_key_set();
    void fourth_key_long_set();

    void update_duration();
    void update_zoomnum();
    void Disable_all_buttons(int flag);
    void Enable_all_buttons();
    void hideAllControlsExcept();
    void showAllControlsExcept();
    void switch_off();
private slots:
    void updateTimer();
    void updateTime_date();
signals:
    void clicked_awb_auto();
    void clicked_awb_manual();
    void clicked_picture_mode();
    void clicked_display_mode();
    void clicked_language_mode();

    void clicked_interface();

    void socket_awb();
    void socket_freeze0();
    void socket_freeze1();
    void socket_rotate1();
    void socket_rotate2();
    void socket_rotate3();
    void socket_rotate4();
    void socket_rotate5();
    void socket_rotate_freeze1();
    void socket_rotate_freeze2();
    void socket_rotate_freeze3();
    void socket_rotate_freeze4();
    void socket_rotate_freeze5();
    void socket_photograph();
    void socket_photograph_name();
    void socket_videoon();
    void socket_videooff();
    void socket_ae1();
    void socket_ae2();
    void socket_ae3();
    void socket_ae4();
    void socket_ae5();

    void socket_store();                //冻结储存
    void socket_cancel_freeze1();       //取消冻结储存
    void socket_single_screen();        //单画面模式
    void socket_dual_screen();          //双画面模式
    void socket_size_screen();          //子母画面模式
    void socket_frames();

    void socket_screen_left();
    void socket_screen_right();

    void socket_set_zoom();

    void nosd_card();
    void stock_full();
    void socket_switch();
private:
    Ui::control_interface *ui;
    QTimer *timer;
    QDateTime startTime;
    QTimer *timer_t;
    QTimer *timer_switchable;
    QTimer *timer_freeze;
    QTimer *loop_video_timer;
    QString exceptionName = "label_switch";
    int year0_data;
    char *pLED0="LL0";
    char *pLED1="LL1";
    char *pLED2="LL2";
    char *pLED3="LL3";
    char *pLED4="LL4";
};

class Label_screen_left : public QLabel
{
    Q_OBJECT
public:
    explicit Label_screen_left(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);//重写mousePressEvent事件
};
class Label_screen_right : public QLabel
{
    Q_OBJECT
public:
    explicit Label_screen_right(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);//重写mousePressEvent事件
};




class Label_picture_mode : public QLabel
{
    Q_OBJECT
public:
    explicit Label_picture_mode(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);//重写mousePressEvent事件
};
class Label_display_mode : public QLabel
{
    Q_OBJECT
public:
    explicit Label_display_mode(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);//重写mousePressEvent事件
};
class Label_custom1 : public QLabel
{
    Q_OBJECT
public:
    explicit Label_custom1(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);//重写mousePressEvent事件
};
class Label_custom2 : public QLabel
{
    Q_OBJECT
public:
    explicit Label_custom2(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);//重写mousePressEvent事件
};
class Label_custom3 : public QLabel
{
    Q_OBJECT
public:
    explicit Label_custom3(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);//重写mousePressEvent事件
};




class Label_awb : public QLabel
{
    Q_OBJECT
public:
    explicit Label_awb(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);//重写mousePressEvent事件
};
class Label_freeze : public QLabel
{
    Q_OBJECT
public:
    explicit Label_freeze(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);//重写mousePressEvent事件
};
class Label_store : public QLabel
{
    Q_OBJECT
public:
    explicit Label_store(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);//重写mousePressEvent事件
};
class Label_rotate : public QLabel
{
    Q_OBJECT
public:
    explicit Label_rotate(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);//重写mousePressEvent事件
};
class Label_photograph : public QLabel
{
    Q_OBJECT
public:
    explicit Label_photograph(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);//重写mousePressEvent事件
};
class Label_videoint : public QLabel
{
    Q_OBJECT
public:
    explicit Label_videoint(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);//重写mousePressEvent事件
};
class Label_ae : public QLabel
{
    Q_OBJECT
public:
    explicit Label_ae(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);//重写mousePressEvent事件
};
class Label_host_led : public QLabel
{
    Q_OBJECT
public:
    explicit Label_host_led(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);//重写mousePressEvent事件
};
class Label_led : public QLabel
{
    Q_OBJECT
public:
    explicit Label_led(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);//重写mousePressEvent事件
};
class Label_pump : public QLabel
{
    Q_OBJECT
public:
    explicit Label_pump(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);//重写mousePressEvent事件
};
class Label_interface : public QLabel
{
    Q_OBJECT
public:
    explicit Label_interface(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);//重写mousePressEvent事件
};
class Label_zoom : public QLabel
{
    Q_OBJECT
public:
    explicit Label_zoom(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);//重写mousePressEvent事件
};
class Label_switch : public QLabel
{
    Q_OBJECT
public:
    explicit Label_switch(QWidget *parent = nullptr);
signals:
    void clicked_1();
protected:
    virtual void mousePressEvent(QMouseEvent* event);//重写mousePressEvent事件
};



class Label_frames : public QLabel {
    Q_OBJECT

public:
    Label_frames(QWidget *parent = nullptr);
    ~Label_frames();

signals:
    void clicked_1();
    void clicked_double();
protected:
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseDoubleClickEvent(QMouseEvent* event);
private:
    QElapsedTimer doubleClickTimer;
    QTimer *timre;
    bool doubleClickFlag;
};

#endif // CONTROL_INTERFACE_H
