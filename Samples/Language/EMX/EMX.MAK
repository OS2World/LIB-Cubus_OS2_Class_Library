!include $(OCLSAMP)\COMMON.INC
!include ..\LANGUAGE.INC

MAKEDEP = EMX.MAK
CFLAGS  = $(S_EMX_COMPILE)
LFLAGS  = $(S_EMX_LINK)
CXFLAGS = $(EMX_COMPILE_DLL)
LXFLAGS = $(EMX_LINK_DLL)

{..\Source}.cpp.obj:
    gcc $(CFLAGS) %s

{..\Source}.cc.obj:
    gcc $(CXFLAGS) %s

language.exe: language.obj {$(LIB)}OCLEMX.LIB $(MAKEDEP)
   rc -r -I E:\EMX\INCLUDE ..\Source\language.rc 
   gcc $(LFLAGS) language.exe language.obj ..\Source\language.def ..\Source\language.res -L$(OCL)\LIB -loclemx -lstdcpp

reseng.dll: res.obj $(MAKEDEP)
   @echo LIBRARY RESENG INITINSTANCE TERMINSTANCE > res.def
   @echo DESCRIPTION 'LANGUAGE Resource Library' >> res.def
   @echo DATA MULTIPLE NONSHARED READWRITE LOADONCALL >> res.def
   @echo CODE LOADONCALL >> res.def
   rc -r -I E:\EMX\INCLUDE ..\Source\reseng.rc 
   gcc $(LXFLAGS) reseng.dll res.obj res.def ..\Source\reseng.res -lstdcpp
   @if exist res.def erase res.def

resger.dll: res.obj $(MAKEDEP)
   @echo LIBRARY RESGER INITINSTANCE TERMINSTANCE > res.def
   @echo DESCRIPTION 'LANGUAGE Resource Library' >> res.def
   @echo DATA MULTIPLE NONSHARED READWRITE LOADONCALL >> res.def
   @echo CODE LOADONCALL >> res.def
   rc -r -I E:\EMX\INCLUDE ..\Source\resger.rc 
   gcc $(LXFLAGS) resger.dll res.obj res.def ..\Source\resger.res -lstdcpp
   @if exist res.def erase res.def

!include ..\LANGUAGE.DEP
