#ifndef FORMATTING_H
#define FORMATTING_H

#include <QWidget>
#include "mykey.h"
namespace Ui {
class formatting;
}

class formatting : public QWidget
{
    Q_OBJECT

public:
    explicit formatting(QWidget *parent = nullptr);
    ~formatting();
    void settext();
signals:
    void clicked_return();
    void no_SDTips();
    void format_ok();
private:
    Ui::formatting *ui;
};

class Label_no_format : public QLabel
{
    Q_OBJECT
public:
    explicit Label_no_format(QWidget *parent = nullptr);
signals:
    void clicked_1();
protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
class Label_yes_format : public QLabel
{
    Q_OBJECT
public:
    explicit Label_yes_format(QWidget *parent = nullptr);
signals:
    void clicked_1();
protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
#endif // FORMATTING_H
