!include $(OCLSAMP)\COMMON.INC
!include ..\BALLOON.INC

MAKEDEP = VA30.MAK
CFLAGS = $(S_ICC_COMPILE_DEBUG)
LFLAGS = $(S_ICC_LINK_DEBUG)

{..\Source}.cpp.obj:
   icc $(CFLAGS) %s

.\Server.exe: $(SERVER) {$(LIB)}OCLVAI.lib $(MAKEDEP)
    icc @<<
$(LFLAGS) /FeServer.exe OCLVAI.lib .\server.obj ..\Source\Server.def
<<
    rc .\server.res Server.exe

.\Client.exe: $(CLIENT) {$(LIB)}OCLVAI.lib $(MAKEDEP)
    icc @<<
$(LFLAGS) /FeClient.exe OCLVAI.lib .\Client.obj ..\Source\Client.def
<<
      rc .\Client.res Client.exe

!include ..\BALLOON.DEP
