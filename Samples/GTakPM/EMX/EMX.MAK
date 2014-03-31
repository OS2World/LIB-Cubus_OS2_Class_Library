# $Header: W:/Projects/OCL/Samples/GTakPM/EMX/rcs/EMX.MAK 1.50 1996/08/11 23:48:04 B.STEIN Release $

!include $(OCLSAMP)\COMMON.INC
!include ..\GTAKPM.INC

MAKEDEP = EMX.MAK
CFLAGS = $(S_EMX_COMPILE)
LFLAGS = $(S_EMX_LINK)

{..\Source}.cpp.obj:
  @echo Compiling: $(@B) 
  @gcc $(CFLAGS) %s

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
  {$(LIB)}OCLEMX.lib \
  $(MAKEDEP)
   @echo Linking... 
   @gcc $(LFLAGS) GTAKPM.EXE *.obj ..\Source\GTakPM.def .\GTakPM.res -L$(OCL)\LIB -loclemx -lstdcpp

!include ..\GTAKPM.DEP
