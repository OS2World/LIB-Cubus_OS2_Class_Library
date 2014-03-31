!include $(OCLSAMP)\COMMON.INC
!include ..\SOCKETS.INC

MAKEDEP = WATCOM.MAK
CFLAGS = $(WATCOM_COMPILE)
LFLAGS = $(WATCOM_LINK)

{..\Source}.cpp.obj:
   wpp386 $(CFLAGS) %s

.\SOCKS.exe: SOCKS.obj {$(LIB)}OCLW.lib {$(LIB)}OIPW.lib $(MAKEDEP)
   wlink SYS os2v2 op m op q op c op maxe=25 op st=65536 libr OCLW libr OIPW libr OTCPIP NAME .\SOCKS.EXE FIL .\SOCKS.obj

.\SOCKC.exe: SOCKC.obj {$(LIB)}OCLW.lib {$(LIB)}OIPW.lib $(MAKEDEP)
   wlink SYS os2v2 op m op q op c op maxe=25 op st=65536 libr OCLW libr OIPW libr OTCPIP NAME .\SOCKC.EXE FIL .\SOCKC.obj

!include ..\SOCKETS.DEP