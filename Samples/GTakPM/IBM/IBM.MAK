# $Header: W:/Projects/OCL/Samples/GTakPM/IBM/rcs/IBM.MAK 1.50 1996/08/11 23:48:04 B.STEIN Release $

!include $(OCLSAMP)\COMMON.INC
!include ..\GTAKPM.INC

MAKEDEP = VA30.MAK
CFLAGS = $(S_ICC_COMPILE)
LFLAGS = $(S_ICC_LINK)

{..\Source}.cpp.obj:
  icc $(CFLAGS) %s


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
  {$(LIB)}OCLII.lib \
  $(MAKEDEP)
    icc @<<
$(LFLAGS)
/FeGTAKPM.EXE 
 OCLII.lib 
 .\GTPMException.obj
 .\GTPMMain.obj
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
