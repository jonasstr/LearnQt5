include(../qmake-target-platform.pri)
include(../qmake-destination-path.pri)

QT += qml quick quickcontrols2

TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

INCLUDEPATH += source \
            ../cm-lib/src

SOURCES += src/main.cpp
RESOURCES += views.qrc

#QML_IMPORT_PATH += $$PWD

DESTDIR = $$PWD/../build/$$DESTINATION_PATH
OBJECTS_DIR = $$PWD/../build/$$DESTINATION_PATH/.obj
MOC_DIR = $$PWD/../build/$$DESTINATION_PATH/.moc
RCC_DIR = $$PWD/../build/$$DESTINATION_PATH/.qrc
UI_DIR = $$PWD/../build/$$DESTINATION_PATH/.ui

LIBS += -L$$PWD/../build/$$DESTINATION_PATH -lcm-lib
