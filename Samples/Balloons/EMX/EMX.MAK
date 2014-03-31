# $Header: W:/Projects/OCL/Samples/Balloons/EMX/rcs/EMX.MAK 1.50 1996/08/11 23:47:44 B.STEIN Release $

!include $(OCLSAMP)\COMMON.INC
!include ..\BALLOON.INC

MAKEDEP = EMX.MAK
CFLAGS = $(S_EMX_COMPILE)
LFLAGS = $(S_EMX_LINK)

{..\Source}.cpp.obj:
    gcc $(CFLAGS) %s

.\Server.EXE: \
  .\Server.obj \
  $(OCL)\LIB\OCLEMXI.LIB \
  $(MAKEDEP)
   rc -r -I E:\EMX\INCLUDE ..\Source\Server.rc 
   gcc $(LFLAGS) .\Server.EXE .\Server.obj ..\Source\Server.def ..\Source\Server.res -L$(OCL)\LIB -loclemxi -lstdcpp

.\Client.EXE: \
  .\Client.obj \
  $(OCL)\LIB\OCLEMXI.LIB \
  $(MAKEDEP)
   rc -r -I E:\EMX\INCLUDE ..\Source\Client.rc 
   gcc $(LFLAGS) .\Client.EXE .\Client.obj ..\Source\Client.def ..\Source\Client.res -L$(OCL)\LIB -loclemxi -lstdcpp

!include ..\BALLOON.DEP
