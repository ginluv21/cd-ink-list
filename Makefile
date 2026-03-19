gcc:
	gcc menu.c list.c ui.c -o list_example.o
clean:
	rm -f list_example.o
run: gcc
	./list_example.o