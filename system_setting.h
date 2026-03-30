#ifndef SYSTEM_SETTING_H
#define SYSTEM_SETTING_H

#include <QWidget>
#include "mykey.h"
namespace Ui {
class system_setting;
}

class system_setting : public QWidget
{
    Q_OBJECT

public:
    explicit system_setting(QWidget *parent = nullptr);
    ~system_setting();
signals:
    void clicked_formatting();
    void clicked_reset();
    void clicked_versions();
    void clicked_time();
    void clicked_language();
    void clicked_return();
private:
    Ui::system_setting *ui;
};


class Label_formatting : public QLabel
{
    Q_OBJECT
public:
    explicit Label_formatting(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};

class Label_reset : public QLabel
{
    Q_OBJECT
public:
    explicit Label_reset(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};

class Label_versions : public QLabel
{
    Q_OBJECT
public:
    explicit Label_versions(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};

class Label_time : public QLabel
{
    Q_OBJECT
public:
    explicit Label_time(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};

class Label_language : public QLabel
{
    Q_OBJECT
public:
    explicit Label_language(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};

class Label_return : public QLabel
{
    Q_OBJECT
public:
    explicit Label_return(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};

#endif // SYSTEM_SETTING_H
