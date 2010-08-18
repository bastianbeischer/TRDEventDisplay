#################################################################
## CVS Information
## $Id: TrdEvent.pro,v 1.2 2010/08/18 18:22:01 beischer Exp $
#################################################################

TEMPLATE = lib
TARGET = TrdEvent
QT -= gui

CONFIG += debug

# Seperate source & build dirs
DESTDIR     = .#
OBJECTS_DIR = .#.tmp
MOC_DIR     = .#.tmp
UI_DIR      = .#.tmp
RCC_DIR     = .#.tmp

CREATE_ROOT_DICT_FOR_CLASSES = TrdRawHitR.hh \
                               AccRawHitR.hh \
                               TrdRawRun.hh \
                               TrdRawEvent.hh
SOURCES = TrdRawHitR.cc \
          AccRawHitR.cc \
          TrdRawRun.cc \
          TrdRawEvent.cc \
          TrdHitRZD.cc

HEADERS += $$CREATE_ROOT_DICT_FOR_CLASSES \
           TrdHitRZD.hh
   
include(../ROOT.pri)
