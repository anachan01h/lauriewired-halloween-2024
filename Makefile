bin/logic_captcha: bin/ src/main.c src/arguments.c inc/arguments.h
	gcc src/main.c src/arguments.c -o bin/logic_captcha

bin/:
	mkdir bin

run: bin/logic_captcha
	./bin/logic_captcha

.PHONY: clean
clean:
	rm -rf bin
