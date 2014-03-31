@echo off
echo Executing OCL Complete Build on:
echo --- jiri.liva.de P100/64MB running OS/2 Warp Connect ---

e:
cd\ocl\va30
build va30.mak

cd\ocl\samples\balloons\ibm
build va30.mak
cd\ocl\samples\collections\ibm
build va30.mak
cd\ocl\samples\critics\ibm
build va30.mak
cd\ocl\samples\dragsamp\ibm
build va30.mak
cd\ocl\samples\editor\ibm
build va30.mak
cd\ocl\samples\gtakpm\ibm
build va30.mak
cd\ocl\samples\iterators\ibm
build va30.mak
cd\ocl\samples\listbox\ibm
build va30.mak
cd\ocl\samples\menus\ibm
build va30.mak
cd\ocl\samples\nexthand\ibm
build va30.mak
cd\ocl\samples\procstat\ibm
build va30.mak
cd\ocl\samples\template\ibm
build va30.mak
cd\ocl\samples\valueset\ibm
build va30.mak

set path=e:\emx\bin;%PATH%
cd\ocl\emx
build emx.mak

set path=e:\bc20\bin;%PATH%
set include=%bcinc%
set lib=%bclib%
cd\ocl\borland
build borland.mak

set include=%wcinc%
set lib=%wclib%
cd\ocl\watcom
build watcom.mak

set lib=e:\hcos2\lib;%LIB%
cd\ocl\metaware
build metaware.mak

icc /Tl-
set include=E:\TK30\H;L:\IBM;%INCLUDE%
set lib=E:\TK30\lib;L:\IBM;%LIB%
set LINK386=/e:2 /align:1 /nos /exepack /packd /packc
set RCPACK=-x:2
set beginlibpath=P:\PATHS
set PATH=P:\PATHS;%PATH%
set DPATH=P:\PATHS;%DPATH%
call d:\tvfs\initcs21.cmd

cd\ocl\ibm
build ibm.mak

icc /Tl-
d:\tvfs\tvfsinit.cmd
 
