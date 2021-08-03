#include <stdio.h>

int bubblesort(int *vet, int n) {
	int i, j, aux, count = 0;
	for (i = 1; i < n; i++){
		for (j = 0; j < n - i; j++) {
			if (vet[j] > vet[j + 1]) {
				aux = vet[j];
				vet[j] = vet[j + 1];
				vet[j + 1] = aux;
				count++;
			}
		}
	}
	return count;
}

int main() {
	int entrada, i;
	scanf("%d", &entrada);
	int seq[entrada];
	for (i = 0; i < entrada; i++) {
		scanf("%d", &seq[i]);
	}
	int saida = bubblesort(seq, entrada);
	for (i = 0; i < entrada; i++) {
		printf("%d ", seq[i]);
	}
	if (saida % 2 == 0) {
		printf("\nCarlos");
	} else {
		printf("\nMarcelo");
	}
	return 0;
}