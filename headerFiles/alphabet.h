#ifndef SYSPROGLAB1_ALPHABET_H
#define SYSPROGLAB1_ALPHABET_H
const int NUMBER_OF_LETTERS = 52;    // including uppercase
const int NUMBER_OF_LETTERS_NO_UPPERCASE = 26;    // including uppercase
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
int letterToNumber(char letter) {
    if (letter >= 'a' && letter <= 'z') {
        return letter - 'a';
    }
    else if (letter >= 'A' && letter <= 'Z') {
        return letter - 'A';
    }
    else {
        return -1;
    }
}
bool isLetter(char letter){
    if (letter >= 'a' && letter <= 'z' || letter >= 'A' && letter <= 'Z') {
        return true;
    }
    return false;
}
#endif //SYSPROGLAB1_ALPHABET_H
