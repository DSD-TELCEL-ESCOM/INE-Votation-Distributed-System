###bin/elecciones: src/main.cpp sqlite-3.2.2/sqlite3.o o/sqlite_cpp.o
###	g++ -o bin/elecciones src/main.cpp o/sqlite_cpp.o sqlite-3.2.2/sqlite3.o -ldl -lpthread
compilar: bin/server bin/client
bin/server: src/servidor.cpp o/SocketDatagrama.o sqlite-3.2.2/sqlite3.o o/sqlite_cpp.o h/header.h 
	g++ -o bin/server src/servidor.cpp o/SocketDatagrama.o o/PaqueteDatagrama.o sqlite-3.2.2/sqlite3.o o/sqlite_cpp.o -ldl -lpthread
bin/client: src/cliente.cpp h/header.h o/SocketDatagrama.o
	g++ src/cliente.cpp o/SocketDatagrama.o o/PaqueteDatagrama.o -o bin/client -lpthread
o/SocketDatagrama.o: src/SocketDatagrama.cpp o/PaqueteDatagrama.o h/SocketDatagrama.h
	g++ src/SocketDatagrama.cpp o/PaqueteDatagrama.o -c
	mv SocketDatagrama.o o/SocketDatagrama.o
o/PaqueteDatagrama.o: src/PaqueteDatagrama.cpp h/PaqueteDatagrama.h
	g++ src/PaqueteDatagrama.cpp h/PaqueteDatagrama.h -c
	mv PaqueteDatagrama.o o/PaqueteDatagrama.o
o/sqlite_cpp.o: src/sqlite_cpp.cpp h/sqlite_cpp.h sqlite-3.2.2/sqlite3.h
	g++ -c src/sqlite_cpp.cpp sqlite-3.2.2/sqlite3.h -ldl -lpthread
	mv sqlite_cpp.o o/sqlite_cpp.o
clean:
	rm o/*.o bin/server bin/client
