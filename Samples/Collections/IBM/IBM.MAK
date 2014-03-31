!include $(OCLSAMP)\COMMON.INC
!include ..\COLLECT.INC

MAKEDEP = IBM.MAK
CFLAGS = $(ICC_COMPILE)
LFLAGS = $(ICC_LINK)

{..\Source}.cpp.obj:
   icc $(CFLAGS) %s

.\COLLECT.EXE: .\COLLECT.obj {$(LIB)}OCLI.LIB $(MAKEDEP)
   icc @<<
$(LFLAGS) /Fe.\COLLECT.EXE OCLI.LIB .\COLLECT.obj
<<

!include ..\COLLECT.DEP
