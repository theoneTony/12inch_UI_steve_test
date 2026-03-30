#ifndef VIDEO_BROWSE_H
#define VIDEO_BROWSE_H

#include <QWidget>
#include "mykey.h"
namespace Ui {
class video_browse;
}

class video_browse : public QWidget
{
    Q_OBJECT

public:
    explicit video_browse(QWidget *parent = nullptr);
    ~video_browse();
    void label_all_false();
    void select_all_mode();
    void deselect_all_true();
    void deselect_all_false();
    void label_play_all_false();
    void video_update();
    void init_video_name();
    void delete_video(int num);
    void set_deselect();
    void sd_convert_usb();
    void clicked_set_return();

    void update_page_button();
signals:
    void clicked_return();
    void goto_void_browse();
    void return_preview();

private:
    Ui::video_browse *ui;
    QList<QLabel*> labels;
    QList<QLabel*> label_tick;
    QList<QLabel*> label_play;
    QList<int> tick_flag;

    QGraphicsOpacityEffect *prevEffect;//按鈕顏色變化
    QGraphicsOpacityEffect *nextEffect;
    int i_num;
    int p_num;
    char result[128];
};


class Label_return_v : public QLabel
{
    Q_OBJECT
public:
    explicit Label_return_v(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_select_v : public QLabel
{
    Q_OBJECT
public:
    explicit Label_select_v(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_select_all_v : public QLabel
{
    Q_OBJECT
public:
    explicit Label_select_all_v(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_deselect_all_v : public QLabel
{
    Q_OBJECT
public:
    explicit Label_deselect_all_v(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_left_v : public QLabel
{
    Q_OBJECT
public:
    explicit Label_left_v(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_right_v : public QLabel
{
    Q_OBJECT
public:
    explicit Label_right_v(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_delete_v : public QLabel
{
    Q_OBJECT
public:
    explicit Label_delete_v(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};




class Label_video_1 : public QLabel
{
    Q_OBJECT
public:
    explicit Label_video_1(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_video_2 : public QLabel
{
    Q_OBJECT
public:
    explicit Label_video_2(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_video_3 : public QLabel
{
    Q_OBJECT
public:
    explicit Label_video_3(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_video_4 : public QLabel
{
    Q_OBJECT
public:
    explicit Label_video_4(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_video_5 : public QLabel
{
    Q_OBJECT
public:
    explicit Label_video_5(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_video_6 : public QLabel
{
    Q_OBJECT
public:
    explicit Label_video_6(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};

#endif // VIDEO_BROWSE_H
