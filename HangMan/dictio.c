/* Author : lostsh
 * This file contains the functions relating to the management of the dictionary
 */

#include <time.h>
#include "dictio.h"

#define T_MAX_WORD 100

void pickWord(char *secretWord){
    FILE* dictionary = NULL;
    dictionary = fopen("../dico.txt", "r");
    int wordNumer = 0;
    if(dictionary != NULL){
        char currentCar = 0;
        while (currentCar != EOF){
            currentCar = fgetc(dictionary);
            if(currentCar == '\n')wordNumer++;
        }
        wordNumer++; //last word don't have line break
        rewind(dictionary);
        int wordIndex = randInt(wordNumer);
        for(int i=0;i<wordIndex;i++){
            fgets(secretWord, T_MAX_WORD, dictionary);
        }
        fclose(dictionary);
    }
}

int randInt(const int upperBound){
    srand(time(NULL));//init rand module
    return (rand()%upperBound);
}