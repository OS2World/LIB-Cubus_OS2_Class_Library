!include $(OCLSAMP)\COMMON.INC
!include ..\PROCSTAT.INC

MAKEDEP = METAWARE.MAK
CFLAGS = $(S_HIGHCPP_COMPILE)
LFLAGS = $(S_HIGHCPP_LINK)

{..\Source}.cpp.obj:
   hc $(CFLAGS) %s

.\PROCSTAT.exe: PROCSTAT.obj PROCSTAT.res {$(LIB)}OCLM.lib $(MAKEDEP)
   hc $(LFLAGS) -Hdef=..\Source\Procstat.def -l$(OCL)\LIB\OCLM.LIB -o .\PROCSTAT.EXE .\PROCSTAT.obj
   rc .\PROCSTAT.res PROCSTAT.exe

!include ..\PROCSTAT.DEP
