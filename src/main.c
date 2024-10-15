#include <stdio.h>

#include "../inc/arguments.h"

int main(void) {
    puts("# Logic Captcha");
    puts("The following argument is valid? (y/n)");
    puts(arguments[1].structure);
    char c = getchar();
    switch (c) {
    case 'Y':
    case 'y':
        puts("AI DETECTED!");
        break;
    case 'N':
    case 'n':
        puts("Congratulations! You're not a robot!");
        break;
    }

    return 0;
}
