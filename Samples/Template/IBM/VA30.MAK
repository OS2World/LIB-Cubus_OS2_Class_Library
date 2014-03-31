!include $(OCLSAMP)\COMMON.INC
!include ..\TEMPLATE.INC

MAKEDEP = VA30.MAK
CFLAGS = $(S_ICC_COMPILE)
LFLAGS = $(S_ICC_LINK)

{..\Source}.cpp.obj:
   icc $(CFLAGS) %s

.\Template.EXE: \
    .\Template.obj \
    .\Container.obj \
    .\Template.res \
    ..\Source\Template.def \
    {$(LIB)}OCLVAI.lib \
    $(MAKEDEP)
   icc @<<
$(LFLAGS) /FeTemplate.EXE
 OCLVAI.lib
 .\Template.obj
 .\Container.obj
 ..\Source\Template.def
<<
   rc .\Template.res Template.EXE

!include ..\TEMPLATE.DEP
