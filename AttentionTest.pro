QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    antmain.cpp \
    anttutorial.cpp \
    antwindow.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    stroopmain.cpp \
    strooptutorial.cpp \
    stroopwindow.cpp

HEADERS += \
    antmain.h \
    anttutorial.h \
    antwindow.h \
    logindialog.h \
    mainwindow.h \
    stroopmain.h \
    strooptutorial.h \
    stroopwindow.h

FORMS += \
    anttutorial.ui \
    antwindow.ui \
    logindialog.ui \
    mainwindow.ui \
    strooptutorial.ui \
    stroopwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
