# $Header: W:/Projects/OCL/Samples/Iterators/EMX/rcs/EMX.MAK 1.50 1996/08/11 23:48:26 B.STEIN Release $

!include $(OCLSAMP)\COMMON.INC
!include ..\ITTEST.INC

MAKEDEP = EMX.MAK
CFLAGS = $(S_EMX_COMPILE)
LFLAGS = $(S_EMX_LINK)

{..\Source}.cpp.obj:
    gcc $(CFLAGS) %s

.\ITTEST.EXE: \
  .\ITTEST.obj \
  $(OCL)\LIB\OCLEMXI.LIB \
  $(MAKEDEP)
  gcc $(LFLAGS) .\ITTEST.EXE .\ITTEST.obj ..\Source\ITTEST.def -L$(OCL)\LIB -loclemxi -lstdcpp

!include ..\ITTEST.DEP
