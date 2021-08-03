#include <stdio.h>
#include <stdlib.h>

//VERMELHO = 1
//PRETO = 0

typedef struct aux
{
	int chave;
	int cor;
	struct aux *pai, *esq, *dir;
} NO;

typedef NO *Pont;

struct aux *RAIZ = NULL; //Inicializar

Pont CriarNovoNo(int x)
{
	Pont p = (Pont)malloc(sizeof(NO));
	p->chave = x;
	p->esq = NULL;
	p->dir = NULL;
	p->pai = NULL;
	p->cor = 1;
	return p;
}

Pont Pesquisar(Pont raiz, int x)
{
	if (raiz == NULL || raiz->chave == x)
	{
		return raiz;
	}
	else if (raiz->chave < x)
	{
		return Pesquisar(raiz->dir, x);
	}
	else
	{
		return Pesquisar(raiz->esq, x);
	}
}

void GirarDireita(Pont no)
{
	Pont aux;
	aux = no->esq;
	no->esq = aux->dir;
	if (no->esq)
	{
		no->esq->pai = no;
	}
	aux->pai = no->pai;
	if (!no->pai)
	{
		RAIZ = aux;
	}
	else if (no == no->pai->esq)
	{
		no->pai->esq = aux;
	}
	else
	{
		no->pai->dir = aux;
	}
	aux->dir = no;
	no->pai = aux;
}

void GirarEsquerda(Pont no)
{
	Pont aux;
	aux = no->dir;
	no->dir = aux->esq;
	if (no->dir)
	{
		no->dir->pai = no;
	}
	aux->pai = no->pai;
	if (!no->pai)
	{
		RAIZ = aux;
	}
	else if (no == no->pai->esq)
	{
		no->pai->esq = aux;
	}
	else
	{
		no->pai->dir = aux;
	}
	aux->esq = no;
	no->pai = aux;
}

void InserirBalanceado(Pont z)
{
	Pont pai_z = NULL;
	Pont avo_z = NULL;
	while ((z != RAIZ) && (z->cor != 0) && (z->pai->cor == 1))
	{
		pai_z = z->pai;
		avo_z = z->pai->pai;
		if (pai_z == avo_z->esq)
		{
			Pont tio_z = avo_z->dir;
			if (tio_z != NULL && tio_z->cor == 1)
			{
				avo_z->cor = 1;
				pai_z->cor = 0;
				tio_z->cor = 0;
				z = avo_z;
			}
			else
			{
				if (z == pai_z->dir)
				{
					GirarEsquerda(pai_z);
					z = pai_z;
					pai_z = z->pai;
				}
				GirarDireita(avo_z);
				int t = pai_z->cor;
				pai_z->cor = avo_z->cor;
				avo_z->cor = t;
				z = pai_z;
			}
		}
		else
		{
			Pont tio_z = avo_z->esq;
			if ((tio_z != NULL) && (tio_z->cor == 1))
			{
				avo_z->cor = 1;
				pai_z->cor = 0;
				tio_z->cor = 0;
				z = avo_z;
			}
			else
			{
				if (z == pai_z->esq)
				{
					GirarDireita(pai_z);
					z = pai_z;
					pai_z = z->pai;
				}
				GirarEsquerda(avo_z);
				int t = pai_z->cor;
				pai_z->cor = avo_z->cor;
				avo_z->cor = t;
				z = pai_z;
			}
		}
	}
	RAIZ->cor = 0;
}

Pont Inserir(Pont Arvore, Pont aux)
{
	if (Arvore == NULL)
	{
		return aux;
	}
	if (aux->chave < Arvore->chave)
	{
		Arvore->esq = Inserir(Arvore->esq, aux);
		Arvore->esq->pai = Arvore;
	}
	else if (aux->chave > Arvore->chave)
	{
		Arvore->dir = Inserir(Arvore->dir, aux);
		Arvore->dir->pai = Arvore;
	}
	return Arvore;
}

int AlturaNegra(Pont No, int altura)
{
	if (No == NULL)
	{
		return altura;
	}
	if (No->cor == 0)
	{
		return AlturaNegra(No->esq, altura + 1);
	}
	else
	{
		return AlturaNegra(No->esq, altura);
	}
}

int AlturaNo(Pont no)
{
	if (no == NULL)
	{
		return 0;
	}
	else
	{
		int AlturaEsq = AlturaNo(no->esq);
		int AlturaDir = AlturaNo(no->dir);
		if (AlturaEsq > AlturaDir)
		{
			return (AlturaEsq + 1);
		}
		else
		{
			return (AlturaDir + 1);
		}
	}
}

int main(void)
{
	int i, j, buscado;

	while (1)
	{
		scanf("%d", &i);
		Pont p = CriarNovoNo(i);
		if (i >= 0)
		{
			RAIZ = Inserir(RAIZ, p);
			InserirBalanceado(p);
		}
		else
		{
			break;
		}
	}
	int AlturaIni, AlturaDirIni, AlturaEsqIni;
	int AlturaAtual, AlturaEsqAtual, AlturaDirAtual;
	AlturaIni = AlturaNo(RAIZ)- 1;
	AlturaDirIni = AlturaNo(RAIZ->dir);
	AlturaEsqIni = AlturaNo(RAIZ->esq);
	printf("%d, %d, %d\n", AlturaIni, AlturaEsqIni, AlturaDirIni);
	while (1)
	{
		scanf("%d", &j);
		if (j >= 0)
		{
			Pont k;
			k = Pesquisar(RAIZ, j);
			if (k == NULL)
			{
			    k = CriarNovoNo(j);
				RAIZ = Inserir(RAIZ, k);
				InserirBalanceado(k);
			}
			else
			{
				AlturaAtual = AlturaNo(k)- 1;
				AlturaEsqAtual = AlturaNo(k->esq) ;
				AlturaDirAtual = AlturaNo(k->dir);
				printf("%d, %d, %d\n", AlturaAtual, AlturaEsqAtual, AlturaDirAtual);
			}
		}
		else
		{
			break;
		}
	}
	scanf("%d", &buscado);
	Pont BuscadoValidado = Pesquisar(RAIZ, buscado);
	if (BuscadoValidado == NULL)
	{
		printf("Valor nao encontrado\n");
	}
	else
	{
		printf("%d\n", AlturaNegra(BuscadoValidado, 0));
	}
	return 0;
}
