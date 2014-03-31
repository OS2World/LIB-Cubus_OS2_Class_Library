!include $(OCLSAMP)\COMMON.INC
!include ..\VALUE.INC

MAKEDEP = BORLAND.MAK
CFLAGS = $(S_BORLAND_COMPILE)
LFLAGS = $(S_BORLAND_LINK)

{..\Source}.cpp.obj:
   bcc $(CFLAGS) %s

.\ValueSet.EXE: .\Value.obj .\Value.res {$(LIB)}OCLB.lib $(MAKEDEP)
   tlink $(LFLAGS) .\Value.obj, .\ValueSet.exe,, OCLB C2MT OS2
   rc .\Value.res .\ValueSet.EXE

!include ..\VALUE.DEP
