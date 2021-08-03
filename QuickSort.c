#include <stdio.h>

void swap(int *vet1, int *vet2) {
    int temp;
    temp = *vet1;
    *vet1 = *vet2;
    *vet2 = temp;
}

int partition(int vet[], int menor, int maior) {
    int pivo, i, j;
    pivo = vet[maior];
    i = menor;
    for (j = menor; j < maior; j++) {
        if (vet[j] < pivo) {
            swap(&vet[i], &vet[j]);
            i++;
        }
    }
    swap(&vet[i], &vet[maior]);
    return i;
}

int quicksort(int vet[], int menor, int maior, int k) {
    int pivo = partition(vet, menor, maior);
    if (pivo == (k - 1)) {
        return vet[pivo];
    }
    else if ((k - 1) < pivo) {
        return quicksort(vet, menor, pivo - 1, k);
    }
    else {
        return quicksort(vet, pivo + 1, maior, k);
    }
    return vet[k];
}

void printVet(int *vet, int tam) {
    int i; 
    for (i = 0; i < tam; i++) {
        printf("%d ", vet[i]);
    }
}

int main(void) {
    int n, k, i;
    scanf("%d", &k);
    scanf("%d", &n);
    int vetor[n];
    for (i = 0; i < n; i++) {
        scanf("%d", &vetor[i]);
    }
    int menorelemento = quicksort(vetor, 0, n - 1, k);
    printf("%do menor elemento eh o %d\n", k, menorelemento);
    printVet(vetor, n);
    return 0;
}
