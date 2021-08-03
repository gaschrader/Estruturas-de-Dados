#include <stdio.h>

int busca_binaria(int *vet, int item, int fim) {
	int ini = -1;
	while (ini < fim - 1) {
		int i;
		i = (ini + fim) / 2;
		if (vet[i] == item) {
			return i;
		}
		if (vet[i] < item) {
			ini = i;
		} else {
			fim = i;	
		}
	}
	return fim;
} 

void insertion_sort(int vet[], int n, int tam) {
	int j, aux, m;
	m = n - 1;
	if (n <= 1) {
		return;
	}
	insertion_sort(vet, n - 1, tam);
	aux = vet[n - 1];
	j = n - 2;
	while (j >= 0 && vet[j] > aux) {
		vet[j + 1] = vet[j];
		j--;
	}
	vet[j + 1] = aux;
	printf("%d %d %d\n", tam - m, vet[j + 1], busca_binaria(vet, vet[j + 1], n));
}

int main(void) {
	int n, m, i;
	scanf("%d", &n);
	m = n - 1;
	int entrada[n];
	for (i = 0; i < n; i++) {
		scanf("%d", &entrada[i]);
	}
	insertion_sort(entrada, n, n);
	for (i = 0; i < n; i++) {
		printf("%d ", entrada[i]);
	}
  return 0;
}