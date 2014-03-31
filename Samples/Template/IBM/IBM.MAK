!include $(OCLSAMP)\COMMON.INC
!include ..\TEMPLATE.INC

MAKEDEP = IBM.MAK
CFLAGS = $(S_ICC_COMPILE)
LFLAGS = $(S_ICC_LINK)

{..\Source}.cpp.obj:
   icc $(CFLAGS) %s

.\Template.EXE: \
    .\Template.obj \
    .\Container.obj \
    .\Template.res \
    ..\Source\Template.def \
    {$(LIB)}OCLII.lib \
    $(MAKEDEP)
   icc @<<
$(LFLAGS) /FeTemplate.EXE
 OCLII.lib
 .\Template.obj
 .\Container.obj
 ..\Source\Template.def
<<
   rc .\Template.res Template.EXE

!include ..\TEMPLATE.DEP
