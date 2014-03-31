!include $(OCLSAMP)\COMMON.INC
!include ..\EDITOR.INC

MAKEDEP = EMX.MAK
CFLAGS = $(S_EMX_COMPILE)
LFLAGS = $(S_EMX_LINK)

{..\Source}.cpp.obj:
    gcc $(CFLAGS) %s

.\EDITOR.EXE: \
  .\EDITOR.obj \
  $(OCL)\LIB\OCLEMXI.LIB \
  $(MAKEDEP)
   rc -r -I E:\EMX\INCLUDE ..\Source\EDITOR.rc 
   gcc $(LFLAGS) .\EDITOR.EXE .\EDITOR.obj ..\Source\EDITOR.def ..\Source\EDITOR.res -L$(OCL)\LIB -loclemxi -lstdcpp

!include ..\EDITOR.DEP
