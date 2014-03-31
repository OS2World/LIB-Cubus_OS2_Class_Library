# $Header: W:/Projects/OCL/Samples/GTakPM/Watcom/rcs/WATCOM.MAK 1.50 1996/08/11 23:48:25 B.STEIN Release $

!include $(OCLSAMP)\COMMON.INC
!include ..\GTAKPM.INC

MAKEDEP = WATCOM.MAK
CFLAGS = $(S_WATCOM_COMPILE)
LFLAGS = $(S_WATCOM_LINK)

{..\Source}.cpp.obj:
  @echo Compiling: $(@B) 
  @wpp386 $(CFLAGS) %s

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
  {$(LIB)}OCLW.LIB \
  $(MAKEDEP)
   @echo Linking... 
   wlink @<<
SYS os2v2 pm op m op q op c op maxe=25 op st=65536
option de 'GTakPM Develop (c) 1995 by Cubus - All Rights reserved.'
NAME GTAKPM.EXE
LIBR OCLW 
FIL .\GTPMException.obj,
.\GTPMMain.obj,
.\GTPMApp.obj,
.\GTPMWin.obj,
.\GTPMWinControl.obj,
.\GTPMWinCommand.obj,
.\FilesCnr.obj,
.\DrivesCnr.obj,
.\Tape.obj,
.\Backup.obj,
.\Restore.obj
<<
   @rc $(RCPACK) GTAKPM.RES GTAKPM.EXE 

!include ..\GTAKPM.DEP
