!include $(OCLSAMP)\COMMON.INC
!include ..\LISTBOX.INC

MAKEDEP = VA30.MAK
CFLAGS = $(S_ICC_COMPILE_DEBUG)
LFLAGS = $(S_ICC_LINK_DEBUG)

{..\Source}.cpp.obj:
   icc $(CFLAGS) %s

.\LISTBOX.EXE: .\LISTBOX.obj .\LISTBOX.res {$(LIB)}OCLVAI.LIB $(MAKEDEP)
   icc @<<
$(LFLAGS) /Fe.\LISTBOX.EXE OCLVAI.LIB .\LISTBOX.obj ..\Source\Listbox.def
<<
   rc .\LISTBOX.res .\LISTBOX.EXE

!include ..\LISTBOX.DEP
