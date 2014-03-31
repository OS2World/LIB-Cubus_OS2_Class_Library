# $Header: W:/Projects/OCL/Samples/GTakPM/Metaware/rcs/METAWARE.MAK 1.50 1996/08/11 23:48:05 B.STEIN Release $

!include $(OCLSAMP)\COMMON.INC
!include ..\GTAKPM.INC

MAKEDEP = METAWARE.MAK
CFLAGS  = $(S_HIGHCPP_COMPILE)
LFLAGS  = $(S_HIGHCPP_LINK)

{..\Source}.cpp.obj:
  @echo Compiling: $(@B) 
  @hc $(CFLAGS) %s

.\GTAKPM.EXE: \
  .\GTPMException.obj \
  .\GTPMMain.obj \
  .\GTPMApp.obj \
  .\GTPMWin.obj \
  .\GTPMWinControl.obj \
  .\GTPMWinCommand.obj \
  .\FilesCnr.obj \
  .\DrivesCnr.obj \
  .\Tape.obj \
  .\Backup.obj \
  .\Restore.obj \
  .\GTakPM.res \
  {$(LIB)}OCLM.LIB \
  $(MAKEDEP)
   @echo Linking... 
   @link386 @<<
/NOE /NOI /NOLOGO /DE +
.\GTPMException.obj +
.\GTPMMain.obj +
.\GTPMApp.obj +
.\GTPMWin.obj +
.\GTPMWinControl.obj +
.\GTPMWinCommand.obj +
.\FilesCnr.obj +
.\DrivesCnr.obj +
.\Tape.obj +
.\Backup.obj +
.\Restore.obj +
E:\HCOS2\LIB\STARTUP.OBJ
.\GTAKPM.EXE 
        
OS2386.LIB +
HCNA.LIB +
HCT.LIB +
HCCT.LIB +
OCLM.LIB
..\Source\GTAKPM.DEF
;
<<
   @rc $(RCPACK) GTAKPM.RES GTAKPM.EXE 

!include ..\GTAKPM.DEP
