#####################################################################
## CVS Information
## $Id: DOC.pri,v 1.2 2010/08/23 13:57:49 beischer Exp $
#################################################################

# Generation of documentation
exists($$system(which doxygen)) {
  FILES = EventDisplay.doxy include/*.hh TrdEvent/*.hh *.cc src/*.cc TrdEvent/*.cc

  doc.target = doc
  doc.commands = doxygen EventDisplay.doxy  
  doc.depends = $$FILES

  QMAKE_EXTRA_TARGETS += $$doc.target
  QMAKE_CLEAN += -r $$doc.target
  QMAKE_DISTCLEAN += -r $$doc.target
}
