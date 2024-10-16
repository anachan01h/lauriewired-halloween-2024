#include <stdlib.h>
#include "../inc/arguments.h"

// Templates for arguments
Argument templates[] = {
    { // Modus Ponens
        "If #0, #1\n"
        "#0\n"
        "#1",
        true
    },
    { // Affirming the consequent
        "If #0, #1\n"
        "#1\n"
        "#0",
        false
    },
    { // Modus Tollens
        "If #0, #1\n"
        "It's not true that #1\n"
        "It's not true that #0",
        true
    },
    { // Denying the antecedent
        "If #0, #1\n"
        "It's not true that #0\n"
        "It's not true that #1",
        false
    }
};

const int NUM_ARG = (sizeof templates) / (sizeof (Argument));

// Atomic sentences
char *atoms[] = {
    "the Earth is flat",
    "it is raining",
    "Kurisu is beautiful",
    "Laurie is intelligent",
};

// Creates a new argument from a template
Argument argument_new(Argument *template) {
    int i, j, k, n;
    char **components = random_components(atoms);
    Argument argument = {
        malloc(1000),
        template->is_valid,
    };

    for (i = 0, j = 0; template->body[i] != '\0'; ++i) {
        if (template->body[i] == '#') {
            n = template->body[++i] - 0x30;
            for (k = 0; components[n][k] != '\0'; ++k)
                argument.body[j++] = components[n][k];
        } else
            argument.body[j++] = template->body[i];
    }

    free(components);
    return argument;
}

// Gets random components, to create an argument
char **random_components(char *components[]) {
    int n1, n2;
    char **selected = malloc(2 * sizeof *selected);
    n1 = rand() % 4;
    do {
        n2 = rand() % 4;
    } while (n1 == n2);

    selected[0] = components[n1];
    selected[1] = components[n2];

    return selected;
}
