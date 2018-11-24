/**
 * Chamada do jogo da memoria
 *
 * @param EstadoJogo* estado    Ponteiro para o estado atual do jogo
 * @param BITMAP* buffer        Ponteiro para uma imagem da tela
 * @param BITMAP* bg            Ponteiro para a imagem de fundo
 * @param short int nivel       Nível atual
 *
 * @return pontuacao            Retorna a pontuação final do nivel jogado
 */
int memoria(EstadoJogo* estado, BITMAP* buffer, BITMAP* bg, short int nivel) {
    BITMAP *back, *front, *numbers;
    MIDI* fundoJogo;
    Carta** tab;
    Carta *carta1 = NULL, *carta2 = NULL;
    FONT* fonte = load_font(FONTS_PATH"cooper_black_italic_BT_14.pcx", NULL, NULL);
    SAMPLE *flip, *flop, *acerto;   // Sons para os movimentos das cartas
    int movimentos = 0;             // Contador de movimentos
    int pontuacao = 0;              // Contador de pontos
    int timer_aux = 0, mov_aux = 0; // Contadores auxiliares
    int restantes = (M*N)/2;        // Numero de pares restantes

    initMemoria(&back, &front, &numbers, &fundoJogo, &flip, &flop, &acerto);
    tab = initTab();
    addValores(tab, nivel);

    play_midi(fundoJogo, 1);        // Toca a música de fundo
    desenhaTab(tab, back, bg, buffer);

    timer = 0;
    LOCK_VARIABLE(timer);
    LOCK_FUNCTION(gameTime);
    install_int_ex(gameTime, SECS_TO_TIMER(1));

    while(!key[KEY_ESC] && restantes > 0) { // Enquanto ainda houver algum par ou não for ESC
        // Máquina de Estados
        if (carta1 == NULL) {                           // Estado 0: nenhuma carta
            carta1 = checkClick(tab, numbers, front, buffer, &movimentos, &flip);
        } else if (carta2 == NULL) {                    // Estado 1: uma carta selecionada
            carta2 = checkClick(tab, numbers, front, buffer, &movimentos, &flip);
            mouse_b = 0x00;
        } else if (mouse_b & 1) {                       // Estado 2: duas cartas selecioandas
            pontuacao += checkCartas(carta1, carta2, &acerto, &flop, &restantes);   // Verifica se as cartas formam par
            desenhaTab(tab, back, bg, buffer);                                      // Redesenha o tabuleiro só com cartas inativas
            carta1 = NULL;
            carta2 = NULL;
            mouse_b = 0x00;
        }
        blit(bg, buffer, 0, ALTURA_TELA - 50, 0, ALTURA_TELA - 50, LARGURA_TELA, 50); //restaura a parte inferior do fundo para imprimir o tempo e os movimentos
        textprintf_centre_ex(buffer, fonte, LARGURA_TELA/2, ALTURA_TELA - 50, PRETO, -1,
            "Tempo: %2d:%02d   Movimentos: %4d   Pontuacao: %4d", (int)(timer / 60), timer % 60, movimentos, pontuacao);

        // Atualiza a retirada de pontos pelo tempo
        if ((timer / 5) > timer_aux) {
            pontuacao -= pontuacao > TIRA_PONTOS ? TIRA_PONTOS : pontuacao;
            timer_aux++;
        }
        // Atualiza a retirada de pontos pelos movimentos
        if ((movimentos / 5) > mov_aux) {
            pontuacao -= pontuacao > (2 * TIRA_PONTOS) ? (2 * TIRA_PONTOS) : pontuacao;
            mov_aux++;
        }
        draw_sprite(screen, buffer, 0, 0);
    }

    if (!key[KEY_ESC]) *estado = EXIBE_PONTUACAO;   // Se não saiu do while por causa do ESC, então o usuário terminou o nível.
    else *estado = MENU_PRINCIPAL;                  // Retorna ao menu principal

    // Atualiza o nivel salvo no arquivo criado na inicialização do jogo
    if ((*estado) == EXIBE_PONTUACAO) {
      FILE *salvaNivel;

      salvaNivel = fopen("param.ini","w");

      fprintf(salvaNivel, "%c", (nivel+131));
      fclose(salvaNivel);
    }

    destroy_bitmap(back);
    destroy_bitmap(front);
    destroy_bitmap(numbers);
    destroy_midi(fundoJogo);
    destroy_sample(flip);
    destroy_sample(flop);
    destroy_sample(acerto);
    destroy_font(fonte);

    return pontuacao; // Retorna a pontuacao a ser avaliada se é um recorde
}
