# Logic Captcha
My solution to the LaurieWired 2024 Halloween Programming Challenge. It's a captcha that prompts the user to determine if arguments are valid or not. It works because computers can't think. 😅️

The Makefile only works for Linux (or WSL).

## How to compile
On Linux, just run the command:
```
make
```

Or use `gcc` directly:
```
gcc src/main.c src/arguments.c -o bin/logic_captcha
```

The executable `logic_captcha` will be in the folder `bin`.