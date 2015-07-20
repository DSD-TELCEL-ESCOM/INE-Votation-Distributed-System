cli-sqlite: cliente-sqlite.cpp ../sqlite3.o sqlite_gestor.o
	g++ -o cli-sqlite cliente-sqlite.cpp ../sqlite3.o sqlite_gestor.o -ldl -lpthread
sqlite_gestor.o: sqlite_gestor.c ../sqlite3.h
	gcc -c sqlite_gestor.c -ldl -lpthread
