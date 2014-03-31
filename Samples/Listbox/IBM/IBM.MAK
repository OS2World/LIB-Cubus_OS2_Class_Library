!include $(OCLSAMP)\COMMON.INC
!include ..\LISTBOX.INC

MAKEDEP = IBM.MAK
CFLAGS = $(S_ICC_COMPILE)
LFLAGS = $(S_ICC_LINK)

{..\Source}.cpp.obj:
   icc $(CFLAGS) %s

.\LISTBOX.EXE: .\LISTBOX.obj .\LISTBOX.res {$(LIB)}OCLII.LIB $(MAKEDEP)
   icc @<<
$(LFLAGS) /Fe.\LISTBOX.EXE OCLII.LIB .\LISTBOX.obj
<<
   rc .\LISTBOX.res .\LISTBOX.EXE

!include ..\LISTBOX.DEP
