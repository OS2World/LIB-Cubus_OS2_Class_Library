!include $(OCLSAMP)\COMMON.INC
!include ..\MENUS.INC

MAKEDEP = VA30.MAK
CFLAGS = $(S_ICC_COMPILE)
LFLAGS = $(S_ICC_LINK)

{..\Source}.cpp.obj:
   icc $(CFLAGS) %s

.\MENUS.EXE: .\MENUS.obj .\MENUS.res {$(LIB)}OCLVAI.LIB $(MAKEDEP)
   icc @<<
$(LFLAGS) /Fe.\MENUS.EXE OCLVAI.LIB .\MENUS.obj
<<
   rc .\MENUS.res .\MENUS.EXE

!include ..\MENUS.DEP
