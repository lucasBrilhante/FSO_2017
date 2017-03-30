HEADERS = estruturas.h func.h

default: exercicio1

exercicio1: exercicio1.o
	gcc exercicio1.c func.c io.c -o exercicio1 -lm

clean:
	rm -f *.o

run: exercicio1
	./exercicio1