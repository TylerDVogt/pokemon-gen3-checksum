checksum: checksum.o
	gcc -o checksum checksum.o

checksum.o: checksum.c checksum.h
	gcc -c checksum.c

.PHONY: clean

clean: 
	rm -f *.o checksum
