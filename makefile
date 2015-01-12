CC=g++
CFLAGS=-Wall -std=c++11 -o2
LDFLAGS=-lsfml-system -lsfml-audio -lsfml-network -lsqlite3 -lncurses
SOURCES=main.cpp src/admin.cpp src/HolidayLights.cpp src/Gui.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXE=HolidayLights

all: $(SOURCES) $(EXE)

$(EXE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	
.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	if [ -e $(EXE) ] ; then rm $(EXE); fi
	rm -rf *.o
