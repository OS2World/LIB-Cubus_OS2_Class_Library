!include $(OCLSAMP)\COMMON.INC
!include ..\TEMPLATE.INC

INCLUDE = $(BCINC)
LIB = $(BCLIB)
PATH = E:\BC20\BIN;$(PATH)

MAKEDEP = BORLAND.MAK
CFLAGS = $(S_BORLAND_COMPILE)
LFLAGS = $(S_BORLAND_LINK)

{..\Source}.cpp.obj:
   bcc $(CFLAGS) %s

.\Template.EXE: \
    .\Template.obj \
    .\Container.obj \
    .\Template.res \
    ..\Source\Template.def \
    {$(LIB)}OCLB.lib \
    $(MAKEDEP)
   tlink $(LFLAGS) .\Template.obj .\Container.obj, \
     .\Template.exe,, OCLB C2MT OS2, ..\Source\Template.def
   rc .\Template.res .\Template.EXE

!include ..\TEMPLATE.DEP
