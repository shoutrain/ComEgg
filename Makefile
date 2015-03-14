CC = g++
CFLAGS = -Wall -g
INCLUDES =
LIBS = -lpthread -lhiredis -llog4c
SOURCE_ROOT = ./src
OBJECT_ROOT = ./obj
SOURCE_PATHS = $(shell find $(SOURCE_ROOT) -maxdepth 3 -type d)
OBJECT_PATHS = $(patsubst $(SOURCE_ROOT)%, $(OBJECT_ROOT)%, $(SOURCE_PATHS))
SOURCES = $(foreach dir, $(SOURCE_PATHS), $(wildcard $(dir)/*.cpp))
OBJECTS = $(subst $(SOURCE_ROOT), $(OBJECT_ROOT), $(patsubst %.cpp, %.o, $(SOURCES)))
TARGET = ComEgg

all: prepare $(TARGET)

.PHONY: prepare
prepare:
	$(foreach path, $(OBJECTS), $(shell mkdir -p $(dir $(path))))

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(LIBS) -o $@ $(OBJECTS)

$(OBJECTS): $(OBJECT_ROOT)%.o: $(SOURCE_ROOT)%.cpp
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	-$(RM) -fr $(OBJECT_ROOT)/* $(TARGET)
