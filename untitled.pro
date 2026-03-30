QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TRANSLATIONS = English.ts Chinese.ts Chinese_t.ts Espanol.ts

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    UsbMcu.cpp \
    control_interface.cpp \
    formatting.cpp \
    language_setting.cpp \
    main.cpp \
    missing_upgrade_file.cpp \
    mykey.cpp \
    no_device.cpp \
    no_memory.cpp \
    photo_browse.cpp \
    photo_browse_single.cpp \
    reset_setting.cpp \
    sensor_restart.cpp \
    system_setting.cpp \
    time_setting.cpp \
    tips_no_sd_card.cpp \
    version_number.cpp \
    video_browse.cpp \
    video_drowse_play.cpp \
    widget.cpp \
    zhukuang.cpp

HEADERS += \
    UsbMcu.h \
    control_interface.h \
    formatting.h \
    language_setting.h \
    libusb.h \
    missing_upgrade_file.h \
    mykey.h \
    no_device.h \
    no_memory.h \
    photo_browse.h \
    photo_browse_single.h \
    reset_setting.h \
    sensor_restart.h \
    system_setting.h \
    time_setting.h \
    tips_no_sd_card.h \
    version_number.h \
    video_browse.h \
    video_drowse_play.h \
    widget.h \
    zhukuang.h

FORMS += \
    control_interface.ui \
    formatting.ui \
    language_setting.ui \
    missing_upgrade_file.ui \
    no_device.ui \
    no_memory.ui \
    photo_browse.ui \
    photo_browse_single.ui \
    reset_setting.ui \
    sensor_restart.ui \
    system_setting.ui \
    time_setting.ui \
    tips_no_sd_card.ui \
    version_number.ui \
    video_browse.ui \
    video_drowse_play.ui \
    widget.ui \
    zhukuang.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    SP.qrc

unix:!macx: LIBS += -L$$PWD/../lib/ -lusb-1.0

INCLUDEPATH += $$PWD/../lib
DEPENDPATH += $$PWD/../lib
