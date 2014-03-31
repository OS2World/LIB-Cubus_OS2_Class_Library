# $Header: W:/Projects/OCL/Samples/NextHand/Watcom/rcs/WATCOM.MAK 1.50 1996/08/11 23:48:46 B.STEIN Release $

!include $(OCLSAMP)\COMMON.INC
!include ..\NEXTHAND.INC

MAKEDEP = WATCOM.MAK
CFLAGS = $(S_WATCOM_COMPILE)
LFLAGS = $(WATCOM_LINK)

{..\Source}.cpp.obj:
   wpp386 $(CFLAGS) %s

.\NEXTHAND.EXE: \
    .\NextCommand.obj \
    .\NextBarDlg.obj \
    .\NextBarEvent.obj \
    .\NextHand.obj \
    .\NextHand.res \
    {$(LIB)}OCLW.LIB $(MAKEDEP)
  wlink $(LFLAGS) @<<
libr OCLWI
NAME .\NEXTHAND.EXE
FIL .\NextCommand.obj , .\NextHand.obj , .\NextBarDlg.obj , .\NextBarEvent.obj
<<
  rc .\NextHand.res .\NEXTHAND.EXE

!include ..\NEXTHAND.DEP

