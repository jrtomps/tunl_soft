#!/bin/tcsh
rootcint -f DetectorClassDict.cc -c DetectorClass.hh DetectorClassLinkDef.h
g++ -c -o DetectorClassDict.o DetectorClassDict.cc `root-config --cflags`
g++ -c -o DetectorClass.o DetectorClass.cc `root-config --cflags` -I../tunl_soft/source/include
g++ -shared -o libDetectorClass.so DetectorClass.o DetectorClassDict.o `root-config --glibs`
rm *.o
