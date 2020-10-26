CC=gcc
CFLAGS=-W -Wall -Wextra -O2 -fstack-protector-all
DFLAGS=-D_FORTIFY_SOURCE=2
DIR=src/
DIROUT=bin/
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	LDFLAGS= 
else
	LDFLAGS=-Wl,-z,relro,-z,now  
endif

arit_eval: $(DIR)main.c 
	@echo "Compile... "
	$(CC) $(CFLAGS) $(DFLAGS) -c $(DIR)*.c 
	$(CC) -o $(DIROUT)arit_eval *.o $(LDFLAGS)
	$(shell make clean)
	@echo " Next step, execute \"bin/arit_eval\" to start...  "   
clean:
	rm -f *.o arit_eval
