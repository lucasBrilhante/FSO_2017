main: trabalho_4

trabalho_4: 
	cc -c libseno.c
	ar -cvq libseno.a libseno.o
	ar -t libseno.a
	cc -o trabalho_4 trabalho_4.c libseno.a
clean:
	rm -f *.o
	rm -f trabalho_4
	rm -f *.a

run: trabalho_4
	./trabalho_4