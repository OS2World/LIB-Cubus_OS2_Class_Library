!include $(OCLSAMP)\COMMON.INC
!include ..\EDITOR.INC

MAKEDEP = BORLAND.MAK
CFLAGS = $(S_BORLAND_COMPILE)
LFLAGS = $(S_BORLAND_LINK)

{..\Source}.cpp.obj:
   bcc $(CFLAGS) %s

.\EDITOR.EXE: .\EDITOR.obj .\EDITOR.res {$(LIB)}OCLB.lib $(MAKEDEP)
   tlink $(LFLAGS) .\EDITOR.obj, .\EDITOR.exe,, OCLB C2MT OS2
   rc .\EDITOR.res .\EDITOR.EXE

!include ..\EDITOR.DEP
