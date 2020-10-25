export MALLOC_MMAP_THRESHOLD_=1
export MALLOC_CHECK_=1
export MALLOC_PERTURB_=1
CC=gcc
CFLAGS=-Wall -Wextra -O2 -fstack-protector-all 
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	LDFLAGS=-Wl
else
	LDFLAGS=-Wl,-z,relro,-z,now 
endif

all: 
	$(CC) -o bin/test_doubly_linked src/main.c lib/ice_doubly_linked.h lib/ice_doubly_linked.c $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf *.o bin/*
