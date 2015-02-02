# Makefile for Holiday-Lights-Display-System
# @author Henry J Schmale

CC=g++

# Flags for the C compiler
CC_FLAGS= \
	-Wall \
	-std=c++11 \
	-O2

# Linker Flags
LD_FLAGS= \
	-lsfml-system \
	-lsfml-audio \
	-lsfml-network \
	-lsqlite3 \
	-lncurses \
	-lcdk \
	-lsndfile \
	-lglog

# Sources to compile
SOURCES=main.cpp \
	src/admin.cpp \
	src/HolidayLights.cpp \
	src/Gui.cpp \
	src/Synthesis.cpp \
	src/ClientDevice.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXE=HolidayLights.out

all: $(SOURCES) $(EXE)

$(EXE): $(OBJECTS)
	echo $(CC_FLAGS)
	$(CC) $(LD_FLAGS) $(OBJECTS) -o $@
	
.o:
	$(CC) -c $(CC_FLAGS) -o $@ $<

clean:
	if [ -e $(EXE) ] ; then rm $(EXE); fi
	rm -rf *.o
	rm -rf src/*.o
