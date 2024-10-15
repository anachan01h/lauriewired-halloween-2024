typedef struct Argument {
    char *structure;
    int is_valid;
} Argument;

Argument arguments[2] = {
    {
        "If it rains, the Earth is flat\n"
        "The Earth is flat\n"
        "Therefore, it rains",
        0
    },
    {
        "Every human is mortal\n"
        "Socrates is a human\n"
        "Therefore, Socrates is mortal",
        1
    },
};
