# $Header: W:/Projects/OCL/Samples/DragSamp/Borland/rcs/BORLAND.MAK 1.50 1996/08/11 23:47:56 B.STEIN Release $

!include $(OCLSAMP)\COMMON.INC
!include ..\DRAGSAMP.INC

MAKEDEP = BORLAND.MAK
CFLAGS = $(S_BORLAND_COMPILE)
LFLAGS = $(S_BORLAND_LINK)

{..\Source}.cpp.obj:
   bcc $(CFLAGS) %s

.\DRAGSAMP.EXE: .\DRAGSAMP.obj .\DRAGSAMP.res {$(LIB)}OCLB.lib $(MAKEDEP)
   tlink $(LFLAGS) .\DRAGSAMP.obj, .\DRAGSAMP.exe,, OCLB C2MT OS2
   rc .\DRAGSAMP.res .\DRAGSAMP.EXE

!include ..\DRAGSAMP.DEP
