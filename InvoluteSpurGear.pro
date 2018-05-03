QT       += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = InvoluteSpurGear
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        widget.cpp \
        SpurGear.cpp \

HEADERS += \
        widget.h \
        SpurGear.h \
        utils/Radian.h \

INCLUDEPATH += third-party/include \

FORMS += \
        Main.ui


unix|win32: LIBS += D:\opencv-win\opencv\build\x64\vc15\lib\opencv_world341.lib
unix|win32: LIBS += D:\opencv-win\opencv\build\x64\vc15\lib\opencv_world341d.lib

INCLUDEPATH += "C:\Program Files (x86)\Windows Kits\10\Include\10.0.16299.0\ucrt"
        LIBS += -L"C:/Program Files (x86)/Windows Kits/10/Lib/10.0.16299.0/ucrt/x64"
