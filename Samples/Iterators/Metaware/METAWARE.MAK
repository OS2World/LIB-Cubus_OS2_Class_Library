!include $(OCLSAMP)\COMMON.INC
!include ..\ITTEST.INC

MAKEDEP = METAWARE.MAK
CFLAGS = $(HIGHCPP_COMPILE)
LFLAGS = $(HIGHCPP_LINK)

{..\Source}.cpp.obj:
   hc $(CFLAGS) %s

.\ITTEST.exe: ITTEST.obj {$(LIB)}OCLM.lib $(MAKEDEP)
   hc $(LFLAGS) -l$(OCL)\LIB\OCLM.LIB -o .\ITTEST.EXE .\ITTEST.obj

!include ..\ITTEST.DEP
