server: server.o 
	gcc -pthread  server.o -o server
server.o: server.c
	gcc -pthread -c server.c
clean:
	rm server.o
