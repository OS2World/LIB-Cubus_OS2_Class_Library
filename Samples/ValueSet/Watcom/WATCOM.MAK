!include $(OCLSAMP)\COMMON.INC
!include ..\VALUE.INC

MAKEDEP = WATCOM.MAK
CFLAGS = $(S_WATCOM_COMPILE)
LFLAGS = $(S_WATCOM_LINK)

{..\Source}.cpp.obj:
   wpp386 $(CFLAGS) %s

.\ValueSet.exe: Value.obj Value.res {$(LIB)}OCLW.lib $(MAKEDEP)
   wlink $(LFLAGS) libr OCLW NAME .\ValueSet.EXE FIL .\Value.obj
   rc .\Value.res ValueSet.exe

!include ..\VALUE.DEP
