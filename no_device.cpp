#include "no_device.h"
#include "ui_no_device.h"

no_device::no_device(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::no_device)
{
    ui->setupUi(this);
    ui->label_backdrop->setStyleSheet("border-radius: 30px 30px 30px 30px;background-color: rgb(110, 215, 230);");
    ui->label_num->setStyleSheet("font-size: 35px;");
}

no_device::~no_device()
{
    delete ui;
}

void no_device::settext()
{
    ui->label_num->setText(tr("无设备链接    请接入设备"));
}
