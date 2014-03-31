!include $(OCLSAMP)\COMMON.INC
!include ..\MENUS.INC

MAKEDEP = BORLAND.MAK
CFLAGS = $(S_BORLAND_COMPILE)
LFLAGS = $(S_BORLAND_LINK)

{..\Source}.cpp.obj:
   bcc $(CFLAGS) %s

.\MENUS.EXE: .\MENUS.obj .\MENUS.res {$(LIB)}OCLB.lib $(MAKEDEP)
   tlink $(LFLAGS) .\MENUS.obj, .\MENUS.exe,, OCLBI C2MT OS2
   rc .\MENUS.res .\MENUS.EXE

!include ..\MENUS.DEP
