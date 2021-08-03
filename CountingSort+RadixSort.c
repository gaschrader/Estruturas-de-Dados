#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MAXTAM 21
#define K 28

void countingsort(char A[][MAXTAM], char B[][MAXTAM], int tam, int digito) {
  int C[K];
  int j;
  for (j = 0; j < K; j++) {
    C[j] = 0;
  }
  for (j = 0; j < tam; j++) {
    if (isspace(A[j][digito])) {
      C[0]++;
    } else {
      C[((A[j][digito]) - 96)]++;
    }
  }
  for (j = 1; j < K; j++) {
    C[j] += C[j - 1];
  }
  for (j = tam - 1; j >= 0; j--) {
    if (isspace(A[j][digito])) {
      strcpy(B[(C[0]) - 1], A[j]);
      C[0]--;
    } else {
      strcpy(B[(C[(A[j][digito] - 96)]) - 1], A[j]);
      C[(A[j][digito]) - 96]--;
    }
  }
  for (j = 1; j < K; j++) {
    printf("%d", C[j]);
  }
  for (j = 0; j < tam; j++) {
    strcpy(A[j], B[j]);
  }
  printf("\n");
}

void radixsort(char A[][MAXTAM], char B[][MAXTAM], int maiortam, int numpalavras) {
  int i;
  for (i = maiortam - 1; i >= 0; i--) {
    countingsort(A, B, numpalavras, i);
  }
}

int main(void) {
  int N, P, M, i, j; // P = posicao e M - quantidade de num a serem exibidos
  scanf("%d", &N);
  int maiortam;
  char string[N][MAXTAM];
  for (i = 0; i < N; i++) {
    scanf("%s", string[i]);
  }
  scanf("%d %d", &P, &M);
  char stringaux[N][MAXTAM];
  i = 0;
  maiortam = 0;

  while (i < N) {
    if (maiortam < strlen(string[i])) {
      maiortam = strlen(string[i]);
    }
    i++;
  }
  i = 0;

  while (i < N) {
    j = 0;
    while (j < strlen(string[i])) {
      string[i][j] = tolower(string[i][j]);
      j++;
    }
    i++;
  }
  for (i = 0; i < N; i++) {
    printf("%s.\n", string[i]);
  }
  printf("%d\n", maiortam);
  i = 0;

  while (i < N) {
    while (strlen(string[i]) < maiortam) {
      strcat(string[i], " ");
    }
    i++;
  }
  radixsort(string, stringaux, maiortam, N);
  i = P - 1;

  while (M > 0) {
    printf("%s\n", string[i]);
    i++;
    M--;
  }
  return 0;
}
