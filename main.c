#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

const int MAXLENGTH = 30;

struct DictNode{
    struct DictNode *Next;
    char *word;
    int count;
};
struct StateStruct{
    int dictLen;
    int maxCount;
    int resultLen;
    char **Result;
    struct DictNode *DictHead;
};
///Task: return words that have more vowels than consonants

const int NUMBER_OF_LETTERS = 52;    // including uppercase

char letters[] = {'a', 'e', 'i', 'o', 'u',
                   'A', 'E', 'I', 'O', 'U',
                   'b', 'c', 'd', 'f', 'g',
                   'h', 'j', 'k', 'l', 'm',
                   'n', 'p', 'q', 'r', 's',
                   't', 'v', 'w', 'x', 'y',
                   'z', 'B', 'C', 'D', 'F',
                   'G', 'H', 'J', 'K', 'L',
                   'M', 'N', 'P', 'Q', 'R',
                   'S', 'T', 'V', 'W', 'X',
                   'Y', 'Z'};


struct StateStruct State;

bool isLetter(char c){
    for (int i = 0; i < NUMBER_OF_LETTERS; i++){
        if(c == letters[i]){
            return true;
        }
    }
    return false;
}
int WordExistsCaseInsensitive(char *word){
    if (State.dictLen == 0){
        return -1;
    }
    char *dictionaryWord = malloc(sizeof(char)*MAXLENGTH);
    struct DictNode *Node = State.DictHead;
    for (int i = 0; i < State.dictLen; i++){

        strcpy(dictionaryWord, Node->word);
        if (strcasecmp(word, dictionaryWord) == 0){
            return i;
        }
        Node = Node->Next;
        if (Node == NULL){
            return -1;
        }
    }
    free(dictionaryWord);
    return -1;
}
void AddWordToResult(char *word){
    State.resultLen++;
    State.Result = realloc(State.Result, sizeof(char) * MAXLENGTH * State.resultLen);
    char *newWord = malloc(sizeof(char)*MAXLENGTH);;
    strcpy(newWord,word);
    State.Result[State.resultLen - 1] = newWord;
}
void AddWordToDictionary(char *word){
    if (WordExistsCaseInsensitive(word) != -1){
        return;
    }
    State.dictLen++;
    char *newWord = malloc(sizeof(char)*MAXLENGTH);;
    strcpy(newWord,word);
    struct DictNode* NewDict = malloc(sizeof(struct DictNode));
    NewDict->count = 1;
    NewDict->Next = NULL;
    NewDict->word = malloc(sizeof(char) * MAXLENGTH);
    strcpy(NewDict->word, newWord);

    if (State.DictHead == NULL) {
        State.DictHead = NewDict;
    } else {
        struct DictNode* Node = State.DictHead;
        while (Node->Next != NULL) {
            Node = Node->Next;
        }
        Node->Next = NewDict;
    }

}
void ProcessWord(char * word){
    int index = WordExistsCaseInsensitive(word);
    if (index == -1){
        AddWordToDictionary(word);
        if (State.maxCount == 0){
            State.maxCount++;
        }
    }
    else{
        struct DictNode *Node = State.DictHead;
        for (int i = 0; i < index; i++){
            Node = Node->Next;
        }
        Node->count++;
        int count = Node->count;

        if (count > State.maxCount){
            State.maxCount = count;
        }
    }
}
void PrintResult(){
    for (int i = 0; i < State.resultLen; i++){
        printf("Word %i: \"%s\"\n", i+1, State.Result[i]);
    }
    printf("Total words: %i;\n", State.resultLen);
    printf("Words happen in text: %i times each\n", State.maxCount);
}
void handleFile(const char* path){
    FILE *fp = fopen(path,"r");
    bool isWord = false;
    char *word = malloc(MAXLENGTH);
    int len = 0;
    char c = ' ';
    while(c != EOF){
        c = (char)fgetc(fp);
        if (!isLetter(c)){
            if (!isWord){}
            else{
                    if (len == 0){}
                    else{
                        word[len] = '\0';
                        ProcessWord(word);
                        len = 0;
                }
            }
        }
        else{
            isWord = true;
            word[len] = c;
            len++;
            if (len == MAXLENGTH){
                word[len] = '\0';
                ProcessWord(word);
                len = 0;
            }
        }
    }
    free(word);
    struct DictNode *Node = State.DictHead;
    for (int i = 0; i < State.dictLen; i++){
        if (Node->count == State.maxCount){
            AddWordToResult(Node->word);
        }
        Node = Node->Next;
    }
    fclose(fp);
}
void FreeResult(){
    for (int i = 0; i < State.resultLen; i++){
        free(State.Result[i]);
    }
    free(State.Result);

    struct DictNode *Node = State.DictHead;
    for (int i = 0; i < State.dictLen; i++){
        struct DictNode *NewNode = Node->Next;
        free(Node->word);
        free(Node);
        Node = NewNode;
    }
}


int main() {
    const char* TEXT = "/home/serg/CLionProjects/SysProgLab1/EnglishText.txt";
    const char* WORDS = "/home/serg/CLionProjects/SysProgLab1/EnglishWords.txt";
    handleFile(WORDS);
    PrintResult();
    FreeResult();
    return 0;
}

