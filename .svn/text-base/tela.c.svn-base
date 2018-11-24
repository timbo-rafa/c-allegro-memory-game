/**
 * Procura a posição do mouse no intervalo
 *
 * @param short int xmin    Posicao x minima
 * @param short int xmax    Posicao x maxima
 * @param short int ymin    Posicao y minima
 * @param short int ymax    Posicao y maxima
 *
 * @return int              Verdadeiro ou falso
 */
static int MouseNoIntervalo(short int xmin, short int xmax, short int ymin, short int ymax) {
    if (mouse_x >= xmin && mouse_x <= xmax && mouse_y >= ymin && mouse_y <= ymax) return TRUE;
    return FALSE;
}

/**
 * Manipula as dimensões do quadro
 *
 * @param Modo direcao          Direcao do movimento do quadro
 * @param BITMAP* bg            Ponteiro para a imagem de fundo
 * @param BITMAP* buffer        Ponteiro para uma imagem da tela
 * @param BITMAP* buffer_quadro Ponteiro para o buffer que auxilia a animação do quadro
 * @param BITMAP* quadro        Ponteiro para a imgem do quadro
 * @param short int i           Contador axiliar na mudança das dimensões do quadro
**/

void ExpandeQuadro(Modo direcao, BITMAP* bg, BITMAP* buffer, BITMAP* buffer_quadro, BITMAP* quadro, short int i) {
    if (direcao == HORIZONTAL)    blit(quadro, buffer_quadro, quadro->w/2, 0, quadro->w/2 + i, 0              , quadro->w/2, quadro->h);
    else if (direcao == VERTICAL) blit(quadro, buffer_quadro, 0, quadro->h/2, 0              , quadro->h/2 + i, quadro->w, quadro->h/2);
    blit(bg, buffer, 0, 0, 0, 0, bg->w, bg->h);
    if (direcao == HORIZONTAL && i < -320) blit(quadro, buffer_quadro, 0, 0, 0, 0, LARGURA_TELA/5, ALTURA_TELA/5);
    draw_sprite(buffer, buffer_quadro, 0, 0);
    blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);

}

/**
 * Gerencia a Expansao ou Retração do quadro
 *
 * @param Modo modo             Indica aumento ou diminuição do quadro
 * @param BITMAP* bg            Ponteiro para a imagem de fundo
 * @param BITMAP* buffer        Ponteiro para uma imagem da tela
 * @param BITMAP* buffer_quadro Ponteiro para o buffer que auxilia a animação do quadro
 * @param BITMAP* quadro        Ponteiro para a imgem do quadro
 *
**/
void GerenciaDimensaoQuadro(Modo modo, BITMAP* bg, BITMAP* buffer, BITMAP* buffer_quadro, BITMAP* quadro) {
    short int h = 10;
    if (modo == EXPANSAO) {
        while ( h + quadro->w <= LARGURA_TELA - QUADRO_X) {
            ExpandeQuadro(HORIZONTAL, bg, buffer, buffer_quadro, quadro, h);
            h += 2;
        }
        //Fazendo com que o bitmap quadro se torne o novo quadro maior horizontalmente
        h = quadro->h;
        destroy_bitmap(quadro);
        quadro = create_bitmap(LARGURA_TELA, h);
        blit(buffer_quadro, quadro, 0 , 0, 0, 0, LARGURA_TELA, h);
        h = 0;
        while ( h + quadro->h <= ALTURA_TELA - QUADRO_X) {
            ExpandeQuadro(VERTICAL, bg, buffer, buffer_quadro, quadro, h);
            h += 2;
        }
    } else if (modo == RETRACAO) {
        quadro = create_bitmap(LARGURA_TELA, ALTURA_TELA);
        rectfill(quadro, 0, 0, quadro->w, quadro->h, TRANSPARENTE);
        blit(buffer_quadro, quadro, 0, 2 * buffer_quadro->h/3, 0, buffer_quadro->h/2, buffer_quadro->w, buffer_quadro->h);
        h = 90;
        while (getpixel(buffer_quadro,LARGURA_TELA/2,QUADRO_H - 8) == VERDE) {
            ExpandeQuadro(VERTICAL, bg, buffer, buffer_quadro, quadro, h);
            rectfill(buffer_quadro, 0, quadro->h + h, LARGURA_TELA, ALTURA_TELA, TRANSPARENTE);
            h -= 2;
        }
        blit(buffer_quadro, quadro, 0, 0, 0, 0, LARGURA_TELA, ALTURA_TELA);
        h = 0;
        while ( getpixel(buffer_quadro, QUADRO_W, QUADRO_H - 10) == VERDE ) {
            ExpandeQuadro(HORIZONTAL, bg, buffer, buffer_quadro, quadro, h);
            h -= 2;
        }
    }
    destroy_bitmap(quadro);
}

/**
 * Exibe a explicação de como jogar
 *
 * @param BITMAP* bg            Ponteiro para a imagem de fundo
 * @param BITMAP* buffer        Ponteiro para uma imagem da tela
 * @param BITMAP* buffer_quadro Ponteiro para o buffer que auxilia a animação do quadro
 * @param short int w           Contém menu->w, depois se torna contador
**/
void telaMenuComoJogar(BITMAP* bg, BITMAP* buffer, BITMAP* buffer_quadro, short int w) {
    FONT* titulo = load_font(FONTS_PATH"cooper_black_italic_BT_20.pcx", NULL, NULL);
    FONT* informacoes = load_font(FONTS_PATH"cooper_black_italic_BT_14.pcx", NULL, NULL);
    BITMAP* quadro = load_bmp(IMAGES_PATH"quadro.bmp", NULL);
    char texto[TOTAL_LINHAS][100] = {TXT_COMOJOGAR_L1, TXT_COMOJOGAR_L2, TXT_COMOJOGAR_L3, TXT_COMOJOGAR_L4, TXT_COMOJOGAR_L5, TXT_COMOJOGAR_L6,
                           TXT_COMOJOGAR_L7, TXT_COMOJOGAR_L8, TXT_COMOJOGAR_L9, TXT_COMOJOGAR_L10, TXT_COMOJOGAR_L11};

    rectfill(buffer_quadro, QUADRO_X, QUADRO_Y, w, SAIR_Y_MAX, VERDE);
    GerenciaDimensaoQuadro(EXPANSAO, bg, buffer, buffer_quadro, quadro);

    textout_centre_ex(buffer, titulo, TIT_CJ, LARGURA_TELA/2, TXT_CJ_UP  , BRANCO, -1);

    for (w = 1; w < TOTAL_LINHAS; w++)
        textout_centre_ex(buffer, informacoes, texto[w], LARGURA_TELA/2, TXT_CJ_UP + 15 + w * DIST_LINHAS , BRANCO, -1);
    blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
    while (!key[KEY_ESC]) rest(50);
    GerenciaDimensaoQuadro(RETRACAO, bg, buffer, buffer_quadro, quadro);
    destroy_font(titulo);
    destroy_font(informacoes);
}
/**
 * Funcao Responsável pela animação do quadro
 *
 * @param BITMAP* bg            Ponteiro para a imagem de fundo
 * @param BITMAP* buffer        Ponteiro para uma imagem da tela
 * @param BITMAP* buffer_quadro Ponteiro para o buffer que auxilia a animação do quadro
 * @param BITMAP* quadro        Ponteiro para a imgem do quadro
 * @param short int i           Movimentacao do quadro
 *
 * @return short int            Verdadeiro ou falso
 */
short int AnimaQuadro(BITMAP* bg, BITMAP* buffer, BITMAP* buffer_quadro, BITMAP* quadro, short int i)
{
    blit(bg, buffer, 0, 0, 0, 0, LARGURA_TELA, ALTURA_TELA);
    blit(quadro, buffer_quadro, 0, quadro->h - i/DELAY_QUADRO, MOVE_QUADRO_X, 0, quadro->w, i/DELAY_QUADRO);
    draw_sprite(buffer, buffer_quadro, 0, 0);
    blit(buffer, screen, 0, 0, 0, 0, LARGURA_TELA, ALTURA_TELA);
    if (i/DELAY_QUADRO >= quadro->h || i <= 0)
        return FALSE;
    else if (key[KEY_ESC]) {
        while (key[KEY_ESC]) rest(50);
        AnimaQuadro(bg, buffer, buffer_quadro, quadro, quadro->h);
        return FALSE;
    }
    else return TRUE;
}
/**
 * Exibe a tela de menu e suas opcoes
 *
 * @param EstadoJogo* estado    Ponteiro para o estado do jogo
 * @param BITMAP* buffer        Ponteiro para uma imagem da tela
 * @param MIDI** musicaFundo    Ponteiro para o som de fundo
 * @param short int* tocando    Ponteiro para decidir se deve tocar ou não
 */
void telaMenuPrincipal(EstadoJogo* estado, BITMAP* buffer, MIDI** musicaFundo, short int* tocando) {
    BITMAP *menu, *menu_selected, *quadro, *bg, *buffer_quadro;
    SAMPLE* clique;
    short int i = DELAY_QUADRO;

    clique = load_sample(SOUNDS_PATH"clique.wav"); // Som para o clique nas opções

    quadro = load_bmp(IMAGES_PATH"quadro.bmp", NULL);
    bg = load_bmp(IMAGES_PATH"abertura.bmp", NULL);
    menu = load_bmp(IMAGES_PATH"menu.bmp", NULL);
    menu_selected = load_bmp(IMAGES_PATH"menu_selected.bmp", NULL);
    buffer_quadro = create_bitmap( LARGURA_TELA, ALTURA_TELA);
    rectfill(buffer_quadro, 0, 0, LARGURA_TELA, ALTURA_TELA, TRANSPARENTE);

    blit(menu, quadro, 0, 0,(QUADRO_X/2), QUADRO_Y, menu->w , menu->h);

    while (key[KEY_ESC]) rest(50);  // Caso o usuario tenha vindo de outra funcao atraves da tecla ESC, aguarde esta deixar de ser pressionada

    if(*tocando) i = quadro->h - 1; // Se já está tocando a música, já mostra o quadro lá embaixo
    else {                          // Se a música de fundo fora destruída, ela é recriada.
        *musicaFundo = load_midi(SOUNDS_PATH"alegre.mid");
        play_midi(*musicaFundo, 1);
        *tocando = TRUE;
    }
    while (AnimaQuadro(bg, buffer, buffer_quadro, quadro, i)) i++;

    i = quadro->h - 1;
    while(*estado == MENU_PRINCIPAL) {
        if (MouseNoIntervalo(OPCAO_X_MIN, OPCAO_X_MAX, INICIAR_JOGO_Y_MIN, INICIAR_JOGO_Y_MAX)) {
                blit(menu_selected, buffer, 0, MARGEM, QUADRO_X, (QUADRO_Y + MARGEM - 5), menu_selected->w, OPCAO_HEIGHT);
                if (mouse_b & 1)
                    *estado = PLACAS_NIVEL;
        } else if (MouseNoIntervalo(OPCAO_X_MIN, OPCAO_X_MAX, COMOJOGAR_Y_MIN, COMOJOGAR_Y_MAX)) {
            blit(menu_selected, buffer, 0, OPCAO_HEIGHT + MARGEM, QUADRO_X, QUADRO_Y + OPCAO_HEIGHT + MARGEM - 5, menu_selected->w, OPCAO_HEIGHT + 3);
            if (mouse_b & 1) {
                play_sample(clique, 255, 255, 1000, 0);
                telaMenuComoJogar(bg, buffer, buffer_quadro, menu->w);
                blit(menu, buffer, 0, 0, QUADRO_X, QUADRO_Y, menu->w, menu->h);
                draw_sprite(buffer, quadro, MOVE_QUADRO_X, 0);
            }
        } else if (MouseNoIntervalo(OPCAO_X_MIN, OPCAO_X_MAX, RECORDES_Y_MIN, RECORDES_Y_MAX)){
            blit(menu_selected, buffer, 0, 2 * OPCAO_HEIGHT + MARGEM + 5, QUADRO_X, QUADRO_Y + 2 * OPCAO_HEIGHT + MARGEM, menu_selected->w, OPCAO_HEIGHT);
                if (mouse_b & 1)
                    *estado = MENU_RECORDES;
        } else if (MouseNoIntervalo(OPCAO_X_MIN, OPCAO_X_MAX, SAIR_Y_MIN, SAIR_Y_MAX)) {
                blit(menu_selected, buffer, 0, 3 * OPCAO_HEIGHT + MARGEM + 5, QUADRO_X, QUADRO_Y + 3 * OPCAO_HEIGHT + MARGEM, menu_selected->w, OPCAO_HEIGHT);
                if (mouse_b & 1)
                    *estado = SAIDA;
        } else blit(menu, buffer, 0, 0, QUADRO_X, QUADRO_Y, menu->w, menu->h);
        blit(buffer, screen, 0, 0, 0, 0, LARGURA_TELA, ALTURA_TELA);
    }
    if(*estado == SAIDA){
        *musicaFundo = load_midi(SOUNDS_PATH"vitoria.mid");
        play_midi(*musicaFundo, 0);
    } else play_sample(clique, 255, 255, 1000, 0);
    /* Animação do quadro subindo*/
    if (*estado != MENU_RECORDES) {
        while (AnimaQuadro(bg, buffer, buffer_quadro, quadro, i)) {
            i--;
            rectfill(buffer_quadro, 0, 0, LARGURA_TELA, ALTURA_TELA, TRANSPARENTE); //evita que o quadro deixe rastro marrom
        }
    } else rest(500); //tempo do clique
    //desaloca os espaços não mais necessário na memória
    destroy_sample(clique);
    destroy_bitmap(quadro);
    destroy_bitmap(buffer_quadro);
    destroy_bitmap(menu);
    destroy_bitmap(menu_selected);
    destroy_bitmap(bg);
}
/**
 * Exibe as opcoes de niveis do jogo
 *
 * @param BITMAP* buffer            Ponteiro para uma imagem da tela
 * @param short int i               Contador que auxilia a animacao do quadro
 * @param BITMAP* placa[5]          Ponteiro de vetor com as placas possíveis
 * @param short int nivelmax        Nivel máximo permitido para o usuário
 */
short int ChamaPlacas(BITMAP* buffer, short int i, BITMAP* placa[5], short int nivelmax) {

    if (nivelmax>= NIVEL1) blit(placa[NIVEL1], buffer, placa[NIVEL1]->w - i, 0,        0        , PLACA1_Y, i, placa[NIVEL1]->h);
    if (nivelmax>= NIVEL2) blit(placa[NIVEL2], buffer,         0           , 0, LARGURA_TELA - i, PLACA2_Y, i, placa[NIVEL2]->h);
    if (nivelmax>= NIVEL3) blit(placa[NIVEL3], buffer, placa[NIVEL3]->w - i, 0,        0        , PLACA3_Y, i, placa[NIVEL3]->h);
    if (nivelmax>= NIVEL4) blit(placa[NIVEL4], buffer,         0           , 0, LARGURA_TELA - i, PLACA4_Y, i, placa[NIVEL4]->h);
    if (nivelmax>= NIVEL5) blit(placa[NIVEL5], buffer, placa[NIVEL5]->w - i, 0,        0        , PLACA5_Y, i, placa[NIVEL5]->h);
    blit(buffer, screen, 0, 0, 0, 0, LARGURA_TELA, ALTURA_TELA);
    if (i > placa[NIVEL1]->w) return TRUE;
    else return FALSE;
}

/**
 * Exibe as opcoes de niveis do jogo
 *
 * @param EstadoJogo* estado    Ponteiro para o estado do jogo
 * @param BITMAP* buffer        Ponteiro para uma imagem da tela
 * @param BITMAP* bg            Ponteiro para uma imagem do fundo da tela
 * @param short int nivelmax    Nivel maximo permitido para o usuario
 * @param short int* nivelatual Ponteiro para o nivel escolhido pelo usuario
 * @param MIDI** musicaFundo    Ponteiro para o som de fundo
 * @param short int* tocando    Ponteiro para decidir se deve tocar ou não
 */
void telaPlacas(EstadoJogo* estado, BITMAP* buffer, BITMAP* bg, short int nivelmax, short int* nivelatual, MIDI** musicaFundo, short int* tocando) {
    BITMAP* placa[5];
    SAMPLE* clique;
    placa[NIVEL1] = load_bmp(IMAGES_PATH"p0.bmp", NULL);
    placa[NIVEL2] = load_bmp(IMAGES_PATH"p1.bmp", NULL);
    placa[NIVEL3] = load_bmp(IMAGES_PATH"p2.bmp", NULL);
    placa[NIVEL4] = load_bmp(IMAGES_PATH"p3.bmp", NULL);
    placa[NIVEL5] = load_bmp(IMAGES_PATH"p4.bmp", NULL);
    clique = load_sample(SOUNDS_PATH"clique.wav");

    blit(bg, buffer, 0 , 0, 0, 0, bg->w, bg->h);
    short int pcont = 0, placasani = TRUE;
    *nivelatual = -1;
    while(*estado == PLACAS_NIVEL) {
        if (placasani) {
            if(ChamaPlacas(buffer, pcont, placa, nivelmax)) {
                pcont = 0;
                placasani = FALSE;
            } else pcont++;
        } else if ((mouse_b & 1) && MouseNoIntervalo(0,LARGURA_TELA, 0, ALTURA_TELA)) {
            // Verifica se o usuario clicou em uma das placas
            if (MouseNoIntervalo(0, placa[NIVEL1]->w, PLACA1_Y, PLACA1_Y + placa[NIVEL1]->h) && NIVEL1 <= nivelmax)
                *nivelatual = NIVEL1;
            else if (MouseNoIntervalo(LARGURA_TELA - placa[NIVEL2]->w, LARGURA_TELA, PLACA2_Y, PLACA2_Y + placa[NIVEL2]->h) && NIVEL2 <= nivelmax)
                *nivelatual = NIVEL2;
            else if (MouseNoIntervalo(0, placa[NIVEL3]->w, PLACA3_Y, PLACA3_Y + placa[NIVEL3]->h) && NIVEL3 <= nivelmax)
                *nivelatual = NIVEL3;
            else if (MouseNoIntervalo(LARGURA_TELA - placa[NIVEL4]->w, LARGURA_TELA, PLACA4_Y, PLACA4_Y + placa[NIVEL4]->h) && NIVEL4 <= nivelmax)
                *nivelatual = NIVEL4;
            else if (MouseNoIntervalo(0, placa[NIVEL5]->w, PLACA5_Y, PLACA5_Y + placa[NIVEL5]->h) && NIVEL5 <= nivelmax)
                *nivelatual = NIVEL5;
        }
        if (key[KEY_ESC]) *estado = MENU_PRINCIPAL;
        else if (*nivelatual >= NIVEL1 && *nivelatual <= nivelmax) {
                play_sample(clique, 255, 255, 1000, 0);
                *estado = JOGO;
                destroy_midi(*musicaFundo); //destroi o midi que tocava no menu, pois haverá uma nova música de fundo no jogo
                *tocando = FALSE; //indica na flag tocando (do main) que a música foi destruída
                rest(500); //tempo do clique do botão
        }
    }

    destroy_sample(clique);
    for (pcont = 0 ; pcont < 5 ; pcont++) destroy_bitmap(placa[pcont]);
}

/**
 * Funcao responsavel por controlar a tela onde sera obtido o nome do jogador para poder
 * gravar o recorde, caso o mesmo tenha atingido.
 *
 * @param EstadoJogo *estado    Ponteiro para o estado do jogo.
 * @param BITMAP* buffer        Ponteiro para uma imagem da tela
 * @param BITMAP* bg            Ponteiro para a imagem de fundo
 * @param short int nivel       Nivel atual
 * @param int pontuacao         Pontuacao do jogador
 */
void exibePontuacaoJogador(EstadoJogo *estado, BITMAP *buffer, BITMAP *bg, short int nivel, int pontuacao){
    // declara o vetor de recorde e obtem ele do arquivo.
    recorde recordes[MAX_RECORDES];
    getListaRecordes(recordes, nivel);

    // declaracao de variaveis utilizadas para leitura do nome do jogador.
    FONT *fonte;
    PALETTE palette;
    int cont  = 0, i = 0;
    char    nome[MAX_DIGITOS_NOME] = {" "};

    MIDI *vitoria; //música de vitória
    vitoria = load_midi(SOUNDS_PATH"vitoria.mid");
    play_midi(vitoria, 0);

    // le a fonte que sera utilizada para exibicao.
    fonte = load_font(FONTS_PATH"cooper_black_italic_BT_18.pcx", NULL, NULL);

    clear(buffer);
    blit(bg, buffer, 0, 0, 0, 0, LARGURA_TELA, ALTURA_TELA);
    textprintf_centre_ex(buffer, fonte, LARGURA_TELA/2, 150, makecol(0, 0, 0), -1, "Parabens, voce terminou o nivel %d - %s!!!",
                nivel + 1, nivel == NIVEL1? "Soma" : (nivel == NIVEL2? "Subtracao" : (nivel == NIVEL3? "Multiplicacao" : (nivel == NIVEL4? "Divisao" : "Desafio"))));
    textprintf_centre_ex(buffer, fonte, LARGURA_TELA/2, 200, makecol(0, 0, 0), -1, "Sua pontuacao: %0*d", MAX_CASAS_DECIMAIS_RECORDE, pontuacao);

    // como o vetor ja vem ordenado, verifica se a menor pontuacao gravada é estritamente menor que a atual.
    if(recordes[MAX_RECORDES-1].pontuacao < pontuacao){
        // enquanto o estado for
        while(*estado == EXIBE_PONTUACAO){

            // caso a tecla enter seja acionada, muda o estado pois entende-se
            // que o jogador ja escreveu o nome.
            if(key[KEY_ENTER] || key[KEY_ENTER_PAD]) *estado = MENU_RECORDES;

            // verifica se alguma tecla foi clicada.

            if(keypressed()) {
                // realiza a conversao do codigo da tecla em inteiro para o formato ASCII.
                int  newkey   = readkey();
                char ASCII    = newkey & 0xff;
                char scancode = newkey >> 8;

                // verifica se a tecla clicada trata-se de uma letra.
                if(ASCII >= 32 && ASCII <= 126) {
                    // verifica se o nome digitado ja nao excedeu o limite de caracteres.
                    if(cont < MAX_DIGITOS_NOME-1) {
                        nome[cont] = ASCII;
                        cont++;
                        //nome[cont] = '\0';
                    }
                } else if(scancode == KEY_BACKSPACE) {  // verifica se a tecla clicada trata-se da tecla backspace.
                    if (cont > 0) cont--;
                    nome[cont] = '\0';
                }
            }
            // desenha a tela.
            clear(buffer);
            blit(bg, buffer, 0, 0, 0, 0, LARGURA_TELA, ALTURA_TELA);
            textprintf_centre_ex(buffer, fonte, LARGURA_TELA/2, 150, makecol(0, 0, 0), -1, "Parabens, voce terminou o nivel %d - %s!!!",
                nivel + 1, nivel == NIVEL1? "Soma" : (nivel == NIVEL2? "Subtracao" : (nivel == NIVEL3? "Multiplicacao" : (nivel == NIVEL4? "Divisao" : "Desafio"))));
            textprintf_centre_ex(buffer, fonte, LARGURA_TELA/2, 200, makecol(0, 0, 0), -1, "Sua pontuacao: %0*d", MAX_CASAS_DECIMAIS_RECORDE, pontuacao);
            textprintf_ex(buffer, fonte, 150, 300, makecol(0, 0, 0), -1, "Digite seu nome: %s", nome);
            // if responsavel por fazer com que o cursor fique piscando.
            if((i % 150 >= 0) && (i % 150 <= 75)) vline(buffer, ((cont * 15) + 397), 295, 330, makecol(0, 0, 0));
            i++;


        blit(buffer, screen, 0, 0, 0, 0, LARGURA_TELA, ALTURA_TELA);
        }

        // chama a funcao que realizada a gravacao do recorde.
        gravaRecorde(pontuacao, nome, nivel);

    }
    // caso nao tenha sido recorde.
    // altera o estado para menu principal.
    else {
        textprintf_ex(buffer, fonte, 300, 300, makecol(0, 0, 0), -1, "Pressione Enter");
        blit(buffer, screen, 0, 0, 0, 0, LARGURA_TELA, ALTURA_TELA);
        while(!key[KEY_ENTER] && !key[KEY_ENTER_PAD]) ; //aguarda a tecla enter
        *estado = MENU_PRINCIPAL;
    }
    // libera memoria.
    destroy_font(fonte);
    destroy_midi(vitoria);
}

/**
 * Exibe o menu de recordes
 *
 * @param EstadoJogo* estado    Ponteiro para o estado do jogo
 * @param BITMAP* buffer        Ponteiro para uma imagem da tela
 * @param MIDI** musicaFundo    Ponteiro para o som de fundo
 * @param short int* tocando    Ponteiro para decidir se deve tocar ou não
 */
void telaMenuRecordes(EstadoJogo *estado, BITMAP *buffer, MIDI** musicaFundo, short int* tocando) {
    BITMAP *quadro, *bg, *buffer_quadro;
    int i, j, nivel = NIVEL1;
    recorde recordes[NIVEIS][MAX_RECORDES]; //matriz com os recordes de cada nível
    FONT *titulo, *subtitulo; //fontes para o texto
    PALETTE palette;
    if(!*tocando) { //se a música de fundo fora destruída, ela é recriada
        *musicaFundo = load_midi(SOUNDS_PATH"alegre.mid");
        play_midi(*musicaFundo, 1);
        *tocando = TRUE;
    }
    /* Fontes */
    titulo = load_font(FONTS_PATH"cooper_black_italic_BT_20.pcx", NULL, NULL);
    subtitulo = load_font(FONTS_PATH"cooper_black_italic_BT_14.pcx", NULL, NULL);
    /* Imagens */
    quadro = load_bmp(IMAGES_PATH"quadro.bmp", NULL);
    bg = load_bmp(IMAGES_PATH"abertura.bmp", NULL);
    buffer_quadro = create_bitmap( LARGURA_TELA, ALTURA_TELA);
    rectfill(buffer_quadro, 0, 0, LARGURA_TELA, ALTURA_TELA, TRANSPARENTE);
    draw_sprite(buffer_quadro, quadro, MOVE_QUADRO_X, 0);
    GerenciaDimensaoQuadro(EXPANSAO, bg, buffer, buffer_quadro, quadro); //Expansão do quadro
    rectfill(buffer, 0, 0, LARGURA_TELA - 1, ALTURA_TELA - 1, TRANSPARENTE); //limpa o buffer

    /* Leitura dos recordes */
    for(nivel = NIVEL1; nivel <= NIVEL5; nivel++)
        getListaRecordes(recordes[nivel], nivel);

    /* Impressão dos títulos*/
    textprintf_centre_ex(buffer, titulo, LARGURA_TELA/2 - 10, 135, BRANCO, -1, "Recordes");
    textprintf_ex(buffer, subtitulo, 55, 180, BRANCO, -1, "Nivel 1 - Soma");
    textprintf_centre_ex(buffer, subtitulo, LARGURA_TELA/2 - 10, 180, BRANCO, -1, "Nivel 2 - Subtracao");
    textprintf_ex(buffer, subtitulo, 530, 180, BRANCO, -1, "Nivel 3 - Multiplicacao");
    textprintf_ex(buffer, subtitulo, 160, 380, BRANCO, -1, "Nivel 4 - Divisao");
    textprintf_ex(buffer, subtitulo, 420, 380, BRANCO, -1, "Nivel 5 - Desafio");
    /* Impressão dos recordes*/
    for(nivel = NIVEL1; nivel <= NIVEL3; nivel++){
        textprintf_ex(buffer, font, 20 + 250*nivel, 210, BRANCO, -1, "    Nome %*s", MAX_DIGITOS_NOME + 1, "Pontos"); //Cabeçalho
        for(i=0; i<MAX_RECORDES; i++){
            textprintf_ex(buffer, font, 20 + 250*nivel, 220 + i*15, BRANCO, -1, "%2d. %*.*s %0*d",
                i+1, MAX_DIGITOS_NOME, MAX_DIGITOS_NOME, recordes[nivel][i].nome, //nome do i-ésimo recordista do nivel em avaliação
                MAX_CASAS_DECIMAIS_RECORDE, recordes[nivel][i].pontuacao); //e pontuacao
        }
    }
    for(nivel = NIVEL4; nivel <= NIVEL5; nivel++){
        textprintf_ex(buffer, font, 130 + 260*(nivel-NIVEL4), 410, BRANCO, -1, "    Nome %*s", MAX_DIGITOS_NOME + 1, "Pontos");
        for(i=0; i<MAX_RECORDES; i++){
            textprintf_ex(buffer, font, 130 + 260*(nivel-3), 420 + i*15, BRANCO, -1, "%2d. %*.*s %0*d",
                i+1, MAX_DIGITOS_NOME, MAX_DIGITOS_NOME, recordes[nivel][i].nome, //nome do i-ésimo recordista
                MAX_CASAS_DECIMAIS_RECORDE, recordes[nivel][i].pontuacao); //e pontuacao
        }
    }
    draw_sprite(screen, buffer, 0, 0); //desenha o buffer na tela
    /* Fim da impressão dos recordes*/

    while(!key[KEY_ESC]) rest(50); //aguarda o usuário teclar ESC para voltar ao menu.
    GerenciaDimensaoQuadro(RETRACAO, bg, buffer, buffer_quadro, quadro);

    destroy_font(titulo);
    destroy_font(subtitulo);
    destroy_bitmap(bg);
    destroy_bitmap(buffer_quadro);
    *estado = MENU_PRINCIPAL; //retorna ao menu principal
}

/**
 * Finaliza o jogo
 */
void despedida(BITMAP* buffer) {
    BITMAP *bg = load_bmp(IMAGES_PATH"abertura.bmp", NULL);
    BITMAP* saida, *aux;
    aux = create_bitmap(LARGURA_TELA, ALTURA_TELA);
    saida = load_bmp(IMAGES_PATH"Tchau.bmp",NULL);
    short int i = 0;

    draw_sprite(bg, saida, 0, ALTURA_TELA/2 - saida->h/2);
    for (i = LARGURA_TELA/2; i >= 0 ; i-= 2) {
        rectfill(aux, 0, 0, LARGURA_TELA, ALTURA_TELA, PRETO);
        circlefill(aux, LARGURA_TELA/2, ALTURA_TELA/2, i, TRANSPARENTE);
        blit(bg, buffer, i/2, i/2, i/2, i/2, LARGURA_TELA - i, ALTURA_TELA - i);
        draw_sprite(buffer, aux, 0, 0);
        draw_sprite(buffer, saida, 0, ALTURA_TELA/2 - saida->h/2);
        //draw_sprite(screen, buffer, 0, 0);
        blit(buffer, screen, 0, 0, 0, 0, LARGURA_TELA, ALTURA_TELA);
        if (i % 1500 == 0) rest(3);
    }
    remove_int(gameTime);
    destroy_bitmap(saida);
    destroy_bitmap(aux);
}
