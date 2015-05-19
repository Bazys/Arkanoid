#-------------------------------------------------
#
# Project created by QtCreator 2015-03-28T14:50:27
#
#-------------------------------------------------

QT += core gui opengl declarative

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets svg

TARGET = Arkanoid_
TEMPLATE = app


SOURCES += main.cpp \
    gamescene.cpp \
    gameview.cpp \
    ball.cpp \
    pad.cpp \
    brick.cpp

HEADERS  += \
    gamescene.h \
    gameview.h \
    ball.h \
    pad.h \
    brick.h

RESOURCES += \
    ball.qrc
