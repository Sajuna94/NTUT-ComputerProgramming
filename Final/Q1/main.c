#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
    char** words;
    int wordCount;
} Sentence;

typedef struct
{
    char* word;
    int wordCount;
} RepeatWord;

int repeatCompare(const void *A, const void *B) {
    const RepeatWord* repeatA = (const RepeatWord*)A;
    const RepeatWord* repeatB = (const RepeatWord*)B;
    return strcmp(repeatA->word, repeatB->word);
}

Sentence* splitString(char* string) {
    char** result = NULL;
    char* token = strtok(string, " ");

    int length = 0;

    while (token != NULL)
    {
        result = realloc(result, (length + 1) * sizeof(char*));
        result[length] = (char*)malloc(strlen(token) * sizeof(char));
        strcpy(result[length++], token);

        token = strtok(NULL, " ");
    }
    Sentence *sentence = (Sentence*)malloc(sizeof(Sentence));
    sentence->words = result;
    sentence->wordCount = length;

    return sentence;
}

int main(void) {
    char input[500] = "I like to like the like you like to like but if you like the like the likely like I would like the like you like to like";
    scanf("%[^\n]", input);
    Sentence *sentence = splitString(input);

    char P[100] = "like", Q[100] = "likely"; 
    scanf(" %s", P); 
    scanf(" %s", Q);
    int C = 4, N = 3; 
    scanf(" %d", &C);
    scanf(" %d", &N);

    bool P_List[sentence->wordCount];

    // initial QList
    for (int i = 0; i < sentence->wordCount; i++) {
        P_List[i] = strcmp(sentence->words[i], P) == 0 ? true : false;
    }

    // process repeatWord
    RepeatWord *repeatWords = NULL;
    int numRepeatWord = 0;
    for (int i = 0; i < sentence->wordCount; i++) {
        bool HAS_SAME_WORD = false;
        for (int t = 0; t < numRepeatWord; t++) {
            if (!strcmp(sentence->words[i], repeatWords[t].word)) {
                repeatWords[t].wordCount++;
                HAS_SAME_WORD = true;
            }
        }
        if (!HAS_SAME_WORD) {
            repeatWords = realloc(repeatWords, (numRepeatWord + 1) * sizeof(RepeatWord));
            repeatWords[numRepeatWord].word = sentence->words[i];
            repeatWords[numRepeatWord].wordCount = 1;
            numRepeatWord++;
        }
    }
    qsort(repeatWords, numRepeatWord, sizeof(RepeatWord), repeatCompare);

    // solve
    switch (C)
    {
    case 1:
        for (int i = 0; i < sentence->wordCount; i++) {
            if (P_List[i])
                printf("%s ", Q);
            printf("%s ", sentence->words[i]);
        }
        break;
    case 2:
        for (int i = 0; i < sentence->wordCount; i++) {
            if (P_List[i])
                printf("%s ", Q);
            else
                printf("%s ", sentence->words[i]);
        }
        break;
    case 3:
        for (int i = 0; i < sentence->wordCount; i++) {
            if (!P_List[i])
                printf("%s ", sentence->words[i]);
        }
        break;
    case 4:
        for (int i = 0; i < sentence->wordCount; i++) {
            for (int t = 0; t < numRepeatWord; t++) {
                if (!strcmp(repeatWords[t].word, sentence->words[i])) {
                    if (repeatWords[t].wordCount < N)
                        continue;
                    printf("%s ", sentence->words[i]);
                }
            }
        }
        break;
    case 5: {
        for (int i = 0; i < numRepeatWord; i++) {
            printf("%s:%d\n", repeatWords[i].word, repeatWords[i].wordCount);
        }
        break;
    }
    }
}
