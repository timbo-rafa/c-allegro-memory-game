/**
 * Aloca um espaco para as pecas do tabuleiro
 *
 * @return Carta**  Ponteiro para a estrutura que contem as informacoes das pecas no tabuleiro
 */
Carta** initTab() {
    Carta** tab;
    int i,  j;

    // Aloca espaço para a matriz que armazena os valores das cartas
    tab = (Carta**) malloc(M * sizeof(Carta*));
    for (i = 0; i < M; i++) {
        tab[i] = (Carta*) malloc (N * sizeof(Carta));
        for (j = 0; j < N; j++) {
            tab[i][j].resultado = VAZIO;
            tab[i][j].ativo = FALSE;
        }
    }
    return tab;
}

/**
 * Encontra posicao vazia para colocar os valores nas pecas
 *
 * @param Carta** tab   Ponteiro para a estrutura que contem as informacoes das pecas no tabuleiro
 *
 * @return int*         Vetor com a posicao vazia encontrada
 */
int* findEmpty(Carta** tab) {
    static int position[2]; // Variavel estatica: usar sempre a mesma, sem precisar realocar/limpar
    int i = 0, j = 0, l = 0;

    // MAX_RAND tentativas para achar uma posicao aleatoria vazia
    for (l = 0; l < MAX_RAND; i = rand() % M, j = rand() % N, l++) {
        if (tab[i][j].resultado == VAZIO)  {
            position[0] = i;
            position[1] = j;
            return position;
        }
    }

    // Encontra a primeira posicao vazia, depois de esgotar l
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            if (tab[i][j].resultado == VAZIO)  {
                position[0] = i;
                position[1] = j;
                return position;
            }
        }
    }
    return NULL;
}

/**
 * Realiza a operação e adiciona a carta
 *
 * @param Carta**           Ponteiro para a estrutura que contem as informacoes das pecas no tabuleiro
 * @param short int nivel   Nivel do jogo
 */
void addValores(Carta** tab, short int nivel) {
    char op_atual, operacoes[4] = {'+', '-', '*', '/'};
    int iE, iR, jE, jR, k, max, min;
    int* position;

    // Limites dos valores
    max = (int) ((MAXIMO - MINIMO) / 10);
    min = MINIMO;

    if (nivel != NIVEL5) op_atual = operacoes[nivel];

    // Encontra uma carta aleatoria vazia
    for (k = 0; k < M*N/2; k++) {
        position = findEmpty(tab);
        iE = position[0];
        jE = position[1];

        if (nivel == NIVEL5) op_atual = operacoes[rand() % 4];  // Checa o nivel e gera as operacoes corretas
        tab[iE][jE].operacao = op_atual;
        tab[iE][jE].resultado = min + 1 + rand() % (max - 1);   // Gera um resultado aleatorio
        min = tab[iE][jE].resultado;

        // Gera os operandos aleatoriamente
        switch (tab[iE][jE].operacao) {
            case '+':
                tab[iE][jE].op1 = rand() % tab[iE][jE].resultado;
                tab[iE][jE].op2 = tab[iE][jE].resultado - tab[iE][jE].op1;
                break;
            case '-':
                tab[iE][jE].op2 = rand() % (MAXIMO - tab[iE][jE].resultado);
                tab[iE][jE].op1 = tab[iE][jE].resultado + tab[iE][jE].op2;
                break;
            case '*':
                do tab[iE][jE].op1 = 1 + rand() % (tab[iE][jE].resultado - 1);
                while (tab[iE][jE].resultado % tab[iE][jE].op1 != 0);
                tab[iE][jE].op2 = tab[iE][jE].resultado / tab[iE][jE].op1;
                break;
            case '/':
                tab[iE][jE].resultado = k;
                tab[iE][jE].op2 = 1 + rand() % MINIMO;
                tab[iE][jE].op1 = tab[iE][jE].op2 * tab[iE][jE].resultado;
                break;
        }
        tab[iE][jE].tipo = EXPRESSAO; // Define a posicao com a operacao como EXPRESSAO

        // Encontra uma carta aleatória vazia
        position = findEmpty(tab);
        iR = position[0];
        jR = position[1];

        tab[iR][jR] = tab[iE][jE];
        tab[iR][jR].tipo = RESULTADO; // Define a posicao com o resultado como RESULTADO
    }
}

/**
 * Desenha o tabuleiro
 *
 * @param Carta** tab       Ponteiro para as informações do tabuleiro
 * @param BITMAP* back      Ponteiro para a imagem do verso da peça
 * @param BITMAP* bg        Ponteiro para a imagem de fundo da tela
 * @param BITMAP* buffer    Ponteiro para uma imagem da tela
 */
void desenhaTab(Carta** tab, BITMAP* back, BITMAP* bg, BITMAP* buffer) {
    int i, j;

    blit(bg, buffer, 0 , 0, 0, 0, LARGURA_TELA, ALTURA_TELA);

    for (i = 0; i < M; i++)
        for (j = 0; j < N; j++)
            if (!tab[i][j].ativo) draw_sprite(buffer, back, DIST_LAR(j), DIST_ALT(i));
}
