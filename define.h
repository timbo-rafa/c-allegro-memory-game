// Pastas auxiliares
#define IMAGES_PATH     "images/"
#define SOUNDS_PATH     "sounds/"
#define FONTS_PATH      "fonts/"

// Dimensões da tela
#define LARGURA_TELA    800
#define ALTURA_TELA     600

#ifndef TRUE
#define TRUE         1
#define FALSE        0
#endif

#define QUADRO_X    16
#define QUADRO_Y    125

#define QUADRO_H 356
#define QUADRO_W 415

// Texto de como jogar
#define TIT_CJ            "Como Jogar"
#define TXT_COMOJOGAR_L1  "Neste jogo voce tera que relacionar pares de cartas."
#define TXT_COMOJOGAR_L2  "Uma carta contem uma operacao e o seu par, o resultado."
#define TXT_COMOJOGAR_L3  "O tipo de conta feita depende do nivel escolhido."
#define TXT_COMOJOGAR_L4  "Nao ha duas cartas com a mesma conta ou com o mesmo resultado."
#define TXT_COMOJOGAR_L5  "Mas seja rapido, pois o tempo estara passando e lhe custara pontos!!"
#define TXT_COMOJOGAR_L6  "Clique em uma peca para vira-la."
#define TXT_COMOJOGAR_L7  "Ao virar duas, se o par estiver correto ou errado,"
#define TXT_COMOJOGAR_L8  "um terceiro clique permitira continuar o jogo."
#define TXT_COMOJOGAR_L9  " "
#define TXT_COMOJOGAR_L10 "Boa Sorte!!"
#define TXT_COMOJOGAR_L11 "Aperte ESC para voltar ao menu Principal."

#define TXT_CJ_UP (QUADRO_Y + 15)
#define DIST_LINHAS     30
#define TOTAL_LINHAS    11

// Menu do jogo
#define OPCAO_X_MIN         55
#define OPCAO_X_MAX         275
#define INICIAR_JOGO_Y_MIN  150
#define INICIAR_JOGO_Y_MAX  180
#define COMOJOGAR_Y_MIN     200
#define COMOJOGAR_Y_MAX     230
#define RECORDES_Y_MIN      250
#define RECORDES_Y_MAX      270
#define SAIR_Y_MIN          295
#define SAIR_Y_MAX          320

#define MARGEM          20
#define OPCAO_HEIGHT    45

// Cores
#define VERDE           makecol(0 , 75, 0)
#define BRANCO          makecol(255, 255, 255)
#define PRETO           makecol(0, 0, 0)
#define TRANSPARENTE    makecol(255, 0, 255)
#define MARROM_CLARO    makecol(225, 209, 155)

// Movimentacao do quadro
#define DELAY_QUADRO    1
#define MOVE_QUADRO_X   8

// Placas de nivel
#define DISTANCIA_PLACAS    8
#define TAM_PLACA           199
#define PLACA1_Y            (1 * DISTANCIA_PLACAS + 0 * TAM_PLACA)
#define PLACA2_Y            (1 * DISTANCIA_PLACAS + 2 * TAM_PLACA / 3)
#define PLACA3_Y            (2 * DISTANCIA_PLACAS + 1 * TAM_PLACA)
#define PLACA4_Y            (2 * DISTANCIA_PLACAS + 5 * TAM_PLACA / 3)
#define PLACA5_Y            (3 * DISTANCIA_PLACAS + 2 * TAM_PLACA)

// Niveis do jogo
#define NIVEL1  0
#define NIVEL2  1
#define NIVEL3  2
#define NIVEL4  3
#define NIVEL5  4
#define NIVEIS  5

// Vezes que procura espaço para os valores nas pecas
#define MAX_RAND 10

// Faixa para calcular as contas
#define MAXIMO     100
#define MINIMO     10

// Tamanho do tabuleiro
#define M   5
#define N   4

// Tipo da peça
#define VAZIO       -1
#define EXPRESSAO   0
#define RESULTADO   1

// Medidas da peça e bordas
#define PECA_LAR    150
#define PECA_ALT    75
#define BORDA_INT   10
#define BORDA_EXT   85

// Medidas dos números a ser desenhados e bordas
#define NUM_LAR     28
#define NUM_ALT     52
#define BORDA_NUM_X 5
#define BORDA_NUM_Y 12

// Distância das peças
#define DIST_LAR(j)   ((j)* (PECA_LAR + BORDA_INT) + BORDA_EXT)
#define DIST_ALT(i)   ((i)* (PECA_ALT + BORDA_INT) + BORDA_EXT)

// Tempo mínimo para o próximo clique
#define TEMPO_CLICK 250

// Pontuação por par de cartas correto
#define SOMA_PONTOS 1000

// Pontuação tirada por tempo gasto
#define TIRA_PONTOS 10

// Defines dos mecanismo de gravao de arquivo.
#define ARQUIVO_RECORDE_N1  "ranking/ranking_n1.bin"
#define ARQUIVO_RECORDE_N2  "ranking/ranking_n2.bin"
#define ARQUIVO_RECORDE_N3  "ranking/ranking_n3.bin"
#define ARQUIVO_RECORDE_N4  "ranking/ranking_n4.bin"
#define ARQUIVO_RECORDE_N5  "ranking/ranking_n5.bin"

// Espaços - Recordes
#define MAX_RECORDES                10
#define MAX_DIGITOS_NOME            20
#define MAX_CASAS_DECIMAIS_RECORDE  5

// Caracteres - Recordes
#define SEPARADOR_BARRA     "|"
#define CHAR_VAZIO          ' '
#define CHAR_ZERO           '0'
#define CHAR_BARRA          '|'
#define FINAL_STRING        '\0'
#define RANKING_TIPO_CLIQUE '\0'
#define RANKING_TIPO_TEMPO  '\0'

typedef enum{
    VERTICAL,
    HORIZONTAL,
    RETRACAO,
    EXPANSAO
} Modo;

typedef enum {
    MENU_PRINCIPAL,
    MENU_COMO_JOGAR,
    MENU_RECORDES,
    PLACAS_NIVEL,
    JOGO,
    SAIDA,
    EXIBE_PONTUACAO,
} EstadoJogo;

/**
 * Struct que representa a entidade recorde. Ele e composto de nome,
 * a pontuacao em string e a pontuacao em int.
 */
typedef struct{
    char nome[MAX_DIGITOS_NOME];
    char pontuacaoStr[MAX_CASAS_DECIMAIS_RECORDE];
    int pontuacao;
} recorde;
