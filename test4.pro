#-------------------------------------------------
#
# Project created by QtCreator 2016-11-21T22:06:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test4
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    scale.cpp \
    vec_extr.cpp \
    sfml_objects.cpp \
    imgbaseinfo.cpp \
    SevenBitComp.cpp \
    vec_bmp.cpp \
    RLE_c.cpp

HEADERS  += mainwindow.h \
    scale.h \
    vec_extr.h \
    sfml_objects.h \
    imgbaseinfo.h \
    SevenBitComp.h \
    vec_bmp.h \
    RLE_c.h

FORMS    += mainwindow.ui


LIBS += -L$$PWD/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1/lib



INCLUDEPATH += $$PWD/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1/include
DEPENDPATH += $$PWD/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1/include

QMAKE_CXXFLAGS +=-static-libgcc -static-libstdc++
CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

RESOURCES += \
    resources.qrc

