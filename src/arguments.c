#include <stdlib.h>
#include <string.h>
#include "../inc/arguments.h"

// Templates for arguments
Argument templates[] = {
    { // Modus Ponens
        "If #0, #1\n"
        "#0\n"
        "Therefore, #1",
        true
    },
    { // Affirming the consequent
        "If #0, #1\n"
        "#1\n"
        "Therefore, #0",
        false
    },
    { // Modus Tollens
        "If #0, #1\n"
        "It's not true that #1\n"
        "Therefore, it's not true that #0",
        true
    },
    { // Denying the antecedent
        "If #0, #1\n"
        "It's not true that #0\n"
        "Therefore, it's not true that #1",
        false
    },
    { // Disjunctive Syllogism
        "#0 or #1\n"
        "It's not true that #0\n"
        "Therefore, #1",
        true
    },
    { // Disjunctive Syllogism
        "#0 or #1\n"
        "It's not true that #1\n"
        "Therefore, #0",
        true
    },
    { // Affirming the disjunct
        "#0 or #1\n"
        "#0\n"
        "Therefore, it's not true that #1",
        false
    },
    { // Affirming the disjunct
        "#0 or #1\n"
        "#1\n"
        "Therefore, it's not true that #0",
        false
    },
    { // Hypothetical Syllogism
        "If #0, #1\n"
        "If #1, #2\n"
        "Therefore, if #0, #2",
        true
    },
    { // Constructive Dilemma
        "If #0, #1\n"
        "If #2, #3\n"
        "#0 or #2\n"
        "Therefore, #1 or #3",
        true
    },
    { // Constructive Dilemma, but wrong
        "If #0, #1\n"
        "If #2, #3\n"
        "#1 or #3\n"
        "Therefore, #0 or #2",
        false
    },
    { // Constructive Dilemma
        "If #0, #1\n"
        "If #2, #1\n"
        "#0 or #2\n"
        "Therefore, #1",
        true
    },
    { // Constructive Dilemma. but wrong
        "If #0, #1\n"
        "If #2, #1\n"
        "#1\n"
        "Therefore, #0 or #2",
        false
    },
    { // Ex contradictione sequitur quodlibet
        "#0\n"
        "It's not true that #0\n"
        "Therefore, #1",
        true
    },
};

const int NUM_TEMPLATES = (sizeof templates) / (sizeof (Argument));

// Atomic sentences
char *atoms[] = {
    "the Earth is flat",
    "it is raining",
    "this sentence is false",
    // Math
    "1 + 1 = 2",
    "1 + 1 = 11",
    "0 is a natural number",
    // Programming
    "Rust is C with training wheels",
    "Web is just CRUD",
    "Linux is better than Windows",
    "DOS is better than Linux",
    // Anime
    "Kurisu is flat",
    "Asuka is a tsundere",
    "Kurisu is my waifu",
    "Kurisu is a mad scientist",
    // Games
    "Sonic is better than Mario",
    "Xbox is dead",
    "Nintendo 3DS is the best console",
    "Nintendo did nothing wrong",
    // LaurieWired
    "Laurie is a hackerwoman",
    "you came from 2038",
    "you should be able to solve this",
};

const int NUM_ATOMS = (sizeof atoms) / (sizeof (char *));

// Creates a new argument from a template
Argument argument_new(Argument *template) {
    int i, j, k, n;

    // Finds the number of ocurrences of components
    int signature[4] = { 0 };
    for (i = 0, n = 0; template->body[i] != '\0'; ++i) {
        if (template->body[i] == '#') {
            n = template->body[++i] - 0x30;
            ++signature[n];
        }
    }

    // Finds the number of different components
    for (i = 0, n = 0; i < 4; ++i)
        if (signature[i] != 0)
            ++n;

    // Generates n random components
    char **components = random_components(atoms, n);

    // Calculates the size of argument
    size_t size = strlen(template->body) + 8;
    for (i = 0; i < 4 && signature[i] != 0; ++i) {
        size -= signature[i] * 2;
        size += signature[i] * strlen(components[i]);
    }

    // Creates new argument struct
    Argument argument = {
        calloc(1, size),
        template->is_valid,
    };

    for (i = 0, j = 0; template->body[i] != '\0'; ++i) {
        // Inserts "> " at the start of a line
        if (i == 0) {
            argument.body[j++] = '>';
            argument.body[j++] = ' ';
        } else if (template->body[i] == '\n') {
            argument.body[j++] = '\n';
            argument.body[j++] = '>';
            argument.body[j++] = ' ';
            ++i;
        }

        // Replaces "#n" with component[n]
        if (template->body[i] == '#') {
            n = template->body[++i] - 0x30;
            for (k = 0; components[n][k] != '\0'; ++k)
                argument.body[j++] = components[n][k];
        } else
            argument.body[j++] = template->body[i];
    }

    // Correct case for the first letter of a line
    for (i = 0; argument.body[i] != '\0'; ++i) {
        if (i == 0 || argument.body[i++] == '\n') {
            i += 2;
            argument.body[i] = toupper(argument.body[i]);
        }
    }

    free(components);
    return argument;
}

// Deletes an argument, freeing the memory allocated by argument_new
void argument_delete(Argument argument) {
    free(argument.body);
}

// Gets random components, to create an argument
char **random_components(char *components[], int n) {
    int i, rcount, rnum;
    bool rnew;
    int *index = malloc(n * sizeof *index);
    char **selected = malloc(n * sizeof *selected);

    rcount = 0;
    while (rcount < n) {
        rnum = rand() % NUM_ATOMS;
        rnew = true;

        for (i = 0; i < rcount; ++i) {
            if (rnum == index[i]) {
                rnew = false;
                break;
            }
        }

        if (rnew)
            index[rcount++] = rnum;
    }

    for (i = 0; i < n; ++i)
        selected[i] = components[index[i]];

    free(index);
    return selected;
}
