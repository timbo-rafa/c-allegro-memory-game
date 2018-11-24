#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <allegro.h>
#include <time.h>
#include "define.h"

#include "inicializacao.c"
#include "cartas.c"
#include "tabuleiro.c"
#include "jogo.c"
#include "recorde.c"
#include "tela.c"

int main() {
    EstadoJogo estado = MENU_PRINCIPAL;
    BITMAP *buffer, *bg;
    int pontuacao;      // Pontuação do jogador no nivel
    short int nivelatual = -1, nivelmax = 0, tocando = FALSE;
    MIDI* musicaFundo;
    FILE* abreNivel;

    // Le o arquivo de jogo salvo
    abreNivel = fopen("param.ini","r");

    // Le o caracte e encontra o nivel certo
    if (abreNivel != NULL) {
      fscanf(abreNivel, "%c", &nivelmax);
      nivelmax -= 130;
      fclose(abreNivel);
    }
    // Delimita o nivel minimo e maximo
    if (nivelmax < 0) nivelmax = NIVEL1;
    else if (nivelmax >= 5) nivelmax = NIVEL5;

    // Inicializa as funções do Allegro
    initAllegro(&buffer, &bg, &musicaFundo);

    //play_midi(musicaFundo, TRUE);

    // Checa o estado do menu
    while(estado != SAIDA) {
        switch(estado) {
            case MENU_PRINCIPAL:
                telaMenuPrincipal(&estado, buffer, &musicaFundo, &tocando);
                break;
            case MENU_RECORDES:
                telaMenuRecordes(&estado, buffer, &musicaFundo, &tocando);
                break;
            case PLACAS_NIVEL:
                telaPlacas(&estado, buffer, bg, nivelmax, &nivelatual, &musicaFundo, &tocando);
                break;
            case JOGO:
                pontuacao = memoria(&estado, buffer, bg, nivelatual);
                if(estado == EXIBE_PONTUACAO && nivelatual == nivelmax) nivelmax++; // Atualiza o nivelmax para a execucao atual
                break;
            case EXIBE_PONTUACAO:
                exibePontuacaoJogador(&estado, buffer, bg, nivelatual, pontuacao);
                break;
        }
    }

    despedida(buffer);
    if(musicaFundo) destroy_midi(musicaFundo);  // Caso não tenha sido destruído antes
    destroy_bitmap(bg);
    destroy_bitmap(buffer);
    allegro_exit();
    return 0;
}
END_OF_MAIN();
