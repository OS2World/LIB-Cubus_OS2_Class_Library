!include $(OCLSAMP)\COMMON.INC
!include ..\LISTBOX.INC

MAKEDEP = EMX.MAK
CFLAGS = $(S_EMX_COMPILE)
LFLAGS = $(S_EMX_LINK)

{..\Source}.cpp.obj:
    gcc $(CFLAGS) %s

.\LISTBOX.EXE: \
  .\LISTBOX.obj \
  $(OCL)\LIB\OCLEMX.LIB \
  $(MAKEDEP)
   rc -r -I E:\EMX\INCLUDE ..\Source\LISTBOX.rc 
   gcc $(LFLAGS) .\LISTBOX.EXE .\LISTBOX.obj ..\Source\LISTBOX.def ..\Source\LISTBOX.res -L$(OCL)\LIB -loclemx -lstdcpp

!include ..\LISTBOX.DEP
