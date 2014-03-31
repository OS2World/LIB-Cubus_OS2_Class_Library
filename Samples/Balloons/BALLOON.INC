SERVER = \
.\Server.obj \
.\Server.res

CLIENT = \
.\Client.obj \
.\Client.res

.all: .\Server.EXE .\Client.EXE

.SUFFIXES:

.SUFFIXES: .cpp .rc

{..\Source}.rc.res:
      rc -r %s %|fF.RES
