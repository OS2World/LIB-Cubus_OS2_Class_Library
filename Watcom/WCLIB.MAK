# $Header: W:/Projects/OCL/Watcom/rcs/WCLIB.MAK 1.50 1996/08/11 23:49:41 B.STEIN Release $

!include $(OCL)\COMMON.INC
!include $(OCL)\OCLOBJ.INC

# When compiling the debug version use the following statements
# CFLAGS = $(WATCOM_COMPILE_DEBUG)
# LINKFILE = OCLD.LNK

CFLAGS = $(WATCOM_COMPILE)
MAKEDEP = WCLIB.MAK

.all: .\OCLW.LIB .\OIPW.LIB

OCL: .\OCLW.LIB
OIP: .\OIPW.LIB
ALL: OCL OIP


.SUFFIXES:
.SUFFIXES: .cpp

{$(OCL)\Source}.cpp.obj:
  @echo Compiling: $(@B)
  @wpp386 $(CFLAGS) %s

.\OCLW.LIB: $(ALLOBJ) $(MAKEDEP)
  @echo Creating OCLW.LIB ...
  @wlib @<<
-b -c -q .\OCLW.LIB $(LIBOBJ)
<<
  @del *.obj
  @copy OCLW.LIB $(OCL)\LIB\OCLW.LIB

.\OIPW.LIB: $(OIPOBJ) $(MAKEDEP)
  @echo Creating OIPW.LIB ...
  @wlib @<<
-b -c -q .\OIPW.LIB $(OIPLIBOBJ)
<<
  @del *.obj
  @copy OIPW.LIB $(OCL)\LIB\OIPW.LIB

!include $(OCL)\COMMON.DEP
