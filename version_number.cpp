#include "version_number.h"
#include "ui_version_number.h"

version_number::version_number(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::version_number)
{
    ui->setupUi(this);
    connect(ui->label_return,&Label_version_return::clicked_1,this,[=](){
        emit clicked_return();
    });

    connect(ui->label_update,&Label_version_update::clicked_1,this,[=](){
        QFile update_file("/mnt/SD_CARD/sp_update.txt");
        if(update_file.exists())
        {
            printf("=====找到标志文件=====\n");
            system("echo 134 > /sys/class/gpio/export");
            usleep(50*1000);
            system("echo out > /sys/class/gpio/gpio134/direction");
            usleep(50*1000);
            system("echo 0 > /sys/class/gpio/gpio134/value");
            usleep(50*1000);
            system("/etc/fw_setenv ota_upgrade_status 1");
            usleep(50*1000);
            system("reboot");
        }
        else
        {
            printf("=====找不到标志文件=====\n");
        }
        /*
        if(flag_SD==1)
        {
            QString dirPath = "/mnt/SD_CARD/sd_upgrade/";
            QDir dir(dirPath);
            QStringList patterns;
            patterns << "IPL" << "IPL_CUST" << "UBOOT";
            QList<QStringList> allFileLists;
            for (const QString &pattern : patterns)
            {
                QStringList fileList = dir.entryList(QStringList(pattern), QDir::Files | QDir::NoDotAndDotDot, QDir::Name);
                allFileLists.append(fileList);
            }
            bool foundAllFiles = true;
            for (const QStringList &fileList : allFileLists)
            {
                if (fileList.isEmpty())
                {
                    foundAllFiles = false;
                    break;
                }
            }
            QString dirPathsd = "/mnt/SD_CARD/";
            QDir dirsd(dirPathsd);
            QStringList patternssd;
            patternssd << "SigmastarUpgradeSD.bin";

            QList<QStringList> allFileListssd;
            for (const QString &pattern : patternssd)
            {
                QStringList fileList = dirsd.entryList(QStringList(pattern), QDir::Files | QDir::NoDotAndDotDot, QDir::Name);
                allFileListssd.append(fileList);
            }
            bool foundAllFilessd = true;
            for (const QStringList &fileList : allFileListssd)
            {
                if (fileList.isEmpty())
                {
                    foundAllFilessd = false;
                    break;
                }
            }
            if (foundAllFiles && foundAllFilessd)
            {
                system("cp /mnt/SD_CARD/sd_upgrade/SigmastarUpgradeSD.bin /mnt/SD_CARD/");
                usleep(50*1000);
                system("cp /mnt/SD_CARD/sd_upgrade/IPL /mnt/SD_CARD/");
                usleep(50*1000);
                system("cp /mnt/SD_CARD/sd_upgrade/IPL_CUST /mnt/SD_CARD/");
                usleep(50*1000);
                system("cp /mnt/SD_CARD/sd_upgrade/UBOOT /mnt/SD_CARD/");
                usleep(50*1000);
                system("reboot");
            }
            else
            {
                printf("Missing upgrade file\n");
                emit missing_file();
            }
        }
        else if(flag_SD==0)
        {
            emit no_SDTips();
        }
        */
    });

    ui->label_backdrop->setStyleSheet("border-radius: 30px 30px 30px 30px;background-color: rgb(110, 215, 230);");
    ui->label_return->setStyleSheet("border-radius: 10px 10px 10px 10px;background-color: rgb(151, 235, 238);");
    ui->label_update->setStyleSheet("border-radius: 10px 10px 10px 10px;background-color: rgb(151, 235, 238);");
}

version_number::~version_number()
{
    delete ui;
}

void version_number::settext()
{
    ui->label_version->setText(tr("当前版本信息"));
    ui->label_return->setText(tr("退出"));
    ui->label_update->setText(tr("升级"));
}

Label_version_return::Label_version_return(QWidget *parent): QLabel(parent)
{

}
void Label_version_return::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}

Label_version_update::Label_version_update(QWidget *parent): QLabel(parent)
{

}
void Label_version_update::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked_1();
    }
   QLabel::mousePressEvent(event);
}
