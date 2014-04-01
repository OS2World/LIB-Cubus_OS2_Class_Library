# $Header: W:/Projects/OCL/rcs/COMMON.INC 1.50 1996/08/11 23:47:04 B.STEIN Release $
# common compiler and link switch definitions for ocl build

ICC_COMPILE = /Tdp /Q /Fi /Si /O /G5 /Gm /C
ICC_LINK = /Tdp /Q /O /Fi /Si /G5 /Gm /B" /noe /e:2"
ICC_COMPILE_DEBUG = /Tdp /Fi /Si /Ti /Tm /Q /Gm /C
ICC_LINK_DEBUG =  /Tdp /Ti /Tm /Gm /B" /noe /e:2"

ICC_COMPILE_DLL = /Ge- $(ICC_COMPILE)
ICC_LINK_DLL = /Ge- $(ICC_LINK)
ICC_COMPILE_DLL_DEBUG = /Ge- $(ICC_COMPILE_DEBUG)
ICC_LINK_DLL_DEBUG = /Ge- $(ICC_LINK_DEBUG)

WATCOM_COMPILE = /fh /otexan /bm /zq /zld /zp4 /5r /mf /xs /bt=os2
WATCOM_LINK = SYS os2v2 pm op m op q op c op maxe=25 op st=65536
WATCOM_COMPILE_DEBUG = /d2 /bm /zq /zld /zp4 /5r /mf /xs /bt=os2
WATCOM_LINK_DEBUG = SYS os2v2 pm d all op q op m op c op maxe=25 op st=65536

WATCOM_COMPILE_DLL = /bd $(WATCOM_COMPILE)
WATCOM_LINK_DLL = SYS os2v2 dll op m op q op c op maxe=25 op st=65536
WATCOM_COMPILE_DLL_DEBUG = /bd $(WATCOM_COMPLE_DEBUG)
WATCOM_LINK_DLL_DEBUG = SYS os2v2 dll d all op q op m op c op maxe=25 op st=65536

BORLAND_COMPILE = /H /L$(LIB) /I$(INCLUDE) /Vmv /sm /X -w-par /c 
BORLAND_LINK = /L$(LIB) /c /Toe C02
BORLAND_COMPILE_DEBUG = /v $(BORLAND_COMPILE)
BORLAND_LINK_DEBUG = /v $(BORLAND_LINK)

BORLAND_COMPILE_DLL = /sd $(BORLAND_COMPILE)
BORLAND_LINK_DLL = /L$(LIB) /w-stk /Tod C02D
BORLAND_COMPILE_DLL_DEBUG = /v $(BORLAND_COMPILE_DLL)
BORLAND_LINK_DLL_DEBUG = /v $(BORLAND_LINK_DLL)

HIGHCPP_COMPILE = -Hthread -586 -O7 -Hexcept -c
HIGHCPP_LINK = -Hthread -Hldopt=/stack:65536
HIGHCPP_COMPILE_DEBUG = -g -Hthread -Hexcept -c
HIGHCPP_LINK_DEBUG = -g -Hthread -Hldopt=/stack:65536

HIGHCPP_COMPILE_DLL = -Hdll $(HIGHCPP_COMPILE)
HIGHCPP_LINK_DLL = -Hdll $(HIGHCPP_LINK) 
HIGHCPP_COMPILE_DLL_DEBUG = $(HIGHCPP_COMPILE_DEBUG)
HIGHCPP_LINK_DLL_DEBUG = -g $(HIGHCPP_LINK_DLL)

HIGHCPP_PPC_COMPILE = -D__PPC__ -Hthread -O7 -Hexcept -c
HIGHCPP_PPC_LINK = -Hthread
HIGHCPP_PPC_COMPILE_DEBUG = -D__PPC__ -g -Hthread -Hexcept -c
HIGHCPP_PPC_LINK_DEBUG = -g $(HIGHCPP_PPC_LINK) 

HIGHCPP_PPC_COMPILE_DLL = -Hdll -D__BUILD_OCL_DLL__ $(HIGHCPP_PPC_COMPILE)
HIGHCPP_PPC_LINK_DLL = -Hdll $(HIGHCPP_PPC_LINK) 
HIGHCPP_PPC_COMPILE_DLL_DEBUG = $(HIGHCPP_PPC_COMPILE_DEBUG)
HIGHCPP_PPC_LINK_DLL_DEBUG = -g $(HIGHCPP_PPC_LINK_DLL)

EMX_COMPILE = -c -DOS2EMX_PLAIN_CHAR -Zmtd -Zcrtdll -Zomf -fhandle-exceptions -fno-implicit-templates
EMX_COMPILE_DEBUG = -g $(EMX_COMPILE)
EMX_LINK = -Zmtd -Zcrtdll -Zomf -o
EMX_LINK_DEBUG = -g $(EMX_LINK)

EMX_COMPILE_DLL = -Zdll $(EMX_COMPILE)
EMX_COMPILE_DLL_DEBUG = -g $(EMX_COMPILE_DLL)
EMX_LINK_DLL = -Zdll $(EMX_LINK)
EMX_LINK_DLL_DEBUG = -g $(EMX_LINK_DLL)

# common compiler and link switch definitions for ocl samples

S_ICC_COMPILE = /Tdp /Q /Gm /O /G5 /C
S_ICC_LINK = /Tdp /Q /Gm /O /G5 /B" /do /nologo /pmtype:pm /e:2 /packd /packc"
S_ICC_COMPILE_DEBUG = /Tdp /Q /Ti /Tm /Gm /C
S_ICC_LINK_DEBUG = /Tdp /Q /Ti /Tm /Gm /B" /de /do /nologo /pmtype:pm /e:2 /packd /packc"

S_ICC_COMPILE_DLL = /Ge- $(ICC_COMPILE)
S_ICC_LINK_DLL = /Ge- $(ICC_LINK)
S_ICC_COMPILE_DLL_DEBUG = /Ge- $(ICC_COMPILE_DEBUG)
S_ICC_LINK_DLL_DEBUG = /Ge- $(ICC_LINK_DEBUG)

S_WATCOM_COMPILE = /otexan /bm /zq /zld /zp4 /5r /mf /xs /bt=os2
S_WATCOM_LINK = SYS os2v2 pm op m op q op c op maxe=25 op st=65536
S_WATCOM_COMPILE_DEBUG = /d2 /otex /bm /zq /zld /zp4 /5r /mf /xs /bt=os2
S_WATCOM_LINK_DEBUG = SYS os2v2 pm d all op q op m op c op symf op maxe=25 op st=65536

S_WATCOM_COMPILE_DLL = /d__BUILD_OCL_DLL__ /bd $(WATCOM_COMPILE)
S_WATCOM_LINK_DLL = SYS os2v2 dll op m op q op c op maxe=25 op st=65536
S_WATCOM_COMPILE_DLL_DEBUG = /d__BUILD_OCL_DLL__ /bd $(WATCOM_COMPLE_DEBUG)
S_WATCOM_LINK_DLL_DEBUG = SYS os2v2 dll d all op q op m op c op symf op maxe=25 op st=65536

S_BORLAND_COMPILE = /L$(LIB) /I$(INCLUDE) /Vmv /sm /Jgd /X -w-par /c
S_BORLAND_LINK = /L$(LIB) /aa /c /Toe C02
S_BORLAND_COMPILE_DEBUG = /v $(BORLAND_COMPILE)
S_BORLAND_LINK_DEBUG = /v $(BORLAND_LINK)

S_BORLAND_COMPILE_DLL = /D__BUILD_OCL_DLL__ /sd $(BORLAND_COMPILE)
S_BORLAND_LINK_DLL = /L$(LIB) /aa /w-stk /c /Tod C02D
S_BORLAND_COMPILE_DLL_DEBUG = /v $(BORLAND_COMPILE_DLL)
S_BORLAND_LINK_DLL_DEBUG = /v $(BORLAND_LINK_DLL)

S_HIGHCPP_COMPILE = -Hthread -586 -O7 -Hexcept -c
S_HIGHCPP_LINK = -Hthread -Hldopt=/stack:65536,/pmtype:pm,/f,/do,/noe,/noi,/nol,/e:2
S_HIGHCPP_COMPILE_DEBUG = -Hthread -g -Hexcept -c
S_HIGHCPP_LINK_DEBUG = -g -Hthread -Hldopt=/de,/pmtype:pm,/nop

S_HIGHCPP_COMPILE_DLL = -Hdll $(HIGHCPP_COMPILE)
S_HIGHCPP_LINK_DLL = -Hdll $(HIGHCPP_LINK) 
S_HIGHCPP_COMPILE_DLL_DEBUG = -Hdll $(HIGHCPP_COMPILE_DEBUG)
S_HIGHCPP_LINK_DLL_DEBUG = -g $(HIGHCPP_LINK_DLL)

S_EMX_COMPILE = -c -DOS2EMX_PLAIN_CHAR -Zmtd -Zcrtdll -Zomf -fhandle-exceptions -fno-implicit-templates
S_EMX_COMPILE_DEBUG = -g $(S_EMX_COMPILE)
S_EMX_LINK = -Zmtd -Zcrtdll -Zomf -o
S_EMX_LINK_DEBUG = -g $(S_EMX_LINK)

S_EMX_COMPILE_DLL = -Zdll $(EMX_COMPILE)
S_EMX_COMPILE_DLL_DEBUG = -g $(EMX_COMPILE_DLL)
S_EMX_LINK_DLL = -Zdll $(EMX_LINK)
S_EMX_LINK_DLL_DEBUG = -g $(EMX_LINK_DLL)

# end of source
