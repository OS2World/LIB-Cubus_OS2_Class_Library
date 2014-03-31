# $Header: W:/Projects/OCL/Watcom/rcs/WCDLL.MAK 1.50 1996/08/11 23:49:41 B.STEIN Release $

!include $(OCL)\COMMON.INC
!include $(OCL)\OCLOBJ.INC

# When compiling the debug version use the following statements
# CFLAGS = $(WATCOM_COMPILE_DLL_DEBUG)

CFLAGS   = $(WATCOM_COMPILE_DLL)
MAKEDEP  = WCDLL.MAK

.all: .\OCLW.DLL .\OIPW.DLL .\OCLWI.LIB 

OCL: .\OCLW.DLL .\OCLWI.LIB 
OIP: .\OIPW.DLL
ALL: OCL OIP

.SUFFIXES:
.SUFFIXES: .cpp .cc

{$(OCL)\Source}.cpp.obj:
  @echo Compiling: $(@B)
  @wpp386 $(CFLAGS) %s

{$(OCL)\Source}.cc.obj:
  @echo Compiling: $(@B)
  @wpp386 $(CFLAGS) %s

.\OCLW.DLL: $(ALLOBJ) OCL_Entry.obj $(OCLFILE) $(MAKEDEP)
  @echo Linking OCLW.DLL ...
  @echo system os2v2 dll initinstance terminstance >OCL.LNK
#  @echo debug all  >>OCL.LNK
  @echo option manyautodata >>OCL.LNK
  @echo option st=65536 >>OCL.LNK
  @echo option c >>OCL.LNK
  @echo option maxe=25 >>OCL.LNK
  @echo option q >>OCL.LNK
  @echo option de 'OCL C++ Class Library 1.50 (WATCOM 10.5a) (c) 1996 by Cubus - All Rights reserved.' >>OCL.LNK
  @echo NAME OCLW >>OCL.LNK
  @echo IMP DosQuerySysState DOSCALLS.368 >>OCL.LNK
  @echo EXP @OCL.EXP >>OCL.LNK
  @echo SEG TY DATA READWRITE LOADONCALL NONSHARED >>OCL.LNK
  @echo SEG TY CODE LOADONCALL >>OCL.LNK
  @echo FIL @OCL.FIL >>OCL.LNK
  @wlink @OCL.LNK
  @del *.obj
  @copy OCLW.DLL $(OCL)\LIB\OCLW.DLL

.\OIPW.DLL: $(OIPOBJ) OIP_Entry.obj $(OIPFILE) $(MAKEDEP)
  @echo Linking OIPW.DLL ...
  @echo system os2v2 dll initinstance terminstance >OCL.LNK
#  @echo debug all  >>OCL.LNK
  @echo option manyautodata >>OCL.LNK
  @echo option st=65536 >>OCL.LNK
  @echo option c >>OCL.LNK
  @echo option maxe=25 >>OCL.LNK
  @echo option q >>OCL.LNK
  @echo option de 'OIP C++ Class Library 1.50 (WATCOM 10.5a) (c) 1996 by Cubus - All Rights reserved.' >>OCL.LNK
  @echo NAME OIPW >>OCL.LNK
  @echo EXP @OIP.EXP >>OCL.LNK
  @echo SEG TY DATA READWRITE LOADONCALL NONSHARED >>OCL.LNK
  @echo SEG TY CODE LOADONCALL >>OCL.LNK
  @echo LIBR OTCPIP >>OCL.LNK
  @echo LIBR OCLW >>OCL.LNK
  @echo FIL @OIP.FIL >>OCL.LNK
  @wlink @OCL.LNK
  @del *.obj
  @copy OIPW.DLL $(OCL)\LIB\OIPW.DLL
 
.\OCLWI.LIB: .\OCLW.DLL .\OIPW.DLL $(MAKEDEP)
  @wlib -n -b .\OCLWI.LIB +.\OCLW.DLL +.\OIPW.DLL

!include $(OCL)\COMMON.DEP
