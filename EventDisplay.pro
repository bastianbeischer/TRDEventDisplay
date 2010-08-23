#####################################################################
## CVS Information
## $Id: EventDisplay.pro,v 1.12 2010/08/23 13:31:05 beischer Exp $
#################################################################

TEMPLATE = subdirs
SUBDIRS += TrdEvent main.pro
CONFIG += ordered

# Docmentation
include(DOC.pri)
# Generate emacs tags
include(TAGS.pri)
