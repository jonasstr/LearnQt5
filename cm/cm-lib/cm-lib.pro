include(../qmake-target-platform.pri)
include(../qmake-destination-path.pri)

QT -= gui
QT += sql

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
    src/data/int-decorator.cpp \
    src/data/enumerator-decorator.cpp \
    src/data/datetime-decorator.cpp \
    src/data/data-decorator.cpp \
    src/data/string-decorator.cpp \
    src/data/entity.cpp \
    src/models/address.cpp \
    src/models/appointment.cpp \
    src/models/contact.cpp \
    src/controllers/database-controller.cpp

HEADERS += src/models/client.h \
        src/cm-lib_global.h \
        src/controllers/master-controller.h \
    src/controllers/navigation-controller.h \
    src/framework/command.h \
    src/controllers/command-controller.h \
    src/data/string-decorator.h \
    src/data/int-decorator.h \
    src/data/enumerator-decorator.h \
    src/data/datetime-decorator.h \
    src/data/data-decorator.h \
    src/data/entity.h \
    src/data/entity-collection.h \
    src/models/address.h \
    src/models/appointment.h \
    src/models/contact.h \
    src/controllers/i-database-controller.h \
    src/controllers/database-controller.h

DESTDIR = $$PWD/../build/$$DESTINATION_PATH
OBJECTS_DIR = $$PWD/../build/$$DESTINATION_PATH/.obj
MOC_DIR = $$PWD/../build/$$DESTINATION_PATH/.moc
RCC_DIR = $$PWD/../build/$$DESTINATION_PATH/.qrc
UI_DIR = $$PWD/../build/$$DESTINATION_PATH/.ui
