#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "game.h"

void run(){
    int lives = 10;
    char secWord[T_MAX_WORD] = "";
    pickWord(secWord);
    //printf("%s", secWord);

    int *trueLetters = NULL; //bool tab contain discovred lettes
    int sizeWord = len(secWord)-1; //the last char of the word is '\n' due to the extraction of the file.
    trueLetters = malloc(sizeof(int)*sizeWord);
    if(trueLetters == NULL){
        fprintf(stderr, "[!] Not enough space\n\n");
        printf("Press a key to exit.\n");
        scanf("%c");
        exit(0);
    }
    initTab(trueLetters, sizeWord);
    //Adding the first letter of the word
    suggestLetter(secWord, trueLetters, sizeWord, secWord[0]);

    printf("Welcome to the hanged man\n\n");
    while (lives > 0 && !win(trueLetters, sizeWord)){
        printf("you have %d chances left.\n", lives);
        for(int i=0;i<sizeWord;i++){
            if(trueLetters[i] == 1){
                printf("%c", secWord[i]);
            }else{
                printf("*");
            }
        }
        printf("\n");
        int propalTrue = suggestLetter(secWord, trueLetters, sizeWord, readChar());
        if(!propalTrue){
            lives--;
        }
    }
    if(win(trueLetters, sizeWord)){
        printf("You found the word %s", secWord);
    }else{
        printf("You lost the word was %s", secWord);
    }
    free(trueLetters);
}

char readChar(){
    printf(":\\>");
    char character = 0;
    character = getchar();
    character = toupper(character);
    while (getchar() != '\n');
    return character;
}

int win(const int* boolTab, const int size){
    int i=0;
    int remainUndiscoveredCars = 0;
    while (i<size && !remainUndiscoveredCars){
        remainUndiscoveredCars = (boolTab[i]==0);
        i++;
    }
    return !remainUndiscoveredCars;
}

//return 1 if the word contain the letter, else return 0
int suggestLetter(const char *hiddenWord, int *charOk, const int sizeOfWord, const char proposal){
    int trueProposal = 0;
    for(int i=0;i<sizeOfWord;i++){
        if(hiddenWord[i] == proposal){
            charOk[i] = 1;
            trueProposal = 1;
        }
    }
    return trueProposal;
}

void initTab(int *tab,const int size){
    for(int i=0;i<size;i++){
        tab[i] = 0;
    }
}

int len(const char* string){
    int size=0;
    char letter = 0;
    do{
        letter = string[size];
        size++;
    }while (letter != '\0');
    return (size-1);
}