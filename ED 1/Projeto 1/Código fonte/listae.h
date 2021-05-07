#ifndef _LISTAE_H
#define _LISTAE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct aluno 
{
	int id;
	float HorasEstudo;
	float Nota1;
	float Nota2;
}Aluno;

typedef struct lista *Lista;

void Menu();
Lista *Criar_Lista();
void Libera_Lista(Lista *li);
int Inserir_Final(Lista *li, Aluno al);
int Remove_Lista(Lista *li, int id);
int Imprimir_Registros(Lista *li);
int Imprimir_Result(Lista *li);
float Imprimir_Tempo(Lista *li);


#endif