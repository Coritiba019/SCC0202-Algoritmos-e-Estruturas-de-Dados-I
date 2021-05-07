#ifndef _ESTACIONAMENTO_H
#define _ESTACIONAMENTO_H
#include <stdio.h>
#include <stdlib.h>
#define MAX 5
#define MAX2 10

struct carro
{
	int placa;
	int hchegada;
	int hsaida;
	float desconto;
};

typedef struct pilha Pilha;
typedef struct fila Fila;


Pilha *cria_pilha();
void libera_pilha(Pilha *pi);
int pilha_cheia(Pilha *pi);
int pilha_vazia(Pilha *pi);
int insere_pilha(Pilha *pi, struct carro al);
int remove_pilha(Pilha *pi, int hrs);
int consulta_pilha(Pilha *pi, struct carro al);
void imprimir_pilha(Pilha *pi);


Fila *cria_fila();
void libera_fila(Fila *fi);
int fila_cheia(Fila *fi);
int fila_vazia(Fila *fi);
int insere_fila(Fila *fi, struct carro al);
int remove_fila(Fila *fi, int hrs);
int consulta_fila(Fila *fi, struct carro al);
void imprimir_fila(Fila *fi);


void menu();
int check_in(Pilha *pi, Fila *fi, struct carro *dados);
int check_out(Pilha *pi, Fila *fi, struct carro dados);
int disponibilidade(Pilha *pi, Fila *fi, struct carro dados);
int rejeicao(int i);
int sorteio(Pilha *pi, Fila *fi, struct carro dados);
void imprimir(Pilha *pi, Fila *fi);

#endif