CC	= gcc
CFLAGS	= -Wall -Wextra -g -O2 -I../include
LDFLAGS	= -L../src -Wl,-z,now,-z,defs,-z,relro,--as-needed,-rpath,../src
LIBS	= -lcweather

sources = $(wildcard *.c)
objects = $(sources:.c=.o)

v = @
ifeq ($V,1)
	v =
endif

all: test

test: $(objects)
	@echo -e "  LNK\t$@"
	$(v)$(CC) $(LDFLAGS) -o $@ $(objects) $(LIBS)

$(objects): %.o: %.c
	@echo -e "  CC\t$@"
	$(v)$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(v)rm -f $(objects) test
