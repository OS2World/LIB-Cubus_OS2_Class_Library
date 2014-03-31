!include $(OCLSAMP)\COMMON.INC
!include ..\BALLOON.INC

MAKEDEP = IBM.MAK
CFLAGS = $(S_ICC_COMPILE)
LFLAGS = $(S_ICC_LINK)

{..\Source}.cpp.obj:
   icc $(CFLAGS) %s

.\Server.exe: $(SERVER) {$(LIB)}OCLI.lib $(MAKEDEP)
    icc @<<
$(LFLAGS) /FeServer.exe OCLI.lib .\server.obj
<<
    rc .\server.res Server.exe

.\Client.exe: $(CLIENT) {$(LIB)}OCLI.lib $(MAKEDEP)
    icc @<<
$(LFLAGS) /FeClient.exe OCLI.lib .\Client.obj
<<
      rc .\Client.res Client.exe

!include ..\BALLOON.DEP
