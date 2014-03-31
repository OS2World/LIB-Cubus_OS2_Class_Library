# $Header: W:/Projects/OCL/EMX/rcs/EMX.MAK 1.50 1996/08/11 23:47:12 B.STEIN Release $

.all: LIB DLL CLEAN

LIB:
  @echo Compiling Library ...
  @nmake /f emxlib.mak

DLL:
  @echo Compiling DLL ...
  @nmake /f emxdll.mak

CLEAN:
  @if exist OCLEMX.LIB  erase OCLEMX.LIB
  @if exist OCLEMX.DLL  erase OCLEMX.DLL
  @if exist OCLEMXI.LIB erase OCLEMXI.LIB
  @if exist OIPEMX.LIB  erase OIPEMX.LIB
  @if exist OIPEMX.DLL  erase OIPEMX.DLL

