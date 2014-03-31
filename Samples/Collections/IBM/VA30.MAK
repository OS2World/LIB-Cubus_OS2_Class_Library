!include $(OCLSAMP)\COMMON.INC
!include ..\COLLECT.INC

MAKEDEP = VA30.MAK
CFLAGS = $(ICC_COMPILE)
LFLAGS = $(ICC_LINK)

{..\Source}.cpp.obj:
   icc $(CFLAGS) %s

.\COLLECT.EXE: .\COLLECT.obj {$(LIB)}OCLVAI.LIB $(MAKEDEP)
   icc @<<
$(LFLAGS) /Fe.\COLLECT.EXE OCLVAI.LIB .\COLLECT.obj
<<

!include ..\COLLECT.DEP
