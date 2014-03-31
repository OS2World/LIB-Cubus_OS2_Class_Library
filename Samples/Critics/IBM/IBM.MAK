!include $(OCLSAMP)\COMMON.INC
!include ..\CRITICS.INC

MAKEDEP = IBM.MAK
CFLAGS = $(ICC_COMPILE)
LFLAGS = $(ICC_LINK)

{..\Source}.cpp.obj:
   icc $(CFLAGS) %s

.\CRITICS.EXE: .\CRITICS.obj {$(LIB)}OCLI.LIB $(MAKEDEP)
   icc @<<
$(LFLAGS) /Fe.\CRITICS.EXE OCLI.LIB .\CRITICS.obj
<<

!include ..\CRITICS.DEP
