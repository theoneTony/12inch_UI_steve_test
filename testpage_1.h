#ifndef TESTPAGE_1_H
#define TESTPAGE_1_H

#include <QWidget>

namespace Ui {
class testPage_1;
}

class testPage_1 : public QWidget
{
    Q_OBJECT

public:
    explicit testPage_1(QWidget *parent = nullptr);
    ~testPage_1();

private:
    Ui::testPage_1 *ui;
};

#endif // TESTPAGE_1_H
