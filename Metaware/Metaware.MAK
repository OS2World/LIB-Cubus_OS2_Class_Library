# $Header: W:/Projects/OCL/Metaware/rcs/Metaware.MAK 1.50 1996/08/11 23:47:41 B.STEIN Release $

.all: LIB DLL CLEAN

LIB:
  @echo Compiling Library ...
  @nmake /f mlib.mak

DLL:
  @echo Compiling DLL ...
  @nmake /f mdll.mak

CLEAN:
  @if exist OCLM.LIB  erase OCLM.LIB
  @if exist OCLM.DLL  erase OCLM.DLL
  @if exist OCLMI.LIB erase OCLMI.LIB
  @if exist OIPM.LIB  erase OIPM.LIB
  @if exist OIPM.DLL  erase OIPM.DLL
