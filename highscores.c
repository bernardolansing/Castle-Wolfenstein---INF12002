#include <stdio.h>
#include <string.h>

#define TAM 5
typedef struct
{
    char nome[60];
    int pontuacao;
}PLAYER;

int pontuacao_jogador = 12;
PLAYER player[(TAM + 1)];

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
               if(fread(&player, sizeof(PLAYER), 1,fp) == 1)
                {
                printf("Jogador: %s \n", player[x].nome);
                printf("Pontuacao: %d\n", player[x].pontuacao);

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
        if(pontuacao_jogador >= player[k].pontuacao)
        {
            printf("Nome do jogador: ");
            scanf("%s", player[5].nome);
            player[5].pontuacao = pontuacao_jogador;
            arruma_posicoes();
            //escreve_ranking();
            return;
        }
    }
}

arruma_posicoes(){
    PLAYER aux;
    for(int j = 0; j < TAM - 1; j++)
    {
        for(int i = TAM - 1; i > -1; i--)
        {
            if(player[i].pontuacao < player[i + 1].pontuacao)
            {
                aux = player[i + 1];
                player[i + 1] = player[i];
                player[i] = aux;
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
        if(fwrite(&player, sizeof(PLAYER), 1, fp) != 1)
        {
            printf("problema de escrita");
        }
    }
    fclose(fp);
    }
}


    char t[60];
    strcpy(t, *b);
    strcpy(*b, *a);
    strcpy(*a, t);
    //t = *b;
   // *b = *a;
   // *a = t;
}
int main()
{

    int pontuacao;

    strcpy(player[0].nome, "Joao");
    player[0].pontuacao = 10;

    strcpy(player[1].nome, "Maria");
    player[1].pontuacao = 8;

    strcpy(player[2].nome, "Joana");
    player[2].pontuacao = 6;

    strcpy(player[3].nome, "Mario");
    player[3].pontuacao = 4;

    strcpy(player[4].nome, "Djario");
    player[4].pontuacao = 2;

    strcpy(player[5].nome, "Jogador");
    player[5].pontuacao = 0;

    if(acessos==0){
        escreve_ranking();
    }
    else{
        print_ranking();
        update_ranking();
        escreve_ranking();
        print_ranking();
    }

    return 0;
}
