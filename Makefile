CFLAGS := -Wall -Wextra
OFILES := src/main.o src/read_file.o

all: blc

blc: $(OFILES)
	gcc $(CFLAGS) $(OFILES) -o blc

%.o: %.c
	gcc -c $(CFLAGS) $^ -o $@

clean:
	rm **/*.o
