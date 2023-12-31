#ifndef SYSPROGLAB1_HASHTABLE_H
#define SYSPROGLAB1_HASHTABLE_H

#include <string.h>
#include <stdio.h>
#include "alphabet.h"

const size_t MAXLENGTH = 30;
size_t NUMBER_OF_LETTERS_NO_UPPERCASE;
struct TableNode{
    struct TableNode *Next;
    char *word;
    int count;
};

struct TableNode **hashTable;

void initialiseTable(){
    NUMBER_OF_LETTERS_NO_UPPERCASE = 26 + strlen(cyryllicAlphabet);
    hashTable = malloc(sizeof (struct TableNode) * NUMBER_OF_LETTERS_NO_UPPERCASE);
    for (int i = 0; i < NUMBER_OF_LETTERS_NO_UPPERCASE; i++){
        struct TableNode *row = malloc(sizeof(struct TableNode));
        row->word = "n0t a w0rd";
        row->count = -1;
        hashTable[i] = row;
    }
}
struct TableNode* getRowByWord(const char* word){
    char firstChar = word[0];
    int idx = letterToNumber(firstChar);
    struct TableNode *Node = hashTable[idx];
    return Node;
}

// returns index of word, otherwise -1
struct TableNode *wordExists(char *word){
    if (strcmp(word, "") == 0){
        return NULL;
    }
    char *dictionaryWord = malloc(sizeof(char)*MAXLENGTH);

    for (struct TableNode *Node = getRowByWord(word);  Node != NULL && Node->word != NULL; Node = Node->Next){
        strcpy(dictionaryWord, Node->word);
        if (strcmp(word, dictionaryWord) == 0){
            free(dictionaryWord);
            return Node;
        }

    }
    free(dictionaryWord);
    return NULL;
}

void addWordToTable(char *word){
    printf("%s\n",word);
    if (wordExists(word) != NULL){
        return;
    }
    char *newWord = malloc(sizeof(char)*MAXLENGTH);
    strcpy(newWord,word);

    struct TableNode *NewWord = malloc(sizeof(struct TableNode));
    NewWord->count = 1;
    NewWord->Next = NULL;
    NewWord->word = malloc(sizeof(char) * MAXLENGTH);
    strcpy(NewWord->word, newWord);

    struct TableNode *Node = getRowByWord(word);
    while (Node->Next != NULL) {
        Node = Node->Next;
    }
    Node->Next = NewWord;

}

void freeTable(){
    for (int i = 0; i < NUMBER_OF_LETTERS_NO_UPPERCASE; i++){
        free(hashTable[i]);
    }
    free(hashTable);
}
#endif //SYSPROGLAB1_HASHTABLE_H
