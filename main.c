#include <stdlib.h>
#include <stdbool.h>
#include "headerFiles/hashTable.h"
#include "headerFiles/resultStruct.h"
void ProcessWord(char * word){
    struct TableNode *Node = wordExistsCaseInsensitive(word);
    if (Node == NULL){
        addWordToTable(word);
        if (maxCount == 0){
            maxCount++;
        }
    }
    else{
        Node->count++;
        if (Node->count > maxCount){
            maxCount = Node->count;
        }
    }
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
    formResult();
    fclose(fp);
}

int main() {
    const char* TEXT = "/home/serg/CLionProjects/SysProgLab1/EnglishText.txt";
    const char* WORDS = "/home/serg/CLionProjects/SysProgLab1/EnglishWords.txt";
    initialiseTable();
    handleFile(TEXT);
    printResult();
    freeTable();
    freeResult();
    return 0;
}

