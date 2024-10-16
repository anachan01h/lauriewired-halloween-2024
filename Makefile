bin/main: bin/ src/main.c src/arguments.c inc/arguments.h
	gcc src/main.c src/arguments.c -o bin/main

bin/:
	mkdir bin

run: bin/main
	./bin/main

.PHONY: clean
clean:
	rm -rf bin
