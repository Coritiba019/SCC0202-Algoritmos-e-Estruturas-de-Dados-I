#include "estacionamento.h"

struct fila{
	int inicio, final, qtd;
	struct carro dados[MAX2];
};

struct pilha{
	int qtd;
	struct carro dados[MAX];
};


//PILHA

Pilha *cria_pilha()
{
	Pilha *pi;

	pi = (Pilha *) malloc(sizeof(struct pilha));

	if(pi!=NULL)
	{
		pi->qtd = 0;
	}

	return pi;
}

void libera_pilha(Pilha *pi)
{
	if(pi==NULL)
	{
		return ;
	}
	free(pi);

	return ;
}


int pilha_cheia(Pilha *pi)
{
	if(pi==NULL)
	{
		return -1;
	}

	return (pi->qtd==MAX);
}

int pilha_vazia(Pilha *pi)
{
	if(pi==NULL)
	{
		return -1;
	}

	return (pi->qtd==0);
}

int insere_pilha(Pilha *pi, struct carro al)
{
	if(pi==NULL || pilha_cheia(pi))
	{
		return 0;
	}

	pi->dados[pi->qtd] = al;
	pi->qtd++;

	return 1;
}

int remove_pilha(Pilha *pi, int hrs)
{
	int i=0,n=0;

	if(pi==NULL || pi->qtd==0)
	{
		return 0;
	}

	while(pi->qtd-1>=0 && pi->dados[pi->qtd-1].hsaida<=hrs)
	{
		pi->qtd--;
	}

	return 1;
}

int consulta_pilha(Pilha *pi, struct carro al)
{
	int i=-1,j=0,n=0;

	if(pi==NULL || pi->qtd==0)
	{
		return 0;
	}

	n=pi->qtd;

	while(j<n)
	{
		if(al.placa==pi->dados[j].placa)
		{
			i = j;
			break;
		}
		j++;
	}

	return (i!=(-1));
}

void imprimir_pilha(Pilha *pi)
{
	int i=0,n=0;
	float total=0;

	n = pi->qtd;

	for(i=0;i<n;i++)
	{
		printf("Placa do Carro: %d\n", pi->dados[i].placa);
		printf("Pátio: 1\n");
		total = (pi->dados[i].hsaida - pi->dados[i].hchegada)*3*pi->dados[i].desconto;
		printf("Valor total: R$ %.2f\n\n", total);
	}

	return ;
}



//FILA

Fila *cria_fila()
{
	Fila *fi = (Fila *) malloc(sizeof(struct fila));

	if(fi!=NULL)
	{
		fi->inicio = 0;
		fi->final=0;
		fi->qtd=0;
	}

	return fi;
}

void libera_fila(Fila *fi)
{
	if(fi==NULL)
	{
		return ;
	}
	free(fi);

	return ;
}

int fila_cheia(Fila *fi)
{
	if(fi==NULL)
	{
		return -1;
	}
	
	return (fi->qtd==MAX2);
}

int fila_vazia(Fila *fi)
{
	if(fi==NULL)
	{
		return -1;
	}

	return (fi->qtd==0);
}

int insere_fila(Fila *fi, struct carro al)
{
	if(fi==NULL || fila_cheia(fi))
	{
		return 0;
	}

	fi->dados[fi->qtd] = al;
	fi->inicio = 0;
	fi->qtd++;
	fi->final = fi->qtd;
	

	return 1;	
}

int remove_fila(Fila *fi, int hrs)
{
	int i=0,k=0;

	if(fi==NULL || fila_vazia(fi))
	{
		return 0;
	}

	while(fi->qtd>0 && fi->dados[i].hsaida<=hrs)
	{
		for(k=0;k<fi->qtd-1;k++)
		{
			fi->dados[k] = fi->dados[k+1];
		}

		i++;
		fi->qtd--;
	}

	return 1;
}

int consulta_fila(Fila *fi, struct carro al)
{
	int i=-1,j=0,n=0;

	if(fi==NULL || fi->qtd==0)
	{
		return 0;
	}

	n=fi->qtd;

	while(j<n)
	{
		if(al.placa==fi->dados[j].placa)
		{
			i = j;
			break;
		}
		j++;
	}

	return (i!=(-1));
}

void imprimir_fila(Fila *fi)
{
	int i=0,n=0;
	float total=0;

	n = fi->qtd;

	for(i=0;i<n;i++)
	{
		printf("Placa do Carro: %d\n", fi->dados[i].placa);
		printf("Pátio: 2\n");
		total = (fi->dados[i].hsaida - fi->dados[i].hchegada)*3*fi->dados[i].desconto;
		printf("Valor total: R$ %.2f\n\n", total);
	}

	return ;
}

//Funções do Programa


void menu()
{
	printf("MENU\n(1) Registrar Carro\n"
		"(2) Imprimir Carros\n"
		"(3) Sair\n");
}

int check_in(Pilha *pi, Fila *fi,struct carro *dados)
{
	int x=0;

	printf("CHECK-IN:\n");
	printf("Placa do carro: ");
	scanf("%d", &dados->placa);
	printf("Horario de chegada: ");
	scanf("%d", &dados->hchegada);
	printf("Horario de saida: ");
	scanf("%d", &dados->hsaida);
	printf("\n");

	dados->desconto = 1;

	x = consulta_pilha(pi, *dados);

	if(x==1)
	{
		return 1;
	}

	x = consulta_fila(fi, *dados);

	if(x==2)
	{
		return 2;
	}

	return 0;
}

int check_out(Pilha *pi, Fila *fi, struct carro dados)
{
	int hrs=0;

	if(!pilha_vazia(pi) || !fila_vazia(fi))
	{
		printf("CHECK-OUT:\n\n");

		imprimir(pi,fi);
			
		hrs = dados.hchegada;

		remove_pilha(pi, hrs);
		remove_fila(fi, hrs);
	}

	return 1;
}

int disponibilidade(Pilha *pi, Fila *fi, struct carro dados)
{
	int i=0,hrs=0,saida1=0,saida2=0;

	hrs = dados.hsaida;
	saida1 = pi->dados[pi->qtd-1].hsaida;
	saida2 = fi->dados[fi->qtd-1].hsaida;

	if(pilha_cheia(pi) && fila_cheia(fi))
	{
		i=1;
	}
	else if(dados.hchegada<8 || dados.hchegada>22 || dados.hsaida<8 || dados.hsaida>22)
	{
		i=2;
	}
	else if(pilha_vazia(pi))
	{
		insere_pilha(pi, dados);
	}
	else if(fila_vazia(fi))
	{
		insere_fila(fi, dados);
	}
	else if(!pilha_cheia(pi) && hrs<=saida1)
	{
		insere_pilha(pi, dados);
	}
	else if(!fila_cheia(fi) && hrs>=saida2)
	{
		insere_fila(fi, dados);
	}
	else
	{
		i=3;	
	}
	
	return i;
}

int rejeicao(int i)
{
	if(i==1)
	{
		printf("--Estacionamento está lotado--\n\n");
	}
	else if(i==2)
	{
		printf("--Horário de atendimento(8h ás 22h)--\n\n");
	}
	else if(i==3)
	{

		printf("--Não atende as regras de disponibilidade--\n\n");
	}

	return 1;
}

int sorteio(Pilha *pi, Fila *fi, struct carro dados)
{
	int x=0,hrs=0,qtd=0;
	float total=0;

	qtd = pi->qtd+fi->qtd;
	hrs = dados.hchegada;

	if(qtd>=5 && (hrs==9 || hrs==12 || hrs==15 || hrs==18))
	{
		x = rand()%qtd;

		printf("SORTEIO DE DESCONTOS: \n\n");

		if(x<pi->qtd)
		{
			if(pi->dados[x].desconto==1)
			{
				pi->dados[x].desconto = 0.9;
			}

			total = (pi->dados[x].hsaida-pi->dados[x].hchegada)*3*pi->dados[x].desconto;

			printf("Placa do Carro: %d\n", pi->dados[x].placa);
			printf("Valor total: R$ %.2f\n\n", total);

		}
		else
		{
			x -= pi->qtd;

			if(fi->dados[x].desconto==1)
			{
				fi->dados[x].desconto = 0.9;
			}

			total = (fi->dados[x].hsaida-fi->dados[x].hchegada)*3*fi->dados[x].desconto;

			printf("Placa do Carro: %d\n", fi->dados[x].placa);
			printf("Valor total: R$ %.2f\n\n", total);

		}

	}

	return 1;
}

void imprimir(Pilha *pi, Fila *fi)
{
	int i=0,n=0,j=0,k=0;
	float total=0;

	if(!pilha_vazia(pi))
	{
		printf("Pátio 1: \n\n");

		n = pi->qtd;

		for(i=0;i<n;i++)
		{
			printf("Placa do Carro: %d\n", pi->dados[i].placa);
			total = (pi->dados[i].hsaida - pi->dados[i].hchegada)*3*pi->dados[i].desconto;
			printf("Valor total: R$ %.2f\n\n", total);
		}
	}

	if(!fila_vazia(fi))
	{
		printf("Pátio 2: \n\n");

		k = fi->qtd;

		for(i=0;i<k;i++)
		{
			printf("Placa do Carro: %d\n", fi->dados[j].placa);
			total = (fi->dados[j].hsaida - fi->dados[j].hchegada)*3*fi->dados[j].desconto;
			printf("Valor total: R$ %.2f\n\n", total);
		}
	}
	

	return ;
}