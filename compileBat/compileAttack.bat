gcc -w -c ..\headers\A51LIB.c -o ..\output\A51LIB.o ^
 && gcc -c ..\headers\treeState.c -o ..\output\treeState.o ^
 && gcc -c ..\retrieveKey.c -o ..\output\retrieveKey.o ^
 && gcc -c ..\attack.c -o ..\output\attack.o ^
 && gcc ..\output\attack.o ..\output\A51LIB.o ..\output\treeState.o ..\output\retrieveKey.o -o ..\execution\attack.exe ^
 && ..\execution\attack.exe > ..\textFiles\keyRegisterState.txt