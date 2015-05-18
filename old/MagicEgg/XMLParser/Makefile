CPP = g++
CPPFLAGS = -Wall -g -I/home/rafael/reference/ACE_wrappers/ -I/home/rafael/reference/xerces-c/src/ -I/home/rafael/reference/fltk/
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
