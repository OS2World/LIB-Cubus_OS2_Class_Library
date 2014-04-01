!include $(OCLSAMP)\COMMON.INC
!include ..\TEMPLATE.INC

MAKEDEP = EMX.MAK
CFLAGS = $(EMX_COMPILE)
LFLAGS = $(EMX_LINK)

{..\Source}.cpp.obj:
    gcc $(CFLAGS) %s

.\Template.EXE: \
  .\Template.obj \
  .\Container.obj \
  $(OCL)\LIB\OCLEMX.LIB \
  $(MAKEDEP)
   rc -r -I E:\EMX\INCLUDE ..\Source\Template.rc 
   gcc $(LFLAGS) .\Template.EXE .\Template.obj .\Container.obj ..\Source\Template.def ..\Source\Template.res -L$(OCL)\LIB -loclemx -lstdcpp

!include ..\TEMPLATE.DEP
