#-------------------------------------------------
#
# Project created by QtCreator 2018-12-07T20:53:30
#
#-------------------------------------------------

QT       += core gui websockets network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BlockchainServer
TEMPLATE = app

MOC_DIR = build
OBJECTS_DIR = build

LIBS += -lcrypto++

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    block/__blockchain.cpp \
    network/__websocketserver.cpp \
    database/handler/__dbhandler.cpp \
    database/structure/__blockdbs.cpp \
    database/provider/__blockprovider.cpp \
    widget/__blockgroupbox.cpp \
    __staticvalue.cpp \
    network/__dispatcher.cpp \
    database/structure/__nodedbs.cpp \
    database/provider/__nodeprovider.cpp \
    network/__iso.cpp \
    report/__reportengin.cpp

HEADERS += \
        mainwindow.h \
    block/__blockchain.h \
    network/__websocketserver.h \
    database/handler/__dbhandler.h \
    database/structure/__blockdbs.h \
    database/provider/__blockprovider.h \
    widget/__blockgroupbox.h \
    __staticvalue.h \
    network/__dispatcher.h \
    database/structure/__nodedbs.h \
    database/provider/__nodeprovider.h \
    network/__iso.h \
    report/__reportengin.h

FORMS += \
        mainwindow.ui
