!include $(OCLSAMP)\COMMON.INC
!include ..\Editor.INC

MAKEDEP = METAWARE.MAK
CFLAGS = $(S_HIGHCPP_COMPILE)
LFLAGS = $(S_HIGHCPP_LINK)

{..\Source}.cpp.obj:
   hc $(CFLAGS) %s

.\Editor.exe: Editor.obj Editor.res {$(LIB)}OCLM.lib $(MAKEDEP)
   hc $(LFLAGS) -l$(OCL)\LIB\OCLM.LIB -o .\Editor.EXE .\Editor.obj
   rc .\Editor.res .\Editor.exe

!include ..\Editor.DEP
