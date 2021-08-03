#include <stdio.h>
#include <stdlib.h>

typedef struct aux {
    int chave;
    struct aux *esq, *dir;
    int h;
} NO;

typedef NO *Pont;

Pont Inicializar(void) {
    return NULL;
}

Pont Pesquisar(Pont raiz, int x) {
    if (raiz == NULL || raiz->chave == x) {
        return raiz;
    } else if (raiz->chave < x) {
        return Pesquisar(raiz->dir, x);
    } else {
        return Pesquisar(raiz->esq, x);
    }
}

Pont CriarNovoNo(int x) {
    Pont p = (Pont)malloc(sizeof(NO));
    p->chave = x;
    p->esq = NULL;
    p->dir = NULL;
    p->h = 0;
    return p;
}

int Maior(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int Altura(Pont raiz) {
    if (raiz == NULL) {
        return -1;
    } else {
        return raiz->h;
    }
}

Pont GirarDireita(Pont raiz) {
    Pont aux;
    aux = raiz->esq;
    raiz->esq = aux->dir;
    aux->dir = raiz;
    raiz->h = Maior(Altura(raiz->dir), Altura(raiz->esq)) + 1;
    aux->h = Maior(Altura(aux->esq), raiz->h) + 1;
    return aux;
}

Pont GirarEsquerda(Pont raiz) {
    Pont aux;
    aux = raiz->dir;
    raiz->dir = aux->esq;
    aux->esq = raiz;
    raiz->h = Maior(Altura(raiz->dir), Altura(raiz->esq)) + 1;
    aux->h = Maior(Altura(aux->dir), raiz->h) + 1;
    return aux;
}

Pont GiraresqDireita(Pont raiz) {
    raiz->esq = GirarEsquerda(raiz->esq);
    return GirarDireita(raiz);
}

Pont GirardirEsquerda(Pont raiz) {
    raiz->dir = GirarDireita(raiz->dir);
    return GirarEsquerda(raiz);
}

Pont Inserir(Pont raiz, int ch) {
    if (raiz == NULL) {
        return CriarNovoNo(ch);
    }
    if (ch < raiz->chave) {
        raiz->esq = Inserir(raiz->esq, ch);
        if (Altura(raiz->esq) - Altura(raiz->dir) == 2) {
            if (ch < raiz->esq->chave) {
                raiz = GirarDireita(raiz);
            } else {
                raiz = GiraresqDireita(raiz);
            }
        }
    } else {
        if (ch > raiz->chave) {
            raiz->dir = Inserir(raiz->dir, ch);
            if (Altura(raiz->dir) - Altura(raiz->esq) == 2) {
                if (ch > raiz->dir->chave) {
                    raiz = GirarEsquerda(raiz);
                } else {
                    raiz = GirardirEsquerda(raiz);
                }
            }
        }
    }
    raiz->h = Maior(Altura(raiz->esq), Altura(raiz->dir)) + 1;
    return raiz;
}

Pont NoMenorValor(Pont no) {
    Pont atual = no;

    while (atual && atual->esq != NULL) {
        atual = atual->esq;
    }
    return atual;
}

Pont Remover(Pont raiz, int ch) {
    if (raiz == NULL) {
        return raiz;
    }
    if (ch < raiz->chave) {
        raiz->esq = Remover(raiz->esq, ch);
    } else if (ch > raiz->chave) {
        raiz->dir = Remover(raiz->dir, ch);
    } else {
        if (raiz->esq == NULL || raiz->dir == NULL) {
            Pont temp = raiz->esq ? raiz->esq : raiz->dir;
            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else {
                *raiz = *temp;
                free(temp);
            }
        } else {
            Pont temp = NoMenorValor(raiz->dir);
            raiz->chave = temp->chave;
            raiz->dir = Remover(raiz->dir, temp->chave);
        }
    }
    if (raiz == NULL) {
        return raiz;
    }
    raiz->h = Maior(Altura(raiz->esq), Altura(raiz->dir)) + 1;
    if (Altura(raiz->esq) - Altura(raiz->dir) == 2 && raiz->esq->esq - raiz->esq->dir >= 0) {
        return GirarDireita(raiz);
    }
    if (Altura(raiz->esq) - Altura(raiz->dir) == 2 && raiz->esq->esq - raiz->esq->dir < 0) {
        return GiraresqDireita(raiz);
    }
    if (Altura(raiz->esq) - Altura(raiz->dir) == 2 && raiz->dir->esq - raiz->dir->dir >= 0) {
        return GirarEsquerda(raiz);
    }
    if (Altura(raiz->esq) - Altura(raiz->dir) == 2 && raiz->dir->esq - raiz->dir->dir < 0) {
        return GirardirEsquerda(raiz);
    }
    return raiz;
}

int AlturaNo(Pont no) {
    if (no == NULL) {
        return 0;
    } else {
        int AlturaEsq = AlturaNo(no->esq);
        int AlturaDir = AlturaNo(no->dir);
        if (AlturaEsq > AlturaDir) {
            return (AlturaEsq + 1);
        } else {
            return (AlturaDir + 1);
        }
    }
}

int main(void) {
    int i, j, buscado;
    Pont Arvore = Inicializar();

    while (1) {
        scanf("%d", &i);
        if (i >= 0) {
            Arvore = Inserir(Arvore, i);
        } else {
            break;
        }
    }
    int AlturaIni, AlturaDirIni, AlturaEsqIni;
    AlturaIni = AlturaNo(Arvore) - 1;
    AlturaDirIni = AlturaNo(Arvore->dir);
    AlturaEsqIni = AlturaNo(Arvore->esq);

    while (1) {
        scanf("%d", &j);
        if (j >= 0) {
            Pont p = Pesquisar(Arvore, j);
            if (p == NULL) {
                Arvore = Inserir(Arvore, j);
            } else {
                Remover(Arvore, j);
            }
        } else {
            break;
        }
    }
    scanf("%d", &buscado);
    printf("%d, %d, %d\n", AlturaIni, AlturaEsqIni, AlturaDirIni);
    Pont AlturaBuscado = Pesquisar(Arvore, buscado);
    if (AlturaBuscado == NULL) {
        printf("Valor nao encontrado\n");
    } else {
        int AlturaFim, AlturaDirFim, AlturaEsqFim;
        AlturaFim = AlturaNo(AlturaBuscado) - 1;
        AlturaDirFim = AlturaNo(AlturaBuscado->dir);
        AlturaEsqFim = AlturaNo(AlturaBuscado->esq);
        printf("%d, %d, %d\n", AlturaFim, AlturaEsqFim, AlturaDirFim);
    }
    return 0;
}
