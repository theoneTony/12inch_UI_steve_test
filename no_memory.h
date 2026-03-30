#ifndef NO_MEMORY_H
#define NO_MEMORY_H

#include <QWidget>
#include "mykey.h"
namespace Ui {
class no_memory;
}

class no_memory : public QWidget
{
    Q_OBJECT

public:
    explicit no_memory(QWidget *parent = nullptr);
    ~no_memory();
    void settext();
private:
    Ui::no_memory *ui;
};

#endif // NO_MEMORY_H
