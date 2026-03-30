#ifndef RESET_SETTING_H
#define RESET_SETTING_H

#include <QWidget>
#include "mykey.h"
namespace Ui {
class reset_setting;
}

class reset_setting : public QWidget
{
    Q_OBJECT

public:
    explicit reset_setting(QWidget *parent = nullptr);
    ~reset_setting();
    void settext();
signals:
    void clicked_return();
    void reset_yes();
private:
    Ui::reset_setting *ui;
};

class Label_no_reset : public QLabel
{
    Q_OBJECT
public:
    explicit Label_no_reset(QWidget *parent = nullptr);
signals:
    void clicked_1();
protected:
    virtual void mousePressEvent(QMouseEvent* event);
};

class Label_yes_reset : public QLabel
{
    Q_OBJECT
public:
    explicit Label_yes_reset(QWidget *parent = nullptr);
signals:
    void clicked_1();
protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
#endif // RESET_SETTING_H
