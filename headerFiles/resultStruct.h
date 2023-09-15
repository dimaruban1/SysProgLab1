#ifndef SYSPROGLAB1_RESULTSTRUCT_H
#define SYSPROGLAB1_RESULTSTRUCT_H

#include <stdio.h>
#include <string.h>
#include "hashTable.h"


int maxCount;
int resultLen;
char **Result;

void printResult(){
    for (int i = 0; i < resultLen; i++){
        printf("Word %i: \"%s\"\n", i+1, Result[i]);
    }
    printf("Total words: %i;\n", resultLen);
    printf("Words happen in text: %i times each\n", maxCount);
}

void addWordToResult(char *word){
    resultLen++;
    Result = realloc(Result, sizeof(char) * MAXLENGTH * resultLen);
    char *newWord = malloc(sizeof(char)*MAXLENGTH);;
    strcpy(newWord,word);
    Result[resultLen - 1] = newWord;
}

void formResult(){
    for (int i = 0; i < NUMBER_OF_LETTERS_NO_UPPERCASE; i++){
        struct TableNode *Node = hashTable[i];
        while (Node != NULL){
            if (Node->count == maxCount){
                addWordToResult(Node->word);
            }
            Node = Node->Next;
        }
    }
}

void freeResult(){
    for (int i = 0; i < resultLen; i++){
        free(Result[i]);
    }
    free(Result);
}
#endif //SYSPROGLAB1_RESULTSTRUCT_H
