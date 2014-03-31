# $Header: W:/Projects/OCL/Samples/NextHand/IBM/rcs/IBM.MAK 1.50 1996/08/11 23:48:41 B.STEIN Release $

!include $(OCLSAMP)\COMMON.INC
!include ..\NEXTHAND.INC

MAKEDEP = IBM.MAK
CFLAGS = $(S_ICC_COMPILE)
LFLAGS = $(S_ICC_LINK)

{..\Source}.cpp.obj:
   icc $(CFLAGS) %s

.\NEXTHAND.EXE: \
    .\NextCommand.obj \
    .\NextHand.obj \
    .\NextBarDlg.obj \
    .\NextBarEvent.obj \
    .\NextHand.res \
    {$(LIB)}OCLII.LIB \
    $(MAKEDEP)
      icc @<<
/Tdp /Q /O /Gm /G5 
/B" /pmtype:pm /base:0x10000 /noe"
 /Fe .\NEXTHAND.EXE
 OCLII.LIB 
 .\NextCommand.obj
 .\NextHand.obj
 .\NextBarDlg.obj
 .\NextBarEvent.obj
<<
      rc .\NextHand.res .\NEXTHAND.EXE

.\NEXTHAND.HLP: \
   .\NextHand.ipf \
   $(MAKEDEP)
     ipfc .\Source\NextHand.ipf .\NEXTHAND.HLP

!include ..\NEXTHAND.DEP
