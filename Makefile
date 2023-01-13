CFLAGS := -Werror -Wall -Wextra -Wundef -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -ansi -pedantic -std=gnu11
LEX_OFILES := src/lexer/lex.o
PARSE_OFILES := src/parser/parse.o
OFILES := src/main.o src/read_file.o

all: blc

blc: $(OFILES) $(LEX_OFILES) $(PARSE_OFILES)
	gcc $(CFLAGS) $(OFILES) $(LEX_OFILES) $(PARSE_OFILES) -o blc

memtest:
	@`which time` -f "\n-----\t------\t-----\nFile system outputs: %O\nMaximum RSS size: %M KB\nCPU percentage used: %P\n-----\t-----\t-----" ./blc examples/nothing.bl

%.o: %.c
	gcc -c $(CFLAGS) $^ -o $@

clean:
	@rm src/*/*.o
