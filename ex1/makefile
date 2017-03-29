HEADERS = struturas.h func.h

default: exercicio1

exercicio1.o: exercicio1.c $(HEADERS)
	gcc -c exercicio1.c -c exercicio1.o

func.o: func.c $(HEADERS)
	gcc -c func.c -o func.o

exercicio1: exercicio1.o $(HEADERS)
	gcc -o exercicio1 exercicio1.o func.o 

clean:
	-rm -f *.o
	-rm -f *~

run: exercicio1
	./exercicio1