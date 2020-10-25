export MALLOC_MMAP_THRESHOLD_=1
export MALLOC_CHECK_=1
export MALLOC_PERTURB_=1
CC=gcc
CFLAGS=-Wall -g -Wextra -O2 -fstack-protector-all 
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	LDFLAGS=-Wl
else
	LDFLAGS=-Wl,-z,relro,-z,now 
endif

all: 
	$(CC) -o bin/test_queue src/main.c lib/ice_queue.h lib/ice_queue.c $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf *.o bin/*
