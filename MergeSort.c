#include <stdio.h>

int Merge(int vet[], int ini, int meio, int fim, int K) {
	int n1, n2, i, j, k, count;
	n1 = meio - ini + 1;
	n2 = fim - meio;
	int L[n1 + 1], R[n2 + 1];
	for (i = 0; i < n1; i++) {
		L[i] = vet[ini + i];
	}
	for (j = 0; j < n2; j++) {
		R[j] = vet[meio + j + 1];
	}
	L[n1 + 1] = 9999999;
	R[n2 + 1] = 9999999;
	i = 0;
	j = 0;
	count = 0;

	while (i < n1 && j < n2) {
		if (L[i] > (K * R[j])) {
			count += (n1 - i);
			j++;
		} else {
			i++;
		}
	}

	i = 0;
	j = 0;
	k = ini;

	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			vet[k] = L[i];
			i++;
		} else {
			vet[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		vet[k] = L[i];
		i++;
		k++;
	}

	while (j < n2) {
		vet[k] = R[j];
		j++;
		k++;
	}
	return count;
}

int MergeSort(int vet[], int ini, int fim, int K) {
	if (ini >= fim) {
		return 0;
	}
	int meio, count;
	meio = ini + (fim - ini) / 2;
	count = Merge(vet, ini, meio, K) + Merge(vet, meio + 1, fim, K) + Merge(vet, ini, meio, fim, K);
	return count;
}

int main(void) {
	int i, n, K;
	scanf("%d", &n);
	scanf("%d", &K);
	int vetor[n];
	for (i = 0; i < n; i++) {
		scanf("%d", &vetor[i]);
	}
	printf("%d\n", MergeSort(vetor, 0, n - 1, K));
	return 0;
}
