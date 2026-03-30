#ifndef VERSION_NUMBER_H
#define VERSION_NUMBER_H

#include <QWidget>
#include "mykey.h"
namespace Ui {
class version_number;
}

class version_number : public QWidget
{
    Q_OBJECT

public:
    explicit version_number(QWidget *parent = nullptr);
    ~version_number();
    void settext();
signals:
    void clicked_return();
    void no_SDTips();
    void missing_file();
private:
    Ui::version_number *ui;
};

class Label_version_return : public QLabel
{
    Q_OBJECT
public:
    explicit Label_version_return(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};

class Label_version_update : public QLabel
{
    Q_OBJECT
public:
    explicit Label_version_update(QWidget *parent = nullptr);

signals:
    void clicked_1();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
#endif // VERSION_NUMBER_H
