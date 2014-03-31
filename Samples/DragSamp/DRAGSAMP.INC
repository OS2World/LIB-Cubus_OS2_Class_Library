.all: .\DRAGSAMP.EXE

.SUFFIXES:

.SUFFIXES: .cpp .rc

{..\Source}.rc.res:
      rc -r %s %|fF.RES
