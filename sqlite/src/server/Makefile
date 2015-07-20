server: servidor.cpp SocketDatagrama.o ../sqlite-3.2.2/sqlite3.o ../sqlite_cpp.o header.h 
	g++ -o server servidor.cpp SocketDatagrama.o PaqueteDatagrama.o ../sqlite-3.2.2/sqlite3.o ../sqlite_cpp.o -ldl -lpthread
SocketDatagrama.o: SocketDatagrama.cpp PaqueteDatagrama.o SocketDatagrama.h
	g++ SocketDatagrama.cpp -c
PaqueteDatagrama.o: PaqueteDatagrama.cpp PaqueteDatagrama.h
	g++ PaqueteDatagrama.cpp -c
clean:
	rm *.o
