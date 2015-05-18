CPP = g++
CPPFLAGS = -Wall -g -I/home/rafael/reference/ACE_wrappers/ -I/home/rafael/reference/xerces-c/src/ -I/home/rafael/reference/fltk/
LDFLAGS = -L/home/rafael/reference/ACE_wrappers/lib -lACE -L/home/rafael/reference/xerces-c/src/.libs -lxerces-c -L/home/rafael/reference/fltk/lib -lfltk2
MAKE = make

COMMON_OBJS := $(patsubst %.cpp, %.o, $(wildcard ./Common/*.cpp))
DATA_OBJS := $(patsubst %.cpp, %.o, $(wildcard ./Data/*.cpp))
NETWORK_OBJS := $(patsubst %.cpp, %.o, $(wildcard ./Network/*.cpp))
LOGIC_OBJS := $(patsubst %.cpp, %.o, $(wildcard ./Logic/*.cpp))
PROTOCOLS_OBJS := $(patsubst %.cpp, %.o, $(wildcard ./Protocols/*.cpp))
INTERFACE_OBJS := $(patsubst %.cpp, %.o, $(wildcard ./UI/*.cpp))
TOOLS_OBJS := $(patsubst %.cpp, %.o, $(wildcard ./Tools/*.cpp))
SYSTEM_OBJS := $(patsubst %.cpp, %.o, $(wildcard ./System/*.cpp))
XMLPARSER_OBJS := $(patsubst %.cpp, %.o, $(wildcard ./XMLParser/*.cpp))

OBJS = $(COMMON_OBJS) $(DATA_OBJS) $(NETWORK_OBJS) $(LOGIC_OBJS) $(PROTOCOLS_OBJS) $(INTERFACE_OBJS) $(TOOLS_OBJS) $(SYSTEM_OBJS) $(XMLPARSER_OBJS)

all: depend MagicEgg

.PHONY: depend
depend: 
	cd Common && $(MAKE)
	cd Data && $(MAKE)
	cd Network && $(MAKE)
	cd Logic && $(MAKE)
	cd Protocols && $(MAKE)
	cd UI && $(MAKE)
	cd Tools && $(MAKE)
	cd System && $(MAKE)
	cd XMLParser && $(MAKE)

MagicEgg: Main.cpp $(OBJS)
	$(CPP) $(CPPFLAGS) $(LDFLAGS) -o $@ Main.cpp $(OBJS)

.PHONY: clean
clean:
	cd Common && $(MAKE) clean
	cd Data && $(MAKE) clean
	cd Network && $(MAKE) clean
	cd Logic && $(MAKE) clean
	cd Protocols && $(MAKE) clean 
	cd UI && $(MAKE) clean
	cd Tools && $(MAKE) clean 
	cd System && $(MAKE) clean	
	cd XMLParser && $(MAKE) clean
	-$(RM) $(OBJECTS) *.o MagicEgg *.depend.*
