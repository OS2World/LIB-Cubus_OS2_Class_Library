!include $(OCLSAMP)\COMMON.INC
!include ..\VALUE.INC

MAKEDEP = METAWARE.MAK
CFLAGS = $(S_HIGHCPP_COMPILE)
LFLAGS = $(S_HIGHCPP_LINK)

{..\Source}.cpp.obj:
   hc $(CFLAGS) %s

.\ValueSet.exe: Value.obj Value.res {$(LIB)}OCLM.LIB $(MAKEDEP)
   hc $(LFLAGS) -l$(OCL)\LIB\OCLM.LIB -o .\ValueSet.EXE .\Value.obj
   rc .\Value.res ValueSet.exe

!include ..\VALUE.DEP
