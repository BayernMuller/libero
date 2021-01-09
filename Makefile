main : TCPServer.o main.o
	g++ -o main main.o TCPServer.o

TCPServer.o : TCPServer.cpp
	g++ -c -o TCPServer.o TCPServer.cpp

main.o :
	g++ -c -o main.o main.cpp

clean :
	rm *.o main
