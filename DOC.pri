#####################################################################
## CVS Information
## $Id: DOC.pri,v 1.4 2010/08/30 16:36:14 beischer Exp $
#################################################################

# Generation of documentation
exists($$system(which doxygen)) {
  FILES = EventDisplay.doxy include/*.hh TrdEvent/*.hh *.cc src/*.cc TrdEvent/*.cc

  doc.target = doc
  doc.commands = doxygen EventDisplay.doxy  
  doc.depends = $$FILES

  QMAKE_EXTRA_TARGETS += $$doc.target
  QMAKE_CLEAN += "-r $$doc.target"
  QMAKE_DISTCLEAN += "-r $$doc.target"
#  PRE_TARGETDEPS += $$doc.target
}
