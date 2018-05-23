#-------------------------------------------------
#
# Project created by QtCreator 2017-12-21T13:53:33
#
#-------------------------------------------------

QT       -= gui
QT       += serialport

TARGET = DriverGC
TEMPLATE = lib

DEFINES += DRIVERGC_LIBRARY

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
        DriverGC.cpp \
    Protocol.cpp \
    Functions.cpp \
    Communication.cpp \
    WaitForSignalHelper.cpp \
    Convert.cpp \
    Debug.cpp

HEADERS += \
        DriverGC.h \
        drivergc_global.h \ 
    Protocol.h \
    Functions.h \
    Communication.h \
    WaitForSignalHelper.h \
    Convert.h \
    Debug.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
