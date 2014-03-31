!include $(OCLSAMP)\COMMON.INC
!include ..\COLLECT.INC

MAKEDEP = BORLAND.MAK
CFLAGS = $(BORLAND_COMPILE)
LFLAGS = $(BORLAND_LINK)

{..\Source}.cpp.obj:
   bcc $(CFLAGS) %s

.\COLLECT.EXE: .\COLLECT.obj {$(LIB)}OCLB.lib $(MAKEDEP)
   tlink $(LFLAGS) .\COLLECT.obj, .\COLLECT.exe,, OCLB C2MT OS2

!include ..\COLLECT.DEP
