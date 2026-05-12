all: test_old test_new a.so b.so

test_old: test.c
	$(CC) -o test_old test.c

test_new: test.c
	$(CC) -DDEFINE_REGISTER_IT -o test_new test.c

a.so: a.c test.h
	$(CC) -fPIC -shared -Wl,-undefined,dynamic_lookup -o a.so a.c

b.so: b.c test.h
	$(CC) -fPIC -shared -Wl,-undefined,dynamic_lookup -o b.so b.c

clean:
	rm -f test_old test_new a.so b.so

.PHONY: clean all
.DEFAULT_GOAL := all
