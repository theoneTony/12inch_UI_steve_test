#include "no_memory.h"
#include "ui_no_memory.h"

no_memory::no_memory(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::no_memory)
{
    ui->setupUi(this);
    ui->label_backdrop->setStyleSheet("border-radius: 30px 30px 30px 30px;background-color: rgb(110, 215, 230);");
    ui->label_num->setStyleSheet("font-size: 35px;");
}

no_memory::~no_memory()
{
    delete ui;
}

void no_memory::settext()
{
    ui->label_num->setText(tr("存储设备空间不足"));
}
