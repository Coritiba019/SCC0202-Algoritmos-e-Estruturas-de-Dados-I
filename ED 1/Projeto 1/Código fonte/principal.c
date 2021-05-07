#include "listae.h"

int main(void)
{
	Lista *li;
	Aluno al;
	int a=1,num=0,x=0,id=0;
	float med=0;

	li = Criar_Lista();

	while(a!=0)
	{
		Menu();

		scanf("%d", &num);

		if(num==1)
		{

			scanf("%d %f %f %f", &al.id, &al.HorasEstudo, &al.Nota1, &al.Nota2);

			x = Inserir_Final(li, al);

			printf("%d\n", x);
		}
		else if(num==2)
		{
			scanf("%d", &id);

			x = Remove_Lista(li, id);

			if(x==0)
			{
				printf("\nAluno foi não encontrado.\n");
			}
		}
		else if(num==3)
		{
			x = Imprimir_Registros(li);

			if(x==0)
			{
				printf("\nNenhum registro foi encontrado.\n");
			}
		}
		else if(num==4)
		{
			x = Imprimir_Result(li);

			if(x==0)
			{
				printf("\nNenhum registro foi encontrado.\n");
			}
		}
		else if(num==5)
		{
			med = Imprimir_Tempo(li);

			if(med==(-1))
			{
				printf("\nNenhum registro foi encontrado.\n");
			}
			else
			{
				printf("\nTempo médio de estudo da turma: %.2f hora(s).\n", med);
			}
		}
		else if(num==6)
		{
			Libera_Lista(li);
			a = 0;
		}
	}

	return 0;
}