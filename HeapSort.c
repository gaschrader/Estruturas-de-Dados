#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAXTAM 21

//Nome: Gabriel Schrader Vilas Boas
//RA: 150981

void swap(char *string1, char *string2) {
	char temp[MAXTAM];
	strcpy(temp, string1);
	strcpy(string1, string2);
	strcpy(string2, temp);
}

void max_heapify(char vet[][MAXTAM], int tam, int i) {
	int esquerda, direita, max;
	max = i;
	esquerda = (2 * i) + 1;
	direita = (2 * i) + 2;
	if (esquerda < tam && strcmp(vet[esquerda], vet[max]) > 0) {
		max = esquerda;
	}
	if (direita < tam && strcmp(vet[direita], vet[max]) > 0) {
		max = direita;
	}
	if (max != i) {
		swap(vet[i], vet[max]);
		max_heapify(vet, tam, max);
	}
}

void build_max_heap(char vet[][MAXTAM], int tam) {
	int n, i;
	i = (tam / 2) - 1;
	
	while (i >= 0) {
		max_heapify(vet, tam, i);
		i--;
	}
	printf("build_heap:");
	for (i = 0; i < tam; i++)	{
		printf(" %s", vet[i]);
	}
}

void heapsort(char vet[][MAXTAM], int tam) {
	int i;
	int n;
	i = (tam / 2) - 1;
	
	while (i >= 0) {
		max_heapify(vet, tam, i);
		i--;
	}
	i = tam - 1;
	
	while (i >= 0) {
		swap(vet[0], vet[i]);
		max_heapify(vet, i, 0);
		i--;
	}
}

int main(void) {
	int N, M, i, j;
	scanf("%d", &N);
	char cadeia[N][MAXTAM];
	for (i = 0; i < N; i++)	{
		scanf("%s", cadeia[i]);
	}
	scanf("%d", &M);
	int indices[M];
	for (i = 0; i < M; i++) {
		scanf("%d", &indices[i]);
	}
	i = 0;

	while (i < N) {
		j = 0;
		while (j < strlen(cadeia[i])) {
			if (isupper(cadeia[i][j])) {
				printf("a palavra %s eh invalida\n", cadeia[i]);
				return 0;
			}
			if (isalpha(cadeia[i][j])) {
			} else {
				printf("a palavra %s eh invalida\n", cadeia[i]);
				return 0;
			}
			j++;
		}
		i++;
	}
	char saida[M][MAXTAM];
	for (i = 0; i < M; i++)	{
		strcpy(saida[i], cadeia[indices[i]]);
	}
	build_max_heap(saida, M);
	printf("\npalavras:");
	heapsort(saida, M);
	for (i = 0; i < M; i++)	{
		printf(" %s", saida[i]);
	}
	printf("\n");
	return 0;
}