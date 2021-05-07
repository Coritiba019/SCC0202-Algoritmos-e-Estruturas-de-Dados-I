#include "estacionamento.h"

int main(void)
{
	int a=0,x=0,y=0,hrs=0;
	struct carro dados;
	Pilha *pi;
	Fila *fi;

	pi = cria_pilha();
	fi = cria_fila();

	do
	{
		menu();

		scanf("%d", &a);
		printf("\n");

		if(a==1)
		{
			x=0;

			x = check_in(pi, fi, &dados);

			if(x==0)
			{
				check_out(pi,fi, dados);

				sorteio(pi,fi,dados);
	
				y = disponibilidade(pi,fi, dados);

				if(y!=0)
				{
					rejeicao(y);
				}
			}
			else if(x==1)
			{
				printf("--Já existe um carro com esta placa estacionado no pátio 1--\n\n");
			}
			else if(x==2)
			{
				printf("--Já existe um carro com esta placa estacionado no pátio 2--\n\n");
			}

		}
		else if(a==2)
		{
			imprimir_pilha(pi);
			imprimir_fila(fi);
		}
		else if(a==3)
		{
			break;
		}
	}while(1);

	libera_pilha(pi);
	libera_fila(fi);

	return 0;
}