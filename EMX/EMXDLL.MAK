# $Header: E:/Projects/OCL/EMX/rcs/EMXDLL.MAK 1.5 1996/01/16 10:12:10 B.STEIN Release B.STEIN $

!include $(OCL)\COMMON.INC
!include $(OCL)\OCLOBJ.INC

# When compiling the debug version use the following statements
# CFLAGS = $(EMX_COMPILE_DEBUG)
# LFLAGS = $(EMX_LINK_DEBUG)

CFLAGS = $(EMX_COMPILE_DLL) 
LFLAGS = $(EMX_LINK_DLL)
MAKEDEP = EMXDLL.MAK

.all: .\OCLEMX.DLL .\OIPEMX.DLL .\OCLEMXI.LIB

.SUFFIXES:
.SUFFIXES: .cpp .cc

{$(OCL)\Source}.cpp.obj:
  @echo Compiling: $(@B)
  @gcc $(CFLAGS) %s

{$(OCL)\Source}.cc.obj:
  @echo Compiling: $(@B)
  @gcc $(CFLAGS) %s

.\OCLEMX.DLL: $(ALLOBJ) OCL_Entry.obj $(MAKEDEP)
  @echo Linking OCLEMX.DLL ...
  @gcc $(LFLAGS) .\OCLEMX.DLL *.obj .\OCLEMX.DEF -lstdcpp
  @del *.obj >NUL
  @copy OCLEMX.DLL $(OCL)\LIB\OCLEMX.DLL


.\OIPEMX.DLL: $(OIPOBJ) OIP_Entry.obj $(MAKEDEP)
  @echo Linking OIPEMX.DLL ...
  @gcc $(LFLAGS) .\OIPEMX.DLL *.obj .\OIPEMX.DEF -lstdcpp -lotcpip -loclemx
  @del *.obj >NUL
  @copy OIPEMX.DLL $(OCL)\LIB\OIPEMX.DLL
  
.\OCLEMXI.LIB: .\OCLEMX.DLL .\OIPEMX.DLL
#  @emximp -o .\OCLEMXI.LIB .\OCLEMX.DEF .\OIPEMX.DEF
  @implib .\OCLEMXI.LIB .\OCLEMX.DEF .\OIPEMX.DEF
  @copy OCLEMXI.LIB $(OCL)\LIB\OCLEMXI.LIB


