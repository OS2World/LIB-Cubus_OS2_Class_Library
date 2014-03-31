# $Header: W:/Projects/OCL/Samples/GTakPM/Borland/rcs/BORLAND.MAK 1.50 1996/08/11 23:48:04 B.STEIN Release $

!include $(OCLSAMP)\COMMON.INC
!include ..\GTAKPM.INC

MAKEDEP = BORLAND.MAK
CFLAGS = $(S_BORLAND_COMPILE)
LFLAGS = $(S_BORLAND_LINK)

{..\Source}.cpp.obj:
   @bcc $(CFLAGS) %s


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
  {$(LIB)}OCLB.LIB \
  $(MAKEDEP)
   @echo Linking... 
   tlink $(LFLAGS) \
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
.\Restore.obj , GTAKPM.EXE ,, OCLB C2MT OS2, ..\Source\GTAKPM.DEF
   @rc $(RCPACK) .\GTAKPM.RES GTAKPM.EXE 

!include ..\GTAKPM.DEP
