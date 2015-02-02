# Makefile for Holiday-Lights-Display-System
# @author Henry J Schmale

CC=g++
CFLAGS=-Wall -std=c++11 -Ofast

# Linker Flags
LDFLAGS=-lsfml-system \
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
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	
.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	if [ -e $(EXE) ] ; then rm $(EXE); fi
	rm -rf *.o
	rm -rf src/*.o
