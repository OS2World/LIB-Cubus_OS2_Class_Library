# $Header: W:/Projects/OCL/Samples/DragSamp/EMX/rcs/EMX.MAK 1.50 1996/08/11 23:47:56 B.STEIN Release $

!include $(OCLSAMP)\COMMON.INC
!include ..\DRAGSAMP.INC

MAKEDEP = EMX.MAK
CFLAGS = $(S_EMX_COMPILE)
LFLAGS = $(S_EMX_LINK)

{..\Source}.cpp.obj:
    gcc $(CFLAGS) %s

.\DRAGSAMP.EXE: \
  .\DRAGSAMP.obj \
  $(OCL)\LIB\OCLEMXI.LIB \
  $(MAKEDEP)
   rc -r -I E:\EMX\INCLUDE ..\Source\DRAGSAMP.rc 
   gcc $(LFLAGS) .\DRAGSAMP.EXE .\DRAGSAMP.obj ..\Source\DRAGSAMP.def ..\Source\DRAGSAMP.res -L$(OCL)\LIB -loclemxi -lstdcpp

!include ..\DRAGSAMP.DEP
