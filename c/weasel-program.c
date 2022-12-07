#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define NUMBER_OF_COPIES 100
#define CHANCE 5

int score(char *string, char *weasel)
{
	int score;
	for (score = 0; *weasel != '\0'; string++, weasel++)
		score += *string == *weasel;
	return score;
}

int random_number(int N) { 
    return (int)rand() % N;
}

void randomize_copy_char(char **string_list, int n_letters, char letters[], int chance){	
	int i, index;

	for (i = 0; (*string_list)[i] != '\0'; i++) {
		if (random_number(100) < chance) { // 5% de chance
			index = random_number(n_letters); // escolhe index de caractere aleatorio do alfabeto 
			// Mesmo caracter passa para o próximo
			if ((*string_list)[i] == letters[index])
				index = (index + 1) % n_letters;
			(*string_list)[i] = letters[index];
		}
	}
}

int main()
{
	char letters[] = "ABCDEFGHIJKLMNO PQRSTUVWXYZ", *weasel = "METHINKS IT IS LIKE A WEASEL";
	char *base_string, *string_list[NUMBER_OF_COPIES];
	int number_of_letters = strlen(letters), len_weasel = strlen(weasel);
	int index, current_score, best_score, iterations, i;

	/* Gera seed para a função rand() */
	srand(time(NULL) + getpid());

    //Gera a string aleatória
    char string_auxiliar[28];
	for (i = 0; i < 28; i++)
		string_auxiliar[i] = letters[random_number(number_of_letters)];
	string_auxiliar[28] = '\0';
	base_string = string_auxiliar;
    
    //Aloca espaço na memória para as 100 cópias da string
	for (i = 0; i < NUMBER_OF_COPIES; i++){
		string_list[i] = (char*) malloc((29) * sizeof(char));
    }

	/* Loop principal */
	iterations = 0;
	while(score(base_string, weasel) < 28){ // Se repete enquanto as strings são diferentes
		best_score = 0;
		index = 0;
		iterations++;

		for (i = 0; i < NUMBER_OF_COPIES; i++) {
			strcpy(string_list[i], base_string); //Copia a string na posição da lista de 100 cópias
            //Substitui um caractere aleatório da string
			randomize_copy_char(string_list + i, number_of_letters, letters, CHANCE); 

			// Retorna o score da copia atual
			current_score = score(string_list[i], weasel);
            // Se o score atual for maior que o maior score, substitui
			if (current_score > best_score) {
				best_score = current_score;
				index = i; // atribui o index da copia atual
			}
		}
        // substitui a string pela copia no index atribuido
		strcpy(base_string, string_list[index]);
		printf("Iteration %d: %s \tScore: %d\n", iterations, base_string, best_score);
	}
	return 0;
}