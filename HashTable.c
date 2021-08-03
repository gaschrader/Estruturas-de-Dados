#include <stdio.h>
#include <stdlib.h>

typedef struct aux {
    int chave;
    struct aux *prox;
} NO;

typedef NO *Pont;

int tipoHash (int valor, int tam) {
    return (valor % tam);
}

void Inicializar(Pont Hash[], int tam) {
    int i;
    for (i = 0; i < tam; i++) {
        Hash[i] = NULL;
    }
}

Pont CriaNo(int valor) {
    Pont no = (Pont) malloc(sizeof(NO));
    no->chave = valor;
    return no;
}

Pont Pesquisa(Pont Hash[], int tam, int valor) {
    int IndiceHash = tipoHash(valor, tam);
    Pont no = Hash[IndiceHash];
    while (no) {
        if (no->chave == valor) {
            return no;
        }
        no = no->prox;
    }
    return NULL;
}

void Inserir(Pont Hash[], int tam, int valor) {
    int IndiceHash = tipoHash(valor, tam);
    Pont no = Hash[IndiceHash];
    if (no == NULL) {
        Hash[IndiceHash] = CriaNo(valor);
    } else {
        while (no) {
            if (no->prox == NULL) {
                no->prox = CriaNo(valor);
                break;
            }
            no = no->prox;
        }
    }
}

void Remover(Pont Hash[], int tam, int valor) {
    int IndiceHash = tipoHash(valor, tam);
    if (Hash[IndiceHash] == NULL) {
        return;
    } else {
        Pont aRemover = Pesquisa(Hash, tam, valor);
        if (aRemover == NULL) {
            return;
        } else {
            Pont temp = Hash[IndiceHash]; 
            if (Hash[IndiceHash]->chave == valor) {
                Hash[IndiceHash] = Hash[IndiceHash]->prox;
                return;
            }
            while (temp->prox->chave != valor) {
                temp = temp->prox;
            }
            temp->prox = temp->prox->prox; 
        }
    }
}

int main(void) {
    int i, tamTabela, chavePesquisa, saidaHash;
    scanf("%d", &tamTabela);
    Pont hash[tamTabela];
    Inicializar(hash, tamTabela);

    while(1) {
        scanf("%d", &i);
        if (i < 0) {
            break;
        } else {
            Inserir(hash, tamTabela, i);
        }
    }
    scanf("%d", &chavePesquisa);
    Pont pesquisado = Pesquisa(hash, tamTabela, chavePesquisa);
    if (pesquisado == NULL) {
        printf("Valor não encontrado\n");
    } else {
        Remover(hash, tamTabela, chavePesquisa);
    }
    scanf("%d", &saidaHash);
    printf("[%d] ", saidaHash);

    while (hash[saidaHash]) {
        printf("%d ", hash[saidaHash]->chave);
        hash[saidaHash] = hash[saidaHash]->prox;
    }
    return 0;
}