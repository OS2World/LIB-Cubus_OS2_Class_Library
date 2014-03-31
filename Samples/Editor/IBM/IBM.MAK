!include $(OCLSAMP)\COMMON.INC
!include ..\Editor.INC

MAKEDEP = IBM.MAK
CFLAGS = $(S_ICC_COMPILE)
LFLAGS = $(S_ICC_LINK)

{..\Source}.cpp.obj:
   icc $(CFLAGS) %s

.\Editor.EXE: .\Editor.obj .\Editor.res {$(LIB)}OCLI.LIB $(MAKEDEP)
   icc @<<
$(LFLAGS) /Fe.\Editor.EXE OCLI.LIB .\Editor.obj ..\Source\Editor.def
<<
   rc .\Editor.res .\Editor.EXE

!include ..\Editor.DEP
