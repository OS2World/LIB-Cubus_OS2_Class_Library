!include $(OCLSAMP)\COMMON.INC
!include ..\Editor.INC

MAKEDEP = WATCOM.MAK
CFLAGS = $(WATCOM_COMPILE)
LFLAGS = $(WATCOM_LINK)

{..\Source}.cpp.obj:
   wpp386 $(CFLAGS) %s

.\Editor.exe: Editor.obj Editor.res {$(LIB)}OCLW.lib $(MAKEDEP)
   wlink $(LFLAGS) libr OCLW NAME .\Editor.EXE FIL .\Editor.obj
   rc .\Editor.res .\Editor.exe

!include ..\Editor.DEP