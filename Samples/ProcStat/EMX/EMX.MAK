!include $(OCLSAMP)\COMMON.INC
!include ..\PROCSTAT.INC

MAKEDEP = EMX.MAK
CFLAGS = $(S_EMX_COMPILE)
LFLAGS = $(S_EMX_LINK)

{..\Source}.cpp.obj:
    gcc $(CFLAGS) %s

.\PROCSTAT.EXE: \
  .\PROCSTAT.obj \
  $(OCL)\LIB\OCLEMXI.LIB \
  $(MAKEDEP)
   rc -r -I E:\EMX\INCLUDE ..\Source\PROCSTAT.rc 
   gcc $(LFLAGS) .\PROCSTAT.EXE .\PROCSTAT.obj ..\Source\PROCSTAT.def ..\Source\PROCSTAT.res -L$(OCL)\LIB -loclemxi -lstdcpp

!include ..\PROCSTAT.DEP
