/* -----------------------------------------------------------------------------
 * ### logic_captcha
 * Prompts the user to determine if arguments are valid or not.
 * By: anachan01h
 * -------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../inc/arguments.h"

int main(void) {
    extern Argument templates[];
    extern int NUM_TEMPLATES;
    int i;
    char c;
    bool answer = true;

    // Generates 3 random arguments
    srand(time(NULL));
    Argument arguments[3] = {
        argument_new(&templates[rand() % NUM_TEMPLATES]),
        argument_new(&templates[rand() % NUM_TEMPLATES]),
        argument_new(&templates[rand() % NUM_TEMPLATES]),
    };

    puts("# Logic Captcha");

    for (i = 0; i < 3; ++i) {
        // Prints the argument, and waits for the answer
        do {
            printf("\n[%d/3] The following argument is valid? (y/n)\n", i + 1);
            puts(arguments[i].body);
            c = getchar();
            while (getchar() != '\n');
        } while (c != 'Y' && c != 'y' && c != 'N' && c != 'n');

        // Process the answer
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

        // Deletes the argument, for memory safety
        argument_delete(arguments[i]);
    }

    // Prints the result
    if (answer)
        puts("You're smarter than ChatGPT! ^-^");
    else
        puts("As a human, you're actually a good AI. :o");

    return 0;
}
