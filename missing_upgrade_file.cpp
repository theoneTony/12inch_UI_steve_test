#include "missing_upgrade_file.h"
#include "ui_missing_upgrade_file.h"

missing_upgrade_file::missing_upgrade_file(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::missing_upgrade_file)
{
    ui->setupUi(this);
    ui->label_backdrop->setStyleSheet("border-radius: 30px 30px 30px 30px;background-color: rgb(110, 215, 230);");
}

missing_upgrade_file::~missing_upgrade_file()
{
    delete ui;
}

void missing_upgrade_file::settext()
{
    ui->label_num->setText(tr("缺少升级文件"));
}
