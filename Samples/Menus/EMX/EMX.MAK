!include $(OCLSAMP)\COMMON.INC
!include ..\MENUS.INC

MAKEDEP = EMX.MAK
CFLAGS = $(S_EMX_COMPILE)
LFLAGS = $(S_EMX_LINK)

{..\Source}.cpp.obj:
    gcc $(CFLAGS) %s

.\MENUS.EXE: \
  .\MENUS.obj \
  $(OCL)\LIB\OCLEMXI.LIB \
  $(MAKEDEP)
   rc -r -I E:\EMX\INCLUDE ..\Source\MENUS.rc 
   gcc $(LFLAGS) .\MENUS.EXE .\MENUS.obj ..\Source\MENUS.def ..\Source\MENUS.res -L$(OCL)\LIB -loclemxi -lstdcpp

!include ..\MENUS.DEP
