LIBNAME = libcweather

SOVER   = 0
VERSION = $(SOVER).0.0

DEPDIR  := .d
$(shell mkdir -p $(DEPDIR) >/dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td

CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 \
          -g -O2 -fexceptions -fno-common -fvisibility=hidden \
          -Wp,-D_FORTIFY_SOURCE=2 --param=ssp-buffer-size=4 -fPIC
LDFLAGS = -fpic -shared -Wl,-z,now,-z,defs,-z,relro,--as-needed
LIBS	= -lcurl
POSTCOMPILE = @mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d && touch $@

sources = $(wildcard *.c ../lib/*.c)
objects = $(sources:.c=.o)

v = @
ifeq ($V,1)
        v =
endif

all: $(LIBNAME)

$(LIBNAME): $(objects)
	@echo -e "  LNK\t$@"
	$(v)$(CC) $(LDFLAGS),-soname,$(LIBNAME).so.$(SOVER) -o $(LIBNAME).so.$(VERSION) $(objects) $(LIBS)
	$(v)ln -sf $(LIBNAME).so.$(VERSION) $(LIBNAME).so.$(SOVER)
	$(v)ln -sf $(LIBNAME).so.$(VERSION) $(LIBNAME).so

%.o: %.c
%.o: %.c $(DEPDIR)/%.d
	@echo -e "  CC\t$@"
	$(v)$(CC) $(DEPFLAGS) $(CFLAGS) -c -o $@ $<
	$(POSTCOMPILE)

../lib/%.o: ../lib/%.c
../lib/%.o: ../lib/%.c $(DEPDIR)/%.d
	@echo -e "  CC\t$@"
	$(v)$(CC) $(DEPFLAGS) $(CFLAGS) -c -o $@ $<
	$(POSTCOMPILE)

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

include $(wildcard $(patsubst %,$(DEPDIR)/%.d,$(basename $(sources))))

clean:
	$(v)rm -f $(objects) $(LIBNAME).so*
	$(v)rm -f $(DEPDIR)/*
	$(v)rmdir $(DEPDIR)
