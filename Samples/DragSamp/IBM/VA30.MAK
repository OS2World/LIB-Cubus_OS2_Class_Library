# $Header: W:/Projects/OCL/Samples/DragSamp/IBM/rcs/VA30.MAK 1.50 1996/08/11 23:47:57 B.STEIN Release $

!include $(OCLSAMP)\COMMON.INC
!include ..\DRAGSAMP.INC

MAKEDEP = VA30.MAK
CFLAGS = $(S_ICC_COMPILE)
LFLAGS = $(S_ICC_LINK)

{..\Source}.cpp.obj:
   icc $(CFLAGS) %s

.\DRAGSAMP.EXE: .\DRAGSAMP.obj .\DRAGSAMP.res {$(LIB)}OCLVAI.LIB $(MAKEDEP)
   icc @<<
$(LFLAGS) /Fe.\DRAGSAMP.EXE OCLVAI.LIB .\DRAGSAMP.obj
<<
   rc .\DRAGSAMP.res .\DRAGSAMP.EXE

!include ..\DRAGSAMP.DEP
