TARGETS = libcweather test

.PHONY: all $(TARGETS)
all: $(TARGETS)

MAKE_OPTS = --no-print-directory V=$V

libcweather:
	@echo -e "Building: libcweather"
	@$(MAKE) $(MAKE_OPTS) -C src/

test:
	@echo -e "Building: test"
	@$(MAKE) $(MAKE_OPTS) -C test/

.PHONY: clean
clean:
	@echo -e "Cleaning: $(TARGETS)"
	@$(MAKE) $(MAKE_OPTS) -C src/ clean
	@$(MAKE) $(MAKE_OPTS) -C test/ clean
