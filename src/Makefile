XERCESC_PATH = /home/rafael/reference/xerces-c/src/
CPP = g++
CPPFLAGS = -Wall -g -I$(XERCESC_PATH)
LDFLAGS = -L$(XERCESC_PATH).libs -lxerces-c
MAKE = make

COMMON_OBJS := $(patsubst %.cpp, %.o, $(wildcard ./Common/*.cpp))
DATA_OBJS := $(patsubst %.cpp, %.o, $(wildcard ./data/*.cpp))
NETWORK_OBJS := $(patsubst %.cpp, %.o, $(wildcard ./Network/*.cpp))
MODULES_OBJS := $(patsubst %.cpp, %.o, $(wildcard ./Modules/*.cpp))
LOGIC_OBJS := $(patsubst %.cpp, %.o, $(wildcard ./Logic/*.cpp))
PROTOCOLS_OBJS := $(patsubst %.cpp, %.o, $(wildcard ./Protocols/*.cpp))
TOOLS_OBJS := $(patsubst %.cpp, %.o, $(wildcard ./Tools/*.cpp))
SYSTEM_OBJS := $(patsubst %.cpp, %.o, $(wildcard ./System/*.cpp))
TRANSACTIONS_OBJS := $(patsubst %.cpp, %.o, $(wildcard ./Transactions/*.cpp))
XMLPARSER_OBJS := $(patsubst %.cpp, %.o, $(wildcard ./XMLParser/*.cpp))

OBJS = $(COMMON_OBJS) $(DATA_OBJS) $(NETWORK_OBJS) $(MODULES_OBJS) $(LOGIC_OBJS) $(PROTOCOLS_OBJS) $(TOOLS_OBJS) $(TRANSACTIONS_OBJS) $(SYSTEM_OBJS) $(XMLPARSER_OBJS)

all: depend ComEgg

.PHONY: depend
depend: 
	cd Common && $(MAKE)
	cd data && $(MAKE)
	cd Network && $(MAKE)
	cd Modules && $(MAKE)
	cd Logic && $(MAKE)
	cd Protocols && $(MAKE)
	cd Tools && $(MAKE)
	cd System && $(MAKE)
	cd Transactions && $(MAKE)
	cd XMLParser && $(MAKE)

ComEgg: Main.cpp $(OBJS)
	$(CPP) $(CPPFLAGS) $(LDFLAGS) -o $@ Main.cpp $(OBJS)

.PHONY: clean
clean:
	cd Common && $(MAKE) clean
	cd data && $(MAKE) clean
	cd Network && $(MAKE) clean
	cd Modules && $(MAKE) clean
	cd Logic && $(MAKE) clean
	cd Protocols && $(MAKE) clean 
	cd Tools && $(MAKE) clean 
	cd System && $(MAKE) clean
	cd Transactions && $(MAKE) clean
	cd XMLParser && $(MAKE) clean
	-$(RM) *.o ComEgg *.depend.*
