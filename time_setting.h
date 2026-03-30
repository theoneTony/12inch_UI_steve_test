#ifndef TIME_SETTING_H
#define TIME_SETTING_H

#include <QWidget>
#include "mykey.h"
namespace Ui {
class time_setting;
}

class time_setting : public QWidget
{
    Q_OBJECT

public:
    explicit time_setting(QWidget *parent = nullptr);
    ~time_setting();
    void settext();
    void update_data();
    void update_setStyleSheet();
signals:
    void clicked_return();
private:
    Ui::time_setting *ui;

    QString qsyear_data_use;
    int year1_data_use;
    int year2_data_use;
    int year3_data_use;
    int year4_data_use;
    int year_data_use;
    int month_data_use;
    int day_data_use;
    int hour_data_use;
    int minute_data_use;

    QByteArray set_time;
    QString splice_data;
};

class Label_up1_time : public QLabel
{
    Q_OBJECT
public:
    explicit Label_up1_time(QWidget *parent = nullptr);
signals:
    void clicked_1();
protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_up2_time : public QLabel
{
    Q_OBJECT
public:
    explicit Label_up2_time(QWidget *parent = nullptr);
signals:
    void clicked_1();
protected:
    virtual void mousePressEvent(QMouseEvent* event);
};

class Label_up3_time : public QLabel
{
    Q_OBJECT
public:
    explicit Label_up3_time(QWidget *parent = nullptr);
signals:
    void clicked_1();
protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_down1_time : public QLabel
{
    Q_OBJECT
public:
    explicit Label_down1_time(QWidget *parent = nullptr);
signals:
    void clicked_1();
protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_down2_time : public QLabel
{
    Q_OBJECT
public:
    explicit Label_down2_time(QWidget *parent = nullptr);
signals:
    void clicked_1();
protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_down3_time : public QLabel
{
    Q_OBJECT
public:
    explicit Label_down3_time(QWidget *parent = nullptr);
signals:
    void clicked_1();
protected:
    virtual void mousePressEvent(QMouseEvent* event);
};


class Label_year1_time : public QLabel
{
    Q_OBJECT
public:
    explicit Label_year1_time(QWidget *parent = nullptr);
signals:
    void clicked_1();
protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_year2_time : public QLabel
{
    Q_OBJECT
public:
    explicit Label_year2_time(QWidget *parent = nullptr);
signals:
    void clicked_1();
protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_year3_time : public QLabel
{
    Q_OBJECT
public:
    explicit Label_year3_time(QWidget *parent = nullptr);
signals:
    void clicked_1();
protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_year4_time : public QLabel
{
    Q_OBJECT
public:
    explicit Label_year4_time(QWidget *parent = nullptr);
signals:
    void clicked_1();
protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_month_time : public QLabel
{
    Q_OBJECT
public:
    explicit Label_month_time(QWidget *parent = nullptr);
signals:
    void clicked_1();
protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_day_time : public QLabel
{
    Q_OBJECT
public:
    explicit Label_day_time(QWidget *parent = nullptr);
signals:
    void clicked_1();
protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_hour_time : public QLabel
{
    Q_OBJECT
public:
    explicit Label_hour_time(QWidget *parent = nullptr);
signals:
    void clicked_1();
protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_minute_time : public QLabel
{
    Q_OBJECT
public:
    explicit Label_minute_time(QWidget *parent = nullptr);
signals:
    void clicked_1();
protected:
    virtual void mousePressEvent(QMouseEvent* event);
};



class Label_return_time : public QLabel
{
    Q_OBJECT
public:
    explicit Label_return_time(QWidget *parent = nullptr);
signals:
    void clicked_1();
protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_save_time : public QLabel
{
    Q_OBJECT
public:
    explicit Label_save_time(QWidget *parent = nullptr);
signals:
    void clicked_1();
protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
#endif // TIME_SETTING_H
