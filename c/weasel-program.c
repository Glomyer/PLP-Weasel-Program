#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

char weasel[] = "METHINKS IT IS LIKE A WEASEL";
char letters[] = "ABCDEFGHIJKL MNOPQRSTUVWXYZ";
char base_string[] = "";

int score(char* string){
    int score = 0;
    for(int i = 0; i < strlen(weasel); i++){
        if(string[i] == weasel[i]) score += 1;
    }
    return score;
}

int random_number(int N) { 
    return (int)rand() % N;
}

int main(){
    int iterations = 0, index = 0, probability = 0;
    //1. Lista com 100 copias da string
    char lista[100][29] = {};

    srand(time(NULL) + getpid());
    //Cria string aleatória
    for(int i = 0; i < 28; i++){
        int index = random_number(27);
        char c = letters[index];
        strncat(base_string, &c, 1);
    }

    //Loop principal, se repete enquanto a frase não é igual    
    while(strcmp(base_string, weasel) != 0){
        iterations += 1;

        // Preenche a lista com 100 cópias da string
        for(int i = 0; i < 100; i++){
            strcpy(lista[i], base_string);
        }
    
        // LOOP de substituição
        srand(time(NULL) + getpid());
        for(int i = 0; i < 100; i++){ // Para cada uma das 100 cópias da string
            for(int j = 0; j < 29; j++){
                probability = random_number(100);
                if(probability > 94){ // 5% de chance
                    index = random_number(27);
                    // Se o caractere for igual ou o mesmo do resultado final
                    // pular para o próximo
                    if (lista[i][j] == letters[index] || lista[i][j] == weasel[j])
				        j = (j + 1) % 27;
                    lista[i][j] = letters[index]; // substitui com letra aleatoria                   
                }
            }

            // Se o score for maior que o anterior, substitui
            if(score(lista[i]) > score(base_string)){
                if(strlen(lista[i]) < 30){
                strcpy(base_string, lista[i]);
                }
            }
        } 
        printf("\n[%s]  | --score: %d\n", base_string, score(base_string));      
    }
    printf("\nITERACOES: %d", iterations);

    return 0;
}