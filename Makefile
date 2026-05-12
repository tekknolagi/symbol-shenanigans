all: test a.so b.so

test: test.c
	$(CC) -o test test.c

a.so: a.c test.h
	$(CC) -fPIC -shared -Wl,-undefined,dynamic_lookup -o a.so a.c

b.so: b.c test.h
	$(CC) -fPIC -shared -Wl,-undefined,dynamic_lookup -o b.so b.c

clean:
	rm -f test a.so b.so

.PHONY: clean all
.DEFAULT_GOAL := all
