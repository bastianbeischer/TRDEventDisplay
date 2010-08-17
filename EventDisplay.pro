# General information
TEMPLATE    = app
TARGET      = EventDisplay
QT          += gui

# Enable Qt linkage & compiler warnings
CONFIG     += qt warn_on

# Possibly enable a debug build
CONFIG    += debug

# Seperate source & build dirs
DESTDIR     = ./
OBJECTS_DIR = ./.tmp
MOC_DIR     = ./.tmp
UI_DIR      = ./.tmp
RCC_DIR     = ./.tmp

# Setup additional paths
DEPENDPATH += . include src ui TrdEvent
INCLUDEPATH += . include TrdEvent
LIBS += -L./TrdEvent -lTrdEvent


# Forms, sources and headers
FORMS = ui/EventDisplayForm.ui
SOURCES = main.cc \
          src/GraphicsView.cc \
          src/MainWindow.cc \
          src/Scene.cc

HEADERS = include/MainWindow.hh \
          include/GraphicsView.hh \
          include/Scene.hh

# Setup ROOT paths and compiler/linker flags
include(ROOT.pri)

# Hack needed for my arch linux because of its Qt installation
QMAKE_LFLAGS -= -Wl,--as-needed