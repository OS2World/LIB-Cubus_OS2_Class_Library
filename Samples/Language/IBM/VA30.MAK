!include $(OCLSAMP)\COMMON.INC
!include ..\LANGUAGE.INC

MAKEDEP = VA30.MAK
CFLAGS  = $(S_ICC_COMPILE)
LFLAGS  = $(S_ICC_LINK)
CXFLAGS = $(ICC_COMPILE_DLL)
LXFLAGS = $(ICC_LINK_DLL)

{..\Source}.cpp.obj:
   icc $(CFLAGS) %s

{..\Source}.cc.obj:
   icc $(CXFLAGS) %s


language.exe: language.obj language.res {$(LIB)}OCLVA.LIB $(MAKEDEP)
   icc @<<
$(LFLAGS) /Fe language.exe language.obj OCLVA.LIB
<<
   rc $(RCPACK) language.res language.exe

reseng.dll: res.obj reseng.res $(MAKEDEP)
   @echo LIBRARY RESENG INITINSTANCE TERMINSTANCE > res.def
   @echo DESCRIPTION 'LANGUAGE Resource Library' >> res.def
   @echo DATA MULTIPLE NONSHARED READWRITE LOADONCALL >> res.def
   @echo CODE LOADONCALL >> res.def
   icc @<<
$(LXFLAGS) /Fe reseng.dll res.obj res.def
<<
   rc $(RCPACK) reseng.res reseng.dll
   @if exist res.def erase res.def

resger.dll: res.obj resger.res $(MAKEDEP)
   @echo LIBRARY RESGER INITINSTANCE TERMINSTANCE > res.def
   @echo DESCRIPTION 'LANGUAGE Resource Library' >> res.def
   @echo DATA MULTIPLE NONSHARED READWRITE LOADONCALL >> res.def
   @echo CODE LOADONCALL >> res.def
   icc @<<
$(LXFLAGS) /Fe resger.dll res.obj res.def
<<
   rc $(RCPACK) resger.res resger.dll
   @if exist res.def erase res.def

!include ..\LANGUAGE.DEP
