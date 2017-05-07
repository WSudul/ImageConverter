#-------------------------------------------------
#
# Project created by QtCreator 2017-01-03T16:29:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GKiM
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    RLE_c.cpp \
    vec_bmp.cpp \
    vec_extr.cpp \
    sevenbitcomp.cpp \
    scale.cpp \
    SevenBitComp_old.cpp \
    imgbaseinfo.cpp \
    sfml_objects.cpp

HEADERS  += mainwindow.h \
    vec_bmp.h \
    RLE_c.h \
    vec_extr.h \
    sevenbitcomp.h \
    SevenBitComp_old.h \
    imgbaseinfo.h \
    sfml_objects.h \
    scale.h

FORMS    += mainwindow.ui


LIBS += -LC:/Users/Blazejek/Desktop/QT/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1/lib



INCLUDEPATH += C:/Users/Blazejek/Desktop/QT/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1/include
DEPENDPATH += C:/Users/Blazejek/Desktop/QT/SFML-2.4.1-windows-gcc-6.1.0-mingw-32-bit/SFML-2.4.1/include


CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

RESOURCES += \
    resources.qrc
