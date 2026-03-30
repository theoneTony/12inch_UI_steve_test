#ifndef MISSING_UPGRADE_FILE_H
#define MISSING_UPGRADE_FILE_H

#include <QWidget>
#include "mykey.h"
namespace Ui {
class missing_upgrade_file;
}

class missing_upgrade_file : public QWidget
{
    Q_OBJECT

public:
    explicit missing_upgrade_file(QWidget *parent = nullptr);
    ~missing_upgrade_file();
    void settext();
private:
    Ui::missing_upgrade_file *ui;
};

#endif // MISSING_UPGRADE_FILE_H
