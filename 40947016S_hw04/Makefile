CC:=gcc
objects = hw0402 hw0404 hw0401 hw0403
all: $(objects)

$(objects): %: %.c 
	$(CC) $(CFLAGS) -o $@ $<  -lm -fsanitize=address -g
#-fsanitize=address -g
clean:
	rm -f *.o
	rm -f $(objects) 
