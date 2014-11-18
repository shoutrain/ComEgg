CPP = g++ 
CPPFLAGS = -Wall -g -I/usr/include/mysql
SO_LDFLAGS = -lmysqlclient
EXE_LDFLAGS = -lmysqlclient -ldl
SOURCES = CConfig.cpp CBlog.cpp inifile.cpp
OBJECTS = $(SOURCES:.cpp=.o)
DEPENDS = $(SOURCES:.cpp=.depend)
SO_PRE = export.o
SO_DESTINE = libblog.so.1.0.0
EXE_PRE = unitTest.o
EXE_DESTINE = blog

default: $(EXE_DESTINE)

$(DEPENDS): %.depend: %.cpp
	@set -e; $(RM) $@; \
	$(CPP) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	$(RM) $@.$$$$

-include $(DEPENDS)

$(SO_PRE): export.h export.cpp
	$(CPP) $(CPPFLAGS) -fPIC -c export.cpp -o $(SO_PRE)

$(SO_DESTINE): $(OBJECTS) $(SO_PRE)
	$(CPP) $(CPPFLAGS) -shared -Wl,-soname,libblog.so $(SO_LDFLAGS) -o $(SO_DESTINE) $(OBJECTS) $(SO_PRE) -lc
	ln -s $(SO_DESTINE) libblog.so.1
	ln -s $(SO_DESTINE) libblog.so

$(EXE_PRE): unitTest.cpp
	$(CPP) $(CPPFLAGS) -c unitTest.cpp -o $(EXE_PRE)

$(EXE_DESTINE): $(SO_DESTINE) $(EXE_PRE)
	$(CPP) $(CPPFLAGS) $(EXE_LDFLAGS) -o $(EXE_DESTINE) $(OBJECTS) $(EXE_PRE)

.PHONY: clean
clean:
	-$(RM) $(DEPENDS) $(OBJECTS) *.depend.* $(SO_PRE)  $(SO_DESTINE) *.so *.so.* $(EXE_PRE) $(EXE_DESTINE) *.depend
