CC:=gcc
objects = hw0301 hw0306 hw0304 hw0302 hw0303 hw0305
all: $(objects)

$(objects): %: %.c 
	$(CC) $(CFLAGS) -o $@ $<  -lm
#-fsanitize=address -g
clean:
	rm -f *.o
	rm -f $(objects) 
