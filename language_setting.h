#ifndef LANGUAGE_SETTING_H
#define LANGUAGE_SETTING_H

#include <QWidget>
#include "mykey.h"
namespace Ui {
class language_setting;
}

class language_setting : public QWidget
{
    Q_OBJECT

public:
    explicit language_setting(QWidget *parent = nullptr);
    ~language_setting();
    void update_data();
    void goto_one();
    void settext();
signals:
    void clicked_return();
    void save_language();
private:
    Ui::language_setting *ui;
    int language_flag_t;
};


class Label_chinese : public QLabel
{
    Q_OBJECT
public:
    explicit Label_chinese(QWidget *parent = nullptr);
signals:
    void clicked_1();
protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_Tchinese : public QLabel
{
    Q_OBJECT
public:
    explicit Label_Tchinese(QWidget *parent = nullptr);
signals:
    void clicked_1();
protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_english : public QLabel
{
    Q_OBJECT
public:
    explicit Label_english(QWidget *parent = nullptr);
signals:
    void clicked_1();
protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_espanol : public QLabel
{
    Q_OBJECT
public:
    explicit Label_espanol(QWidget *parent = nullptr);
signals:
    void clicked_1();
protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_save_L : public QLabel
{
    Q_OBJECT
public:
    explicit Label_save_L(QWidget *parent = nullptr);
signals:
    void clicked_1();
protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_return_L : public QLabel
{
    Q_OBJECT
public:
    explicit Label_return_L(QWidget *parent = nullptr);
signals:
    void clicked_1();
protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
#endif // LANGUAGE_SETTING_H
