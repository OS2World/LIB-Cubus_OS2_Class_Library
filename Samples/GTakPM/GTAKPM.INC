# $Header: W:/Projects/OCL/Samples/GTakPM/rcs/GTAKPM.INC 1.50 1996/08/11 23:48:04 B.STEIN Release $

.all: .\GTAKPM.EXE

.SUFFIXES:
.SUFFIXES: .rc .cpp

{..\Source}.rc.res:
  rc -r %s %|fF.RES

