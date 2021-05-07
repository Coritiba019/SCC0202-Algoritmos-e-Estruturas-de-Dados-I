#include "listae.h"

struct lista
{
	struct aluno dados;
	struct lista *prox;
};

typedef struct lista Elem;


Lista *Criar_Lista()
{
	Lista *li = (Lista *) malloc(sizeof(Lista));

	if(*li!=NULL)
	{
		*li = NULL;
	}

	return li;
}

void Libera_Lista(Lista *li)
{
	Elem *no;

	if(li!=NULL)
	{
	
		while((*li)!=NULL)
		{
			no = *li;
			*li = (*li)->prox;
			free(no);
		}
		free(li);
	}

	return ;
}

void Menu()
{
	printf("\n(1)-Inserir Registro\n"
		   "(2)-Remover Registro\n"
		   "(3)-Imprimir Registros\n"
		   "(4)-Relatório de Aprovação\n"
		   "(5)-Horas de estudo(Média)\n"
		   "(6)-Sair\n\n");
}

int Inserir_Final(Lista *li, Aluno al)
{
	Elem *no = (Elem *) malloc(sizeof(Elem));
	Elem *aux = *li;

	if(li==NULL || no==NULL)
	{
		return 0;
	}

	no->dados = al;
	no->prox = NULL;

	if((*li)==NULL)
	{
		*li = no;
	}
	else
	{
		while(aux->prox!=NULL)
		{
			aux = aux->prox;
		}

		aux->prox = no;

	}

	return 1;
}

int Remove_Lista(Lista *li, int id)
{
	Elem *ant, *no = *li;

	if(li==NULL)
	{
		return -1;
	}

	while(no!=NULL && no->dados.id!=id)
	{
		ant = no;
		no = no->prox;
	}

	if(no==NULL)//não encontrado
	{
		return 0;
	}

	if(no==(*li))//remove o primeiro
	{
		*li = no->prox;
	}
	else
	{
		ant->prox = no->prox;
	}
	free(no);


	return 1;
}

int Imprimir_Registros(Lista *li)
{
	int i=1;
	Elem *no = *li;

	if(*li==NULL || li==NULL)
	{
		return 0;
	}

	while(no!=NULL)
	{
		printf("\nRegistro %d:\n\n", i);
		printf("Identificador do Aluno: %d\n"
			   "Horas de estudo: %.2f\n"
			   "Nota 1 avaliação: %.2f\n"
			   "Nota 2 avaliação: %.2f\n", no->dados.id, no->dados.HorasEstudo, no->dados.Nota1, no->dados.Nota2);
		i++;
		no = no->prox;
	}

	return 1;
}

int Imprimir_Result(Lista *li)
{
	float media=0;
	int i=1;
	Elem *no = *li;

	if(*li==NULL || li==NULL)
	{
		return 0;
	}

	while(no!=NULL)
	{
		printf("\nRegistro %d:\n\n", i);
		printf("Identificador do Aluno: %d\n", no->dados.id);

		media = (no->dados.Nota1+no->dados.Nota2)/2;

		if(media>=5)
		{
			printf("Situação: Aprovado\n");
		}
		else
		{
			printf("Situação: Reprovado\n");
		}

		i++;
		no = no->prox;
	}

	return 1;
}

float Imprimir_Tempo(Lista *li)
{
	float total=0,media=0;
	int i=0;
	Elem *no = *li;

	if(*li==NULL || li==NULL)
	{
		return -1;
	}

	while(no!=NULL)
	{
		total += no->dados.HorasEstudo;
		i++;
		no = no->prox;
	}

	media = total/i;

	return media;
}