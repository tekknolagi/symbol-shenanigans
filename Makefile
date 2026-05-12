test: test.c a.so b.so
	$(CC) -o test test.c

a.so: a.c test.h
	$(CC) -fPIC -shared -o a.so a.c

b.so: b.c test.h
	$(CC) -fPIC -shared -o b.so b.c

clean:
	rm -f test a.so b.so

.PHONY: clean
