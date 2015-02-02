# Makefile for Holiday-Lights-Display-System
# @author Henry J Schmale

CXX=g++

# Flags for the C compiler
CXX_FLAGS= \
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
SOURCES= \
	main.cpp \
	src/admin.cpp \
	src/HolidayLights.cpp \
	src/Gui.cpp \
	src/Synthesis.cpp \
	src/ClientDevice.cpp

OBJECTS=$(SOURCES:.cpp=.o)

EXE=HolidayLights.out

all: $(SOURCES) $(EXE)

# Primary build target
$(EXE): $(OBJECTS)
	$(CXX) $(LD_FLAGS) -o $@ $(OBJECTS)
	
# Recipe to build the files
.cpp.o:
	$(CXX) -c $(CXX_FLAGS) -o $@ $<

# Remove all the object files
clean:
	if [ -e $(EXE) ] ; then rm $(EXE); fi
	rm -rf *.o
	rm -rf src/*.o
