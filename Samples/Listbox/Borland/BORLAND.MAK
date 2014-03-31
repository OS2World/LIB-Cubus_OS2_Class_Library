!include $(OCLSAMP)\COMMON.INC
!include ..\LISTBOX.INC

MAKEDEP = BORLAND.MAK
CFLAGS = $(S_BORLAND_COMPILE)
LFLAGS = $(S_BORLAND_LINK)

{..\Source}.cpp.obj:
   bcc $(CFLAGS) %s

.\LISTBOX.EXE: .\LISTBOX.obj .\LISTBOX.res {$(LIB)}OCLB.lib $(MAKEDEP)
   tlink $(LFLAGS) .\LISTBOX.obj, .\LISTBOX.exe,, OCLB C2MT OS2
   rc .\LISTBOX.res .\LISTBOX.EXE

!include ..\LISTBOX.DEP
