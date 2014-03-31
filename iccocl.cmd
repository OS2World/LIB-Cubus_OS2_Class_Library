@echo off
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
nmake /f ibm.mak

icc /Tl-
d:\tvfs\tvfsinit.cmd
