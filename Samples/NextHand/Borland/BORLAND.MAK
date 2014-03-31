# $Header: W:/Projects/OCL/Samples/NextHand/Borland/rcs/BORLAND.MAK 1.50 1996/08/11 23:48:41 B.STEIN Release $

!include $(OCLSAMP)\COMMON.INC
!include ..\NEXTHAND.INC

MAKEDEP = BORLAND.MAK
CFLAGS = $(S_BORLAND_COMPILE)
LFLAGS = $(S_BORLAND_LINK)

{..\Source}.cpp.obj:
   bcc $(CFLAGS) %s

.\NEXTHAND.EXE: \
    .\NextCommand.obj \
    .\NextBarDlg.obj \
    .\NextBarEvent.obj \
    .\NextHand.obj \
    .\NextHand.res \
    {$(LIB)}OCLB.LIB $(MAKEDEP)
    tlink $(LFLAGS) \
.\NextCommand.obj \
.\NextHand.obj \
.\NextBarDlg.obj \
.\NextBarEvent.obj, \
NEXTHAND.EXE,,  OCLB C2MT OS2
    rc .\NextHand.res .\NEXTHAND.EXE

!include ..\NEXTHAND.DEP
