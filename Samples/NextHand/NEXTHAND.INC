# $Header: W:/Projects/OCL/Samples/NextHand/rcs/NEXTHAND.INC 1.50 1996/08/11 23:48:40 B.STEIN Release $

.all: .\NEXTHAND.EXE

.SUFFIXES:

.SUFFIXES: .cpp .rc

{..\Source}.rc.res:
      rc -r %s %|fF.RES

