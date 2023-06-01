LISTC = main.c grafo_listaadj.c
LISTO = $(LISTC:.c=.o)
LISTEXE = ep1_lista_13836149.exe
MATC = main.c grafo_matrizadj.c
MATO = $(MATC:.c=.o)
MATEXE = ep1_matriz_13836149.exe

.PHONY: all clean

all: $(LISTEXE) $(MATEXE)

$(LISTEXE): $(LISTO)
	gcc -Wall -Werror -o $@ $^

$(MATEXE): $(MATO)
	gcc -Wall -Werror -o $@ $^

%.o: %.c
	gcc -Wall -Werror -c $<

clean:
	rm -f $(LISTO) $(MATO)

cleanall: clean
	rm -f $(LISTEXE) $(MATEXE)