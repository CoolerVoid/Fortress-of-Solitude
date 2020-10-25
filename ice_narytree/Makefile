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
	$(CC) -o bin/test_tree src/main.c lib/ice_narytree.h lib/ice_narytree.c $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf *.o bin/*
