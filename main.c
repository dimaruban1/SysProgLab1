#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

const int MAXLENGTH = 30;

struct StateStruct{
    int len;
    char **Result;
    int vowelsCount;
    int consonantsCount;
};
///Task: return words that have more vowels than consonants

const int NUMBER_OF_VOWELS = 10;    // including uppercase
const int NUMBER_OF_CONSONANTS = 42;    //same

char vowels[] = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};

char consonants[] = {'b', 'c', 'd', 'f', 'g',
                     'h', 'j', 'k', 'l', 'm',
                     'n', 'p', 'q', 'r', 's',
                     't', 'v', 'w', 'x', 'y',
                     'z', 'B', 'C', 'D', 'F',
                     'G', 'H', 'J', 'K', 'L',
                     'M', 'N', 'P', 'Q', 'R',
                     'S', 'T', 'V', 'W', 'X',
                     'Y', 'Z'};


struct StateStruct State;

bool isVowel(char c){

    for (int i = 0; i < NUMBER_OF_VOWELS; i++){
        if(c == vowels[i]){
            return true;
        }
    }
    return false;
}
bool isLetter(char c){
    for (int i = 0; i < NUMBER_OF_CONSONANTS; i++){
        if(c == consonants[i]){
            return true;
        }
    }
    return isVowel(c);
}
bool WordExistsCaseSensitive(char *word){
    if (State.len == 0){
        return false;
    }
    for (int i = 0; i < State.len; i++){
        if (strcmp(word,State.Result[i]) == 0){
            return true;
        }
    }
    return false;
}
bool WordExistsCaseInsensitive(char *word){
    if (State.len == 0){
        return false;
    }
    char *dictionaryWord = malloc(sizeof(char)*30);
    for(int i = 0; word[i]; i++){
        word[i] = tolower(word[i]);
    }
    for (int i = 0; i < State.len; i++){
        strcpy(dictionaryWord, State.Result[i]);
        for(int i = 0; dictionaryWord[i]; i++){
            dictionaryWord[i] = tolower(dictionaryWord[i]);
        }
        if (strcmp(word,dictionaryWord) == 0){
            return true;
        }
    }
    free(dictionaryWord);
    return false;
}
void AddWord(char *word){
    State.len++;
    State.Result = realloc(State.Result, sizeof(char) * MAXLENGTH * State.len);
    char *newWord = malloc(sizeof(char)*MAXLENGTH);;
    strcpy(newWord,word);
    State.Result[State.len-1] = newWord;
}
void PrintResult(){
    for (int i = 0; i < State.len; i++){
        printf("%s\n", State.Result[i]);
    }
    printf("Total words: %i;\n", State.len);
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
                if (State.vowelsCount > State.consonantsCount){
                    word[len] = '\0';
                    if (!WordExistsCaseInsensitive(word)){
                        AddWord(word);
                    }
                }
                State.consonantsCount = 0;
                State.vowelsCount = 0;
                len = 0;
            }
        }
        else{
            if (isVowel(c)){
                State.vowelsCount++;
            } else {
                State.consonantsCount++;
            }
            isWord = true;
            word[len] = c;
            len++;
        }
    }
    free(word);
}
void FreeResult(){
    for (int i = 0; i < State.len; i++){
        free(State.Result[i]);
    }
    free(State.Result);
}


int main() {
    const char* TEXT = "/home/serg/CLionProjects/SysProgLab1/EnglishText.txt";
    const char* WORDS = "/home/serg/CLionProjects/SysProgLab1/EnglishWords.txt";
    handleFile(TEXT);
    PrintResult();
    FreeResult();
    return 0;
}

