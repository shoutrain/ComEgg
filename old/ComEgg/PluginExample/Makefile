CPP = g++ 
CPPFLAGS = -Wall -g -I/usr/include/mysql
SO_LDFLAGS = -lmysqlclient
EXE_LDFLAGS = -lmysqlclient -ldl
SOURCES = CConfig.cpp CSCSBlog.cpp inifile.cpp
OBJECTS = $(SOURCES:.cpp=.o)
DEPENDS = $(SOURCES:.cpp=.depend)
SO_PRE = SCSBlogExport.o
SO_DESTINE = libSCSBlog.so.1.0.0
EXE_PRE = Main.o
EXE_DESTINE = scsblog

default: $(EXE_DESTINE)

$(DEPENDS): %.depend: %.cpp
	@set -e; $(RM) $@; \
	$(CPP) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	$(RM) $@.$$$$

-include $(DEPENDS)

$(SO_PRE): SCSBlogExport.h SCSBlogExport.cpp
	$(CPP) $(CPPFLAGS) -fPIC -c SCSBlogExport.cpp -o $(SO_PRE)

$(SO_DESTINE): $(OBJECTS) $(SO_PRE)
	$(CPP) $(CPPFLAGS) -shared -Wl,-soname,libSCSBlog.so $(SO_LDFLAGS) -o $(SO_DESTINE) $(OBJECTS) $(SO_PRE) -lc
	ln -s $(SO_DESTINE) libSCSBlog.so.1
	ln -s $(SO_DESTINE) libSCSBlog.so

$(EXE_PRE): Main.cpp
	$(CPP) $(CPPFLAGS) -c Main.cpp -o $(EXE_PRE)

$(EXE_DESTINE): $(SO_DESTINE) $(EXE_PRE)
	$(CPP) $(CPPFLAGS) $(EXE_LDFLAGS) -o $(EXE_DESTINE) $(OBJECTS) $(EXE_PRE)

.PHONY: clean
clean:
	-$(RM) $(DEPENDS) $(OBJECTS) *.depend.* $(SO_PRE)  $(SO_DESTINE) *.so *.so.* $(EXE_PRE) $(EXE_DESTINE) *.depend
