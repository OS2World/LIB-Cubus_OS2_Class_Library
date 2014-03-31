# $Header: W:/Projects/OCL/Watcom/rcs/Watcom.MAK 1.50 1996/08/11 23:49:42 B.STEIN Release $

.all: LIB DLL CLEAN

LIB:      
  @echo Compiling Library ..
  @nmake /nologo /f WCLIB.MAK

DLL:
  @echo Compiling DLL ..
  @nmake /nologo /f WCDLL.MAK

CLEAN:
  @if exist OCLW.LIB  erase OCLW.LIB
  @if exist OCLW.DLL  erase OCLW.DLL
  @if exist OCLWI.LIB erase OCLWI.LIB
  @if exist OIPW.LIB  erase OIPW.LIB
  @if exist OIPW.DLL  erase OIPW.DLL
