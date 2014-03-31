# $Header: W:/Projects/OCL/Samples/DragSamp/Watcom/rcs/WATCOM.MAK 1.50 1996/08/11 23:47:59 B.STEIN Release $

!include $(OCLSAMP)\COMMON.INC
!include ..\DRAGSAMP.INC

MAKEDEP = WATCOM.MAK
CFLAGS = $(WATCOM_COMPILE)
LFLAGS = $(WATCOM_LINK)

{..\Source}.cpp.obj:
   wpp386 $(CFLAGS) %s

.\DRAGSAMP.exe: DRAGSAMP.obj DRAGSAMP.res {$(LIB)}OCLWI.lib $(MAKEDEP)
   wlink $(LFLAGS) libr OCLWI NAME .\DRAGSAMP.EXE FIL .\DRAGSAMP.obj
   rc .\DRAGSAMP.res .\DRAGSAMP.exe

!include ..\DRAGSAMP.DEP