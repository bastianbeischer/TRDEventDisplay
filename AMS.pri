AMSWD = $(AMSWD)
INCLUDEPATH += $${AMSWD}/include

linux-g++ | linux-g++-32 {
  LIBS += $${AMSWD}/lib/linux/ntuple_slc4_PG.so
}

linux-g++-64 {
  LIBS += $${AMSWD}/lib/linuxx8664gcc/ntuple_slc4_PG.so
}

linux-icc | linux-icc-32 {
  LIBS += $${AMSWD}/lib/linuxicc/ntuple_slc4_PG.so
}

linux-icc-64 {
  LIBS += $${AMSWD}/lib/linuxx8664icc/ntuple_slc4_PG.so
}
