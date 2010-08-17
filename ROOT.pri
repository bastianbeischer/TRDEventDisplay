ROOT_INCLUDE_DIR = $$system(root-config --incdir)

# Check for ROOT
!exists ($$ROOT_INCLUDE_DIR/TObject.h) {
    error("Could NOT find ROOT!")
}

include($$ROOT_INCLUDE_DIR/rootcint.pri)
LIBS += $$system(root-config --libs)
INCLUDEPATH += $$ROOT_INCLUDE_DIR
