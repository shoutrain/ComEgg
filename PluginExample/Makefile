CC = g++ 
FLAGS = -Wall -g
LIBS = -L/usr/lib64/mysql -lmysqlclient
SOURCES = CConfig.cpp CBlog.cpp inifile.cpp Export.cpp
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))
TARGET_SO = libblog.so.1.0.0
TARGET_TEST = UnitTest

default: $(TARGET_TEST)

$(TARGET_TEST): $(TARGET_SO) UnitTest.o
	$(CC) $(FLAGS) $(LIBS) -ldl -o $@ $^

$(TARGET_SO): $(OBJECTS) 
	$(CC) $(FLAGS) -shared -Wl,-soname,libblog.so $(LIBS) -o $@ $^ -lc
	$(shell ln -s $(TARGET_SO) libblog.so.1)
	$(shell ln -s $(TARGET_SO) libblog.so)
	
$(OBJECTS): %.o: %.cpp
	$(CC) $(FLAGS) -fPIC -c $< -o $@

.PHONY: clean
clean:
	-$(RM) *.o *.so* UnitTest
