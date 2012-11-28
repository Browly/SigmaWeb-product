@echo OFF
SET MODEL_NAME=SigCake2

cd "C:\Users\Browly\Documents\16th Grade\Fall\IEOR 131\Product\SigmaWeb-product\sigma\extra\"

REM Basic config defines
SET STD_C_INCLUDES=C:\PROGRA~2\BIOPRO~1\Sigma\Libs\
SET STD_C_LIBS=C:\PROGRA~2\BIOPRO~1\Sigma\Libs\std_lib

REM Compile the C code to .obj files
C:\PROGRA~2\BIOPRO~1\Sigma\Libs\wpp386 SigCake2.c -bc -d0 -w3 -xs -ot -bt=nt -3s -mf -q -i=%STD_C_INCLUDES% -i=%STD_C_INCLUDES%std_inc

REM Do the link step
if exist SigCake2.exe del SigCake2.exe
C:\PROGRA~2\BIOPRO~1\Sigma\Libs\wlink @linker_args.lnk

REM CLEANUP TEMP FILE
if exist SigCake2.obj del SigCake2.obj

SigCake2.exe
