#ifndef SENSOR_RESTART_H
#define SENSOR_RESTART_H

#include <QWidget>
#include "mykey.h"
namespace Ui {
class sensor_restart;
}

class sensor_restart : public QWidget
{
    Q_OBJECT

public:
    explicit sensor_restart(QWidget *parent = nullptr);
    ~sensor_restart();
    void settext();
signals:
    void clicked_return();
private:
    Ui::sensor_restart *ui;
};

class Label_sensor : public QLabel
{
    Q_OBJECT
public:
    explicit Label_sensor(QWidget *parent = nullptr);
signals:
    void clicked_1();
protected:
    virtual void mousePressEvent(QMouseEvent* event);
};
#endif // SENSOR_RESTART_H
