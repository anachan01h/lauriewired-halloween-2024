#pragma once

#include <stdbool.h>

typedef struct Argument {
    char *body;
    bool is_valid;
} Argument;

Argument argument_new(Argument *template);
void argument_delete(Argument argument);

char **random_components(char *components[], int n);
