gcc -w -c ..\headers\A51LIB.c -o ..\output\A51LIB.o ^
 && gcc -c ..\headers\stringBitLib.c -o ..\output\stringBitLib.o ^
 && gcc -w -c ..\A51.c -o ..\output\A51.o ^
 && gcc -w ..\output\A51.o ..\output\A51LIB.o ..\output\stringBitLib.o -o ..\execution\A51.exe ^
 && ..\execution\A51.exe > ..\textFiles\A51.txt