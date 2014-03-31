!include $(OCLSAMP)\COMMON.INC
!include ..\MENUS.INC

MAKEDEP = WATCOM.MAK
CFLAGS = $(S_WATCOM_COMPILE)
LFLAGS = $(S_WATCOM_LINK)

{..\Source}.cpp.obj:
   wpp386 $(CFLAGS) %s

.\MENUS.exe: MENUS.obj MENUS.res {$(LIB)}OCLW.lib $(MAKEDEP)
   wlink $(LFLAGS) libr OCLW NAME .\MENUS.EXE FIL .\MENUS.obj
   rc .\MENUS.res MENUS.exe

!include ..\MENUS.DEP
