#ifndef PHOTO_BROWSE_SINGLE_H
#define PHOTO_BROWSE_SINGLE_H

#include <QWidget>
#include "mykey.h"
namespace Ui {
class photo_browse_single;
}

class photo_browse_single : public QWidget
{
    Q_OBJECT

public:
    explicit photo_browse_single(QWidget *parent = nullptr);
    ~photo_browse_single();
    void photo_update();
    void sd_convert_usb();

    void update_photo_single_page_button();
signals:
    void return_photo();
    void update_photo_name();
    void update_page_button();
private:
    Ui::photo_browse_single *ui;
    QTimer *timer_switchable;
    QGraphicsOpacityEffect *prevEffect;//按鈕顏色變化
    QGraphicsOpacityEffect *nextEffect;

};


class Label_full_screen : public QLabel
{
    Q_OBJECT
public:
    explicit Label_full_screen(QWidget *parent = nullptr);
protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;
signals:
    void doubleClicked();
};
class Label_screen : public QLabel
{
    Q_OBJECT
public:
    explicit Label_screen(QWidget *parent = nullptr);
protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;
signals:
    void doubleClicked();
};
class Label_delete_ps : public QLabel
{
    Q_OBJECT
public:
    explicit Label_delete_ps(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_left_ps : public QLabel
{
    Q_OBJECT
public:
    explicit Label_left_ps(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_right_ps : public QLabel
{
    Q_OBJECT
public:
    explicit Label_right_ps(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_return_ps : public QLabel
{
    Q_OBJECT
public:
    explicit Label_return_ps(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
#endif // PHOTO_BROWSE_SINGLE_H
