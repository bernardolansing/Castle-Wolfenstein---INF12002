#include <stdio.h>
#include <string.h>

#define TAM 5

typedef struct
{
	char user[31];
	int pont;
} PLAYER;
PLAYER player[TAM];


void ranking()
{
	FILE *fp;
	fp = fopen("highscores.bin", "rb+");
   // rewind(fp);
	printf("Ranking:\n");
	int i =0;
		for (i; i < TAM; i++){
	  if(fread(&player, sizeof(PLAYER), 1, fp))
		{
			printf("%s\nPontuacao: %d\n", player->user, player->pont);
		}
		}



}

void atualiza_ranking()
{
	char nome[31];
	int pontuacao;
	printf("Digite pontuacao");
	scanf("%d", &pontuacao);
	FILE *fp;
	fp = fopen("highscores.bin", "rb+");
	//int j= 0;
	int auxpont;
	rewind(fp);
	for(int i = 0; i < TAM; i++)
	{
		auxpont = player[i].pont;
		if (pontuacao >= auxpont){
			printf("Nome do jogador: ");
			scanf("%s", nome);
				//j = i;
				for(int j = i; j < TAM; j++){
					strcpy(player[(TAM-j)].user, player[(TAM -j - 1)].user);
					player[(TAM-j)].pont = player[(TAM -j - 1)].pont;
						if(fwrite(&player, sizeof(PLAYER), 1, fp) != 1)
							{
								printf("problema de escrita");
							}
				}

			strcpy(player[i].user, nome);
			player[i].pont = pontuacao;

			if(fwrite(&player, sizeof(PLAYER), 1, fp) != 1)
			{
				printf("problema de escrita");
			}
			fclose(fp);
			return;

		}
		/* if( pontuacao > player[i].pont){
			 printf("Nome do jogador: ");
			 scanf("%s", &nome);
			 player[i].user = nome;
			 player[i].pont = pontuacao;

		 }*/
	}

}

int main()
{

	FILE *fp;
	fp = fopen("highscores.bin", "wb");
	if( fp == NULL)
	{
		printf ("Erro de criacao!\n");
	}


	for(int i = 0; i < 5; i++)
	{
		sprintf(player[i].user, "Jogador %d", i+ 1);
		player[i].pont = 2;
		if(fwrite(&player[i], sizeof(PLAYER), 1, fp) != 1)
		{
			printf("problema de escrita");
		}

	}
	fclose(fp);
	ranking();
	atualiza_ranking();
	printf("Bora ver oq mudou\n");
	ranking();
	atualiza_ranking();
	ranking();
	fclose(fp);
	return 0;
}
