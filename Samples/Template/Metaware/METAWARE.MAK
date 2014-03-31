!include $(OCLSAMP)\COMMON.INC
!include ..\TEMPLATE.INC

MAKEDEP = METAWARE.MAK
CFLAGS = $(S_HIGHCPP_COMPILE)
LFLAGS = $(S_HIGHCPP_LINK)

{..\Source}.cpp.obj:
    hc $(CFLAGS) %s

.\Template.EXE: \
  .\Template.obj \
  .\Container.obj \
  .\Template.res \
  {$(LIB)}OCLM.lib \
  $(MAKEDEP)
   hc $(LFLAGS) -l$(OCL)\LIB\OCLM.LIB -o .\Template.EXE .\Template.obj .\Container.obj
   rc .\Template.res .\Template.EXE

!include ..\TEMPLATE.DEP
