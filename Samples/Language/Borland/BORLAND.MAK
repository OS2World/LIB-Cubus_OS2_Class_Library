!include $(OCLSAMP)\COMMON.INC
!include ..\LANGUAGE.INC

MAKEDEP = BORLAND.MAK
CFLAGS  = $(S_BORLAND_COMPILE)
LFLAGS  = $(S_BORLAND_LINK)
CXFLAGS = $(BORLAND_COMPILE_DLL)
LXFLAGS = $(BORLAND_LINK_DLL)

{..\Source}.cpp.obj:
   bcc $(CFLAGS) %s

{..\Source}.cc.obj:
   bcc $(CXFLAGS) %s

language.exe: language.obj language.res {$(LIB)}OCLB.LIB $(MAKEDEP)
   tlink $(LFLAGS) language.obj, language.exe,, OCLB C2MT OS2
   rc language.res language.exe

reseng.dll: res.obj reseng.res $(MAKEDEP)
   @echo LIBRARY RESENG INITINSTANCE TERMINSTANCE > res.def
   @echo DESCRIPTION 'LANGUAGE Resource Library' >> res.def
   @echo DATA MULTIPLE NONSHARED READWRITE LOADONCALL >> res.def
   @echo CODE LOADONCALL >> res.def
   @tlink @<< 
$(LXFLAGS) res.obj , reseng.dll ,, C2MT OS2, res.def
<<
   rc $(RCPACK) reseng.res reseng.dll
   @if exist res.def erase res.def

resger.dll: res.obj resger.res $(MAKEDEP)
   @echo LIBRARY RESGER INITINSTANCE TERMINSTANCE > res.def
   @echo DESCRIPTION 'LANGUAGE Resource Library' >> res.def
   @echo DATA MULTIPLE NONSHARED READWRITE LOADONCALL >> res.def
   @echo CODE LOADONCALL >> res.def
   @tlink @<< 
$(LXFLAGS) res.obj , resger.dll ,, C2MT OS2, res.def
<<
   rc $(RCPACK) resger.res resger.dll
   @if exist res.def erase res.def

!include ..\LANGUAGE.DEP
