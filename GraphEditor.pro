# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = GraphEditor

CONFIG += sailfishapp

HEADERS += src/Model/Graph.h \
    src/ViewModel/GraphViewModel.h \
    src/ViewModel/MainViewModel.h \
    src/ViewModel/VertexListViewModel.h

SOURCES += src/GraphEditor.cpp \
    src/Model/Graph.cpp \
    src/ViewModel/GraphViewModel.cpp \
    src/ViewModel/MainViewModel.cpp \
    src/ViewModel/VertexListViewModel.cpp

DISTFILES += qml/GraphEditor.qml \
    qml/components/Line.qml \
    qml/components/Vertex.qml \
    qml/cover/CoverPage.qml \
    qml/pages/AlgorithmsPage.qml \
    qml/pages/CliqueViewPage.qml \
    qml/pages/MainPage.qml \
    rpm/GraphEditor.changes.in \
    rpm/GraphEditor.changes.run.in \
    rpm/GraphEditor.spec \
    rpm/GraphEditor.yaml \
    translations/*.ts \
    GraphEditor.desktop

SAILFISHAPP_ICONS = 86x86 108x108 128x128 172x172

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n

# German translation is enabled as an example. If you aren't
# planning to localize your app, remember to comment out the
# following TRANSLATIONS line. And also do not forget to
# modify the localized app name in the the .desktop file.
TRANSLATIONS += translations/GraphEditor-de.ts
