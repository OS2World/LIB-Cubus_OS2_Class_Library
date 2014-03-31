!include $(OCLSAMP)\COMMON.INC
!include ..\SOCKETS.INC

MAKEDEP = IBM.MAK
CFLAGS = $(ICC_COMPILE_DEBUG)
LFLAGS = $(ICC_LINK_DEBUG)

{..\Source}.cpp.obj:
   icc $(CFLAGS) %s

.\SOCKS.EXE: .\SOCKS.obj {$(LIB)}OCLII.LIB $(MAKEDEP)
   icc @<<
$(LFLAGS) /Fe.\SOCKS.EXE OCLII.LIB .\SOCKS.obj
<<

.\SOCKC.EXE: .\SOCKC.obj {$(LIB)}OCLII.LIB $(MAKEDEP)
   icc @<<
$(LFLAGS) /Fe.\SOCKC.EXE OCLII.LIB .\SOCKC.obj
<<

!include ..\SOCKETS.DEP
