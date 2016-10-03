main: main.o 
	gcc -pthread  main.o -o main
main.o: main.c
	gcc -pthread -c main.c
clean:
	rm main.o
