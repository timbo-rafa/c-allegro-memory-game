typedef struct {
    int op1, op2, resultado, tipo, ativo;
    char operacao;
} Carta;

/**
 * Converte o sinal da operação no indice de BITMAP* numbers
 *
 * @param char op   Sinal a ser convertido
 *
 * @return int      Sinal convertido em caracteres
 */
int op2int(char op) {
    switch (op) {
        case '+':
            return 10;
        case '-':
            return 11;
        case '*':
            return 12;
        case '/':
            return 13;
    }
}

/**
 * Converte um numero em imagem (56x52)
 *
 * @param int n             Numero a ser convertido
 * @param BITMAP* numbers   Ponteiro para a imagem que contem os numeros
 *
 * @return BITMAP*          Ponteiro para a imagem convertida
 */
BITMAP* int2bmp(int n, BITMAP* numbers) {
    int dezena, unidade;
    BITMAP* numero;

    dezena = (int) (n / 10);
    unidade = n % 10;

    numero = create_bitmap(2 * NUM_LAR, NUM_ALT);
    rectfill(numero, 0, 0, 2 * NUM_LAR, NUM_ALT, MARROM_CLARO);

    if(dezena != 0) blit(numbers, numero, dezena * NUM_LAR, 0, 0, 0, NUM_LAR, NUM_ALT);
    blit(numbers, numero, unidade * NUM_LAR, 0, (dezena == 0 ? (int)(NUM_LAR/2) : NUM_LAR), 0, NUM_LAR, NUM_ALT);

    return numero;
}

/**
 * Checa o clique nas peças
 *
 * @param int i             Linha atual
 * @param int j             Coluna atual
 * @param Carta** tab       Ponteiro para o tabuleiro de cartas
 * @param BITMAP* numbers   Ponteiro para a imagem que contem os numeros
 * @param BITMAP* front     Ponteiro para a imagem da frente da peça
 * @param BITMAP** buffer   Ponteiro para uma imagem da tela
 */
void desenhaCarta(int i, int j, Carta** tab, BITMAP* numbers, BITMAP* front, BITMAP* buffer) {
    BITMAP *carta, *op1, *op2;

    carta = create_bitmap(5 * NUM_LAR, NUM_ALT);
    tab[i][j].ativo = TRUE;
    rectfill(carta, 0, 0, 5 * NUM_LAR, NUM_ALT, MARROM_CLARO);

    // Desenha a carta da EXPRESSAO ou a carta do RESULTADO
    if (tab[i][j].tipo == EXPRESSAO) {
        blit(op1 = int2bmp(tab[i][j].op1, numbers), carta, 0, 0, 0          , 0, 2 * NUM_LAR, NUM_ALT);
        blit(op2 = int2bmp(tab[i][j].op2, numbers), carta, 0, 0, 3 * NUM_LAR, 0, 2 * NUM_LAR, NUM_ALT);
        blit(numbers, carta, op2int(tab[i][j].operacao) * NUM_LAR, 0, 2 * NUM_LAR, 0, NUM_LAR, NUM_ALT);
        destroy_bitmap(op2);
    } else blit(op1 = int2bmp(tab[i][j].resultado, numbers), carta, 0, 0, (int)(1.5 * NUM_LAR), 0, 2 * NUM_LAR, NUM_ALT);
    destroy_bitmap(op1);

    draw_sprite(buffer, front, DIST_LAR(j), DIST_ALT(i));
    blit(carta, buffer, 0, 0, DIST_LAR(j) + BORDA_NUM_X, DIST_ALT(i) + BORDA_NUM_Y, 5 * NUM_LAR, NUM_ALT);
    blit(buffer, screen, 0, 0, 0, 0, LARGURA_TELA, ALTURA_TELA);
    destroy_bitmap(carta);
}

/**
 * Checa o clique nas peças
 *
 * @param Carta** tab       Ponteiro para o tabuleiro de cartas
 * @param BITMAP* numbers   Ponteiro para a imagem que contem os numeros
 * @param BITMAP* front     Ponteiro para a imagem da frente da peça
 * @param BITMAP** buffer   Ponteiro para uma imagem da tela
 * @param int movimentos    Movimentos efetuados
 * @param SAMPLE** flip     Ponteiro para o som da carta virando para cima
 *
 * @return Carta*           Ponteiro com informações da carta clicada
 */
Carta* checkClick(Carta** tab, BITMAP* numbers, BITMAP* front, BITMAP* buffer, int* movimentos, SAMPLE** flip) {
    int i, j, x, y;
    static int click_x = 0, click_y = 0, clicked_at = 0;

    // Clique nas bordas externas ou não clique - Não faz nada
    if (!((mouse_b & 1) && mouse_x > DIST_LAR(0) && mouse_x < (DIST_LAR(N-1) + PECA_LAR) &&
        mouse_y > DIST_ALT(0) && mouse_y < (DIST_ALT(M-1) + PECA_ALT))) return NULL;

    x = mouse_x - BORDA_EXT;
    y = mouse_y - BORDA_EXT;

    j = (int)(x / (PECA_LAR + BORDA_INT));
    i = (int)(y / (PECA_ALT + BORDA_INT));

    x = (int)(x % (PECA_LAR + BORDA_INT));
    y = (int)(y % (PECA_ALT + BORDA_INT));

    // Clique nas bordas internas - Não faz nada
    if (!(x <= PECA_LAR && y <= PECA_ALT && !tab[i][j].ativo)) return NULL;

    // Clique Carta[i][j]
    play_sample(*flip, 255, 255, 1000, 0);  // Carta virando para cima
    desenhaCarta(i, j, tab, numbers, front, buffer);
    (*movimentos)++;                        // Incremento da quantidade de movimentos

    rest(TEMPO_CLICK);

    return &tab[i][j];
}

/**
 * Checa se as cartas formam par
 *
 * @param Carta* carta1     Ponteiro para primeira carta virada
 * @param Carta* carta2     Ponteiro para segunda carta virada
 * @param SAMPLE** acerto   Ponteiro para o som quando o par está certo
 * @param SAMPLE** flop     Ponteiro para o som das cartas virando para baixo
 * @param int* restantes    Ponteiro para o número de peças restantes
 *
 * @return int              Pontos ganhos
 */
int checkCartas(Carta* carta1, Carta* carta2, SAMPLE** acerto, SAMPLE** flop, int* restantes) {
    if (carta1->resultado == carta2->resultado){
        play_sample(*acerto, 255, 255, 1000, 0);
        (*restantes)--;                     // Decrementa o número de pares restantes
        return SOMA_PONTOS;
    }
    play_sample(*flop, 255, 255, 1000, 0);  // Carta virando para baixo
    carta1->ativo = FALSE;
    carta2->ativo = FALSE;
    return 0;
}
