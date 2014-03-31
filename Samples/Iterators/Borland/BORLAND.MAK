!include $(OCLSAMP)\COMMON.INC
!include ..\ITTEST.INC

MAKEDEP = BORLAND.MAK
CFLAGS = $(S_BORLAND_COMPILE)
LFLAGS = $(BORLAND_LINK)

{..\Source}.cpp.obj:
   bcc $(CFLAGS) %s

.\ITTEST.EXE: .\ITTEST.obj {$(LIB)}OCLB.lib $(MAKEDEP)
   tlink $(LFLAGS) .\ITTEST.obj, .\ITTEST.exe,, OCLB C2MT OS2

!include ..\ITTEST.DEP
