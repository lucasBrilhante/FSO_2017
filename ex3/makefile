all: exercicio3

exercicio3.o: exercicio3.c
	gcc -c exercicio3.c -o exercicio3.o

exercicio3: exercicio3.o
	gcc exercicio3.o -o exercicio3

clean:
	-rm -f exercicio3.o
	-rm -f exercicio3

run: exercicio3
	./exercicio3