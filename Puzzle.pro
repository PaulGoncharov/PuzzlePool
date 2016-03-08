#-------------------------------------------------
#
# Project created by QtCreator 2016-02-23T16:05:51
#
#-------------------------------------------------

QT       += core gui opengl multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Puzzle
TEMPLATE = app
QMAKE_CXXFLAGS += -std=gnu++11 -Wall -Wnon-virtual-dtor

SOURCES += main.cpp\
        mainwindow.cpp \
    listdialog.cpp \
    src/SoundManager/sounddescription.cpp \
    src/SoundManager/soundmanager.cpp \
    src/Canvas/Canvas.cpp \
    src/Canvas/texture.cpp \
    src/Game/Game.cpp \
    src/Game/Grid.cpp \
    src/Game/mixer.cpp \
    src/Game/swappinganimation.cpp \

INCLUDEPATH += include

HEADERS  += mainwindow.h \
    include/SoundManager/sounddescription.h \
    include/SoundManager/soundmanager.h \
    include/Canvas/Canvas.h \
    include/Canvas/texture.h \
    include/Game/Game.h \
    include/Game/Grid.h \
    include/Game/minigameinterface.h \
    include/Game/mixer.h \
    include/Game/swappinganimation.h \
    listdialog.h

FORMS    += mainwindow.ui \
    listdialog.ui

LIBS += -lopengl32

RESOURCES += \
    res.qrc

