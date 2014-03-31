!include $(OCLSAMP)\COMMON.INC
!include ..\MENUS.INC

MAKEDEP = METAWARE.MAK
CFLAGS = $(S_HIGHCPP_COMPILE)
LFLAGS = $(S_HIGHCPP_LINK)

{..\Source}.cpp.obj:
   hc $(CFLAGS) %s

.\MENUS.exe: MENUS.obj MENUS.res {$(LIB)}OCLM.lib $(MAKEDEP)
   hc $(LFLAGS) -l$(OCL)\LIB\OCLM.LIB -o .\MENUS.EXE .\MENUS.obj
   rc .\MENUS.res MENUS.exe

!include ..\MENUS.DEP
