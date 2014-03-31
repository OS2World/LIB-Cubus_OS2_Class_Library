!include $(OCLSAMP)\COMMON.INC
!include ..\LISTBOX.INC

MAKEDEP = WATCOM.MAK
CFLAGS = $(S_WATCOM_COMPILE)
LFLAGS = $(S_WATCOM_LINK)

{..\Source}.cpp.obj:
   wpp386 $(CFLAGS) %s

.\LISTBOX.exe: LISTBOX.obj LISTBOX.res {$(LIB)}OCLW.lib $(MAKEDEP)
   wlink $(LFLAGS) libr OCLW NAME .\LISTBOX.EXE FIL .\LISTBOX.obj
   rc .\LISTBOX.res LISTBOX.exe

!include ..\LISTBOX.DEP
