!include $(OCLSAMP)\COMMON.INC
!include ..\VALUE.INC

MAKEDEP = VA30.MAK
CFLAGS = $(S_ICC_COMPILE)
LFLAGS = $(S_ICC_LINK)

{..\Source}.cpp.obj:
   icc $(CFLAGS) %s

.\ValueSet.exe: .\Value.obj .\Value.res {$(LIB)}OCLVAI.LIB $(MAKEDEP)
   icc @<<
$(LFLAGS) /Fe.\ValueSet.exe OCLVAI.LIB .\Value.obj
<<
   rc .\Value.res .\ValueSet.exe

!include ..\VALUE.DEP
