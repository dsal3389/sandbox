#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void switch_chars(size_t len, char *word){
    /*
        switching between the first and the last char in a string
    */
    int i;
    char first;
    memcpy(&first, word, sizeof(char));

    for(i=1;i<len;i++)
        memcpy(&word[i-1], &word[i], sizeof(char));
    word[len -1] = first;
}

int necklace(char word[], char *x){
    /*
        checking if word can be "necklaced" to x, and return a correct exit status
    */
    size_t len = strlen(word);
    int max;
    memcpy(&max, &len, sizeof(int));

    while(strcmp(word, x) && max){
        switch_chars(len, word);
        printf("%s\n", word);
        max--;
    }
    return !max; // max returns 0 if not found, and return a number heigher then 0 if found
}

int main(int argc, char *argv[]){
    if(argc <= 2){
        printf("Missing arguments\n");
        return 1;
    }
    return necklace(argv[1], argv[2]);
}
