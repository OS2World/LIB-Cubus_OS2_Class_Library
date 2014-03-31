# $Header: W:/Projects/OCL/Samples/DragSamp/Metaware/rcs/METAWARE.MAK 1.50 1996/08/11 23:47:57 B.STEIN Release $

!include $(OCLSAMP)\COMMON.INC
!include ..\DRAGSAMP.INC

MAKEDEP = METAWARE.MAK
CFLAGS = $(S_HIGHCPP_COMPILE)
LFLAGS = $(S_HIGHCPP_LINK)

{..\Source}.cpp.obj:
   hc $(CFLAGS) %s

.\DRAGSAMP.exe: DRAGSAMP.obj DRAGSAMP.res {$(LIB)}OCLM.lib $(MAKEDEP)
   hc $(LFLAGS) -l$(OCL)\LIB\OCLM.LIB -o .\DRAGSAMP.EXE .\DRAGSAMP.obj
   rc .\DRAGSAMP.res .\DRAGSAMP.exe

!include ..\DRAGSAMP.DEP
