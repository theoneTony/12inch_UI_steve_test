#ifndef VIDEO_DROWSE_PLAY_H
#define VIDEO_DROWSE_PLAY_H

#include <QWidget>
#include "mykey.h"
namespace Ui {
class video_drowse_play;
}

class video_drowse_play : public QWidget
{
    Q_OBJECT

public:
    explicit video_drowse_play(QWidget *parent = nullptr);
    ~video_drowse_play();
    void video_update();
    void extract_name_play(int num);//提取名字并播放
    void extract_name_play_one(int num);//提取名字并播放
    void reset_progress_bar();
    void sd_convert_usb();

    void update_video_page_button();
signals:
    void socket_pause();
    void socket_play_on();
    void socket_play_video();
    void socket_play_video_one();
    void socket_close_play();
    void socket_close_play_return();
    void socket_fast_forward();
    void socket_fast_backward();

    void return_video();
    void update_video_name();


private:
    Ui::video_drowse_play *ui;
    QTimer *timer;
    QTimer *timer_socket;
    double currentProgress;
    int currentSeconds;
    int hours;
    int minutes;
    int seconds;
    QString tem_str;
    QTimer *timer_switchable;
    bool replayFlag = false;

    QGraphicsOpacityEffect *prevEffect;//按鈕顏色變化
    QGraphicsOpacityEffect *nextEffect;
};

class Label_return_vs : public QLabel
{
    Q_OBJECT
public:
    explicit Label_return_vs(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_left_vs : public QLabel
{
    Q_OBJECT
public:
    explicit Label_left_vs(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_right_vs : public QLabel
{
    Q_OBJECT
public:
    explicit Label_right_vs(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_recoil_vs : public QLabel
{
    Q_OBJECT
public:
    explicit Label_recoil_vs(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_pause_vs : public QLabel
{
    Q_OBJECT
public:
    explicit Label_pause_vs(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_advance_vs : public QLabel
{
    Q_OBJECT
public:
    explicit Label_advance_vs(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_delete_vs : public QLabel
{
    Q_OBJECT
public:
    explicit Label_delete_vs(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
#endif // VIDEO_DROWSE_PLAY_H
