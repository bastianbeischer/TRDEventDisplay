#####################################################################
## CVS Information
## $Id: EventDisplay.pro,v 1.7 2010/08/18 19:00:49 beischer Exp $
#################################################################

# General information
TEMPLATE    = app
TARGET      = EventDisplay
QT          += gui

# Enable Qt linkage & compiler warnings
CONFIG     += qt warn_on

# Possibly enable a debug build
CONFIG     += debug

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
          src/DataManager.cc \
          src/EventDisplayScene.cc \
          src/MainWindow.cc \
          src/StrawTube.cc \
          src/ZoomableView.cc

HEADERS = include/DataManager.hh \
          include/EventDisplayScene.hh \
          include/MainWindow.hh \
          include/StrawTube.hh \
          include/ZoomableView.hh

# Setup ROOT paths and compiler/linker flags
include(ROOT.pri)

# Hack needed for my arch linux because of its Qt installation
QMAKE_LFLAGS -= -Wl,--as-needed