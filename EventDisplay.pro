#####################################################################
## CVS Information
## $Id: EventDisplay.pro,v 1.14 2010/08/24 12:10:46 beischer Exp $
#################################################################

TEMPLATE = subdirs
SUBDIRS += TrdEvent main.pro
CONFIG += ordered

# Docmentation
include(DOC.pri)