//Nome: Gabriel Schrader Vilas Boas
//RA: 150981
 
#include <stdio.h>
#include <stdlib.h>
 
typedef struct aux {
    int chave;
    struct aux *esq, *dir;
} NO;
 
typedef NO* Pont;
 
Pont Inicializar(void) {
    return NULL;
}
 
Pont Pesquisar(Pont raiz, int x) {
    if (raiz == NULL || raiz->chave == x) {
        return raiz;
    } else if(raiz->chave < x) {
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
    return p;
}
 
Pont Inserir(Pont raiz, Pont no) {
    if (raiz == NULL) {
        return no;
    }
    if (no->chave < raiz->chave) {
        raiz->esq = Inserir(raiz->esq, no);
    } else {
        raiz->dir = Inserir(raiz->dir, no);
    }
    return raiz;
}
 
Pont NoMenorValor(Pont node){
  Pont current = node;
  while (current && current->esq != NULL) {
    current = current->esq;
  }
  return current;
}
 
Pont Remover(Pont raiz, int x) {
    if (raiz == NULL) {
        return raiz;
    }
    if (x < raiz->chave) {
        raiz->esq = Remover(raiz->esq, x);
    } else if (x > raiz->chave) {
        raiz->dir = Remover(raiz->dir, x);
    } else {
        if(raiz->esq == NULL) {
            Pont temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            Pont temp = raiz->esq;
            free(raiz);
            return temp;
        }
        Pont temp = NoMenorValor(raiz->dir);
        raiz->chave = temp->chave;
        raiz->dir = Remover(raiz->dir, temp->chave);
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
            Pont No = CriarNovoNo(i);
            Arvore = Inserir(Arvore, No);             //primeira linha de entrada
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
                Pont No = CriarNovoNo(j);
                Arvore = Inserir(Arvore, No);
            } else {
                Remover(Arvore, j);
            }                                              //segunda linha de entrada
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