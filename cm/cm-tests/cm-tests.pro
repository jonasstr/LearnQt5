include(../qmake-target-platform.pri)
include(../qmake-destination-path.pri)

QT += testlib
QT -= gui

TARGET = client-tests
TEMPLATE = app

CONFIG += c++14
CONFIG += console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += src \
    ../cm-lib/src

HEADERS += \
    src/test-suite.h \
    src/controllers/master-controller-tests.h \
    src/data/int-decorator-tests.h \
    src/data/datetime-decorator-tests.h \
    src/data/enumerator-decorator-tests.h \
    src/data/string-decorator-tests.h

SOURCES += src/test-suite.cpp \
    src/controllers/master-controller-tests.cpp \
    src/test-main.cpp \
    src/data/int-decorator-tests.cpp \
    src/data/datetime-decorator-tests.cpp \
    src/data/enumerator-decorator-tests.cpp \
    src/data/string-decorator-tests.cpp

DESTDIR = $$PWD/../build/$$DESTINATION_PATH
OBJECTS_DIR = $$PWD/../build/$$DESTINATION_PATH/.obj
MOC_DIR = $$PWD/../build/$$DESTINATION_PATH/.moc
RCC_DIR = $$PWD/../build/$$DESTINATION_PATH/.qrc
UI_DIR = $$PWD/../build/$$DESTINATION_PATH/.ui

LIBS += -L$$PWD/../build/$$DESTINATION_PATH -lcm-lib
