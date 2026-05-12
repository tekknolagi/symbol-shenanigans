ifeq ($(OS),Windows_NT)
    SHARED_LDFLAGS = -shared
    EXEC_LDFLAGS =
    SHARED_EXT = dll
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
        SHARED_LDFLAGS = -fPIC -shared -Wl,-undefined,dynamic_lookup
        EXEC_LDFLAGS =
    else
        SHARED_LDFLAGS = -fPIC -shared
        EXEC_LDFLAGS = -rdynamic -ldl
    endif
    SHARED_EXT = so
endif

all: test_old test_new a.$(SHARED_EXT) b.$(SHARED_EXT)

test_old: test.c
	$(CC) -o test_old test.c $(EXEC_LDFLAGS)

test_new: test.c
	$(CC) -DDEFINE_REGISTER_IT -o test_new test.c $(EXEC_LDFLAGS)

a.$(SHARED_EXT): a.c test.h
	$(CC) $(SHARED_LDFLAGS) -o a.$(SHARED_EXT) a.c

b.$(SHARED_EXT): b.c test.h
	$(CC) $(SHARED_LDFLAGS) -o b.$(SHARED_EXT) b.c

clean:
	rm -f test_old test_new test_old.exe test_new.exe a.so b.so a.dll b.dll

.PHONY: clean all
.DEFAULT_GOAL := all
