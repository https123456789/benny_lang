CFLAGS := -Wall -Wextra
LEX_OFILES := src/lexer/lex.o
OFILES := src/main.o src/read_file.o

all: blc

blc: $(OFILES) $(LEX_OFILES)
	gcc $(CFLAGS) $(OFILES) $(LEX_OFILES) -o blc

%.o: %.c
	gcc -c $(CFLAGS) $^ -o $@

clean:
	rm **/*.o
