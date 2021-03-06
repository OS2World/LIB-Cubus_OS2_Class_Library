!include $(OCLSAMP)\COMMON.INC
!include ..\SOCKETS.INC

MAKEDEP = VA30.MAK
CFLAGS = $(ICC_COMPILE_DEBUG)
LFLAGS = $(ICC_LINK_DEBUG)

{..\Source}.cpp.obj:
   icc $(CFLAGS) %s

.\SOCKS.EXE: .\SOCKS.obj {$(LIB)}OCLVAI.LIB $(MAKEDEP)
   icc @<<
$(LFLAGS) /Fe.\SOCKS.EXE OCLVAI.LIB .\SOCKS.obj
<<

.\SOCKC.EXE: .\SOCKC.obj {$(LIB)}OCLVAI.LIB $(MAKEDEP)
   icc @<<
$(LFLAGS) /Fe.\SOCKC.EXE OCLVAI.LIB .\SOCKC.obj
<<

!include ..\SOCKETS.DEP
