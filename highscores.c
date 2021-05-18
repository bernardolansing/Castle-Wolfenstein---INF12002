#ifndef HIGHSCORES_C
#define HIGHSCORES_C


#include <stdio.h>
#include <string.h>
#include "ctype.h"
#include "main.h"
#define TAM 5
#define TAM_NOME 60

typedef struct{
    char nome[60];
    int pontuacao;
}VPLAYER;

VPLAYER vplayer[(TAM + 1)];
char nome[TAM_NOME] = "\0";

// testa se a pontuação entra para os highscores e pergunta o nome do jogador
void gameover() {
    Rectangle textbox = {largura / 2 - 200, altura / 2 - 25, largura / 2, 50};
        int letras = 0, key;

    while (1) {
        if (WindowShouldClose()) CloseWindow();

        // desenhar
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Insira seu nome:", 50, 20, 20, RED);
        DrawRectangleLinesEx(textbox, 3, RED);
        DrawText(nome, 210, 135, 20, YELLOW);
        EndDrawing();

        // obter texto
        key = GetKeyPressed();

        if (isalpha((char) key) && (letras < TAM_NOME)) {
            nome[letras] = (char) key;
            letras++;
        }

        else if (key == KEY_BACKSPACE) {
            nome[letras - 1] = '\0';
            letras--;
        }

        else if (key == KEY_ENTER) {
            strcpy(vplayer[5].nome, nome);
            update_ranking();
            concatenate--;
            break;
            //return 0;
            //main();
            //startmenu();
        }
        return;
    }



}

// funcao de teste para imprimir ranking
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

// atualizar o ranking
void update_ranking()
{
        if( game.pontuacao >= vplayer[4].pontuacao)
        {
            //scanf("%s", vplayer[5].nome);
            vplayer[5].pontuacao = game.pontuacao;
            arruma_posicoes();
            escreve_ranking();
        }

}

// coloca a nova pontuacao no ranking
arruma_posicoes(){
    VPLAYER aux;
    for(int j = 0; j < TAM - 1; j++)
    {
        for(int i = TAM - j; i > -1; i--)
        {
            if(vplayer[i].pontuacao < vplayer[i + 1].pontuacao)
            {
                aux.pontuacao = vplayer[i].pontuacao;
                vplayer[i].pontuacao = vplayer[i+1].pontuacao;
                vplayer[i+ 1].pontuacao = aux.pontuacao;
                strcpy(aux.nome, vplayer[i].nome);
                strcpy( vplayer[i].nome, vplayer[i+1].nome);
                strcpy(vplayer[i+1].nome, aux.nome);
                //vplayer[i].nome = vplayer[i+1].nome;
               // vplayer[i+ 1].nome = aux.nome;
            }
        }
    }
     return;
}

// salva ranking no highscores.bin
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
    //fseek(fp, 0, SEEK_SET);
    for(int i = 0; i < TAM ; i++)
    {
        if(fwrite(&vplayer[i], sizeof(VPLAYER), 1, fp) != 1)
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

    if(acessos==0){
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


    escreve_ranking();
    }
   else{
      escreve_ranking();
     }
   acessos++;

    return 0;
}

#endif
