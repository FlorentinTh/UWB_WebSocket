QT -= gui

QT += serialport

CONFIG += c++11 console
CONFIG -= app_bundle

win32:RC_ICONS += UWB_WebSocket.ico

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += ASIO_STANDALONE

SOURCES += \
        main.cpp \
        uwbradar.cpp \
        websocketserver.cpp

INCLUDEPATH += includes

win32 {
    DEFINES += _WEBSOCKETPP_MINGW_THREAD_
    LIBS += -lwsock32 -lws2_32
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    uwbradar.h \
    websocketserver.h

contains(QT_ARCH, i386) {
    DEFINES += _WEBSOCKETPP_MINGW_THREAD_
    LIBS += -lwsock32 -lws2_32 -L$$PWD/libs/win32/ -lModuleConnector
    INCLUDEPATH += $$PWD/libs/win32
    DEPENDPATH += $$PWD/libs/win32
} else {
    LIBS += -L$$PWD/libs/win64/ -lModuleConnector
    INCLUDEPATH += $$PWD/libs/win64
    DEPENDPATH += $$PWD/libs/win64
}

unix:!macx: LIBS += -L$$PWD/libs/unix/ -lModuleConnector

INCLUDEPATH += $$PWD/libs/unix
DEPENDPATH += $$PWD/libs/unix
