!include $(OCLSAMP)\COMMON.INC
!include ..\BALLOON.INC

MAKEDEP = METAWARE.MAK
CFLAGS = $(S_HIGHCPP_COMPILE)
LFLAGS = $(S_HIGHCPP_LINK)

{..\Source}.cpp.obj:
   hc $(CFLAGS) %s

.\Server.exe: $(SERVER) {$(LIB)}OCLM.lib $(MAKEDEP)
   hc $(LFLAGS) -l$(OCL)\LIB\OCLM.LIB -o .\Server.EXE .\Server.obj
   rc .\server.res Server.exe

.\Client.exe: $(CLIENT) {$(LIB)}OCLM.lib $(MAKEDEP)
   hc $(LFLAGS) -l$(OCL)\LIB\OCLM.LIB -o .\Client.EXE .\Client.obj
   rc .\Client.res Client.exe

!include ..\BALLOON.DEP
