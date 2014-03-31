!include $(OCLSAMP)\COMMON.INC
!include ..\ITTEST.INC

MAKEDEP = IBM.MAK
CFLAGS = $(ICC_COMPILE)
LFLAGS = $(ICC_LINK)

{..\Source}.cpp.obj:
   icc $(CFLAGS) %s

.\ITTEST.EXE: .\ITTEST.obj {$(LIB)}OCLI.LIB $(MAKEDEP)
   icc @<<
$(LFLAGS) /Fe.\ITTEST.EXE OCLI.LIB .\ITTEST.obj ..\Source\ITTest.def
<<

!include ..\ITTEST.DEP
