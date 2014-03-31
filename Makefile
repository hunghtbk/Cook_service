all: lib.c lib.h _service
	gcc -o test test.c
	rm -f *~

clean:
	rm -f *~
	rm -f test