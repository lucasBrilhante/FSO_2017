all: exercicio3

exercicio3: exercicio3.o
	gcc exercicio3.c lista_encadeada.c -o exercicio3

clean:
	-rm -f exercicio3.o
	-rm -f exercicio3

run: exercicio3
	./exercicio3 ${ARGS}