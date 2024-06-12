```c
typedef struct {
    char **words;
    int length;
} Sentence;

Sentence stringToSentence(char *string) {
    int length = 0;

    char **tokens = NULL;
    char *token = strtok(string, " ");

    while (token != NULL)
    {
        tokens = realloc(tokens, (length + 1) * sizeof(char*));
        tokens[length] = (char*)malloc((strlen(token) + 1) * sizeof(char));
        strcpy(tokens[length], token);
        length++;

        token = strtok(NULL, " ");
    }
    Sentence sentence = { .words = tokens, .length = length };

    return sentence;
}
```
