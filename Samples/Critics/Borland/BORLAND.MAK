!include $(OCLSAMP)\COMMON.INC
!include ..\CRITICS.INC

MAKEDEP = BORLAND.MAK
CFLAGS = $(BORLAND_COMPILE)
LFLAGS = $(BORLAND_LINK)

{..\Source}.cpp.obj:
   bcc $(CFLAGS) %s

.\CRITICS.EXE: .\CRITICS.obj {$(LIB)}OCLB.lib $(MAKEDEP)
   tlink $(LFLAGS) .\CRITICS.obj, .\CRITICS.exe,, OCLB C2MT OS2

!include ..\CRITICS.DEP
