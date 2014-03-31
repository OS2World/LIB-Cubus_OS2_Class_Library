!include $(OCLSAMP)\COMMON.INC
!include ..\ITTEST.INC

MAKEDEP = VA30.MAK
CFLAGS = $(ICC_COMPILE)
LFLAGS = $(ICC_LINK)

{..\Source}.cpp.obj:
   icc $(CFLAGS) %s

.\ITTEST.EXE: .\ITTEST.obj {$(LIB)}OCLVAI.LIB $(MAKEDEP)
   icc @<<
$(LFLAGS) /Fe.\ITTEST.EXE OCLVAI.LIB .\ITTEST.obj ..\Source\ITTest.def
<<

!include ..\ITTEST.DEP
