#####################################################################
## CVS Information
## $Id: DOC.pri,v 1.1 2010/08/23 13:31:04 beischer Exp $
#################################################################

# Generation of documentation
exists($$system(which doxygen)) {
  FILES = EventDisplay.doxy include/*.hh TrdEvent/*.hh *.cc src/*.cc TrdEvent/*.cc

  doc.target = doc
  doc.commands = doxygen EventDisplay.doxy  
  doc.depends = EventDisplay.doxy $$FILES

  QMAKE_EXTRA_TARGETS += $$doc.target
  QMAKE_CLEAN += -r $$doc.target
  QMAKE_DISTCLEAN += -r $$doc.target
}
