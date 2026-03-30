#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    printf("==============1749=================\n");
    QApplication a(argc, argv);
    Widget w;

    QFile styleFile(":/sanping.qss");
    styleFile.open(QFile::ReadOnly);
    QString style = QLatin1String(styleFile.readAll());
    a.setStyleSheet(style);
    styleFile.close();

    w.show();
    return a.exec();
}
