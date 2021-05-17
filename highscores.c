#include <stdio.h>
#include <string.h>
#include "main.h"
#define TAM 5
typedef struct
{
    char nome[60];
    int pontuacao;
}VPLAYER;

int pontuacao_jogador = 12;
VPLAYER vplayer[(TAM + 1)];

void print_ranking()
{
    int x = 0;
    FILE *fp;
    if(!(fp = fopen("highscores.bin","rb")))
        printf("Erro na abertura\n");

    else
    {
        rewind(fp);
        printf("Ranking:\n");
        while(x < TAM)
        {
            if(x < TAM)
            {
               if(fread(&vplayer, sizeof(VPLAYER), 1,fp) == 1)
                {
                printf("Jogador: %s \n", vplayer[x].nome);
                printf("Pontuacao: %d\n", vplayer[x].pontuacao);

                }
            }
            x++;
        }
    }
    fclose(fp);
}

void update_ranking()
{
    for(int k = 0; k < TAM; k ++)
    {
        if(pontuacao_jogador >= vplayer[k].pontuacao)
        {
            printf("Nome do jogador: ");
            scanf("%s", vplayer[5].nome);
            vplayer[5].pontuacao = pontuacao_jogador;
            arruma_posicoes();
            //escreve_ranking();
            return;
        }
    }
}

arruma_posicoes(){
    VPLAYER aux;
    for(int j = 0; j < TAM - 1; j++)
    {
        for(int i = TAM - 1; i > -1; i--)
        {
            if(vplayer[i].pontuacao < vplayer[i + 1].pontuacao)
            {
                aux = vplayer[i + 1];
                vplayer[i + 1] = vplayer[i];
                vplayer[i] = aux;
            }
        }
    }
     return;
}

escreve_ranking()
{
    FILE *fp;
    if(!(fp= fopen("highscores.bin","wb")))
    {
        printf("Erro criacao");
    }
    else
    {
    rewind(fp);
    fseek(fp, 0, SEEK_SET);
    for(int i = 0; i < TAM ; i++)
    {
        if(fwrite(&vplayer, sizeof(VPLAYER), 1, fp) != 1)
        {
            printf("problema de escrita");
        }
    }
    fclose(fp);
    }
}



int starthighscores()
{

    int pontuacao;

    strcpy(vplayer[0].nome, "Joao");
    vplayer[0].pontuacao = 10;

    strcpy(vplayer[1].nome, "Maria");
    vplayer[1].pontuacao = 8;

    strcpy(vplayer[2].nome, "Joana");
    vplayer[2].pontuacao = 6;

    strcpy(vplayer[3].nome, "Mario");
    vplayer[3].pontuacao = 4;

    strcpy(vplayer[4].nome, "Djario");
    vplayer[4].pontuacao = 2;

    strcpy(vplayer[5].nome, "Jogador");
    vplayer[5].pontuacao = 0;

    if(acessos==0){
        escreve_ranking();
    }
    else{
        print_ranking();
    }

    return 0;
}
