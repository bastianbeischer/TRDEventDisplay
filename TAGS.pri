# TAGS file generation for emacs tags
exists($$system(which etags)) {
  FILES = include/*.hh TrdEvent/*.hh *.cc src/*.cc TrdEvent/*.cc

  TAGS.target = TAGS
  TAGS.commands = etags -o $$TAGS.target $$FILES
  TAGS.depends = $$FILES
  
  QMAKE_EXTRA_TARGETS += $$TAGS.target
  QMAKE_CLEAN += $$TAGS.target
  QMAKE_DISTCLEAN += $$TAGS.target
  PRE_TARGETDEPS += $$TAGS.target
}
