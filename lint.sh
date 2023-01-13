gcc -fsyntax-only -Wall -Werror -ansi -pedantic -Wundef -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -O2 -std=gnu11 src/*.c src/*.h src/lexer/*.c src/lexer/*.h
exit $?