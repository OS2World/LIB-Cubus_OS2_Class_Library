# $Header: W:/Projects/OCL/Samples/Sockets/EMX/rcs/EMX.MAK 1.50 1996/08/11 23:48:52 B.STEIN Release $

!include $(OCLSAMP)\COMMON.INC
!include ..\SOCKETS.INC

MAKEDEP = EMX.MAK
CFLAGS = $(S_EMX_COMPILE)
LFLAGS = $(S_EMX_LINK)

{..\Source}.cpp.obj:
    gcc $(CFLAGS) %s

.\SOCKS.EXE: \
  .\SOCKS.obj \
  $(OCL)\LIB\OCLEMXI.LIB \
  $(MAKEDEP)
  gcc $(LFLAGS) .\SOCKS.EXE .\SOCKS.obj ..\Source\SOCKS.def -L$(OCL)\LIB -loclemx -loipemx -lotcpip -lstdcpp

.\SOCKC.EXE: \
  .\SOCKC.obj \
  $(OCL)\LIB\OCLEMXI.LIB \
  $(MAKEDEP)
  gcc $(LFLAGS) .\SOCKC.EXE .\SOCKC.obj ..\Source\SOCKC.def -L$(OCL)\LIB -loclemx -loipemx -lotcpip -lstdcpp

!include ..\SOCKETS.DEP
