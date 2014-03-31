.all: .\Editor.exe

.SUFFIXES:

.SUFFIXES: .cpp .rc

{..\Source}.rc.res:
      rc -r %s %|fF.RES
