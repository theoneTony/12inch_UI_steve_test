#ifndef TIPS_NO_SD_CARD_H
#define TIPS_NO_SD_CARD_H

#include <QWidget>

namespace Ui {
class tips_no_sd_card;
}

class tips_no_sd_card : public QWidget
{
    Q_OBJECT

public:
    explicit tips_no_sd_card(QWidget *parent = nullptr);
    ~tips_no_sd_card();
    void settext();
private:
    Ui::tips_no_sd_card *ui;
};

#endif // TIPS_NO_SD_CARD_H
