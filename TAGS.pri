#####################################################################
## CVS Information
## $Id: TAGS.pri,v 1.1 2010/08/23 13:31:05 beischer Exp $
#################################################################

# TAGS file generation for emacs tags
exists($$system(which etags)) {
  FILES = include/*.hh TrdEvent/*.hh *.cc src/*.cc TrdEvent/*.cc

  TAGS.target = TAGS
  TAGS.commands = etags -o $$TAGS.target $$FILES
  TAGS.depends = $$FILES
  
  QMAKE_EXTRA_TARGETS += $$TAGS.target
  QMAKE_CLEAN += $$TAGS.target
  PRE_TARGETDEPS += $$TAGS.target
}
