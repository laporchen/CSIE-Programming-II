CC:=gcc
objects = hw0101 hw0102 hw0103 hw0104 hw0105
all: $(objects)

$(objects): %: %.c
	$(CC) $(CFLAGS) -o $@ $< -lm
hw6:
	$(CC) -c hw6.c -lm
clean:
	rm -f *.o
	rm -f $(objects)
