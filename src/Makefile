CPP = g++
CPPFLAGS = -Wall -g -I/home/rafael/reference/xerces-c/src/
LDFLAGS = -L/home/rafael/reference/xerces-c/src/.libs -lxerces-c
MAKE = make

COMMON_OBJS := $(patsubst %.cpp, %.o, $(wildcard ./common/*.cpp))
DATA_OBJS := $(patsubst %.cpp, %.o, $(wildcard ./data/*.cpp))
LOGIC_OBJS := $(patsubst %.cpp, %.o, $(wildcard ./logic/*.cpp))
NETWORK_OBJS := $(patsubst %.cpp, %.o, $(wildcard ./network/*.cpp))
PARSER_OBJS := $(patsubst %.cpp, %.o, $(wildcard ./parser/*.cpp))
PLUGIN_OBJS := $(patsubst %.cpp, %.o, $(wildcard ./plugin/*.cpp))
PROTOCOL_OBJS := $(patsubst %.cpp, %.o, $(wildcard ./protocol/*.cpp))
TRANSACTION_OBJS := $(patsubst %.cpp, %.o, $(wildcard ./transaction/*.cpp))

OBJS = $(COMMON_OBJS) $(DATA_OBJS) $(LOGIC_OBJS) $(NETWORK_OBJS) $(PARSER_OBJS) $(PLUGIN_OBJS) $(PROTOCOL_OBJS) $(TRANSACTION_OBJS)

all: depend ComEgg

.PHONY: depend
depend: 
	cd common && $(MAKE)
	cd data && $(MAKE)
	cd logic && $(MAKE)
	cd network && $(MAKE)
	cd parser && $(MAKE)
	cd plugin && $(MAKE)
	cd protocol && $(MAKE)
	cd transaction && $(MAKE)

ComEgg: ComEgg.cpp $(OBJS)
	$(CPP) $(CPPFLAGS) $(LDFLAGS) -o $@ ComEgg.cpp $(OBJS)

.PHONY: clean
clean:
	cd commmon && $(MAKE) clean
	cd data && $(MAKE) clean
	cd logic && $(MAKE) clean
	cd network && $(MAKE) clean
	cd parser && $(MAKE) clean
	cd plugin && $(MAKE) clean
	cd protocol && $(MAKE) clean 
	cd transaction && $(MAKE) clean 
	-$(RM) *.o ComEgg *.depend.*
