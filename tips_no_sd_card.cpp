#include "tips_no_sd_card.h"
#include "ui_tips_no_sd_card.h"

tips_no_sd_card::tips_no_sd_card(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tips_no_sd_card)
{
    ui->setupUi(this);
    ui->label_backdrop->setStyleSheet("border-radius: 30px 30px 30px 30px;background-color: rgb(110, 215, 230);");
}

tips_no_sd_card::~tips_no_sd_card()
{
    delete ui;
}

void tips_no_sd_card::settext()
{
    ui->label_num->setText(tr("请插入SD卡"));
}
