#####################################################################
## CVS Information
## $Id: main.pro,v 1.3 2010/08/24 12:10:46 beischer Exp $
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

QMAKE_DISTCLEAN += -r $$OBJECTS_DIR

# Setup additional paths
DEPENDPATH += . include src ui TrdEvent
INCLUDEPATH += . include TrdEvent
LIBS += -L./TrdEvent -lTrdEvent

# Forms, sources and headers
FORMS = ui/EventDisplayForm.ui \
        ui/MainForm.ui

SOURCES = main.cc \
          src/ColorScale.cc \
          src/DataManager.cc \
          src/DataWidget.cc \
          src/EventDisplayScene.cc \
          src/EventDisplayWidget.cc \
          src/MainWindow.cc \
          src/StrawTube.cc \
          src/TrdScene.cc \
          src/ZoomableView.cc

HEADERS = include/DataManager.hh \
          include/DataWidget.hh \
          include/ColorScale.hh \
          include/EventDisplayScene.hh \
          include/EventDisplayWidget.hh \
          include/MainWindow.hh \
          include/StrawTube.hh \
          include/TrdScene.hh \
          include/ZoomableView.hh

# Setup ROOT paths and compiler/linker flags
include(ROOT.pri)

# Generate emacs tags
include(TAGS.pri)

# Hack needed for my arch linux because of its Qt installation
QMAKE_LFLAGS -= -Wl,--as-needed
