TEMPLATE = subdirs

SUBDIRS += \
    cm-lib \
    cm-ui \
    cm-tests

cm-ui.depends = cm-lib
cm-tests.depends = cm-lib
