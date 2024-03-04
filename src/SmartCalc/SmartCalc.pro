#-------------------------------------------------
#
# Project created by QtCreator 2023-11-15T23:29:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = SmartCalc
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    calculate_func/validator.c \
    calculate_func/parse.c \
    calculate_func/pol.c \
    qcustomplot.cpp \
    creditwindow.cpp \
    depositwindow.cpp \
    credit.c \
    deposit.c

HEADERS += \
        mainwindow.h \
    validator.h \
    parse.h \
    pol.h \
    qcustomplot.h \
    creditwindow.h \
    depositwindow.h \
    credit.h \
    deposit.h

FORMS += \
        mainwindow.ui \
    creditwindow.ui \
    depositwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
