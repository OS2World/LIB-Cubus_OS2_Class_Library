# $Header: W:/Projects/OCL/Samples/NextHand/IBM/rcs/VA30.MAK 1.50 1996/08/11 23:48:42 B.STEIN Release $

!include $(OCLSAMP)\COMMON.INC
!include ..\NEXTHAND.INC

MAKEDEP = VA30.MAK
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
    {$(LIB)}OCLVAI.LIB \
    $(MAKEDEP)
      icc @<<
/Tdp /Q /O /Gm /G5 
/B" /pmtype:pm /base:0x10000 /noe"
 /Fe .\NEXTHAND.EXE
 OCLVAI.LIB 
 .\NextCommand.obj
 .\NextHand.obj
 .\NextBarDlg.obj
 .\NextBarEvent.obj
<<
      rc .\NextHand.res .\NEXTHAND.EXE

.\NEXTHAND.HLP: \
   ..\Source\NextHand.ipf \
   $(MAKEDEP)
     ipfc ..\Source\NextHand.ipf .\NEXTHAND.HLP

!include ..\NEXTHAND.DEP
