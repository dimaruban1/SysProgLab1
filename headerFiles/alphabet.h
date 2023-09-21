#ifndef SYSPROGLAB1_ALPHABET_H
#define SYSPROGLAB1_ALPHABET_H

const char *cyryllicAlphabet = "йцукенгшщзхїфівапролджєячсмитьбюЙЦУКЕНГШЩЗХЇФІВАПРОЛДЖЄЯЧСМИТЬБЮ";
int letterToNumber(char letter) {
    if (letter >= 'a' && letter <= 'z') {
        return letter - 'a';
    }
    else if (letter >= 'A' && letter <= 'Z') {
        return letter - 'A';
    }
    else {
        for (int i = 0; i < strlen(cyryllicAlphabet); i++){
            if (cyryllicAlphabet[i] == letter){
                return i;
            }
        }
        return -1;
    }
}
bool isLetter(char letter){
    if (letter >= 'a' && letter <= 'z' || letter >= 'A' && letter <= 'Z') {
        return true;
    }
    return false;
}
bool isCyrillicLetter(char letter){
    for (int i = 0; i < strlen(cyryllicAlphabet); i++){
        if (cyryllicAlphabet[i] == letter){
            return true;
        }
    }
    return false;
}
#endif //SYSPROGLAB1_ALPHABET_H
