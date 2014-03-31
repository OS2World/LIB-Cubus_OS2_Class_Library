# $Header: W:/Projects/OCL/Samples/GTakPM/IBM/rcs/VA30.MAK 1.50 1996/08/11 23:48:05 B.STEIN Release $

!include $(OCLSAMP)\COMMON.INC
!include ..\GTAKPM.INC

MAKEDEP = VA30.MAK
CFLAGS = $(S_ICC_COMPILE)
LFLAGS = $(S_ICC_LINK)

{..\Source}.cpp.obj:
  icc $(CFLAGS) %s


.\GTAKPM.EXE: \
  .\GTPMMain.obj \
  .\GTPMException.obj \
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
  {$(LIB)}OCLVAI.lib \
  $(MAKEDEP)
    icc @<<
$(LFLAGS)
/FeGTAKPM.EXE 
 OCLVAI.lib 
 .\GTPMMain.obj
 .\GTPMException.obj
 .\GTPMApp.obj
 .\GTPMWin.obj
 .\GTPMWinControl.obj
 .\GTPMWinCommand.obj
 .\FilesCnr.obj 
 .\DrivesCnr.obj
 .\Tape.obj
 .\Backup.obj
 .\Restore.obj
 ..\Source\GTakPM.def
<<
   rc $(RCPACK) .\GTakPM.res GTAKPM.EXE

!include ..\GTAKPM.DEP
