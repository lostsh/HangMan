#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "main.h"

#define T_MAX_WORD 100

int main() {
    int coupsRestants = 10;
    char secWord[T_MAX_WORD] = "";
    pickWord(secWord);
    printf("%s", secWord);

    int *lettresTrouvees = NULL; //tableau de boolean contenant les lettres trouvees
    int sizeWord = len(secWord)-1;
    lettresTrouvees = malloc(sizeof(int)*sizeWord);
    if(lettresTrouvees == NULL){
        exit(0);
    }
    initTab(lettresTrouvees, sizeWord);

    while (coupsRestants > 0 && !gagne(lettresTrouvees, sizeWord)){
        printf("Il vous reste %d chances.\n", coupsRestants);
        for(int i=0;i<sizeWord;i++){
            if(lettresTrouvees[i] == 1){
                printf("%c", secWord[i]);
            }else{
                printf("*");
            }
        }
        printf("\n");
        int propalTrue = proposerChar(secWord, lettresTrouvees, sizeWord, lireCaractere());
        if(!propalTrue){
            coupsRestants--;
        }
    }
    if(gagne(lettresTrouvees, sizeWord)){
        printf("Vous avez trouver le mot %s", secWord);
    }else{
        printf("Vous avez perdu.");
    }
    free(lettresTrouvees);
    return 0;
}

char lireCaractere(){
    printf(":\\>");
    char caractere = 0;
    caractere = getchar();
    caractere = toupper(caractere);
    while (getchar() != '\n');
    return caractere;
}

void pickWord(char *secretWord){
    FILE* dictionnaire = NULL;
    dictionnaire = fopen("../dico.txt", "r");
    int nbMots = 0;
    if(dictionnaire != NULL){
        char currentCar = 0;
        while (currentCar != EOF){
            currentCar = fgetc(dictionnaire);
            if(currentCar == '\n')nbMots++;
        }
        nbMots++; //le dernier mot n'a pas de retour a la ligne
        rewind(dictionnaire);
        int indexMot = nombreAleatoire(nbMots);
        for(int i=0;i<indexMot;i++){
            fgets(secretWord, T_MAX_WORD, dictionnaire);
        }
        fclose(dictionnaire);
    }
}

int nombreAleatoire(const int borneSup){
    srand(time(NULL));
    return (rand()%borneSup);
}

int gagne(const int* boolTab, const int size){
    int i=0;
    int isLettreNonTrouve = 0;
    while (i<size && !isLettreNonTrouve){
        isLettreNonTrouve = (boolTab[i]==0);
        i++;
    }
    return !isLettreNonTrouve;
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

//renvoi 1 si la lettre propose est juste et 0 sinon
int proposerChar(const char *hiddenWord, int *charOk, const int sizeOfWord, const char proposition){
    int propositionVrai = 0;
    for(int i=0;i<sizeOfWord;i++){
        if(hiddenWord[i] == proposition){
            charOk[i] = 1;
            propositionVrai = 1;
        }
    }
    return propositionVrai;
}