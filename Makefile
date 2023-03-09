CFLAGS := -Werror -Wall -Wextra -Wundef -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -ansi -pedantic -std=gnu11 -g
SRC := $(wildcard src/*.c) $(wildcard src/**/*.c)
OFILES := $(SRC:.c=.o)

all: blc

blc: $(OFILES)
	gcc $(CFLAGS) $(OFILES) -o blc

memtest:
	@`which time` -f "\n-----\t------\t-----\nFile system outputs: %O\nMaximum RSS size: %M KB\nCPU percentage used: %P\n-----\t-----\t-----" ./blc examples/nothing.bl

%.o: %.c
	gcc -c $(CFLAGS) $^ -o $@

clean:
	@rm $(OFILES) blc
