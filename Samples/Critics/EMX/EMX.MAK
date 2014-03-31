# $Header: W:/Projects/OCL/Samples/Critics/EMX/rcs/EMX.MAK 1.50 1996/08/11 23:47:53 B.STEIN Release $

!include $(OCLSAMP)\COMMON.INC
!include ..\CRITICS.INC

MAKEDEP = EMX.MAK
CFLAGS = $(S_EMX_COMPILE)
LFLAGS = $(S_EMX_LINK)

{..\Source}.cpp.obj:
    gcc $(CFLAGS) %s

.\CRITICS.EXE: \
  .\CRITICS.obj \
  $(OCL)\LIB\OCLEMXI.LIB \
  $(MAKEDEP)
  gcc $(LFLAGS) .\CRITICS.EXE .\CRITICS.obj ..\Source\CRITICS.def -L$(OCL)\LIB -loclemxi -lstdcpp

!include ..\CRITICS.DEP
