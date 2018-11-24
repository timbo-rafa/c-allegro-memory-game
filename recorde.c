/**
 * Funcao que obtem o nome da estrutura recorde passada.
 *
 * @param RECORDE origem     Estrutura na qual sera obtido o valor do nome.
 * @param CHAR str[]         Vetor que contera o nome.
 */
void getNomeStruct(recorde origem, char str[]){
    int i;
    for(i = 0; i < MAX_CASAS_DECIMAIS_RECORDE; i++){
        str[i] = origem.nome[i];
    }
}

/**
 * Funcao que obtem a pontuacao no formato string da estrutura recorde passada.
 *
 * @param RECORDE origem     Estrutura na qual sera obtido o valor do nome.
 * @param CHAR str[]         Vetor que contera a pontuacao.
 */
void getPontuacaoStrStruct(recorde origem, char str[]){
    int i;
    for(i = 0; i < MAX_DIGITOS_NOME; i++){
        str[i] = origem.pontuacaoStr[i];
    }
}

/**
 * Funcao que obtem a pontuacao da estrutura recorde passada.
 *
 * @param RECORDE origem     Estrutura na qual sera obtido o valor do nome.
 * @param INT *variavel      Ponteiro para a variavel alterada.
 */
void getPontuacaoStruct(recorde origem, int *variavel){
    *variavel = origem.pontuacao;
}

/**
 * Funcao que seta nome na estrutura recorde passada.
 *
 * @param RECORDE *origem                  Ponteiro da estrutura que deve ser alterada.
 * @param CHAR nome[MAX_DIGITOS_NOME]      Nome no formato string a ser setado.
 */
void setNomeStruct(recorde *origem, char nome[MAX_DIGITOS_NOME]){
    int i;
    for (i = 0; i < MAX_DIGITOS_NOME; i++){
        origem->nome[i] = nome[i];
    }
}

/**
 * Funcao que seta uma string pontuacao na estrutura recorde passada.
 *
 * @param RECORDE *origem                                    Ponteiro da estrutura que deve ser alterada.
 * @param CHAR pontuacaoStr[MAX_CASAS_DECIMAIS_RECORDE]      Pontuacao no formato string a ser setado.
 */
void setPontuacaoStrStruct(recorde *origem, char pontuacaoStr[MAX_CASAS_DECIMAIS_RECORDE]){
    int i;
    for (i = 0; i < MAX_CASAS_DECIMAIS_RECORDE; i++){
        origem->pontuacaoStr[i] = pontuacaoStr[i];
    }
}

/**
 * Funcao que seta uma pontuacao na estrutura recorde passada.
 *
 * @param RECORDE *origem    Ponteiro da estrutura que deve ser alterada.
 * @param INT pontuacao      Valor que devera ser setado
 */
void setPontuacaoStruct(recorde *origem, int pontuacao){
    origem->pontuacao = pontuacao;
}

/**
 * Funcao que ordena a lista de recordes.
 *
 * @param RECORDE recordes[]     Vetor que contem os recordes.
 * @param INT tam                Tamanho do vetor para ordenacao.
 */
void ordenaLista(recorde recordes[], int tam) {
  int i, j, max;
  for (i = 0; i < (tam - 1); i++) {
        max = i;
        for (j = (i + 1); j < tam; j++) {
          if(recordes[j].pontuacao > recordes[max].pontuacao) {
            max = j;
          }
        }
        if (i != max) {
          recorde swap = recordes[i];
          recordes[i] = recordes[max];
          recordes[max] = swap;
        }
  }
}

/**
 * Funcao que extrai os caracteres de uma string de entre dois indices.
 *
 * @param CHAR origem[]  String a ser quebrada
 * @param INT inicio     Posicao do primeiro caracter
 * @param INT quant      Quantidade de caractes a serem considerados apos o primeiro.
 * @param CHAR res[]     String extraida.
 */
void substring(char origem[], int inicio, int quant, char res[]){

    int i = 0;
    char auxiliar[strlen(origem)];

    for(i = 0; i<strlen(origem); i++){
       auxiliar[i] = origem[i];
    }

    // posição inicial menor que 0 ou
    // posição inicial muito exagerada?
    if((inicio < 0) || (inicio > strlen(origem)))
    inicio = 0;

    // quantidade de caracteres muito exagerada?
    if(quant > inicio + strlen(origem))
    quant = strlen(origem) - inicio;

    // obtem os caracteres desejados
    for(i = 0; i <= quant - 1; i++){
        auxiliar[i] = origem[inicio + i];
    }

    // marca o fim da string
    res[i] = '\0';

    for(i = 0; i<quant; i++){
        res[i] = auxiliar[i];
    }
}

/**
 * Funcao que converte um INT em uma STRING com zeros na frente quando nao possuir todos as casas decimais
 * necessarias. Exemplo: 100 -> 00100.
 *
 * @param INT pontuacao     Valor do inteiro.
 * @param CHAR str[]        String que sera retornada.
 */
void converteIntToString(int value, char str[]){
    int i, n = 0;
    char valor[MAX_CASAS_DECIMAIS_RECORDE];

    //itoa(value,valor,10);
    sprintf(valor, "%d", value);

    for(i = 0; i < (MAX_CASAS_DECIMAIS_RECORDE - strlen(valor)); i++){
        str[n] = CHAR_ZERO;
        n++;
    }

    for(i = 0; i <= (strlen(valor) - 1); i++){
        str[n] = valor[i];
        n++;
    }
}

/**
 * Funcao que insere um novo recorde no vetor de recordes considerando, validando se o recorde realmente e
 * o maior.
 *
 * @param RECORDE recordes[MAX_RECORDES]     Vetor que contem os recordes.
 * @param INT pontuacao                      Pontuacao do jogador.
 * @param CHAR nome[MAX_DIGITOS_NOME]        String com o nome do jogador.
 */
void insereRecordeListaRecordes(recorde recordes[MAX_RECORDES], int pontuacao, char nome[MAX_DIGITOS_NOME]){
    recorde blocoRecorde;
    char pontuacaoStr[MAX_CASAS_DECIMAIS_RECORDE];

    // converte a pontuacao para string.
    converteIntToString(pontuacao, pontuacaoStr);

    // seta o nome na estruta recorde.
    setNomeStruct(&blocoRecorde, nome);
    // seta a pontuacao no formato string na estruta recorde.
    setPontuacaoStrStruct(&blocoRecorde, pontuacaoStr);
    // seta a pontuacao na estruta recorde.
    setPontuacaoStruct(&blocoRecorde, pontuacao);

    // ordena a lista.
    ordenaLista(recordes, MAX_RECORDES);
    // insere na ultima posicao, pois a ultima eh sempre a menor.
    recordes[MAX_RECORDES - 1] = blocoRecorde;
    // reordena a lista para poder ficar correta.
    ordenaLista(recordes, MAX_RECORDES);
}

/**
 * Funcao para ler o arquivo e montar o vetor de recordes, atraves das informacoes contidas
 * no arquivo.
 *
 * @param RECORDE recordes[MAX_RECORDES]     Vetor que os recordes vindos do arquivo serao adicionados.
 */
void getListaRecordes(recorde recordes[MAX_RECORDES], int nivel){
    FILE *arquivo;

    char *strArquivoQuebrada;
    char strArquivo[((MAX_DIGITOS_NOME + MAX_CASAS_DECIMAIS_RECORDE + 1) * MAX_RECORDES)];

    char nome[MAX_DIGITOS_NOME];
    char pontuacaoStr[MAX_CASAS_DECIMAIS_RECORDE];

    int cont = 0, i;

    switch(nivel) {
        case NIVEL1:
            // abre o arquivo no modo somente leitura.
            arquivo = fopen(ARQUIVO_RECORDE_N1, "r");
            break;
        case NIVEL2:
            // abre o arquivo no modo somente leitura.
            arquivo = fopen(ARQUIVO_RECORDE_N2, "r");
            break;
        case NIVEL3:
            // abre o arquivo no modo somente leitura.
            arquivo = fopen(ARQUIVO_RECORDE_N3, "r");
            break;
        case NIVEL4:
            // abre o arquivo no modo somente leitura.
            arquivo = fopen(ARQUIVO_RECORDE_N4, "r");
            break;
        case NIVEL5:
            // abre o arquivo no modo somente leitura.
            arquivo = fopen(ARQUIVO_RECORDE_N5, "r");
            break;
    }

    // caso o arquvio exista.
    if(arquivo != NULL){

        // seta o curso na primeira posicao do arquvio.
        rewind(arquivo);

        // enquanto nao for encontrado o final do arquivo.
        while(fgets(strArquivo,(((MAX_CASAS_DECIMAIS_RECORDE + MAX_DIGITOS_NOME) * MAX_RECORDES) + (MAX_RECORDES)),arquivo) != NULL){

            // quebra a string obtida no caracter barra.
            strArquivoQuebrada = strtok (strArquivo, SEPARADOR_BARRA);

            // enquanto a string obtida for diferente de NULL.
            while(strArquivoQuebrada != NULL){

                //obtem a parte da string referente ao nome.
                substring(strArquivoQuebrada, 0, MAX_DIGITOS_NOME, nome);
                //obtem a parte da string referente a pontuacao.
                substring(strArquivoQuebrada, MAX_DIGITOS_NOME, MAX_CASAS_DECIMAIS_RECORDE, pontuacaoStr);

                //seta o nome na estrutura recorde, dentro do vetor de recordes.
                setNomeStruct(&recordes[cont], nome);
                //seta a pontuacao no formato string na estrutura recorde, dentro do vetor de recordes.
                setPontuacaoStrStruct(&recordes[cont], pontuacaoStr);
                //seta a pontuacao na estrutura recorde, dentro do vetor de recordes.
                setPontuacaoStruct(&recordes[cont], atoi(pontuacaoStr));

                // obtem a string ate encontrar o proximo separador.
                strArquivoQuebrada = strtok (NULL, SEPARADOR_BARRA);
                cont++;
            }
        }
    }
    else{
        cont = 0; //se não foi criado o arquivo, começa da primeira posição a zerar o vetor de recordes
    }

    // criar um vetor que representa string vazia para nome.
    char strNomeVazia[MAX_DIGITOS_NOME];
    for(i = 0; i < MAX_DIGITOS_NOME; i++){
        strNomeVazia[i] = CHAR_VAZIO;
    }

    // criar um vetor que representa string vazia para pontuacao.
    char strPontuacaoVazia[MAX_CASAS_DECIMAIS_RECORDE];
    for(i = 0; i < MAX_CASAS_DECIMAIS_RECORDE; i++){
        strPontuacaoVazia[i] = CHAR_VAZIO;
    }

    // pega a ultima posicao que foi inseridos com dados do arquivo e caso ainda haja
    // posicoes vazias vai setando valores em branco na lista.
    while(cont != MAX_RECORDES){
        //seta o nome na estrutura recorde, dentro do vetor de recordes.
        setNomeStruct(&recordes[cont], strNomeVazia);
        //seta a pontuacao no formato string na estrutura recorde, dentro do vetor de recordes.
        setPontuacaoStrStruct(&recordes[cont], strPontuacaoVazia);
        //seta a pontuacao na estrutura recorde, dentro do vetor de recordes.
        setPontuacaoStruct(&recordes[cont], 0);
        cont++;
    }
}

/**
 * Funcao que gera a string que sera gravada no arquivo.
 *
 * @param RECORDE recordes[MAX_RECORDES]     Vetor que contem os recorde que deverao ser gravados.
 * @param CHAR str[]                         Vetor que representa a string que sera gravada.
 */
void geraStrArquivo(recorde recordes[MAX_RECORDES], char str[]){
    int i, j, tNome, n = 0;

    // verifica quantos caracteres tem o nome do usario em cada registro de recorde.
    for (j = 0; j < MAX_RECORDES; j++){
        tNome = 0;
        for (i = 0; i < MAX_DIGITOS_NOME; i++){
            if(recordes[j].nome[i] != FINAL_STRING){
                tNome++;
            }
        }

        // preenche o nome na string que sera gerada para cada recorde.
        for(i = 0; i < tNome; i++){
            str[n] = recordes[j].nome[i];
            n++;
        }

        // preenche em branco os espacos restantes caso a string estaja em branco.
        for(i = 0; i < (MAX_DIGITOS_NOME - tNome); i++){
            str[n] = CHAR_VAZIO;
            n++;
        }

        // insere a pontuacao no formato string para cada recorde.
        for(i = 0; i < MAX_CASAS_DECIMAIS_RECORDE; i++){
            str[n] = recordes[j].pontuacaoStr[i];
            n++;
        }

        // insere o caracter de barra para indicar o final de cada registro de recorde.
        str[n] = CHAR_BARRA;
        n++;
    }

    // insere o caracter de final de string.
    str[n] = FINAL_STRING;
    n++;
}

/**
 * Funcao responsavel por gravar o recorde informado.
 *
 * @param INT pontuacao                  Numero de cliques do jogador
 * @param CHAR nome[MAX_DIGITOS_NOME]    Nome do jogador
 */
void gravaRecorde(int pontuacao, char nome[MAX_DIGITOS_NOME], int nivel){
    FILE *arquivo;
    recorde recordes[MAX_RECORDES];
    char str[(((MAX_CASAS_DECIMAIS_RECORDE + MAX_DIGITOS_NOME) * MAX_RECORDES) + (MAX_RECORDES - 1))];

    switch(nivel) {
        case NIVEL1:
            // abre o arquivo para gravacao.
            if((arquivo = fopen(ARQUIVO_RECORDE_N1, "r+b")) ==  NULL){
                arquivo = fopen(ARQUIVO_RECORDE_N1,"w+b");
            }
            break;
        case NIVEL2:
            // abre o arquivo para gravacao.
            if((arquivo = fopen(ARQUIVO_RECORDE_N2, "r+b")) ==  NULL){
                arquivo = fopen(ARQUIVO_RECORDE_N2,"w+b");
            }
            break;
        case NIVEL3:
            // abre o arquivo para gravacao.
            if((arquivo = fopen(ARQUIVO_RECORDE_N3, "r+b")) ==  NULL){
                arquivo = fopen(ARQUIVO_RECORDE_N3,"w+b");
            }
            break;
        case NIVEL4:
            // abre o arquivo para gravacao.
            if((arquivo = fopen(ARQUIVO_RECORDE_N4, "r+b")) ==  NULL){
                arquivo = fopen(ARQUIVO_RECORDE_N4,"w+b");
            }
            break;
        case NIVEL5:
            // abre o arquivo para gravacao.
            if((arquivo = fopen(ARQUIVO_RECORDE_N5, "r+b")) ==  NULL){
                arquivo = fopen(ARQUIVO_RECORDE_N5,"w+b");
            }
            break;
    }

    // chama funcao que obtem a lista que esta no arquivo caso a mesma exista.
    getListaRecordes(recordes, nivel);

    // chama funcao que insere o novo recorde na lista.
    insereRecordeListaRecordes(recordes, pontuacao, nome);

    // chama funcao que gera a string que sera gravada novamente no arquivo.
    geraStrArquivo(recordes, str);

    // insere a string no arquivo.
    fputs(str,arquivo);

    // fecha o arquivo.
    fclose(arquivo);
}

