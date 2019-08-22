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
        src/controllers/master-controller.cpp \
    src/framework/command.cpp \
    src/controllers/command-controller.cpp \
    data/int-decorator.cpp \
    data/enumerator-decorator.cpp \
    data/datetime-decorator.cpp \
    data/data-decorator.cpp \
    data/string-decorator.cpp \
    data/entity.cpp

HEADERS += src/models/client.h \
        src/cm-lib_global.h \
        src/controllers/master-controller.h \
    src/controllers/navigation-controller.h \
    src/framework/command.h \
    src/controllers/command-controller.h \
    data/string-decorator.h \
    data/int-decorator.h \
    data/enumerator-decorator.h \
    data/datetime-decorator.h \
    data/data-decorator.h \
    data/entity.h \
    data/entity-collection.h

DESTDIR = $$PWD/../build/$$DESTINATION_PATH
OBJECTS_DIR = $$PWD/../build/$$DESTINATION_PATH/.obj
MOC_DIR = $$PWD/../build/$$DESTINATION_PATH/.moc
RCC_DIR = $$PWD/../build/$$DESTINATION_PATH/.qrc
UI_DIR = $$PWD/../build/$$DESTINATION_PATH/.ui
