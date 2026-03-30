#ifndef NO_DEVICE_H
#define NO_DEVICE_H

#include <QWidget>
#include "mykey.h"
namespace Ui {
class no_device;
}

class no_device : public QWidget
{
    Q_OBJECT

public:
    explicit no_device(QWidget *parent = nullptr);
    ~no_device();
    void settext();
private:
    Ui::no_device *ui;
};

#endif // NO_DEVICE_H
