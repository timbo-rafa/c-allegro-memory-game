LIBFLAG = $(shell pkg-config  allegro --libs --cflags)

NAME=memory-game

default: $(NAME)

$(NAME) : super_memoria.c inicializacao.c cartas.c tabuleiro.c jogo.c recorde.c tela.c
		cc super_memoria.c -o $(NAME) $(LIBFLAG)

clean:
	 rm -f $(NAME)
