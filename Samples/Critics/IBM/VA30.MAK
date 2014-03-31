!include $(OCLSAMP)\COMMON.INC
!include ..\CRITICS.INC

MAKEDEP = VA30.MAK
CFLAGS = $(ICC_COMPILE)
LFLAGS = $(ICC_LINK)

{..\Source}.cpp.obj:
   icc $(CFLAGS) %s

.\CRITICS.EXE: .\CRITICS.obj {$(LIB)}OCLVA.LIB $(MAKEDEP)
   icc @<<
$(LFLAGS) /Fe.\CRITICS.EXE OCLVA.LIB .\CRITICS.obj
<<

!include ..\CRITICS.DEP
