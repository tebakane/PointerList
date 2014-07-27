CC=gcc
LIB=pointer_list.o key_value.o
SRC=sample/main.c
all: libplist.a exec

libplist.a: $(LIB)
	ar rv libplist.a $(LIB)
	ranlib libplist.a

exec:
	$(CC) -I./ -o sample.out $(SRC) -lplist

.c.o:
	$(CC) -I./ -c -o $@ $<

clean:
	\rm -rf *.o *.mod ./sample/*.o

