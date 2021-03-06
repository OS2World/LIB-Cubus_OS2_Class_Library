!include $(OCLSAMP)\COMMON.INC
!include ..\ITTEST.INC

MAKEDEP = WATCOM.MAK
CFLAGS = $(WATCOM_COMPILE)
LFLAGS = $(WATCOM_LINK)

{..\Source}.cpp.obj:
   wpp386 $(CFLAGS) %s

.\ITTEST.exe: ITTEST.obj {$(LIB)}OCLW.lib $(MAKEDEP)
   wlink SYS os2v2 op m op q op c op maxe=25 op st=65536 libr OCLW NAME .\ITTEST.EXE FIL .\ITTEST.obj

!include ..\ITTEST.DEP