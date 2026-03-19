gcc:
	gcc main.c list.c -o list_example.o
clean:
	rm -f list_example.o
run: gcc
	./list_example.o