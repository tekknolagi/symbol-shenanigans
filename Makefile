UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
    SHARED_LDFLAGS = -fPIC -shared -Wl,-undefined,dynamic_lookup
    EXEC_LDFLAGS =
else
    SHARED_LDFLAGS = -fPIC -shared
    EXEC_LDFLAGS = -rdynamic -ldl
endif

all: test_old test_new a.so b.so

test_old: test.c
	$(CC) -o test_old test.c $(EXEC_LDFLAGS)

test_new: test.c
	$(CC) -DDEFINE_REGISTER_IT -o test_new test.c $(EXEC_LDFLAGS)

a.so: a.c test.h
	$(CC) $(SHARED_LDFLAGS) -o a.so a.c

b.so: b.c test.h
	$(CC) $(SHARED_LDFLAGS) -o b.so b.c

clean:
	rm -f test_old test_new a.so b.so

.PHONY: clean all
.DEFAULT_GOAL := all
