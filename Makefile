CFLAGS := -Wall -Wextra
LEX_OFILES := src/lexer/lex.o
OFILES := src/main.o src/read_file.o src/util/compare.o src/util/strip.o src/util/strslice.o
TEST_OFILES := test/test.o test/lexer/lex.o

all: blc

test: $(LEX_OFILES) $(TEST_OFILES)
	gcc $(TEST_OFILES) $(LEX_OFILES) -o blc-test

blc: $(OFILES) $(LEX_OFILES)
	gcc $(CFLAGS) $(OFILES) $(LEX_OFILES) -o blc

%.o: %.c
	gcc -c $(CFLAGS) $^ -o $@

clean:
	rm **/*.o
