#include "testpage_1.h"
#include "ui_testpage_1.h"

testPage_1::testPage_1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::testPage_1)
{
    ui->setupUi(this);
}

testPage_1::~testPage_1()
{
    delete ui;
}
