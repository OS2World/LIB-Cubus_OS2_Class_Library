# $Header: W:/Projects/OCL/Samples/NextHand/Metaware/rcs/METAWARE.MAK 1.50 1996/08/11 23:48:42 B.STEIN Release $

!include $(OCLSAMP)\COMMON.INC
!include ..\NEXTHAND.INC

MAKEDEP = METAWARE.MAK
CFLAGS  = $(S_HIGHCPP_COMPILE)
LFLAGS  = $(S_HIGHCPP_LINK)

{..\Source}.cpp.obj:
  @echo Compiling: $(@B) 
  @hc $(CFLAGS) %s

.\NEXTHAND.EXE: \
    .\NextCommand.obj \
    .\NextHand.obj \
    .\NextBarDlg.obj \
    .\NextBarEvent.obj \
    .\NextHand.res \
    {$(LIB)}OCLM.LIB \
    $(MAKEDEP)
   @echo Linking... 
   @link386 @<<
/NOE /NOI /NOLOGO /DE +
.\NextCommand.obj +
.\NextHand.obj +
.\NextBarDlg.obj +
.\NextBarEvent.obj +
E:\HCOS2\LIB\STARTUP.OBJ
.\NEXTHAND.EXE 
        
OS2386.LIB +
HCNA.LIB +
HCT.LIB +
HCCT.LIB +
OCLM.LIB
..\Source\NEXTHAND.DEF
;
<<
   @rc $(RCPACK) NEXTHAND.RES NEXTHAND.EXE 

!include ..\NEXTHAND.DEP
