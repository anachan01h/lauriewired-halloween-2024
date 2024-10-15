bin/main: bin/ src/main.c
	gcc src/main.c -o bin/main

bin/:
	mkdir bin

run: bin/main
	./bin/main

.PHONY: clean
clean:
	rm -rf bin
