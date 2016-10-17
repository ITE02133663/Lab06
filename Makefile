server: server.o 
	gcc -pthread  server.o -o server
server.o: server.c
	gcc -pthread -c server.c
client: client.o
        gcc client.o -o client
client.o: client.c
        gcc -c client.c
clean:
	rm server.o client.o
