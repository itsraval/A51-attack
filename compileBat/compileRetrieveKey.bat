gcc -c ..\headers\A51LIB.c -o ..\output\A51LIB.o ^
 && gcc -c ..\headers\treeState.c -o ..\output\treeState.o ^
 && gcc -c ..\retrieveKey.c -o ..\output\retrieveKey.o ^
 && gcc ..\output\retrieveKey.o ..\output\A51LIB.o ..\output\treeState.o -o ..\execution\retrieveKey.exe ^
 && ..\execution\retrieveKey.exe > ..\textFiles\retrieveKey.txt