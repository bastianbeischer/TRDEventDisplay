#####################################################################
## CVS Information
## $Id: EventDisplay.pro,v 1.15 2010/08/24 14:43:10 beischer Exp $
#################################################################

TEMPLATE = subdirs
SUBDIRS += TrdEvent main.pro
CONFIG += ordered

# Docmentation, build with "make doc"
include(DOC.pri)

# included here so we can "make TAGS"
include(TAGS.pri)