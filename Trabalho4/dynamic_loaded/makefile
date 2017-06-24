
main: trabalho_4

trabalho_4: 
	gcc -c -fpic libseno.c
	gcc -shared -o libseno.so libseno.o
	gcc -I. -L. -rdynamic -o trabalho_4 trabalho_4.c -ldl


clean:
	rm -f *.o
	rm -f trabalho_4
	rm -f *.so
run: trabalho_4
	./trabalho_4