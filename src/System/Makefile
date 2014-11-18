CPP = g++
CPPFLAGS = -Wall -g
LDFLAGS = 
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
DEPENDS = $(SOURCES:.cpp=.depend)

default: $(DEPENDS) $(OBJECTS)

$(DEPENDS): %.depend: %.cpp
	@set -e; $(RM) $@; \
	$(CPP) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	$(RM) $@.$$$$

-include $(DEPENDS)

.PHONY: clean
clean:
	-$(RM) $(DEPENDS) $(OBJECTS) *.depend.*