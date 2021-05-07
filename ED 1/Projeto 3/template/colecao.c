#include <stdlib.h>
#include <stdio.h>
#include "colecao.h"

struct _no{
    int valor;
    struct _no* esq;
    struct _no* dir;
    int altura; // Usado somente na AVL
};

struct _c{
    No* inicio;
    int estrutura_id;
};

Colecao* cria_colecao(int estrutura_id) 
{
    Colecao *c, *raiz;

    if(estrutura_id==LISTA_ORDENADO || estrutura_id==LISTA_ULTIMO || estrutura_id==LISTA_PRIMEIRO)
    {
        c = (Colecao *) malloc(sizeof(Colecao));

        if(c!=NULL)
        {
            c->inicio = NULL;
            c->estrutura_id = estrutura_id;
        }

        return c;
    }
    else if(estrutura_id==ARVORE_BINARIA || estrutura_id==ARVORE_AVL)
    {
        raiz = (Colecao *) malloc(sizeof(Colecao));

        if(raiz!=NULL)
        {
            raiz->inicio = NULL;
            raiz->estrutura_id = estrutura_id;
        }

        return raiz;
    }

    return NULL;
}

No* cria_no(int valor)
{
    No *no;

    no = (No *) malloc(sizeof(No));

    if(no!=NULL)
    {
        no->valor = valor;
        no->altura = 0;

        return no;
    }

    return NULL;
}

void adiciona(Colecao* c, int valor)
{
    
    No *no, *ante, *aux, *atual;
    
    no = cria_no(valor);

    if(c->estrutura_id==LISTA_ORDENADO)
    {
       if(c->inicio==NULL)//insere inicio
        {
            no->esq = NULL;
            no->dir = NULL;
            c->inicio = no;
        }
        else//procura onde inserir
        {
            atual = c->inicio;

            while(atual!=NULL && atual->valor < valor)
            {
                ante = atual;
                atual = atual->dir;
            }

            if(atual==(c->inicio))
            {
                no->esq = NULL;
                c->inicio->esq = no;
                no->dir = c->inicio;
                c->inicio = no;
            }
            else
            {
                no->dir = ante->dir;
                no->esq = ante;
                ante->dir = no;

                if(atual!=NULL)
                {
                    atual->esq = no;
                }
            }
        }
    }
    else if(c->estrutura_id==LISTA_ULTIMO)
    {
        aux = c->inicio;
        no->dir = NULL;

        if((c->inicio)==NULL)//lista vazia: insere inicio
        {
            no->esq = NULL;
            c->inicio = no;
        }
        else
        {
            while(aux->dir!=NULL)
            {
                aux = aux->dir;
            }
            aux->dir = no;
            no->esq = aux;
        }
    } 
    else if(c->estrutura_id==LISTA_PRIMEIRO)
    {
        no->dir = c->inicio;
        no->esq = NULL;

        //lista não vazia: apontar para o anterior
        if(c->inicio!=NULL)
        {
            c->inicio->esq = no;
        }

        c->inicio = no; 
    }
    else if(c->estrutura_id==ARVORE_BINARIA)
    {
        inserir_ABB(c, no, valor);
    }
    else if(c->estrutura_id==ARVORE_AVL)
    {
        inserir_AVL(c, no, valor);
    }
    
    return ;
}

int existe(Colecao* c, int valor)
{
    int num=0;
    No *no, *atual;

    if(c->estrutura_id==LISTA_ORDENADO || c->estrutura_id==LISTA_ULTIMO || c->estrutura_id==LISTA_PRIMEIRO)
    {
        no = c->inicio;

        if(c==NULL)
        {
            return 0;
        }

        while(no!=NULL && no->valor!=valor)
        {
            no = no->dir;
        }

        if(no==NULL)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else if(c->estrutura_id==ARVORE_BINARIA || c->estrutura_id==ARVORE_AVL)
    {
        return buscar(c, valor);
    }
    
    return 1;
}
void destroi(Colecao* c)
{
    if(c->estrutura_id==LISTA_ORDENADO || c->estrutura_id==LISTA_ULTIMO || c->estrutura_id==LISTA_PRIMEIRO)
    {
       No *no;

        if(c!=NULL)
        {
            while(c->inicio!=NULL)
            {
                no = c->inicio;
                c->inicio = c->inicio->dir;
                free(no);
            }
            free(c);
        }

        return ;
    }
    else if(c->estrutura_id==ARVORE_BINARIA || c->estrutura_id==ARVORE_AVL)
    {
        libera_ArvBin(c);
    }

    return ;
}

//Funções auxiliares

void libera_NO(No *no)
{
    if(no==NULL)
    {
        return ;
    }

    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvBin(Colecao *raiz)
{
    if(raiz==NULL)
    {
        return ;
    }
    libera_NO(raiz->inicio);//libera cada nó
    free(raiz);//libera a raiz
}

int inserir_ABB(Colecao *c, No *dado, int valor) 
{
    return inserirSubarvore(&(c->inicio), dado, valor); // inicia recursividade
}

int inserirSubarvore(No **no, No *dado, int valor) 
{
    if(*no==NULL) 
    {
        *no = dado;
        return 1; // sucesso
    }
    if((*no)->valor==valor)
    {
        return 0; // erro, elemento ja existe
    }

    return (valor < (*no)->valor) ? inserirSubarvore( &((*no)->esq), dado, valor) : inserirSubarvore( &((*no)->dir), dado, valor);
}

int buscar(Colecao *c, int valor) 
{
    return buscarSubarvore(c->inicio, valor); // inicia recursividade
}

int buscarSubarvore(No *no, int valor) 
{
    if(no==NULL)
    {
        return 0; // nao achou
    }
    if(no->valor==valor)
    {
        return 1; // achou
    }
    if (valor<no->valor)
    {
        return buscarSubarvore(no->esq, valor);
    }
    else
    {
        return buscarSubarvore(no->dir, valor);
    }
}

int inserir_AVL(Colecao *c, No *no, int valor) 
{
    int cresceu = 0; // subarvore nao cresceu, a principio
    return inserirSubarvore_AVL(&(c->inicio), no, valor, &cresceu); // inicia recursividade
}

int inserirSubarvore_AVL(No **p, No *no, int valor, int *cresceu) 
{
    int retorno;
    if(*p==NULL) 
    {
        *p = no;
        no->esq = NULL;
        no->dir = NULL;
        no->altura = 0;
        *cresceu = 1; // subarvore cresceu
        
        return 1; // sucesso
    }
    if((*p)->valor==valor)
    {
        return 0; // erro, elemento ja existe
    }
    retorno = (valor < (*p)->valor) ? inserirSubarvore_AVL( &((*p)->esq), no, valor, cresceu) : inserirSubarvore_AVL( &((*p)->dir), no, valor, cresceu); // insere recursivamente
    // verifica se ha atualizacao a fazer
    if (*cresceu) 
    { // ha algo a fazer, se a subarvore na qual o elemento foi inserido cresceu
        (*p)->altura += (valor < (*p)->valor) ? -1 : 1; // atualize fb
        if ((*p)->altura == 0 || (*p)->altura == 2 || (*p)->altura == -2) 
        {
            *cresceu = 0; // subarvore atual nao cresceu; 0 => balanceamento foi melhorado; 2 ou -2: desbalanceamento sera corrigido
            switch ((*p)->altura) 
            {
                case 2: // arvore pende para a direita
                    if ((*p)->dir->altura == 1) 
                    {
                        // caso 1: sinais iguais
                        rotacionarE(p); // rotaciona a esquerda
                        // atualiza fatores de balanceamento
                        (*p)->altura = 0;
                        (*p)->esq->altura = 0;
                    } 
                    else 
                    {
                        // caso 2: sinais opostos
                        rotacionarDE(p); // rotacao dupla
                        atualizarFB(*p); // atualiza fatores de balanceamento
                    }
                    break;
                case -2: // arvore pende para a esquerda
                    if ((*p)->esq->altura == -1) {
                        // caso 1: sinais iguais
                        rotacionarD(p); // rotaciona a direita
                        // atualiza fatores de balanceamento
                        (*p)->altura = 0;
                        (*p)->dir->altura = 0;
                    } else {
                        // caso 2: sinais opostos
                        rotacionarED(p); // rotacao dupla
                        atualizarFB(*p); // atualiza fatores de balanceamento
                    }
                    break;
            }
        }
        
    }
    return retorno; // retorna resultado da insercao recursiva
}

void rotacionarE(No **p) 
{
    No *realocar, *novaRaiz;
    novaRaiz = (*p)->dir;
    realocar = novaRaiz->esq;
    novaRaiz->esq = *p;
    (*p)->dir = realocar;
    *p = novaRaiz;
    return;
}

void rotacionarD(No **p) 
{
    No *realocar, *novaRaiz;
    novaRaiz = (*p)->esq;
    realocar = novaRaiz->dir;
    novaRaiz->dir = *p;
    (*p)->esq = realocar;
    *p = novaRaiz;
    return;
}

void rotacionarED(No **no) 
{
    rotacionarE(&((*no)->esq)); // rotaciona filho esquerdo a esquerda
    rotacionarD(no); // rotaciona raiz a direita
    
    return;
}

void rotacionarDE(No **no) 
{
    rotacionarD(&((*no)->dir)); // rotaciona filho direito a direita
    rotacionarE(no); // rotaciona raiz a esquerda
    
    return;
}

void atualizarFB(No *no) 
{
    switch (no->altura) 
    { // fator de balanceamento atual do raiz
        case 0:
            no->dir->altura = 0;
            no->esq->altura = 0;
            break;
        case -1:
            no->dir->altura = 1;
            no->esq->altura = 0;
            break;
        case 1:
            no->dir->altura = 0;
            no->esq->altura = -1;
            break;
    }
    no->altura = 0;

    return;
}