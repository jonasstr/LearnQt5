include(../qmake-target-platform.pri)
include(../qmake-destination-path.pri)

QT -= gui

TARGET = cm-lib
TEMPLATE = lib

CONFIG += c++14

DEFINES += CMLIB_LIBRARY \
        QT_DEPRECATED_WARNINGS

INCLUDEPATH += src

SOURCES += src/models/client.cpp \
        src/controllers/master-controller.cpp

HEADERS += src/models/client.h \
        src/cm-lib_global.h \
        src/controllers/master-controller.h \
    src/controllers/navigation-controller.h

DESTDIR = $$PWD/../build/$$DESTINATION_PATH
OBJECTS_DIR = $$PWD/../build/$$DESTINATION_PATH/.obj
MOC_DIR = $$PWD/../build/$$DESTINATION_PATH/.moc
RCC_DIR = $$PWD/../build/$$DESTINATION_PATH/.qrc
UI_DIR = $$PWD/../build/$$DESTINATION_PATH/.ui
