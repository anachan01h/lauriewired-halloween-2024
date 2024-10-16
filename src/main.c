#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../inc/arguments.h"

int main(void) {
    extern Argument templates[];
    extern int NUM_ARG;
    int i;
    char c;
    bool answer = true;

    srand(time(NULL));
    Argument arguments[3] = {
        argument_new(&templates[rand() % NUM_ARG]),
        argument_new(&templates[rand() % NUM_ARG]),
        argument_new(&templates[rand() % NUM_ARG]),
    };

    puts("# Logic Captcha");

    for (i = 0; i < 3; ++i) {
        do {
            printf("\n[%d/3] The following argument is valid? (y/n)\n", i + 1);
            puts(arguments[i].body);
            c = getchar();
            while (getchar() != '\n');
        } while (c != 'Y' && c != 'y' && c != 'N' && c != 'n');

        switch (c) {
        case 'Y':
        case 'y':
            answer = answer && arguments[i].is_valid;
            break;
        case 'N':
        case 'n':
            answer = answer && !arguments[i].is_valid;
            break;
        }

        free(arguments[i].body);
    }

    if (answer)
        puts("Congratulations! You're not a robot!");
    else
        puts("AI DETECTED!");

    return 0;
}
