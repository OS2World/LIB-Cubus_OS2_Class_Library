!include $(OCLSAMP)\COMMON.INC
!include ..\VALUE.INC

MAKEDEP = EMX.MAK
CFLAGS = $(S_EMX_COMPILE)
LFLAGS = $(S_EMX_LINK)

{..\Source}.cpp.obj:
    gcc $(CFLAGS) %s

.\VALUESET.EXE: \
  .\VALUE.obj \
  $(OCL)\LIB\OCLEMXI.LIB \
  $(MAKEDEP)
   rc -r -I E:\EMX\INCLUDE ..\Source\VALUE.rc 
   gcc $(LFLAGS) .\VALUESET.EXE .\VALUE.obj ..\Source\VALUE.def ..\Source\VALUE.res -L$(OCL)\LIB -loclemxi -lstdcpp

!include ..\VALUE.DEP
