!include $(OCLSAMP)\COMMON.INC
!include ..\VALUE.INC

MAKEDEP = IBM.MAK
CFLAGS = $(S_ICC_COMPILE)
LFLAGS = $(S_ICC_LINK)

{..\Source}.cpp.obj:
   icc $(CFLAGS) %s

.\ValueSet.exe: .\Value.obj .\Value.res {$(LIB)}OCLI.LIB $(MAKEDEP)
   icc @<<
$(LFLAGS) /Fe.\ValueSet.exe OCLI.LIB .\Value.obj
<<
   rc .\Value.res .\ValueSet.exe

!include ..\VALUE.DEP
