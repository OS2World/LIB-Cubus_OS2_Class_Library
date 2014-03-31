!include $(OCLSAMP)\COMMON.INC
!include ..\PROCSTAT.INC

MAKEDEP = VA30.MAK
CFLAGS = $(S_ICC_COMPILE)
LFLAGS = $(S_ICC_LINK)

{..\Source}.cpp.obj:
   icc $(CFLAGS) %s

.\PROCSTAT.EXE: .\PROCSTAT.obj .\PROCSTAT.res {$(LIB)}OCLVAI.LIB  $(MAKEDEP)
   icc @<<
$(LFLAGS) /Fe.\PROCSTAT.EXE
   OCLVAI.LIB
   .\PROCSTAT.obj
   ..\Source\Procstat.def
<<
   rc .\PROCSTAT.res .\PROCSTAT.EXE

!include ..\PROCSTAT.DEP
