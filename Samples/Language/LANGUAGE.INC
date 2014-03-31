.all: language.exe reseng.dll resger.dll 

.SUFFIXES:
.SUFFIXES: .cpp .cc .rc

{..\Source}.rc.res:
   rc -r %s %|fF.RES 

