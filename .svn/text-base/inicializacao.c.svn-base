/**
 * Inicialização do Allegro
 *
 * @param BITMAP** buffer       Ponteiro para uma imagem da tela
 * @param BITMAP** background   Ponteiro para a imagem de fundo
 * @param MIDI** musica         Ponteiro para o som do menu
 */
void initAllegro(BITMAP** buffer, BITMAP** background, MIDI** musica){
    allegro_init();
    install_keyboard();
    install_timer();
    install_mouse();
    srand(time(NULL));
    set_color_depth(desktop_color_depth());

    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, LARGURA_TELA, ALTURA_TELA, 0, 0) || install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL)) {
		allegro_message(allegro_error);
		exit(EXIT_FAILURE);
	}

	// Configurações - volume do som e nome
	set_volume(255, 255);
    set_window_title("Super Memoria");

    // Imagens do jogo
	*buffer = create_bitmap(LARGURA_TELA, ALTURA_TELA);     // Carrega as telas
    *background = load_bmp(IMAGES_PATH"bg.bmp",NULL);       // Fundo do jogo

    // Sons do menu
    *musica = load_midi(SOUNDS_PATH"alegre.mid");       // Musica de fundo do menu

	// Exibe o mouse na tela.
    enable_hardware_cursor();
    select_mouse_cursor(MOUSE_CURSOR_ARROW);
    show_mouse(screen);
}

/**
 * Inicialização do Jogo da Memória
 *
 * @param BITMAP** back     Ponteiro para a imagem do verso da peça
 * @param BITMAP** front    Ponteiro para a imagem da frente da peça
 * @param BITMAP** numbers  Ponteiro para os números e sinais das cartas
 * @param MIDI** fundoJogo  Ponteiro para a música de fundo do jogo
 * @param SAMPLE** flip     Ponteiro para o som da carta virando para cima
 * @param SAMPLE** flop     Ponteiro para o som da carta virando para baixo
 * @param SAMPLE** acerto   Ponteiro para o som de acertar o par de cartas
 */
void initMemoria( BITMAP** back, BITMAP** front, BITMAP** numbers, MIDI** fundoJogo, SAMPLE** flip, SAMPLE** flop, SAMPLE** acerto){
    // Imagens do jogo
    *back = load_bmp(IMAGES_PATH"back.bmp", NULL);          // Verso da carta
    *front = load_bmp(IMAGES_PATH"front.bmp", NULL);        // Frente da carta
    *numbers = load_bmp(IMAGES_PATH"numbers.bmp", NULL);    // Sequencia de numeros e sinais

    // Sons do jogo
    *fundoJogo = load_midi(SOUNDS_PATH"fundo.mid");     // Musica de fundo do jogo
    *flip = load_sample(SOUNDS_PATH"flip.wav");         // Carta virando para cima
    *flop = load_sample(SOUNDS_PATH"flop.wav");         // Carta virando para baixo
    *acerto = load_sample(SOUNDS_PATH"acerto.wav");     // Acerto de duas cartas
}

volatile int timer;

/**
 * Incrementa o contador de tempo do jogo a cada segundo
 * OBS: Deve ser usada com LOCK_VARIABLE, LOCK_FUNCTION e INSTALL_INT_EX
 */
void gameTime() {
  timer++;
}
END_OF_FUNCTION(gameTime);
