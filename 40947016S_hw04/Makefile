CC:=gcc
objects = hw0401 hw0402 hw0403 hw0404
all: 
	gcc myprintf.c -c
	gcc hw0402.c -o hw0402
	gcc hw0401.c -o hw0401
	gcc hw0403.c -o hw0403 myprintf.o -fsanitize=address -g
	gcc hw0404.c -o hw0404
#-fsanitize=address -g
clean:
	rm -f *.o
	rm -f $(objects) 
