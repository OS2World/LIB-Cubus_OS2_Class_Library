# $Header: W:/Projects/OCL/Samples/NextHand/EMX/rcs/EMX.MAK 1.50 1996/08/11 23:48:41 B.STEIN Release $

!include $(OCLSAMP)\COMMON.INC
!include ..\NEXTHAND.INC

MAKEDEP = EMX.MAK
CFLAGS = $(S_EMX_COMPILE)
LFLAGS = $(S_EMX_LINK)

{..\Source}.cpp.obj:
    gcc $(CFLAGS) %s

.\NEXTHAND.EXE: \
  .\NextCommand.obj \
  .\NextBarDlg.obj \
  .\NextBarEvent.obj \
  .\NextHand.obj \
  .\NextHand.res \
  $(OCL)\LIB\OCLEMXI.LIB \
  $(MAKEDEP)
   rc -r -I E:\EMX\INCLUDE ..\Source\Nexthand.rc 
   gcc $(LFLAGS) \
.\NEXTHAND.EXE \
.\NextCommand.obj \
.\NextBarDlg.obj \
.\NextBarEvent.obj \
.\NextHand.obj \
..\Source\Nexthand.def \
..\Source\NextHand.res \
-L$(OCL)\LIB -loclemxi -lstdcpp

!include ..\NEXTHAND.DEP
