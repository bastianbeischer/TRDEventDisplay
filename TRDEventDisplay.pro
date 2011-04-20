TEMPLATE = subdirs
SUBDIRS += TrdEvent main.pro
CONFIG += ordered

# Docmentation, build with "make doc"
include(DOC.pri)
