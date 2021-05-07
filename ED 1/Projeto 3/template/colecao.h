#ifndef __COLECAO__
#define __COLECAO__

#define LISTA_ORDENADO 1
#define LISTA_ULTIMO   2
#define LISTA_PRIMEIRO 3
#define ARVORE_BINARIA 4
#define ARVORE_AVL     5

typedef struct _no No;
typedef struct _c Colecao;

Colecao* cria_colecao(int estrutura_id);
No* cria_no(int valor);
void adiciona(Colecao* c, int valor);
int existe(Colecao* c, int valor);
void destroi(Colecao* c);

//Funções auxiliares

void libera_NO(No *no);
void libera_ArvBin(Colecao *raiz);
int inserir_ABB(Colecao *c, No *dado, int valor);
int inserirSubarvore(No **no, No *dado, int valor);
int buscar(Colecao *c, int valor);
int buscarSubarvore(No *no, int valor);
void rotacionarE(No **p);
void rotacionarD(No **p);
void rotacionarED(No **no);
void rotacionarDE(No **no);
void atualizarFB(No *no);
int inserir_AVL(Colecao *c, No *no, int valor);
int inserirSubarvore_AVL(No **p, No *no, int valor, int *cresceu);

#endif