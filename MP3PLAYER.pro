
QT       += core gui multimedia webkitwidgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MP3PLAYER
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    songdialog.cpp \
    music.cpp \
    aboutartist.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    songdialog.h \
    music.h \
    aboutartist.h

FORMS    += mainwindow.ui \
    dialog.ui \
    songdialog.ui \
    aboutartist.ui

RESOURCES +=
