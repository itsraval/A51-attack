gcc -w -c ..\headers\A51LIB.c -o ..\output\A51LIB.o ^
 && gcc -w -c ..\generateRealOutput.c -o ..\output\generateRealOutput.o ^
 && gcc -w ..\output\generateRealOutput.o ..\output\A51LIB.o -o ..\execution\generateRealOutput.exe ^
 && ..\execution\generateRealOutput.exe > ..\textFiles\testUnit.txt