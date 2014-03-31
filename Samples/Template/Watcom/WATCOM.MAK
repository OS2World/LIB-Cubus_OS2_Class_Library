!include $(OCLSAMP)\COMMON.INC
!include ..\TEMPLATE.INC

MAKEDEP = WATCOM.MAK
CFLAGS = $(S_WATCOM_COMPILE)
LFLAGS = $(S_WATCOM_LINK)

{..\Source}.cpp.obj:
    wpp386 $(CFLAGS) %s

.\Template.EXE: \
  .\Template.obj \
  .\Container.obj \
  .\Template.res \
  {$(LIB)}OCLW.lib \
  $(MAKEDEP)
   wlink $(LFLAGS) libr OCLW NAME .\Template.EXE FIL .\Template.obj, .\Container.obj
   rc .\Template.res .\Template.EXE

!include ..\TEMPLATE.DEP
