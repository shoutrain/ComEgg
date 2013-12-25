MAKE = make

all:
	cd src && $(MAKE)
	-cp src/ComEgg bin

.PHONY: clean
clean:
	-$(RM) bin/ComEgg
	cd src && $(MAKE) clean
