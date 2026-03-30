#ifndef PHOTO_BROWSE_H
#define PHOTO_BROWSE_H

#include <QWidget>
#include "mykey.h"
namespace Ui {
class photo_browse;
}

class photo_browse : public QWidget
{
    Q_OBJECT

public:
    explicit photo_browse(QWidget *parent = nullptr);
    ~photo_browse();
    void photo_update();
    void select_all_mode();

    void deselect_all_false();
    void deselect_all_true();

    void label_all_false();
    void label_all_true();
    void init_photo_name();
    void displayCompressedImage(const QString &filePath, QLabel *label);
    void delete_photo(int num);
    void set_deselect();

    void sd_convert_usb();
    void clicked_set_return();

    void record_tick_flag(int num);
    void update_page_button();


signals:
    void clicked_return();
    void goto_photo_browse();
private:
    Ui::photo_browse *ui;
    QList<QLabel*> labels;
    QList<QLabel*> label_tick;
    QList<int> tick_flag;

    QGraphicsOpacityEffect *prevEffect;//按鈕顏色變化
    QGraphicsOpacityEffect *nextEffect;




    int i_num;
    int p_num;
};


class Label_return_p : public QLabel
{
    Q_OBJECT
public:
    explicit Label_return_p(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_select_p : public QLabel
{
    Q_OBJECT
public:
    explicit Label_select_p(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_select_all_p : public QLabel
{
    Q_OBJECT
public:
    explicit Label_select_all_p(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_deselect_all_p : public QLabel
{
    Q_OBJECT
public:
    explicit Label_deselect_all_p(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_left_p : public QLabel
{
    Q_OBJECT
public:
    explicit Label_left_p(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_right_p : public QLabel
{
    Q_OBJECT
public:
    explicit Label_right_p(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_delete_p : public QLabel
{
    Q_OBJECT
public:
    explicit Label_delete_p(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};




class Label_photo_1 : public QLabel
{
    Q_OBJECT
public:
    explicit Label_photo_1(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_photo_2 : public QLabel
{
    Q_OBJECT
public:
    explicit Label_photo_2(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_photo_3 : public QLabel
{
    Q_OBJECT
public:
    explicit Label_photo_3(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_photo_4 : public QLabel
{
    Q_OBJECT
public:
    explicit Label_photo_4(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_photo_5 : public QLabel
{
    Q_OBJECT
public:
    explicit Label_photo_5(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_photo_6 : public QLabel
{
    Q_OBJECT
public:
    explicit Label_photo_6(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};

#endif // PHOTO_BROWSE_H
