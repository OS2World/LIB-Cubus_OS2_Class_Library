# $Header: W:/Projects/OCL/Samples/Collections/EMX/rcs/EMX.MAK 1.50 1996/08/11 23:47:50 B.STEIN Release $

!include $(OCLSAMP)\COMMON.INC
!include ..\COLLECT.INC

MAKEDEP = EMX.MAK
CFLAGS = $(S_EMX_COMPILE_DEBUG)
LFLAGS = $(S_EMX_LINK_DEBUG)

{..\Source}.cpp.obj:
    gcc $(CFLAGS) %s

.\Collect.EXE: \
  .\Collect.obj \
  $(OCL)\LIB\OCLEMXI.LIB \
  $(MAKEDEP)
  gcc $(LFLAGS) .\Collect.EXE .\Collect.obj ..\Source\Collect.def -L$(OCL)\LIB -loclemxi -lstdcpp

!include ..\COLLECT.DEP
