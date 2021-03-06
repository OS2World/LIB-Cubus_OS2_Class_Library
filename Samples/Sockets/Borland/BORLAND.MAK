!include $(OCLSAMP)\COMMON.INC
!include ..\SOCKETS.INC

MAKEDEP = BORLAND.MAK
CFLAGS = $(S_BORLAND_COMPILE_DEBUG)
LFLAGS = $(BORLAND_LINK_DEBUG)

{..\Source}.cpp.obj:
   bcc $(CFLAGS) %s

.\SOCKS.EXE: .\SOCKS.obj {$(LIB)}OCLBI.lib $(MAKEDEP)
   tlink $(LFLAGS) .\SOCKS.obj, .\SOCKS.exe,, OCLB OIPB OTCPIP C2MT OS2

.\SOCKC.EXE: .\SOCKC.obj {$(LIB)}OCLBI.lib $(MAKEDEP)
   tlink $(LFLAGS) .\SOCKC.obj, .\SOCKC.exe,, OCLB OIPB OTCPIP C2MT OS2

!include ..\SOCKETS.DEP
