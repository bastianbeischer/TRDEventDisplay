#################################################################
## CVS Information
## $Id: ROOT.pri,v 1.7 2010/08/18 18:22:01 beischer Exp $
#################################################################

ROOT_INCLUDE_DIR = $$system(root-config --incdir)
ROOT_LIB_DIR = $$system(root-config --libdir)

# Check for ROOT
!exists ($$ROOT_INCLUDE_DIR/TObject.h) {
    error("Could NOT find ROOT!")
}

LIBS += -L$$ROOT_LIB_DIR -lCore -lTree -lRIO -lThread -lCint -lNet -lMathCore
INCLUDEPATH += $$ROOT_INCLUDE_DIR
INCLUDEPATH -= /usr/include

!isEmpty( CREATE_ROOT_DICT_FOR_CLASSES ) {
   DICTDEFINES += -DQT_VERSION=0x30000
   QT_VERSION=$$[QT_VERSION]
   contains( QT_VERSION, "^4.*" ) {
     DICTDEFINES -= -DQT_VERSION=0x30000
     DICTDEFINES *= -DQT_VERSION=0x40000
   }

  ROOT_CINT_TARGET = $${TARGET}
  SOURCES	  *= $${ROOT_CINT_TARGET}Dict.cxx 

  rootcint.target       = $${ROOT_CINT_TARGET}Dict.cxx 

  win32:  rootcint.commands    +="$$(ROOTSYS)\bin\rootcint.exe"
  unix:   rootcint.commands    +=$(ROOTSYS)/bin/rootcint

  rootcint.commands    +=  -f $$rootcint.target  -c -p $$DICTDEFINES $(INCPATH) $$CREATE_ROOT_DICT_FOR_CLASSES
  rootcint.depends      = $$CREATE_ROOT_DICT_FOR_CLASSES
  
  rootcintecho.commands = @echo "Generating dictionary $$rootcint.target for $$CREATE_ROOT_DICT_FOR_CLASSES classes"

unix:   QMAKE_EXTRA_UNIX_TARGETS += rootcintecho rootcint 
win32:  QMAKE_EXTRA_WIN_TARGETS  += rootcintecho rootcint 

  QMAKE_CLEAN       +=  $${ROOT_CINT_TARGET}Dict.cxx $${ROOT_CINT_TARGET}Dict.h
}
