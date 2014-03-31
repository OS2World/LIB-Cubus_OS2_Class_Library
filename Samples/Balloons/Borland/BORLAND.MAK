!include $(OCLSAMP)\COMMON.INC
!include ..\BALLOON.INC

MAKEDEP = BORLAND.MAK
CFLAGS = $(S_BORLAND_COMPILE)
LFLAGS = $(S_BORLAND_LINK)

.all: .\Server.EXE .\Client.EXE

.SUFFIXES:

.SUFFIXES: .cpp .rc

{..\Source}.rc.res:
      rc -r %s %|fF.RES

{..\Source}.cpp.obj:
   bcc $(CFLAGS) %s


.\Server.EXE: $(SERVER) {$(LIB)}OCLB.lib $(MAKEDEP)
   tlink $(LFLAGS) .\Server.obj, .\Server.exe,, OCLB C2MT OS2
   rc .\Server.res .\Server.EXE

.\Client.EXE: $(CLIENT) {$(LIB)}OCLB.lib $(MAKEDEP)
   tlink $(LFLAGS) .\Client.obj, .\Client.exe,, OCLB C2MT OS2
   rc .\Client.res .\Client.EXE

!include ..\BALLOON.DEP
